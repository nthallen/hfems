/* OUI output from the following packages:
   nctable
   dc
   msghdr_default
   msghdr
   msg
   nl_error_init
*/
char *opt_string = "at:h:vo:mV";
#include "oui.h"
#include "nctable.h"
#include "DC.h"
#include <unistd.h>
#include "nortlib.h"
#include "msg.h"
  int (*nl_error)(int level, const char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr_default = "DC";
  const char *msg_hdr;

  { int optltr;

	optind = OPTIND_RESET;
	opterr = 0;
	while ((optltr = getopt(argc, argv, opt_string)) != -1) {
	  switch (optltr) {
		  case 't':
		    dc_set_srcnode(optarg);
		    break;
		  case '?':
			nl_error(3, "Unrecognized Option -%c", optopt);
		  default:
			break;
	  }
	}
  }
  nct_init_options(argc, argv);
  msg_hdr = msghdr_init( msg_hdr_default, argc, argv );
  msg_init_options(msg_hdr, argc, argv);
}

#ifdef __USAGE
%C [options] term ...
	-a Use ASCII graphics characters
	-h <msg header>
	-m write to memo [default]
	-o <error filename> Write to specified file
	-t <TMbfr node>
	-v add a level of verbosity
	-V write to stderr
	term tty on which to display the first screen
#endif
