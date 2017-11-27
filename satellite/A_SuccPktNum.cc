#include "A_SuccPktNum.h"

static class A_SuccPktNumClass : public TclClass
{
public:
	A_SuccPktNumClass():TclClass ("A_SuccPktNum") {}
	TclObject *create ( int, const char* const* )
	{
		return (new A_SuccPktNum ());
	}
}class_A_SuccPktNum_obj;

int A_SuccPktNum :: command(int argc, const char* const* argv )
{
	Tcl&tcl = Tcl :: instance();
	 if(strcmp(argv[1], "returnSucessPktNum"))
	{
		tcl.resultf("%d",sucess_pkt_num_);
	}
	return TCL_OK;
};

int A_SuccPktNum::sucess_pkt_num_ = 0;
