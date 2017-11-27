#include "connector.h"
#include "object.h"
#include "lib/bsd-list.h"

class A_RetransTimes :  public TclObject
{
public :
	static int successful_retrans_times_sum_ ;
	A_RetransTimes() {}
	int command(int, const char* const* );
};
