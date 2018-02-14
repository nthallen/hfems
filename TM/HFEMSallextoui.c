/* OUI output from the following packages:
   edfoui
   dc
   msghdr_default
   msghdr
   msg
   nl_error_init
*/
char *opt_string = "t:h:vo:mV";
#include "oui.h"
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
  msg_hdr = msghdr_init( msg_hdr_default, argc, argv );
  msg_init_options(msg_hdr, argc, argv);
}

#ifdef __USAGE
%C	[options]
	-h <msg header>
	-m write to memo [default]
	-o <error filename> Write to specified file
	-t <TMbfr node>
	-v add a level of verbosity
	-V write to stderr

CSV sonic1, 7 columns:
  sonic1       [ 0] = Time
  sonic1       [ 1] = ueddy1
  sonic1       [ 2] = veddy1
  sonic1       [ 3] = weddy1
  sonic1       [ 4] = Teddy1
  sonic1       [ 5] = sdev_stale1
  sonic1       [ 6] = sdrv_stale1

CSV sonic2, 7 columns:
  sonic2       [ 0] = Time
  sonic2       [ 1] = ueddy2
  sonic2       [ 2] = veddy2
  sonic2       [ 3] = weddy2
  sonic2       [ 4] = Teddy2
  sonic2       [ 5] = sdev_stale2
  sonic2       [ 6] = sdrv_stale2

CSV eddy1, 3 columns:
  eddy1        [ 0] = Time
  eddy1        [ 1] = vCO2e1
  eddy1        [ 2] = vH2Oe1

CSV eddy2, 3 columns:
  eddy2        [ 0] = Time
  eddy2        [ 1] = vCO2e2
  eddy2        [ 2] = vH2Oe2

CSV eddyO3, 2 columns:
  eddyO3       [ 0] = Time
  eddyO3       [ 1] = vO3ed

CSV counts, 4 columns:
  counts       [ 0] = Time
  counts       [ 1] = NOx
  counts       [ 2] = NOy
  counts       [ 3] = CtStat

CSV status, 7 columns:
  status       [ 0] = Time
  status       [ 1] = DSt0
  status       [ 2] = DSt1
  status       [ 3] = DSt4
  status       [ 4] = DSt5
  status       [ 5] = Dst6
  status       [ 6] = SolSt

CSV pressures, 9 columns:
  pressures    [ 0] = Time
  pressures    [ 1] = Pamb
  pressures    [ 2] = Pman
  pressures    [ 3] = PrCO2p
  pressures    [ 4] = PrNOx
  pressures    [ 5] = PrNOy
  pressures    [ 6] = PrCO2e1
  pressures    [ 7] = PrCO2e2
  pressures    [ 8] = PrCO

CSV flows, 17 columns:
  flows        [ 0] = Time
  flows        [ 1] = FlowT
  flows        [ 2] = FlCO2p
  flows        [ 3] = FlNOx
  flows        [ 4] = FlO3_NOx
  flows        [ 5] = fcNO_NOx
  flows        [ 6] = fcNO2_NOx
  flows        [ 7] = FlNOy
  flows        [ 8] = fcNO_NOy
  flows        [ 9] = fcEff_NOy
  flows        [10] = fcZer_NOy
  flows        [11] = FlO3_NOy
  flows        [12] = FlCO2e1
  flows        [13] = FlCO2e2
  flows        [14] = FlCO2e3
  flows        [15] = fc_CO2e
  flows        [16] = FlCO

CSV profile, 4 columns:
  profile      [ 0] = Time
  profile      [ 1] = vCO2prf
  profile      [ 2] = vO3prf
  profile      [ 3] = vCO

CSV radiation, 10 columns:
  radiation    [ 0] = Time
  radiation    [ 1] = Rnet
  radiation    [ 2] = PPFD_top
  radiation    [ 3] = PPFD_mid
  radiation    [ 4] = PPFD_gnd
  radiation    [ 5] = PPFD_ref
  radiation    [ 6] = PPFD_t
  radiation    [ 7] = PPFD_d
  radiation    [ 8] = Rnet_cal
  radiation    [ 9] = PPFD_cal

CSV RH, 11 columns:
  RH           [ 0] = Time
  RH           [ 1] = RH1
  RH           [ 2] = RH2
  RH           [ 3] = RH3
  RH           [ 4] = RH4
  RH           [ 5] = RH5
  RH           [ 6] = RH6
  RH           [ 7] = RH7
  RH           [ 8] = RH8
  RH           [ 9] = RH9
  RH           [10] = RH10

CSV tair, 12 columns:
  tair         [ 0] = Time
  tair         [ 1] = Ta1
  tair         [ 2] = Ta2
  tair         [ 3] = Ta3
  tair         [ 4] = Ta4
  tair         [ 5] = Ta5
  tair         [ 6] = Ta6
  tair         [ 7] = Ta7
  tair         [ 8] = Ta8
  tair         [ 9] = Ta9
  tair         [10] = Ta10
  tair         [11] = Tcal

CSV troom, 4 columns:
  troom        [ 0] = Time
  troom        [ 1] = Tr1
  troom        [ 2] = Tr2
  troom        [ 3] = Tr3

CSV tsoil, 12 columns:
  tsoil        [ 0] = Time
  tsoil        [ 1] = Ts1
  tsoil        [ 2] = Ts2
  tsoil        [ 3] = TS3
  tsoil        [ 4] = Ts4
  tsoil        [ 5] = Ts5
  tsoil        [ 6] = Ts6
  tsoil        [ 7] = Ts7
  tsoil        [ 8] = TS8
  tsoil        [ 9] = TS9
  tsoil        [10] = Ts10
  tsoil        [11] = Ts11

CSV tcells, 5 columns:
  tcells       [ 0] = Time
  tcells       [ 1] = T_MB
  tcells       [ 2] = TCO2e1
  tcells       [ 3] = TCO2e2
  tcells       [ 4] = TCO2p

CSV cpu, 4 columns:
  cpu          [ 1] = CPU_Pct
  cpu          [ 2] = Disk
  cpu          [ 3] = TDrift

CSV setpt, 17 columns:
  setpt        [ 0] = Time
  setpt        [ 1] = Pman_SP
  setpt        [ 2] = PrCO2p_SP
  setpt        [ 3] = FlCO2p_SP
  setpt        [ 4] = PrCO2e1_SP
  setpt        [ 5] = PrCO2e2_SP
  setpt        [ 6] = PrCO_SP
  setpt        [ 7] = fcNO_NOx_SP
  setpt        [ 8] = fcNO2_NOx_SP
  setpt        [ 9] = fc_CO2e_SP
  setpt        [10] = fcNO_NOy_SP
  setpt        [11] = fcEff_NOy_SP
  setpt        [12] = fcZer_NOy_SP
  setpt        [13] = FlNOx_SP
  setpt        [14] = FlNOy_SP
  setpt        [15] = FlCO2e3_SP
  setpt        [16] = FlCO_SP
#endif
