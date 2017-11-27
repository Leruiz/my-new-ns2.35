#include "connector.h"
#include "object.h"
#include "lib/bsd-list.h"

class A_SuccPktNum :  public TclObject
{
public :
	static int sucess_pkt_num_;
	A_SuccPktNum() {}
	int command(int, const char* const* );
};
