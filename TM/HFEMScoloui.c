/* OUI output from the following packages:
   collect
   msghdr_default
   subbus
   msghdr
   msg
   nl_error_init
*/
char *opt_string = "h:vo:mV";
#include "oui.h"
#include "subbus.h"
#include "msg.h"
#include "nortlib.h"
  int (*nl_error)(int level, const char *s, ...) = msg;

void oui_init_options(int argc, char **argv) {
  char *msg_hdr_default = "Col";
  int subbus_id;
  const char *msg_hdr;
  subbus_id = load_subbus();
  msg_hdr = msghdr_init( msg_hdr_default, argc, argv );
  msg_init_options(msg_hdr, argc, argv);
}

#ifdef __USAGE
%C	[options]
	-h <msg header>
	-m write to memo [default]
	-o <error filename> Write to specified file
	-v add a level of verbosity
	-V write to stderr
#endif
