/* OUI output from the following packages:
   civ
   cis
   msghdr_default
   subbus
   msghdr
   msg
   nl_error_init
*/
char *opt_string = "Rh:vo:mV";
#include "oui.h"
#include "tm.h"
#include <unistd.h>
#include "nortlib.h"
#include "subbus.h"
#include "msg.h"
  int (*nl_error)(int level, const char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr_default = "Srvr";
  int subbus_id;
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
  subbus_id = load_subbus();
  msg_hdr = msghdr_init( msg_hdr_default, argc, argv );
  msg_init_options(msg_hdr, argc, argv);
}

#ifdef __USAGE
%C	[options]
	-h <msg header>
	-m write to memo [default]
	-o <error filename> Write to specified file
	-R Report version string to stdout and quit
	-v add a level of verbosity
	-V write to stderr
#endif
