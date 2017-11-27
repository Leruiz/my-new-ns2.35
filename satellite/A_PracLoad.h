#include "connector.h"
#include "object.h"
#include "lib/bsd-list.h"

class A_PracLoad :  public TclObject
{
public :
	static int prctical_sent_bits_num_;
	A_PracLoad() {}
	int command(int, const char* const* );
};
