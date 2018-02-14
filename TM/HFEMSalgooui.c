/* OUI output from the following packages:
   tma
   msghdr_default
   dc
   nl_error_init
   civ
   msghdr
   msg
   cic
*/
char *opt_string = "t:Rh:vo:mVC:p";
#include "oui.h"
#include "tma.h"
#include "DC.h"
#include <unistd.h>
#include "nortlib.h"
#include "tm.h"
#include "msg.h"
  int (*nl_error)(int level, const char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr_default = "TMA";
  const char *msg_hdr;

  { int optltr;

	optind = OPTIND_RESET;
	opterr = 0;
	while ((optltr = getopt(argc, argv, opt_string)) != -1) {
	  switch (optltr) {
		  case 't':
		    dc_set_srcnode(optarg);
		    break;
		  case 'R':
		    ci_report_version();
		  case '?':
			nl_error(3, "Unrecognized Option -%c", optopt);
		  default:
			break;
	  }
	}
  }
  tma_init_options( argc, argv );
  msg_hdr = msghdr_init( msg_hdr_default, argc, argv );
  msg_init_options(msg_hdr, argc, argv);
  cic_options(argc, argv, msg_hdr);
}

#ifdef __USAGE
%C	[options]
	-C <node> send commands to server on specified node
	-h <msg header>
	-m write to memo [default]
	-o <error filename> Write to specified file
	-p Playback mode: do not send commands to server
	-R Report version string to stdout and quit
	-t <TMbfr node>
	-v add a level of verbosity
	-V write to stderr
#endif
