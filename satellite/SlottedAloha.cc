#include "SlottedAloha.h"
#include "sattrace.h"
#include "satposition.h"
#include "satgeometry.h"
#include "satnode.h"
#include "satroute.h"
#include "errmodel.h"
#include "sat-hdlc.h"
#include "AddOutputVariables.h"
#include "A_SuccPktNum.h"
#include "A_PracLoad.h"
#include "A_RetransTimes.h"

static class SlottedAlohaClass : public TclClass {
public:
	SlottedAlohaClass() : TclClass("Mac/Sat/SlottedAloha") {}
	TclObject* create(int, const char*const*) {
		return (new SlottedAloha());
	}
} sat_class_SlottedAloha;

SlottedAloha::SlottedAloha() : SatMac(), tx_state_(MAC_IDLE),
    rx_state_(MAC_IDLE), rtx_(0), end_of_contention_(0)
{
	bind_time("mean_backoff_", &mean_backoff_);
	bind("rtx_limit_", &rtx_limit_);
	bind_time("send_timeout_", &send_timeout_);

	bind_bw("aloha_bandwidth_", &aloha_bandwidth_);
		bind("pkt_bit_length_", &pkt_bit_length_);
}

void SlottedAloha::send_timer()
{
	switch (tx_state_) {

	case MAC_SEND:
		// We've timed out on send-- back off
		backoff();
		break;
	case MAC_COLL:
		// Our backoff timer has expired-- resend
		sendDown(snd_pkt_);
		break;
	default:
		printf("Error: wrong tx_state in unslotted aloha: %d\n",
		    tx_state_);
		break;
	}
}

void SlottedAloha::recv_timer()
{
	switch (rx_state_) {

	case MAC_RECV:
		// We've successfully waited out the reception
		end_of_contention(rcv_pkt_);
		break;
	default:
		printf("Error: wrong rx_state in unslotted aloha: %d\n",
		    rx_state_);
		break;
	}

}

void SlottedAloha::sendUp(Packet* p)
{
	hdr_mac* mh = HDR_MAC(p);
	int dst;

	if (rx_state_ == MAC_IDLE) {
		// First bit of packet has arrived-- wait for
		// txtime to make sure no collisions occur
		rcv_pkt_ = p;
		end_of_contention_ = NOW + mh->txtime();
		rx_state_ = MAC_RECV;
		recv_timer_.resched(mh->txtime());
	} else {
		// Collision: figure out if contention phase must be lengthened
		if ( (NOW + mh->txtime()) > end_of_contention_ ) {
			recv_timer_.resched(mh->txtime());
		}
		// If this is the first collision, we will also have a
		// rcv_pkt_ pending
		if (rcv_pkt_) {
			// Before dropping rcv_pkt_, trace the collision
			// if it was intended for us
			mh = HDR_MAC(rcv_pkt_);
			dst = this->hdr_dst((char*)mh); // mac dest. address
			if (((u_int32_t)dst == MAC_BROADCAST)||(dst == index_))
				if (coll_trace_ && trace_collisions_)
					coll_trace_->traceonly(rcv_pkt_);
			drop(rcv_pkt_);
		}
		rcv_pkt_ = 0;
		// Again, before we drop this packet, log a collision if
		// it was intended for us
		mh = HDR_MAC(p);
		dst = this->hdr_dst((char*)mh); // mac destination address
		if (((u_int32_t)dst == MAC_BROADCAST) || (dst == index_))
			if (coll_trace_ && trace_collisions_)
				coll_trace_->traceonly(p);
		drop(p);
	}
}

void SlottedAloha::sendDown(Packet* p)
{
	double txt;
	// compute transmission delay:
/*	int packetsize_ = HDR_CMN(p)->size() + LINK_HDRSIZE;
	assert (bandwidth_ != 0);
	txt = txtime(packetsize_);*/

	txt = pkt_bit_length_ / aloha_bandwidth_;

        HDR_MAC(p)->txtime() = txt;
        //printf("%f\n",txt);
	// Send the packet down
	tx_state_ = MAC_SEND;
	p->cur_retrans_times_ ++;

	//AddOutputVariables::prctical_sent_bits_num_ += HDR_CMN(p)->size();
	A_PracLoad::prctical_sent_bits_num_ += pkt_bit_length_;

	//printf ("%d\n", HDR_CMN(p)->size());
	snd_pkt_ = p->copy();  // save a copy in case it gets retransmitted
	downtarget_->recv(p, this);

	// Set a timer-- if we do not hear our own transmission within this
	// interval (and cancel the timer), the send_timer will expire and
	// we will backoff and retransmit.

	/*
	 * send_timer_.resched(send_timeout_ + txt);
	 */

	//compute the delay from now to the beginning of the next slot
	double wait_slot_delay = wait_for_slot_begin(send_timeout_ + txt);
	send_timer_.resched(wait_slot_delay);
}

// Called when contention period ends
void SlottedAloha::end_of_contention(Packet* p)
{
	rx_state_ = MAC_IDLE;
	if (!p)
		return; // No packet to free or send up.

	hdr_mac* mh = HDR_MAC(p);
	int dst = this->hdr_dst((char*)mh); // mac destination address
	int src = this->hdr_src((char*)mh); // mac source address

	if (((u_int32_t)dst != MAC_BROADCAST) && (dst != index_) &&
    	    (src != index_)) {
		drop(p); // Packet not intended for our station
		return;
	}
	if (src == index_) {
		// received our own packet: free up transmit side, drop this
		// packet, and perform callback to queue which is blocked
		if (!callback_) {
			printf("Error, queue callback_ is not valid\n");
			exit(1);
		}
		send_timer_.force_cancel();
		tx_state_ = MAC_IDLE;
		rtx_ = 0;
		drop(snd_pkt_); // Free the packet cached for retransmission
		resume(p);
	} else {
		// wait for processing delay (delay_) to send packet upwards
		//AddOutputVariables::successful_retrans_times_sum_ += p->cur_retrans_times_;

		A_RetransTimes::successful_retrans_times_sum_ += p->cur_retrans_times_;
		A_SuccPktNum::sucess_pkt_num_ ++;

		Scheduler::instance().schedule(uptarget_, p, delay_);
	}
}

void SlottedAloha::backoff(double delay)
{
	double backoff_ = Random::exponential(mean_backoff_);

	// if number of retransmissions is within limit, do exponential backoff
	// else drop the packet and resume
	if (++rtx_ <= rtx_limit_) {
		tx_state_ = MAC_COLL;
		delay += backoff_;

		//compute the delay from now to the beginning of the next slot
		delay = wait_for_slot_begin(delay);

		send_timer_.resched(delay);
	} else {
		tx_state_ = MAC_IDLE;
		rtx_ = 0;
		// trace the dropped packet
		if (drop_trace_ && trace_drops_)
			drop_trace_->traceonly(snd_pkt_);
		resume(snd_pkt_);
	}
}

double SlottedAloha::wait_for_slot_begin(double origin_delay)
{
	//compute the delay from now to the beginning of the next slot
	//set the slot duration = 0.002 s;
	int next_slot_seq = (int)((origin_delay + NOW) * 500) + 1;
	double wait_slot_delay = next_slot_seq * 0.002 - NOW;
	return wait_slot_delay;
}
