#include "A_PracLoad.h"

static class A_PracLoad : public TclClass
{
public:
	A_PracLoad():TclClass ("A_PracLoad") {}
	TclObject *create ( int, const char* const* )
	{
		return (new A_PracLoad ());
	}
}class_A_PracLoad_obj;

int A_PracLoad :: command(int argc, const char* const* argv )
{
	Tcl&tcl = Tcl :: instance();
	if(strcmp(argv[1], "returnPracticalSentBitsNum"))
	{
		tcl.resultf("%d",prctical_sent_bits_num_);
	}
	
	return TCL_OK;
};
int A_PracLoad::prctical_sent_bits_num_ = 0;
