#include "satlink.h"

class PureAloha : public SatMac {
public:
	PureAloha();
	void sendDown(Packet* p);
	void sendUp(Packet *p);
	void send_timer();
	void recv_timer();
	void end_of_contention(Packet* p);

protected:
	virtual void backoff(double delay=0);
	Packet* snd_pkt_;	// stores packet currently being sent
	Packet* rcv_pkt_;	// stores packet currently being recieved
	MacState tx_state_;	// transmit state (SEND or COLL or IDLE)
	MacState rx_state_;	// receive state (RECV or IDLE)
	int rtx_; 		// # of retransmissions so far
	int rtx_limit_;		// Set in OTcl-- retransmission limit
	double mean_backoff_;	// Set in OTcl-- mean backoff time
	double send_timeout_;	// Set in OTcl-- time out after this interval
	double end_of_contention_; // Saves time that contention will be over
	//double bit_duration_;
	double aloha_bandwidth_;
	int pkt_bit_length_;
};
