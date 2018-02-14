/* OUI output from the following packages:
   nctable
   nl_error_init
   civ
   msghdr_default
   msghdr
   msg
   kbdclt
   cic
*/
char *opt_string = "aRh:vo:mVC:p";
#include "oui.h"
#include "nctable.h"
#include "nortlib.h"
#include "tm.h"
#include <unistd.h>
#include "msg.h"
  int (*nl_error)(int level, const char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr_default = "Clt";
  const char *msg_hdr;

  { int optltr;

	optind = OPTIND_RESET;
	opterr = 0;
	while ((optltr = getopt(argc, argv, opt_string)) != -1) {
	  switch (optltr) {
		  case 'R':
		    ci_report_version();
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
  cic_options(argc, argv, msg_hdr);
}

#ifdef __USAGE
%C [options] term ...
	-a Use ASCII graphics characters
	-C <node> send commands to server on specified node
	-h <msg header>
	-m write to memo [default]
	-o <error filename> Write to specified file
	-p Playback mode: do not send commands to server
	-R Report version string to stdout and quit
	-v add a level of verbosity
	-V write to stderr
	term tty on which to display the first screen
#endif
