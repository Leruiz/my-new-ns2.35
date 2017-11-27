#include "A_RetransTimes.h"

static class A_RetransTimesClass : public TclClass
{
public:
	A_RetransTimesClass():TclClass ("A_RetransTimes") {}
	TclObject *create ( int, const char* const* )
	{
		return (new A_RetransTimes ());
	}
}class_A_RetransTimes_obj;

int A_RetransTimes :: command(int argc, const char* const* argv )
{
	Tcl&tcl = Tcl :: instance();
	if(true)
	//if(strcmp(argv[1], "returnRetransTimesSum"))
	{
		tcl.resultf("%d",successful_retrans_times_sum_);
	}
	
	return TCL_OK;
};
int A_RetransTimes::successful_retrans_times_sum_  = 0;
