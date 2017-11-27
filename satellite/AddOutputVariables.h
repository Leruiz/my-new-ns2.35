#include "connector.h"
#include "object.h"
#include "lib/bsd-list.h"

class AddOutputVariables :  public TclObject
{
public :
	static int successful_retrans_times_sum_ ;
	static int prctical_sent_bits_num_;
	static int sucess_pkt_num_;
	AddOutputVariables() {}
	int command(int, const char* const* );
};
