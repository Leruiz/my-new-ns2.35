#include "AddOutputVariables.h"

static class AddOutputVariablesClass : public TclClass
{
public:
	AddOutputVariablesClass():TclClass ("AddOutputVariables") {}
	TclObject *create ( int, const char* const* )
	{
		return (new AddOutputVariables ());
	}
}class_addoutputvariables_obj;

int AddOutputVariables :: command(int argc, const char* const* argv )
{
	Tcl&tcl = Tcl :: instance();
	if(strcmp(argv[1], "returnRetransTimesSum"))
	{
		tcl.resultf("%d",successful_retrans_times_sum_);
	}
	else if(strcmp(argv[1], "returnPracticalSentBitsNum"))
	{
		tcl.resultf("%d",prctical_sent_bits_num_);
	}
	else if(strcmp(argv[1], "returnSucessPktNum"))
	{
		tcl.resultf("%d",sucess_pkt_num_);
	}
	return TCL_OK;
};
int AddOutputVariables::successful_retrans_times_sum_  = 0;
int AddOutputVariables::prctical_sent_bits_num_ = 0;
int AddOutputVariables::sucess_pkt_num_ = 0;
