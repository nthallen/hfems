/* cmdgen output.
 * Thu Sep  8 15:39:37 2016
 */
/* cmdgen.skel skeleton file */
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include "cmdalgo.h"
#include "nortlib.h" /* Included for cis_init. prototype(), nl_error() */
#include "nl_assert.h"
                     /* <stdio.h>   Included by nortlib.h */
#include "oui.h"

static char cg_rcsid[] =
      "$Id: cmdgen.skel,v 1.42 2012/08/04 19:29:20 ntallen Exp $";

/* iomode defines determine the mode of input.
   IO_BACKSPACE indicates that backspace should backup
   to the last non-trivial input character.
   IO_SPACE auto-advances when a space or newline is entered
   IO_ALWAYS advances within words whenever the following
	 letters are unambiguous.
   IO_WORD only advances within words when the rest of the current
	 word is unambiguous (e.g. prevents advancing 'O' for On/Off)
   IO_WORDSKIP Controls advancing at the beginning of a word. If
     not specified, no advancement will take place at the
	 beginning of a word without further input. If specified,
	 entire words may be skipped if they are unambiguous.
*/
static short iomode;
#define IO_BACKSPACE 1
#define IO_SPACE 2
#define IO_ALWAYS 4
#define IO_WORD 8
#define IO_WORDSKIP 0x10

#define IOF_NO_ADV 0x1
#define IOF_UNGOTNL 0x2
#define IOF_UPDATE 0x4
#define IOF_EXECUTE 0x8
#define IOF_INTERACTIVE 0x10
static short ioflags;


  #include <string.h>
  #include <errno.h>
  #include "tm.h"
  #include "msg.h"
#ifdef SERVER
  cmdif_wr if_DG("DG", "DG/cmd");
#endif
#ifdef SERVER
  cmdif_rd if_Quit("Quit");
#endif

  /* HFEMS.cmd */
  #ifdef SERVER
    #include "address.h"
    #include "subbus.h"
  
    void write_savelog( char *s ) {
      FILE *fp;
      fp = fopen( "saverun.log", "a" );
      if ( fp == 0 ) nl_error( 2, "Unable to write to saverun.log" );
      else {
        fprintf( fp, "%s\n", s );
        fclose( fp );
      }
    }
    
    void write_restart() {
      FILE *fp;
      fp = fopen("restart.txt", "a");
      if (fp == 0) nl_error(2, "Unable to create restart.txt");
      else {
        fclose(fp);
      }
    }

  #endif
#ifdef SERVER
  cmdif_wr if_dccc("dccc", "dccc");
#endif
#ifdef SERVER
  cmdif_rd if_SoldrvA("SoldrvA");
#endif

  #include <string.h>
  #include <errno.h>
  #include "tm.h"

#ifdef SERVER
  cmdif_rd if_phrtg("phrtg");
#endif
#ifdef SERVER
  cmdif_rd if_getcon("getcon");
#endif
#include "subbus.h"

#ifdef SERVER
  void cis_interfaces(void) {
    if_DG.Setup();
    if_Quit.Setup();
    if_dccc.Setup();
    if_SoldrvA.Setup();
    if_phrtg.Setup();
    if_getcon.Setup();
  };

  void cis_interfaces_close(void) {
    if_DG.Shutdown();
    if_Quit.Shutdown();
    if_dccc.Shutdown();
    if_SoldrvA.Shutdown();
    if_phrtg.Shutdown();
    if_getcon.Shutdown();
    subbus_quit();
  }
#endif

typedef unsigned short cg_token_type;
typedef unsigned char cg_nonterm_type;

#if defined SNAFU_CURSES && ! defined SELF_SERVE
  #define SELF_SERVE
#endif

/* Compilations options:
 Interface options:
   CLIENT        Ships commands to a server
   SERVER        Receives commands from clients
   SELF_SERVE    Does it all! (default if SNAFU_CURSES)

 Low-level action options:
   CLIENT_ACTIONS Executes actions specified for client.
   SERVER_ACTIONS Executes actions specified for server.
     (default is to do both, but usually controlled by Interace option)
 
 Low-level mode options:
   CMD_BATCH_MODE generates cmd_batch()
   CMD_INTERACT_MODE generates cmd_interact()
     (INTERACT is default, but usually controlled by interface option)

	 These are set by the Interface option, although it is still 
	 possible to specify them individually if necessary.

	 I expect keyboard (CLIENT) programs to usually define just 
	 CMD_INTERACT_MODE (although history would require BATCH also) 
	 and SERVERs to define just CMD_BATCH_MODE. Note that if only 
	 CMD_BATCH_MODE is defined, NO_PROMPTS is assumed.

 I/O options:
   QNX_CONS      uses nortlib nl_cons.h stuff (default on QNX4)
   SNAFU_CURSES  specific to snafu. Implies SELF_SERVE
   PHOTON_INTERFACE uses Photon (default on QNX6)
   NCT_INTERFACE uses the nctable library for ncurses
   LL_INTERFACE  allows for external definition each
		 interface element, but defaults to a
		 "Low Level" interface.

 Prompt options:
   NO_PROMPTS      suppresses all prompting code and data
                   default when CMD_INTERACT_MODE is not
		   defined (i.e. when SERVER is defined)
   MACHINE_PROMPTS used by QNX_CONS to generate faster prompts.
                   Irrelevant if NO_PROMPTS is defined.

 I/O Mode:
   IOMODE_INIT   initial value to be assigned for iomode
*/
#if defined SELF_SERVE
  #define CMD_INTERACT_MODE
  #define SERVER_ACTIONS
  #define CLIENT_ACTIONS
#elif defined CLIENT
  #define CMD_INTERACT_MODE
  #define CLIENT_ACTIONS
  static short saw_server_action;
#elif defined SERVER
  #define CMD_BATCH_MODE
  #define SERVER_ACTIONS
#else /* default to all actions to support existing usage */
  #define SERVER_ACTIONS
  #define CLIENT_ACTIONS
#endif

#if defined CLIENT || defined SERVER
  #include "tm.h" /* for ci* library functions */
#endif

#if ! (defined CMD_INTERACT_MODE || defined CMD_BATCH_MODE)
  #define CMD_INTERACT_MODE
#endif

#ifdef CMD_INTERACT_MODE
  #if ! (defined QNX_CONS || defined SNAFU_CURSES || defined PHOTON_INTERFACE || defined LL_INTERFACE || defined NCT_INTERFACE)
    #if __QNXNTO__
      #define PHOTON_INTERFACE 1
    #else
      #define QNX_CONS
    #endif
  #endif
#endif

#if ! (defined CMD_INTERACT_MODE || defined NO_PROMPTS)
  #define NO_PROMPTS
#endif

#ifdef QNX_CONS
  #include "nl_cons.h"
#elif defined SNAFU_CURSES
  #include <ncurses/curses.h>
  #include "scurses.h"
#elif defined PHOTON_INTERFACE
  #include <Pt.h>
  #include "nlphcmd.h"
#elif defined NCT_INTERFACE
  #include <ncurses/curses.h>
  #include "nctable.h"
#endif

#define CG_IBUF_SIZE 256
static char ibuf[CG_IBUF_SIZE];

#ifndef IOMODE_INIT
  #define IOMODE_INIT (IO_SPACE|IO_BACKSPACE|IO_ALWAYS)
#endif

#define STORE_CHAR(x) do {\
  if (ibufidx==CG_IBUF_SIZE)\
	{ CMD_ERROR("Input buffer overflow"); }\
  ibuf[ibufidx++] = x;\
} while (0)
#define UNSTORE_CHAR { assert(ibufidx > 0); ibufidx--; }

#ifdef QNX_CONS
  #define GETCH() nlcon_getch()
  #define DISPLAY_CHAR(c) con_dispc(c)
  #define UNDISPLAY_CHAR con_undispc()
  #define CLEAR_DISPLAY_LINE do { con_col = con_low = 1;\
				  con_nchars = 0;\
				  ioflags |= IOF_UPDATE; } while (0)
  #define DISPLAY_PROMPT(x) con_prompt(prmt_text+x)
  #define UPDATE_OUTPUT con_update()
#endif
#ifdef SNAFU_CURSES
  #define REJECT_CHAR snafu_reject_char()
  #define SPECIAL_CHAR_FUNC(x) REJECT_CHAR
  #define CMD_ERROR(x) cmderr(x); exit(1)
  #define DISPLAY_CHAR(x) do { waddch(cmdwin.w, (x)?(x):' ');\
			       ioflags |= IOF_UPDATE; } while (0)
  #define UNDISPLAY_CHAR do { waddstr(cmdwin.w, "\b \b");\
			      ioflags |= IOF_UPDATE; } while (0)
  #define CLEAR_DISPLAY_LINE do { wclear(cmdwin.w);\
				  wmove(cmdwin.w, 0, 0);\
				  swrefresh(cmdwin.h); } while (0)
  #define DISPLAY_PROMPT(x) disp_prompt(prmt_text[x])
  #define GETCH() snfgetch()
  #define UPDATE_OUTPUT curses_update()

  static int snfgetch() {
	int c;
	
	for (;;) {
	  c = sgetch();
	  if (c == '@') {
		c = sgetch();
		if (c == '@') break;
		else snafu_scan_code(c);
	  } else break;
	}
	return(c);
  }

  static void curses_update(void) {
	if (ioflags & IOF_UPDATE) {
	  swrefresh(cmdwin.h);
	  ioflags &= ~IOF_UPDATE;
	}
  }
#endif
#ifdef PHOTON_INTERFACE
  #define GETCH() nlph_getch()
  #define DISPLAY_CHAR(c) nlph_dispc(c?c:' ')
  #define UNDISPLAY_CHAR nlph_undispc()
  #define CLEAR_DISPLAY_LINE nlph_clearline()
  #define DISPLAY_PROMPT(x) nlph_prompt(prmt_text[x])
  #define UPDATE_OUTPUT nlph_update()
#endif
#ifdef NCT_INTERFACE
  #define GETCH() nct_getch()
  #define DISPLAY_CHAR(c) nct_dispc(c?c:' ')
  #define UNDISPLAY_CHAR nct_undispc()
  #define CLEAR_DISPLAY_LINE move(0,0); clrtoeol(); nct_col = 0
  #define DISPLAY_INPUT_PROMPT mvaddch(0,0,'>'); nct_col = 1;
  #define DISPLAY_PROMPT(x) nct_prompt(prmt_text[x])
  #define UPDATE_OUTPUT refresh()
#endif

/*----------------------------------------------------------------
  These are the routines which define the operating system interface.
  These are default routines which should be replaced by better ones.
----------------------------------------------------------------*/
/* REJECT_CHAR only referenced in CMD_INTERACT_MODE */
#ifndef REJECT_CHAR
  #define REJECT_CHAR do { putc('\a', stderr); fflush(stderr); } while (0)
#endif

/* SPECIAL_CHAR_FUNC(x) always called for non-printable characters */
#ifndef SPECIAL_CHAR_FUNC
  #ifdef CMD_INTERACT_MODE
    #define SPECIAL_CHAR_FUNC(x) REJECT_CHAR
  #else
    #define SPECIAL_CHAR_FUNC(x)
  #endif
#endif

/* CMD_ERROR is for fatal internal errors
    it can safely include multiple statements since its use is
	quite limited.
*/
#ifndef CMD_ERROR
  #define CMD_ERROR(x) nl_error(4,x)
#endif

/* DISPLAY_CHAR always referenced */
#ifndef DISPLAY_CHAR
  #ifdef CMD_INTERACT_MODE
    #define DISPLAY_CHAR(c) putchar((c)?(c):' ')
  #else
    #define DISPLAY_CHAR(c)
  #endif
#endif

/* UNDISPLAY_CHAR is referenced by RUBOUT which is always referenced,
   although it needn't really be unless CMD_INTERACT_MODE. */
#ifndef UNDISPLAY_CHAR
  #ifdef CMD_INTERACT_MODE
    #define UNDISPLAY_CHAR fputs("\b \b", stdout)
  #else
    #define UNDISPLAY_CHAR
  #endif
#endif

/* CLEAR_DISPLAY_LINE Always used regardless of mode */
#ifndef CLEAR_DISPLAY_LINE
  #ifdef CMD_INTERACT_MODE
    #define CLEAR_DISPLAY_LINE putchar('\n')
    #ifndef DISPLAY_INPUT_PROMPT
      #define DISPLAY_INPUT_PROMPT fputs("& ", stdout);
    #endif
  #else
    #define CLEAR_DISPLAY_LINE
  #endif
#endif

/* DISPLAY_EOL Referenced when newline is accepted */
#ifndef DISPLAY_EOL
  #ifdef LL_INTERFACE
    #define DISPLAY_EOL putchar('\n');
  #else
    #define DISPLAY_EOL
  #endif
#endif

/* DISPLAY_INPUT_PROMPT Always referenced regardless of mode */
#ifndef DISPLAY_INPUT_PROMPT
  #define DISPLAY_INPUT_PROMPT
#endif

/* DISPLAY_PROMPT displays a prompt. Not referenced if NO_PROMPTS */
#ifndef DISPLAY_PROMPT
  #define DISPLAY_PROMPT(x) { int i; printf("\n%s", prmt_text[x]);\
	  CLEAR_DISPLAY_LINE; DISPLAY_INPUT_PROMPT \
	  for (i = 0; i < ibufidx; i++) DISPLAY_CHAR(ibuf[i]); }
#endif

/* GETCH is low-level get character routine for interactive input.
   It is not used if CMD_INTERACT_MODE is not defined. */
#if ! defined(GETCH) && defined(CMD_INTERACT_MODE)
  #include <conio.h>
  #define GETCH() getch()
#endif

/* UPDATE_OUTPUT always used regardless of mode. This is used for
   indicating when output really needs to be forced to the screen.
 */
#ifndef UPDATE_OUTPUT
  #define UPDATE_OUTPUT fflush(stdout)
#endif

/*----------------------------------------------------------------*/
#define RUBOUT { UNSTORE_CHAR; UNDISPLAY_CHAR; }
#define ACCEPT_CHAR(c) { STORE_CHAR(c); DISPLAY_CHAR(c); }

#define T_FLAG 0x80
#define T_ROOT 1
#define T_CHAR(i) (trie[i].code&0x7F)
#define T_MATCH(i,c) (tolower(c)==tolower(T_CHAR(i)))
typedef struct {
  unsigned char code;
  cg_token_type next;
  cg_token_type prev;
} trie_type;

#ifndef NO_PROMPTS
typedef struct {
  int more;
  unsigned short txt_idx;
} prompt_type;
#endif

#ifdef QNX_CONS
  #define MACHINE_PROMPTS
  #define PROMPT_ATTR 0x70
  #define CMD_ATTR 7
#endif

#ifdef MACHINE_PROMPTS
  #define PRMTOFST(x) ((x)*80*2)
#else
  #define PRMTOFST(x) x
#endif

typedef struct {
  cg_nonterm_type nt;
  cg_token_type shift;
} shift_type;

#define STFL_REDUCE 1
#define STFL_VARIABLE 2
#define STFL_WORD 4
typedef struct {
  unsigned char flag;
  unsigned short offset; /* offset in rules[], vardef[] or trie[] */
  short prompt; /* offset in prompts[] or -1 */
  unsigned short nterm_offset; /* offset in non_terminals[] */
} state_type;
/* If flag == STFL_REDUCE
	  offset is the rule number
	  prompt is unused (-1)
	  nterm_offset is offset in non_terminals[]
   If flag == STFL_VARIABLE
	  offset is variable type
	  prompt is offset in prompts[]
	  nterm_offset is offset in non_terminals[]
   If flag == STFL_WORD
	  offset is offset in trie[]
	  prompt is offset in prompts[]
	  nterm_offset is offset in non_terminals[]
   Variables should be treated as some sort of non-terminal
*/

/* KG_ defines are values returned by command_getch() (and hence input())
   for the specified keys
*/
#define KG_RUBOUT 8
#define KG_ESCAPE 27
#define KG_DEL 127
#define KG_TAB 9

static void nterm_shift(cg_nonterm_type nt, unsigned short val, short prev);

/* Unshifting and Cancellation definitions:
   CANCEL_LINE may be used in actions. (The do/while allows use
   of the form: if (x) CANCEL_LINE; else ...) CANCEL_LINE
   includes a return(0) which is the right thing to do in
   rule_action or in read_variable() or read_words(), but
   care should be taken if this construct is used elsewhere.
*/
static unsigned short unshift_value;
static short full_reduce;
static int unshift(void);
static int ibufidx;
#define CANCEL_LINE do {\
  while (unshift());\
  full_reduce=1;\
  unshift_value = ibufidx = 0;\
  return(0);\
} while (0)

#ifdef CLIENT
  extern int cgc_forwarding;
  int cgc_exit_code = 0;
#endif

char ci_version[] = "$CGID: HFEMScmd.cc: Thu Sep  8 15:39:37 2016 $";
#define VTP_SHRT vu01
#define VTP_DBL vu02
#define VTP_STR vu00
#define VAR_d 0
#define VAR_lf 1
#define VAR_w 2
#define VAR_s 3
typedef union {
   int  vu05;
  int vu04;
  unsigned short vu03;
  double vu02;
  short vu01;
  char * vu00;
} vstack_type;

#define VSTACK_SIZE 20
#define NEED_VALUES
vstack_type vstack[VSTACK_SIZE];
short vsp;
#define V(d,x) vstack[tstack[x-(d)].valpos]


/* prev member is non-negative if we left the previous state via
   a non-terminal. If so, it gives the tstack position of the
   previous element on the stack and value is set to the rule
   number by which the non-terminal was derived.
   If prev is negative, we left the
   previous state via a terminal and the previous state is
   the previous position on the stack (offset -1). Information
   about what kind of terminal it was is available in the
   state description of this previous state. If it is a variable,
   value is the number of characters. If it is a word,
   value is the offset of the final position in the grand trie
   as measured from the starting offset found in the state.
   As such, a value of 0 is an appropriate starting point for
   either type of terminal.
   
   Note that the value in one state position pertains to the
   previous state. As such it indicates "how we got to this
   state" not "how we left this state". This is necessary
   due to the fact that one state may be previous to several
   other states. For example, you may leave state 1 via a
   word, then when the word reduces to a non-terminal, you
   may leave state 1 via that non-terminal also while the
   word is still saved on the stack for backtracking. The
   non-terminal may in fact reduce to another non-terminal,
   and so on.
*/
typedef struct {
  cg_token_type state;
  unsigned char reversible;
  short prev;
  #ifdef CLIENT
    short saw_srvr;
  #endif
  #ifdef NEED_VALUES
    unsigned char valpos;
  #endif
  unsigned short value; /* n_chars for variables, trie offset for words */
} tstack_type;
#define TSTACK_SIZE 40
tstack_type tstack[TSTACK_SIZE];
short tsp;
#define P(d,x) (tstack[x-(d)+1].prev-1)
#define PP(d,x) (x-(d)+1)
trie_type trie[] = {
  { 0x01          ,   1,   0 },
  { 0x0A          ,  10,   1 },
  { 0x43 /* 'C' */,  10,   2 },
  { 0x45 /* 'E' */,  10,   3 },
  { 0x67 /* 'g' */,  10,   4 },
  { 0x4C /* 'L' */,  10,   5 },
  { 0x50 /* 'P' */,  10,   6 },
  { 0x51 /* 'Q' */,  10,   7 },
  { 0x52 /* 'R' */,  10,   8 },
  { 0x53 /* 'S' */,  10,   9 },
  { 0xD4 /* 'T' */,  12,  10 },
  { 0x80          ,   3,  10 },
  { 0xCD /* 'M' */,  11,  10 },
  { 0xF8 /* 'x' */,  11,  10 },
  { 0xE5 /* 'e' */,  11,  10 },
  { 0xEF /* 'o' */,  11,  10 },
  { 0xE8 /* 'h' */,  11,  10 },
  { 0xF5 /* 'u' */,  11,  10 },
  { 0xE5 /* 'e' */,  11,  10 },
  { 0x61 /* 'a' */,  11,  10 },
  { 0x65 /* 'e' */,  11,  11 },
  { 0xEF /* 'o' */,  11,  12 },
  { 0xE5 /* 'e' */,  11,  12 },
  { 0xC4 /* 'D' */,  11,  11 },
  { 0xE9 /* 'i' */,  11,  11 },
  { 0xF4 /* 't' */,  11,  11 },
  { 0xE7 /* 'g' */,  11,  11 },
  { 0xD2 /* 'R' */,  11,  11 },
  { 0xE9 /* 'i' */,  11,  11 },
  { 0xF1 /* 'q' */,  11,  11 },
  { 0xF6 /* 'v' */,  11,  11 },
  { 0xF4 /* 't' */,  11,  11 },
  { 0xEC /* 'l' */,  11,  11 },
  { 0xEC /* 'l' */,  12,  11 },
  { 0xC5 /* 'E' */,  12,  11 },
  { 0xF4 /* 't' */,  12,  11 },
  { 0xE3 /* 'c' */,  12,  11 },
  { 0x80          ,   7,  11 },
  { 0xD4 /* 'T' */,  11,  11 },
  { 0xF4 /* 't' */,  11,  11 },
  { 0xF5 /* 'u' */,  11,  11 },
  { 0xE5 /* 'e' */,  11,  11 },
  { 0x80          ,  12,  11 },
  { 0x64 /* 'd' */,  10,  11 },
  { 0xE5 /* 'e' */,  10,  12 },
  { 0xE5 /* 'e' */,  10,  12 },
  { 0xCE /* 'N' */,  10,  12 },
  { 0x80          ,   5,  12 },
  { 0xEF /* 'o' */,   9,  12 },
  { 0xC7 /* 'G' */,   9,  11 },
  { 0x80          ,   9,  11 },
  { 0xE5 /* 'e' */,   8,  11 },
  { 0xEC /* 'l' */,   8,  11 },
  { 0xF2 /* 'r' */,   8,  10 },
  { 0xEE /* 'n' */,   8,  10 },
  { 0xED /* 'm' */,   8,  10 },
  { 0xC2 /* 'B' */,   8,  10 },
  { 0xEE /* 'n' */,   8,   9 },
  { 0x80          ,   8,   9 },
  { 0xF3 /* 's' */,   7,   8 },
  { 0xEF /* 'o' */,   7,   8 },
  { 0xF6 /* 'v' */,   7,   8 },
  { 0xEF /* 'o' */,   7,   8 },
  { 0xE5 /* 'e' */,   7,   8 },
  { 0xCC /* 'L' */,   7,   8 },
  { 0x80          ,   6,   8 },
  { 0xF4 /* 't' */,   6,   7 },
  { 0xE7 /* 'g' */,   6,   7 },
  { 0x80          ,  13,   7 },
  { 0xE9 /* 'i' */,   5,   7 },
  { 0xF4 /* 't' */,   5,   7 },
  { 0x80          ,   4,   7 },
  { 0x80          ,  10,   6 },
  { 0x80          ,  11,   6 },
  { 0xE4 /* 'd' */,   2,   5 },
  { 0xF2 /* 'r' */,   2,   5 },
  { 0x80          ,  14,   2 },
  { 0xF9 /* 'y' */,   1,   2 },
  { 0x80          ,  15,   1 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x66 /* 'f' */,   2,   1 },
  { 0xEE /* 'n' */,   2,   2 },
  { 0xE6 /* 'f' */,   2,   2 },
  { 0x80          ,  20,   2 },
  { 0x80          ,  19,   2 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          ,  22,   1 },
  { 0x01          ,   1,   0 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xE4 /* 'd' */,   1,   1 },
  { 0x80          ,  23,   1 },
  { 0x01          ,   1,   0 },
  { 0x44 /* 'D' */,   2,   1 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0xE1 /* 'a' */,   2,   2 },
  { 0xE9 /* 'i' */,   2,   2 },
  { 0xF4 /* 't' */,   2,   2 },
  { 0xEC /* 'l' */,   2,   2 },
  { 0xF5 /* 'u' */,   2,   2 },
  { 0xE5 /* 'e' */,   2,   2 },
  { 0xED /* 'm' */,   2,   2 },
  { 0x80          ,  26,   2 },
  { 0x80          ,  25,   2 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          ,  28,   1 },
  { 0x01          ,   1,   0 },
  { 0xD2 /* 'R' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xE1 /* 'a' */,   1,   1 },
  { 0xF2 /* 'r' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          ,  29,   1 },
  { 0x01          ,   1,   0 },
  { 0x66 /* 'f' */,   2,   1 },
  { 0xD0 /* 'P' */,   3,   2 },
  { 0x63 /* 'c' */,   4,   2 },
  { 0xEC /* 'l' */,   7,   3 },
  { 0x6D /* 'm' */,   8,   3 },
  { 0xF2 /* 'r' */,   8,   4 },
  { 0x45 /* 'E' */,   8,   4 },
  { 0x4E /* 'N' */,   8,   5 },
  { 0x5A /* 'Z' */,   8,   6 },
  { 0xDF /* '_' */,   8,   7 },
  { 0x43 /* 'C' */,   8,   7 },
  { 0xCE /* 'N' */,   8,   8 },
  { 0xE1 /* 'a' */,   8,   8 },
  { 0xC3 /* 'C' */,   8,   8 },
  { 0xE6 /* 'f' */,   8,   8 },
  { 0xCF /* 'O' */,   8,   8 },
  { 0xE5 /* 'e' */,   9,   8 },
  { 0xC3 /* 'C' */,   9,   8 },
  { 0xCF /* 'O' */,   9,   8 },
  { 0xCF /* 'O' */,  10,   8 },
  { 0xEE /* 'n' */,  11,   8 },
  { 0xCF /* 'O' */,  11,   8 },
  { 0xE6 /* 'f' */,  12,   8 },
  { 0x32 /* '2' */,  12,   8 },
  { 0xDF /* '_' */,  12,   9 },
  { 0xF2 /* 'r' */,  12,   9 },
  { 0xCF /* 'O' */,  12,   9 },
  { 0x00          ,  37,   9 },
  { 0xB2 /* '2' */,  11,  10 },
  { 0x78 /* 'x' */,  12,  10 },
  { 0xF9 /* 'y' */,  12,  11 },
  { 0x80          ,  42,  11 },
  { 0x00          ,  43,  11 },
  { 0xB2 /* '2' */,  10,  12 },
  { 0xDF /* '_' */,  11,  12 },
  { 0xDF /* '_' */,  11,  12 },
  { 0xCE /* 'N' */,  11,  12 },
  { 0xDF /* '_' */,  11,  12 },
  { 0xB2 /* '2' */,  11,  12 },
  { 0x65 /* 'e' */,  11,  11 },
  { 0xF0 /* 'p' */,  11,  12 },
  { 0x80          ,  40,  12 },
  { 0x80          ,  41,  12 },
  { 0x65 /* 'e' */,   9,  10 },
  { 0xF0 /* 'p' */,  10,  11 },
  { 0xCE /* 'N' */,  10,  11 },
  { 0xCE /* 'N' */,  10,  11 },
  { 0xCF /* 'O' */,  10,  11 },
  { 0xCE /* 'N' */,  11,  11 },
  { 0xE5 /* 'e' */,  11,  11 },
  { 0xB3 /* '3' */,  11,  11 },
  { 0x80          ,  39,  11 },
  { 0x31 /* '1' */,  10,   9 },
  { 0xB2 /* '2' */,  10,  10 },
  { 0x80          ,  46,  10 },
  { 0xCF /* 'O' */,   9,  10 },
  { 0xCF /* 'O' */,   9,  10 },
  { 0x78 /* 'x' */,   9,  10 },
  { 0xF9 /* 'y' */,   9,  11 },
  { 0xCF /* 'O' */,   9,  11 },
  { 0x80          ,  36,  11 },
  { 0x80          ,  38,  11 },
  { 0x80          ,  44,  10 },
  { 0x80          ,  45,  10 },
  { 0xF9 /* 'y' */,   5,   9 },
  { 0xF8 /* 'x' */,   5,   9 },
  { 0x80          ,  33,   9 },
  { 0x80          ,  34,   9 },
  { 0xF9 /* 'y' */,   3,   9 },
  { 0x80          ,  31,   5 },
  { 0x80          ,  32,   5 },
  { 0x80          ,  35,   3 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xEC /* 'l' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xE3 /* 'c' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          ,  48,   1 },
  { 0x01          ,   1,   0 },
  { 0x43 /* 'C' */,   8,   1 },
  { 0x65 /* 'e' */,   8,   2 },
  { 0x48 /* 'H' */,   9,   3 },
  { 0x4C /* 'L' */,   9,   4 },
  { 0x4E /* 'N' */,   9,   5 },
  { 0x70 /* 'p' */,  10,   6 },
  { 0x53 /* 'S' */,  10,   7 },
  { 0xFA /* 'z' */,  12,   8 },
  { 0xCF /* 'O' */,  12,   8 },
  { 0x43 /* 'C' */,  13,   8 },
  { 0xE6 /* 'f' */,  13,   9 },
  { 0xF5 /* 'u' */,  13,   9 },
  { 0xF6 /* 'v' */,  13,   9 },
  { 0x4F /* 'O' */,  13,   9 },
  { 0xD0 /* 'P' */,  15,  10 },
  { 0xC3 /* 'C' */,  15,  10 },
  { 0x68 /* 'h' */,  15,  10 },
  { 0x6F /* 'o' */,  16,  11 },
  { 0xF0 /* 'p' */,  16,  12 },
  { 0xCE /* 'N' */,  16,  12 },
  { 0x32 /* '2' */,  16,  12 },
  { 0xDF /* '_' */,  16,  13 },
  { 0xCF /* 'O' */,  18,  13 },
  { 0xE6 /* 'f' */,  18,  13 },
  { 0xE2 /* 'b' */,  18,  13 },
  { 0xEC /* 'l' */,  18,  13 },
  { 0x32 /* '2' */,  25,  13 },
  { 0x5F /* '_' */,  25,  14 },
  { 0xF9 /* 'y' */,  25,  15 },
  { 0xCE /* 'N' */,  25,  15 },
  { 0xCF /* 'O' */,  25,  15 },
  { 0x6B /* 'k' */,  25,  15 },
  { 0xF5 /* 'u' */,  25,  16 },
  { 0xEC /* 'l' */,  25,  16 },
  { 0xC3 /* 'C' */,  25,  16 },
  { 0xCF /* 'O' */,  25,  16 },
  { 0xE1 /* 'a' */,  26,  16 },
  { 0x63 /* 'c' */,  26,  16 },
  { 0x73 /* 's' */,  26,  17 },
  { 0xFA /* 'z' */,  26,  18 },
  { 0xB2 /* '2' */,  26,  18 },
  { 0xDF /* '_' */,  26,  18 },
  { 0xDF /* '_' */,  26,  18 },
  { 0x31 /* '1' */,  26,  18 },
  { 0x32 /* '2' */,  26,  19 },
  { 0x33 /* '3' */,  26,  20 },
  { 0x34 /* '4' */,  26,  21 },
  { 0x35 /* '5' */,  26,  22 },
  { 0x36 /* '6' */,  26,  23 },
  { 0x37 /* '7' */,  26,  24 },
  { 0xB8 /* '8' */,  26,  25 },
  { 0xDF /* '_' */,  26,  25 },
  { 0xCE /* 'N' */,  27,  25 },
  { 0xDF /* '_' */,  27,  25 },
  { 0xDF /* '_' */,  27,  25 },
  { 0xB2 /* '2' */,  28,  25 },
  { 0xDF /* '_' */,  28,  25 },
  { 0xF4 /* 't' */,  28,  25 },
  { 0xDF /* '_' */,  28,  25 },
  { 0xED /* 'm' */,  28,  25 },
  { 0x78 /* 'x' */,  28,  25 },
  { 0xF9 /* 'y' */,  28,  26 },
  { 0xE4 /* 'd' */,  28,  26 },
  { 0xE1 /* 'a' */,  28,  26 },
  { 0xED /* 'm' */,  28,  26 },
  { 0xE5 /* 'e' */,  28,  26 },
  { 0xE3 /* 'c' */,  28,  26 },
  { 0xC8 /* 'H' */,  28,  26 },
  { 0xF3 /* 's' */,  28,  26 },
  { 0x80          ,  59,  26 },
  { 0x80          ,  60,  26 },
  { 0x80          ,  61,  26 },
  { 0x80          ,  62,  26 },
  { 0x80          ,  63,  26 },
  { 0x80          ,  64,  26 },
  { 0x80          ,  65,  26 },
  { 0x80          ,  66,  26 },
  { 0x61 /* 'a' */,  20,  26 },
  { 0xEF /* 'o' */,  20,  27 },
  { 0xCF /* 'O' */,  20,  27 },
  { 0xE5 /* 'e' */,  21,  27 },
  { 0x61 /* 'a' */,  21,  27 },
  { 0xEF /* 'o' */,  21,  28 },
  { 0xDF /* '_' */,  21,  28 },
  { 0xF3 /* 's' */,  22,  28 },
  { 0xF4 /* 't' */,  22,  28 },
  { 0xB4 /* '4' */,  22,  28 },
  { 0xE4 /* 'd' */,  29,  28 },
  { 0xDF /* '_' */,  29,  28 },
  { 0xDF /* '_' */,  30,  28 },
  { 0xE4 /* 'd' */,  31,  28 },
  { 0xEC /* 'l' */,  32,  28 },
  { 0xF0 /* 'p' */,  33,  28 },
  { 0xF2 /* 'r' */,  33,  28 },
  { 0xE1 /* 'a' */,  33,  28 },
  { 0xE7 /* 'g' */,  33,  28 },
  { 0xF0 /* 'p' */,  33,  28 },
  { 0xE4 /* 'd' */,  34,  20 },
  { 0xEE /* 'n' */,  34,  20 },
  { 0x78 /* 'x' */,  34,  20 },
  { 0xF9 /* 'y' */,  34,  21 },
  { 0xE6 /* 'f' */,  34,  21 },
  { 0xE4 /* 'd' */,  34,  21 },
  { 0xEE /* 'n' */,  34,  21 },
  { 0x63 /* 'c' */,  34,  21 },
  { 0xF3 /* 's' */,  34,  22 },
  { 0xF0 /* 'p' */,  34,  22 },
  { 0xE5 /* 'e' */,  35,  22 },
  { 0x31 /* '1' */,  35,  22 },
  { 0x32 /* '2' */,  35,  23 },
  { 0x33 /* '3' */,  35,  24 },
  { 0x34 /* '4' */,  35,  25 },
  { 0x35 /* '5' */,  35,  26 },
  { 0x36 /* '6' */,  35,  27 },
  { 0x37 /* '7' */,  35,  28 },
  { 0xB8 /* '8' */,  35,  29 },
  { 0xDF /* '_' */,  35,  29 },
  { 0x61 /* 'a' */,  37,  29 },
  { 0xC8 /* 'H' */,  37,  30 },
  { 0x61 /* 'a' */,  37,  30 },
  { 0xC8 /* 'H' */,  37,  31 },
  { 0x31 /* '1' */,  37,  31 },
  { 0xB2 /* '2' */,  37,  32 },
  { 0x31 /* '1' */,  37,  32 },
  { 0xB2 /* '2' */,  37,  33 },
  { 0xEC /* 'l' */,  37,  33 },
  { 0x80          ,  54,  33 },
  { 0xEC /* 'l' */,  36,  33 },
  { 0x80          ,  56,  33 },
  { 0x31 /* '1' */,  35,  33 },
  { 0xB2 /* '2' */,  35,  34 },
  { 0xE4 /* 'd' */,  35,  34 },
  { 0x80          ,  68,  34 },
  { 0xDF /* '_' */,  34,  34 },
  { 0xDF /* '_' */,  35,  34 },
  { 0xE6 /* 'f' */,  36,  34 },
  { 0xE4 /* 'd' */,  36,  34 },
  { 0x80          ,  75,  34 },
  { 0xE1 /* 'a' */,  35,  34 },
  { 0xED /* 'm' */,  35,  34 },
  { 0x31 /* '1' */,  35,  34 },
  { 0xB2 /* '2' */,  35,  35 },
  { 0xF2 /* 'r' */,  35,  35 },
  { 0x80          ,  85,  35 },
  { 0x80          ,  86,  35 },
  { 0x80          ,  87,  35 },
  { 0x80          ,  88,  35 },
  { 0x80          ,  89,  35 },
  { 0x80          ,  90,  35 },
  { 0x80          ,  91,  35 },
  { 0x80          ,  92,  35 },
  { 0x31 /* '1' */,  27,  35 },
  { 0x32 /* '2' */,  29,  36 },
  { 0xB3 /* '3' */,  38,  37 },
  { 0xE4 /* 'd' */,  40,  37 },
  { 0xE7 /* 'g' */,  40,  37 },
  { 0xE4 /* 'd' */,  40,  37 },
  { 0xE7 /* 'g' */,  40,  37 },
  { 0x80          ,  49,  37 },
  { 0x80          ,  50,  37 },
  { 0x80          ,  51,  37 },
  { 0x80          ,  52,  37 },
  { 0x80          ,  53,  37 },
  { 0xDF /* '_' */,  35,  36 },
  { 0x80          ,  57,  35 },
  { 0x80          ,  58,  35 },
  { 0x80          ,  67,  35 },
  { 0x61 /* 'a' */,  32,  34 },
  { 0xEF /* 'o' */,  32,  35 },
  { 0x61 /* 'a' */,  32,  35 },
  { 0xEF /* 'o' */,  32,  36 },
  { 0xDF /* '_' */,  32,  36 },
  { 0x80          ,  74,  36 },
  { 0xEC /* 'l' */,  31,  35 },
  { 0xF0 /* 'p' */,  35,  35 },
  { 0x80          ,  82,  35 },
  { 0x80          ,  83,  35 },
  { 0x80          ,  84,  35 },
  { 0x37 /* '7' */,  32,  27 },
  { 0x38 /* '8' */,  32,  28 },
  { 0xB9 /* '9' */,  32,  29 },
  { 0x30 /* '0' */,  32,  29 },
  { 0x31 /* '1' */,  32,  30 },
  { 0x32 /* '2' */,  32,  31 },
  { 0x33 /* '3' */,  32,  32 },
  { 0x34 /* '4' */,  32,  33 },
  { 0x35 /* '5' */,  32,  34 },
  { 0x36 /* '6' */,  32,  35 },
  { 0x37 /* '7' */,  32,  36 },
  { 0x38 /* '8' */,  32,  37 },
  { 0xB9 /* '9' */,  32,  38 },
  { 0x30 /* '0' */,  32,  38 },
  { 0x31 /* '1' */,  32,  39 },
  { 0xB2 /* '2' */,  32,  40 },
  { 0xE4 /* 'd' */,  32,  40 },
  { 0x80          , 110,  40 },
  { 0xE4 /* 'd' */,  31,  40 },
  { 0x80          , 112,  40 },
  { 0xEF /* 'o' */,  30,  35 },
  { 0xE4 /* 'd' */,  30,  32 },
  { 0xEE /* 'n' */,  30,  32 },
  { 0xE4 /* 'd' */,  30,  32 },
  { 0xEE /* 'n' */,  30,  32 },
  { 0xE1 /* 'a' */,  30,  32 },
  { 0x31 /* '1' */,  30,  31 },
  { 0x32 /* '2' */,  30,  32 },
  { 0x33 /* '3' */,  30,  33 },
  { 0x61 /* 'a' */,  30,  34 },
  { 0xD2 /* 'R' */,  30,  35 },
  { 0xEC /* 'l' */,  30,  35 },
  { 0x80          ,  93,  32 },
  { 0x80          ,  94,  32 },
  { 0x80          ,  95,  32 },
  { 0x80          ,  96,  32 },
  { 0x80          ,  97,  32 },
  { 0x80          ,  98,  32 },
  { 0x80          ,  99,  32 },
  { 0x80          , 100,  32 },
  { 0x80          , 101,  32 },
  { 0x80          , 102,  32 },
  { 0x80          , 103,  32 },
  { 0x80          , 104,  32 },
  { 0x80          , 105,  32 },
  { 0x80          , 106,  32 },
  { 0x80          , 107,  32 },
  { 0x80          , 108,  32 },
  { 0x80          , 109,  32 },
  { 0x80          , 111,  31 },
  { 0xEE /* 'n' */,  12,  30 },
  { 0xE4 /* 'd' */,  12,  30 },
  { 0x80          ,  70,  30 },
  { 0xE4 /* 'd' */,  11,  30 },
  { 0x80          ,  72,  30 },
  { 0xE4 /* 'd' */,  10,  30 },
  { 0x80          ,  76,  30 },
  { 0x80          ,  77,  30 },
  { 0x80          ,  78,  30 },
  { 0x80          ,  79,  30 },
  { 0x80          ,  80,  30 },
  { 0x80          ,  81,  30 },
  { 0x80          ,  55,  12 },
  { 0x80          ,  69,  12 },
  { 0x80          ,  71,  11 },
  { 0xE4 /* 'd' */,   1,  10 },
  { 0x80          ,  73,   1 },
  { 0x01          ,   1,   0 },
  { 0xD3 /* 'S' */,   1,   1 },
  { 0x69 /* 'i' */,   2,   1 },
  { 0xF4 /* 't' */,   2,   2 },
  { 0xEE /* 'n' */,   2,   2 },
  { 0xE1 /* 'a' */,   2,   2 },
  { 0xE7 /* 'g' */,   2,   2 },
  { 0xF2 /* 'r' */,   2,   2 },
  { 0xEC /* 'l' */,   2,   2 },
  { 0xF4 /* 't' */,   2,   2 },
  { 0xE5 /* 'e' */,   2,   2 },
  { 0x80          , 114,   2 },
  { 0x80          , 113,   2 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 116,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0x80          , 117,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 118,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 121,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 122,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 123,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 124,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 125,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 126,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 127,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 128,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 129,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 130,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 131,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 132,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 133,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 134,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 135,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 136,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 137,   1 },
  { 0x01          ,   1,   0 },
  { 0xF3 /* 's' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE9 /* 'i' */,   1,   1 },
  { 0xEE /* 'n' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0x80          , 138,   1 },
  { 0x01          ,   1,   0 },
  { 0xED /* 'm' */,   1,   1 },
  { 0xEF /* 'o' */,   1,   1 },
  { 0xE4 /* 'd' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0x80          , 140,   1 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 142,   2 },
  { 0x80          , 141,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 144,   2 },
  { 0x80          , 143,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 146,   2 },
  { 0x80          , 145,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 148,   2 },
  { 0x80          , 147,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 150,   2 },
  { 0x80          , 149,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 152,   2 },
  { 0x80          , 151,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 154,   2 },
  { 0x80          , 153,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 156,   2 },
  { 0x80          , 155,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 158,   2 },
  { 0x80          , 157,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 160,   2 },
  { 0x80          , 159,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 162,   2 },
  { 0x80          , 161,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 164,   2 },
  { 0x80          , 163,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 166,   2 },
  { 0x80          , 165,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 168,   2 },
  { 0x80          , 167,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 170,   2 },
  { 0x80          , 169,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 172,   2 },
  { 0x80          , 171,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 174,   2 },
  { 0x80          , 173,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 176,   2 },
  { 0x80          , 175,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 178,   2 },
  { 0x80          , 177,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 180,   2 },
  { 0x80          , 179,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 182,   2 },
  { 0x80          , 181,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 184,   2 },
  { 0x80          , 183,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 186,   2 },
  { 0x80          , 185,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 188,   2 },
  { 0x80          , 187,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 190,   2 },
  { 0x80          , 189,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 192,   2 },
  { 0x80          , 191,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 194,   2 },
  { 0x80          , 193,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 196,   2 },
  { 0x80          , 195,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 198,   2 },
  { 0x80          , 197,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 200,   2 },
  { 0x80          , 199,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 202,   2 },
  { 0x80          , 201,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 204,   2 },
  { 0x80          , 203,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 206,   2 },
  { 0x80          , 205,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 208,   2 },
  { 0x80          , 207,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 210,   2 },
  { 0x80          , 209,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 212,   2 },
  { 0x80          , 211,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 214,   2 },
  { 0x80          , 213,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 216,   2 },
  { 0x80          , 215,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 218,   2 },
  { 0x80          , 217,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 220,   2 },
  { 0x80          , 219,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 222,   2 },
  { 0x80          , 221,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 224,   2 },
  { 0x80          , 223,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 226,   2 },
  { 0x80          , 225,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 228,   2 },
  { 0x80          , 227,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 230,   2 },
  { 0x80          , 229,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 232,   2 },
  { 0x80          , 231,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 234,   2 },
  { 0x80          , 233,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 236,   2 },
  { 0x80          , 235,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 238,   2 },
  { 0x80          , 237,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 240,   2 },
  { 0x80          , 239,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 242,   2 },
  { 0x80          , 241,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 244,   2 },
  { 0x80          , 243,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 246,   2 },
  { 0x80          , 245,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 248,   2 },
  { 0x80          , 247,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 250,   2 },
  { 0x80          , 249,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 252,   2 },
  { 0x80          , 251,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 254,   2 },
  { 0x80          , 253,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 256,   2 },
  { 0x80          , 255,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 258,   2 },
  { 0x80          , 257,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 260,   2 },
  { 0x80          , 259,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 262,   2 },
  { 0x80          , 261,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 264,   2 },
  { 0x80          , 263,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 266,   2 },
  { 0x80          , 265,   2 },
  { 0x01          ,   1,   0 },
  { 0xCF /* 'O' */,   1,   1 },
  { 0x46 /* 'F' */,   2,   1 },
  { 0xCE /* 'N' */,   2,   2 },
  { 0xC6 /* 'F' */,   2,   2 },
  { 0x80          , 268,   2 },
  { 0x80          , 267,   2 },
  { 0x01          ,   1,   0 },
  { 0xD3 /* 'S' */,   1,   1 },
  { 0xF4 /* 't' */,   1,   1 },
  { 0xE5 /* 'e' */,   1,   1 },
  { 0xF0 /* 'p' */,   1,   1 },
  { 0x80          , 269,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 270,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 274,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 276,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 277,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 278,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 279,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 280,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 281,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 282,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 283,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 284,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 285,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 286,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 287,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 288,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 289,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 290,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 291,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 292,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 293,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 294,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 295,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 296,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 297,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 298,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 299,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 300,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 301,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 302,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 303,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 304,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 305,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 306,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 307,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 308,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 309,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 310,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 311,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 312,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 313,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 314,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 315,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 316,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 317,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 318,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 319,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 320,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 321,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 322,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 323,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 324,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 325,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 326,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 327,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 328,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 329,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 330,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 331,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 332,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 333,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 334,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 335,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 336,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 337,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 338,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 339,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 340,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 341,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 342,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 343,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 344,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 345,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 346,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 347,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 348,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 349,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 350,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 351,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 352,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 353,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 354,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 355,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 356,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 357,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 358,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 359,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 360,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 361,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 362,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 363,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 364,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 365,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 366,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 367,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 368,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 369,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 370,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 371,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 372,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 373,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 374,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 375,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 376,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 377,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 378,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 379,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 380,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 381,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 382,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 383,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 384,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 385,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 386,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 387,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 388,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 389,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 390,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 391,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 392,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 393,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 394,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 395,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 396,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 397,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 398,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 399,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 400,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 401,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 402,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 403,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 404,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 405,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 406,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 407,   1 },
  { 0x01          ,   1,   0 },
  { 0x8A          ,   1,   1 },
  { 0x80          , 408,   1 }
};
#ifndef NO_PROMPTS
prompt_type prompts[] = {
  {  1, PRMTOFST(0) },
  { -1, PRMTOFST(1) },
  {  0, PRMTOFST(2) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(4) },
  {  0, PRMTOFST(5) },
  {  0, PRMTOFST(6) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(7) },
  {  0, PRMTOFST(8) },
  {  1, PRMTOFST(9) },
  {  1, PRMTOFST(10) },
  { -2, PRMTOFST(11) },
  {  0, PRMTOFST(12) },
  {  1, PRMTOFST(13) },
  {  1, PRMTOFST(14) },
  {  1, PRMTOFST(15) },
  {  1, PRMTOFST(16) },
  {  1, PRMTOFST(17) },
  {  1, PRMTOFST(18) },
  {  1, PRMTOFST(19) },
  {  1, PRMTOFST(20) },
  { -8, PRMTOFST(21) },
  {  0, PRMTOFST(22) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(23) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(24) },
  {  0, PRMTOFST(24) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(25) },
  {  0, PRMTOFST(26) },
  {  0, PRMTOFST(27) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(28) },
  {  0, PRMTOFST(29) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(30) },
  {  0, PRMTOFST(31) },
  {  0, PRMTOFST(32) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(33) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) },
  {  0, PRMTOFST(3) }
};
#ifdef MACHINE_PROMPTS
  unsigned char prmt_text[] = {
    60, PROMPT_ATTR, 67, PROMPT_ATTR, 82, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 67, PROMPT_ATTR, 77, PROMPT_ATTR,
    68, PROMPT_ATTR, 69, PROMPT_ATTR, 78, PROMPT_ATTR, 66, PROMPT_ATTR,
    76, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 120, PROMPT_ATTR, 105, PROMPT_ATTR, 116, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 103, PROMPT_ATTR, 101, PROMPT_ATTR,
    116, PROMPT_ATTR, 99, PROMPT_ATTR, 111, PROMPT_ATTR, 110, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    76, PROMPT_ATTR, 111, PROMPT_ATTR, 103, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 80, PROMPT_ATTR, 104, PROMPT_ATTR,
    82, PROMPT_ATTR, 84, PROMPT_ATTR, 71, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    81, PROMPT_ATTR, 117, PROMPT_ATTR, 105, PROMPT_ATTR, 116, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    82, PROMPT_ATTR, 101, PROMPT_ATTR, 113, PROMPT_ATTR, 117, PROMPT_ATTR,
    101, PROMPT_ATTR, 115, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 97, PROMPT_ATTR,
    118, PROMPT_ATTR, 101, PROMPT_ATTR, 108, PROMPT_ATTR, 111, PROMPT_ATTR,
    103, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 101, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 111, PROMPT_ATTR,
    108, PROMPT_ATTR, 100, PROMPT_ATTR, 114, PROMPT_ATTR, 118, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 111, PROMPT_ATTR, 108, PROMPT_ATTR, 101, PROMPT_ATTR,
    110, PROMPT_ATTR, 111, PROMPT_ATTR, 105, PROMPT_ATTR, 100, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 84, PROMPT_ATTR, 101, PROMPT_ATTR,
    108, PROMPT_ATTR, 101, PROMPT_ATTR, 109, PROMPT_ATTR, 101, PROMPT_ATTR,
    116, PROMPT_ATTR, 114, PROMPT_ATTR, 121, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    79, PROMPT_ATTR, 102, PROMPT_ATTR, 102, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 79, PROMPT_ATTR, 110, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    60, PROMPT_ATTR, 67, PROMPT_ATTR, 82, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    101, PROMPT_ATTR, 110, PROMPT_ATTR, 100, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR,
    101, PROMPT_ATTR, 114, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR,
    116, PROMPT_ATTR, 114, PROMPT_ATTR, 105, PROMPT_ATTR, 110, PROMPT_ATTR,
    103, PROMPT_ATTR, 32, PROMPT_ATTR, 116, PROMPT_ATTR, 111, PROMPT_ATTR,
    32, PROMPT_ATTR, 76, PROMPT_ATTR, 111, PROMPT_ATTR, 103, PROMPT_ATTR,
    32, PROMPT_ATTR, 116, PROMPT_ATTR, 111, PROMPT_ATTR, 32, PROMPT_ATTR,
    77, PROMPT_ATTR, 101, PROMPT_ATTR, 109, PROMPT_ATTR, 111, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    68, PROMPT_ATTR, 97, PROMPT_ATTR, 116, PROMPT_ATTR, 117, PROMPT_ATTR,
    109, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 70, PROMPT_ATTR, 105, PROMPT_ATTR,
    108, PROMPT_ATTR, 101, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    82, PROMPT_ATTR, 101, PROMPT_ATTR, 115, PROMPT_ATTR, 116, PROMPT_ATTR,
    97, PROMPT_ATTR, 114, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 76, PROMPT_ATTR, 111, PROMPT_ATTR,
    103, PROMPT_ATTR, 32, PROMPT_ATTR, 77, PROMPT_ATTR, 101, PROMPT_ATTR,
    115, PROMPT_ATTR, 115, PROMPT_ATTR, 97, PROMPT_ATTR, 103, PROMPT_ATTR,
    101, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    102, PROMPT_ATTR, 99, PROMPT_ATTR, 69, PROMPT_ATTR, 102, PROMPT_ATTR,
    102, PROMPT_ATTR, 95, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    121, PROMPT_ATTR, 32, PROMPT_ATTR, 102, PROMPT_ATTR, 99, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR, 95, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 120, PROMPT_ATTR, 32, PROMPT_ATTR,
    102, PROMPT_ATTR, 99, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    95, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR, 120, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 102, PROMPT_ATTR, 99, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 95, PROMPT_ATTR, 78, PROMPT_ATTR,
    79, PROMPT_ATTR, 121, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    102, PROMPT_ATTR, 99, PROMPT_ATTR, 90, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 95, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    121, PROMPT_ATTR, 32, PROMPT_ATTR, 102, PROMPT_ATTR, 99, PROMPT_ATTR,
    95, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR,
    101, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    70, PROMPT_ATTR, 108, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    70, PROMPT_ATTR, 108, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    50, PROMPT_ATTR, 101, PROMPT_ATTR, 51, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 70, PROMPT_ATTR, 108, PROMPT_ATTR,
    67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR, 112, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    70, PROMPT_ATTR, 108, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    120, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 70, PROMPT_ATTR, 108, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 121, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    80, PROMPT_ATTR, 109, PROMPT_ATTR, 97, PROMPT_ATTR, 110, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 80, PROMPT_ATTR, 114, PROMPT_ATTR,
    67, PROMPT_ATTR, 79, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    80, PROMPT_ATTR, 114, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    50, PROMPT_ATTR, 101, PROMPT_ATTR, 49, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    80, PROMPT_ATTR, 114, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    50, PROMPT_ATTR, 101, PROMPT_ATTR, 50, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 80, PROMPT_ATTR, 114, PROMPT_ATTR,
    67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR, 112, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    115, PROMPT_ATTR, 101, PROMPT_ATTR, 108, PROMPT_ATTR, 101, PROMPT_ATTR,
    99, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR, 97, PROMPT_ATTR,
    100, PROMPT_ATTR, 100, PROMPT_ATTR, 49, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    50, PROMPT_ATTR, 97, PROMPT_ATTR, 100, PROMPT_ATTR, 100, PROMPT_ATTR,
    50, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    67, PROMPT_ATTR, 79, PROMPT_ATTR, 95, PROMPT_ATTR, 99, PROMPT_ATTR,
    97, PROMPT_ATTR, 108, PROMPT_ATTR, 49, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    95, PROMPT_ATTR, 99, PROMPT_ATTR, 97, PROMPT_ATTR, 108, PROMPT_ATTR,
    50, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    67, PROMPT_ATTR, 79, PROMPT_ATTR, 95, PROMPT_ATTR, 115, PROMPT_ATTR,
    109, PROMPT_ATTR, 112, PROMPT_ATTR, 108, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR,
    95, PROMPT_ATTR, 122, PROMPT_ATTR, 101, PROMPT_ATTR, 114, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    101, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR,
    99, PROMPT_ATTR, 97, PROMPT_ATTR, 108, PROMPT_ATTR, 95, PROMPT_ATTR,
    111, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    101, PROMPT_ATTR, 102, PROMPT_ATTR, 102, PROMPT_ATTR, 95, PROMPT_ATTR,
    72, PROMPT_ATTR, 103, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 72, PROMPT_ATTR, 117, PROMPT_ATTR,
    98, PROMPT_ATTR, 95, PROMPT_ATTR, 115, PROMPT_ATTR, 112, PROMPT_ATTR,
    49, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    72, PROMPT_ATTR, 117, PROMPT_ATTR, 98, PROMPT_ATTR, 95, PROMPT_ATTR,
    115, PROMPT_ATTR, 112, PROMPT_ATTR, 50, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 76, PROMPT_ATTR, 118, PROMPT_ATTR,
    108, PROMPT_ATTR, 49, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    76, PROMPT_ATTR, 118, PROMPT_ATTR, 108, PROMPT_ATTR, 50, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 76, PROMPT_ATTR, 118, PROMPT_ATTR,
    108, PROMPT_ATTR, 51, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    76, PROMPT_ATTR, 118, PROMPT_ATTR, 108, PROMPT_ATTR, 52, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    76, PROMPT_ATTR, 118, PROMPT_ATTR, 108, PROMPT_ATTR, 53, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 76, PROMPT_ATTR, 118, PROMPT_ATTR,
    108, PROMPT_ATTR, 54, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    76, PROMPT_ATTR, 118, PROMPT_ATTR, 108, PROMPT_ATTR, 55, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 76, PROMPT_ATTR, 118, PROMPT_ATTR,
    108, PROMPT_ATTR, 56, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR, 95, PROMPT_ATTR,
    97, PROMPT_ATTR, 100, PROMPT_ATTR, 100, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    50, PROMPT_ATTR, 95, PROMPT_ATTR, 111, PROMPT_ATTR, 110, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 95, PROMPT_ATTR, 78, PROMPT_ATTR,
    79, PROMPT_ATTR, 120, PROMPT_ATTR, 95, PROMPT_ATTR, 97, PROMPT_ATTR,
    100, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 95, PROMPT_ATTR, 78, PROMPT_ATTR,
    79, PROMPT_ATTR, 120, PROMPT_ATTR, 95, PROMPT_ATTR, 111, PROMPT_ATTR,
    110, PROMPT_ATTR, 32, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    95, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR, 121, PROMPT_ATTR,
    95, PROMPT_ATTR, 97, PROMPT_ATTR, 100, PROMPT_ATTR, 32, PROMPT_ATTR,
    78, PROMPT_ATTR, 79, PROMPT_ATTR, 95, PROMPT_ATTR, 78, PROMPT_ATTR,
    79, PROMPT_ATTR, 121, PROMPT_ATTR, 95, PROMPT_ATTR, 111, PROMPT_ATTR,
    110, PROMPT_ATTR, 32, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR,
    121, PROMPT_ATTR, 95, PROMPT_ATTR, 101, PROMPT_ATTR, 102, PROMPT_ATTR,
    102, PROMPT_ATTR, 95, PROMPT_ATTR, 97, PROMPT_ATTR, 32, PROMPT_ATTR,
    78, PROMPT_ATTR, 80, PROMPT_ATTR, 78, PROMPT_ATTR, 95, PROMPT_ATTR,
    97, PROMPT_ATTR, 100, PROMPT_ATTR, 100, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 78, PROMPT_ATTR, 80, PROMPT_ATTR,
    78, PROMPT_ATTR, 95, PROMPT_ATTR, 111, PROMPT_ATTR, 110, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    112, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR,
    95, PROMPT_ATTR, 99, PROMPT_ATTR, 97, PROMPT_ATTR, 108, PROMPT_ATTR,
    49, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    112, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR,
    95, PROMPT_ATTR, 99, PROMPT_ATTR, 97, PROMPT_ATTR, 108, PROMPT_ATTR,
    50, PROMPT_ATTR, 32, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR,
    79, PROMPT_ATTR, 50, PROMPT_ATTR, 95, PROMPT_ATTR, 99, PROMPT_ATTR,
    97, PROMPT_ATTR, 108, PROMPT_ATTR, 51, PROMPT_ATTR, 32, PROMPT_ATTR,
    112, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR,
    95, PROMPT_ATTR, 99, PROMPT_ATTR, 97, PROMPT_ATTR, 108, PROMPT_ATTR,
    97, PROMPT_ATTR, 32, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR,
    79, PROMPT_ATTR, 50, PROMPT_ATTR, 95, PROMPT_ATTR, 99, PROMPT_ATTR,
    97, PROMPT_ATTR, 108, PROMPT_ATTR, 82, PROMPT_ATTR, 32, PROMPT_ATTR,
    112, PROMPT_ATTR, 67, PROMPT_ATTR, 79, PROMPT_ATTR, 50, PROMPT_ATTR,
    95, PROMPT_ATTR, 115, PROMPT_ATTR, 109, PROMPT_ATTR, 112, PROMPT_ATTR,
    108, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 104, PROMPT_ATTR,
    107, PROMPT_ATTR, 95, PROMPT_ATTR, 115, PROMPT_ATTR, 112, PROMPT_ATTR,
    49, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 104, PROMPT_ATTR, 107, PROMPT_ATTR, 95, PROMPT_ATTR,
    115, PROMPT_ATTR, 112, PROMPT_ATTR, 50, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 104, PROMPT_ATTR, 117, PROMPT_ATTR, 116, PROMPT_ATTR,
    116, PROMPT_ATTR, 101, PROMPT_ATTR, 114, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 111, PROMPT_ATTR,
    108, PROMPT_ATTR, 95, PROMPT_ATTR, 52, PROMPT_ATTR, 49, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 111, PROMPT_ATTR, 108, PROMPT_ATTR, 95, PROMPT_ATTR,
    52, PROMPT_ATTR, 50, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 111, PROMPT_ATTR,
    108, PROMPT_ATTR, 95, PROMPT_ATTR, 52, PROMPT_ATTR, 51, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 111, PROMPT_ATTR, 108, PROMPT_ATTR, 95, PROMPT_ATTR,
    52, PROMPT_ATTR, 52, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 111, PROMPT_ATTR,
    108, PROMPT_ATTR, 95, PROMPT_ATTR, 52, PROMPT_ATTR, 53, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 111, PROMPT_ATTR, 108, PROMPT_ATTR, 95, PROMPT_ATTR,
    52, PROMPT_ATTR, 54, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 111, PROMPT_ATTR, 108, PROMPT_ATTR, 95, PROMPT_ATTR,
    52, PROMPT_ATTR, 55, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 111, PROMPT_ATTR,
    108, PROMPT_ATTR, 95, PROMPT_ATTR, 52, PROMPT_ATTR, 56, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 49, PROMPT_ATTR, 55, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    49, PROMPT_ATTR, 56, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 49, PROMPT_ATTR, 57, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    50, PROMPT_ATTR, 48, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 50, PROMPT_ATTR, 49, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 50, PROMPT_ATTR, 50, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    50, PROMPT_ATTR, 51, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 50, PROMPT_ATTR, 52, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    50, PROMPT_ATTR, 53, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 50, PROMPT_ATTR, 54, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    50, PROMPT_ATTR, 55, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 50, PROMPT_ATTR, 56, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 60, PROMPT_ATTR, 77, PROMPT_ATTR,
    111, PROMPT_ATTR, 114, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 50, PROMPT_ATTR, 57, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    51, PROMPT_ATTR, 48, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 112, PROMPT_ATTR, 67, PROMPT_ATTR, 109, PROMPT_ATTR,
    100, PROMPT_ATTR, 95, PROMPT_ATTR, 51, PROMPT_ATTR, 49, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 112, PROMPT_ATTR,
    67, PROMPT_ATTR, 109, PROMPT_ATTR, 100, PROMPT_ATTR, 95, PROMPT_ATTR,
    51, PROMPT_ATTR, 50, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    122, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR, 120, PROMPT_ATTR,
    95, PROMPT_ATTR, 97, PROMPT_ATTR, 100, PROMPT_ATTR, 100, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 122, PROMPT_ATTR, 78, PROMPT_ATTR,
    79, PROMPT_ATTR, 120, PROMPT_ATTR, 95, PROMPT_ATTR, 72, PROMPT_ATTR,
    103, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    122, PROMPT_ATTR, 78, PROMPT_ATTR, 79, PROMPT_ATTR, 121, PROMPT_ATTR,
    95, PROMPT_ATTR, 97, PROMPT_ATTR, 100, PROMPT_ATTR, 100, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 122, PROMPT_ATTR, 78, PROMPT_ATTR,
    79, PROMPT_ATTR, 121, PROMPT_ATTR, 95, PROMPT_ATTR, 72, PROMPT_ATTR,
    103, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 105, PROMPT_ATTR, 110, PROMPT_ATTR, 103, PROMPT_ATTR,
    108, PROMPT_ATTR, 101, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 116, PROMPT_ATTR,
    97, PROMPT_ATTR, 114, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    115, PROMPT_ATTR, 101, PROMPT_ATTR, 115, PROMPT_ATTR, 115, PROMPT_ATTR,
    105, PROMPT_ATTR, 111, PROMPT_ATTR, 110, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 87, PROMPT_ATTR, 111, PROMPT_ATTR,
    114, PROMPT_ATTR, 100, PROMPT_ATTR, 32, PROMPT_ATTR, 84, PROMPT_ATTR,
    101, PROMPT_ATTR, 114, PROMPT_ATTR, 109, PROMPT_ATTR, 105, PROMPT_ATTR,
    110, PROMPT_ATTR, 97, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    100, PROMPT_ATTR, 32, PROMPT_ATTR, 98, PROMPT_ATTR, 121, PROMPT_ATTR,
    32, PROMPT_ATTR, 60, PROMPT_ATTR, 115, PROMPT_ATTR, 112, PROMPT_ATTR,
    97, PROMPT_ATTR, 99, PROMPT_ATTR, 101, PROMPT_ATTR, 62, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    115, PROMPT_ATTR, 101, PROMPT_ATTR, 116, PROMPT_ATTR, 112, PROMPT_ATTR,
    111, PROMPT_ATTR, 105, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 101, PROMPT_ATTR,
    116, PROMPT_ATTR, 112, PROMPT_ATTR, 111, PROMPT_ATTR, 105, PROMPT_ATTR,
    110, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR, 86, PROMPT_ATTR,
    97, PROMPT_ATTR, 108, PROMPT_ATTR, 117, PROMPT_ATTR, 101, PROMPT_ATTR,
    32, PROMPT_ATTR, 105, PROMPT_ATTR, 110, PROMPT_ATTR, 32, PROMPT_ATTR,
    86, PROMPT_ATTR, 111, PROMPT_ATTR, 108, PROMPT_ATTR, 116, PROMPT_ATTR,
    115, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    109, PROMPT_ATTR, 111, PROMPT_ATTR, 100, PROMPT_ATTR, 101, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    79, PROMPT_ATTR, 70, PROMPT_ATTR, 70, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 79, PROMPT_ATTR, 78, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    83, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR, 112, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 83, PROMPT_ATTR, 101, PROMPT_ATTR,
    115, PROMPT_ATTR, 115, PROMPT_ATTR, 105, PROMPT_ATTR, 111, PROMPT_ATTR,
    110, PROMPT_ATTR, 32, PROMPT_ATTR, 73, PROMPT_ATTR, 68, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 84, PROMPT_ATTR, 101, PROMPT_ATTR,
    120, PROMPT_ATTR, 116, PROMPT_ATTR, 32, PROMPT_ATTR, 84, PROMPT_ATTR,
    101, PROMPT_ATTR, 114, PROMPT_ATTR, 109, PROMPT_ATTR, 105, PROMPT_ATTR,
    110, PROMPT_ATTR, 97, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    100, PROMPT_ATTR, 32, PROMPT_ATTR, 98, PROMPT_ATTR, 121, PROMPT_ATTR,
    32, PROMPT_ATTR, 60, PROMPT_ATTR, 67, PROMPT_ATTR, 82, PROMPT_ATTR,
    62, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 73, PROMPT_ATTR, 110, PROMPT_ATTR,
    116, PROMPT_ATTR, 101, PROMPT_ATTR, 103, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 40, PROMPT_ATTR, 68, PROMPT_ATTR,
    101, PROMPT_ATTR, 99, PROMPT_ATTR, 105, PROMPT_ATTR, 109, PROMPT_ATTR,
    97, PROMPT_ATTR, 108, PROMPT_ATTR, 58, PROMPT_ATTR, 32, PROMPT_ATTR,
    49, PROMPT_ATTR, 50, PROMPT_ATTR, 51, PROMPT_ATTR, 44, PROMPT_ATTR,
    32, PROMPT_ATTR, 72, PROMPT_ATTR, 101, PROMPT_ATTR, 120, PROMPT_ATTR,
    58, PROMPT_ATTR, 32, PROMPT_ATTR, 48, PROMPT_ATTR, 120, PROMPT_ATTR,
    49, PROMPT_ATTR, 50, PROMPT_ATTR, 51, PROMPT_ATTR, 70, PROMPT_ATTR,
    44, PROMPT_ATTR, 32, PROMPT_ATTR, 79, PROMPT_ATTR, 99, PROMPT_ATTR,
    116, PROMPT_ATTR, 97, PROMPT_ATTR, 108, PROMPT_ATTR, 58, PROMPT_ATTR,
    32, PROMPT_ATTR, 48, PROMPT_ATTR, 49, PROMPT_ATTR, 50, PROMPT_ATTR,
    51, PROMPT_ATTR, 41, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    69, PROMPT_ATTR, 110, PROMPT_ATTR, 116, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 77, PROMPT_ATTR, 111, PROMPT_ATTR,
    100, PROMPT_ATTR, 101, PROMPT_ATTR, 32, PROMPT_ATTR, 78, PROMPT_ATTR,
    117, PROMPT_ATTR, 109, PROMPT_ATTR, 98, PROMPT_ATTR, 101, PROMPT_ATTR,
    114, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR,
    32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR, 32, PROMPT_ATTR
  };
#else
  const char *prmt_text[] = {
    "<CR>      CMDENBL   Exit      getcon    Log       PhRTG     Quit      <More>",
    "Request   Savelog   Set       Soldrv    Solenoid  Telemetry",
    "Off       On",
    "<CR>",
    "end",
    " Enter String to Log to Memo ",
    "Datum     File",
    "Restart",
    "Enter Log Message",
    "fcEff_NOy fcNO2_NOx fcNO_NOx  fcNO_NOy  fcZer_NOy fc_CO2e   FlCO      <More>",
    "FlCO2e3   FlCO2p    FlNOx     FlNOy     Pman      PrCO      PrCO2e1   <More>",
    "PrCO2e2   PrCO2p",
    "select",
    "CO2add1   CO2add2   CO_cal1   CO_cal2   CO_smpl   CO_zer    eCO2cal_o <More>",
    "eff_Hg    Hub_sp1   Hub_sp2   Lvl1      Lvl2      Lvl3      Lvl4      <More>",
    "Lvl5      Lvl6      Lvl7      Lvl8      NO2_add   NO2_on    NO_NOx_ad <More>",
    "NO_NOx_on NO_NOy_ad NO_NOy_on NOy_eff_a NPN_add   NPN_on    pCO2_cal1 <More>",
    "pCO2_cal2 pCO2_cal3 pCO2_cala pCO2_calR pCO2_smpl Shk_sp1   Shk_sp2   <More>",
    "Shutter   Sol_41    Sol_42    Sol_43    Sol_44    Sol_45    Sol_46    <More>",
    "Sol_47    Sol_48    SpCmd_17  SpCmd_18  SpCmd_19  SpCmd_20  SpCmd_21  <More>",
    "SpCmd_22  SpCmd_23  SpCmd_24  SpCmd_25  SpCmd_26  SpCmd_27  SpCmd_28  <More>",
    "SpCmd_29  SpCmd_30  SpCmd_31  SpCmd_32  zNOx_add  zNOx_Hg   zNOy_add  zNOy_Hg",
    "Single    Start",
    "session",
    "Enter Word Terminated by <space>",
    "setpoint",
    "Enter Setpoint Value in Volts",
    "mode",
    "OFF       ON",
    "Step",
    "Enter Session ID",
    "Enter Text Terminated by <CR>",
    "Enter Integer (Decimal: 123, Hex: 0x123F, Octal: 0123)",
    "Enter Mode Number"
  };
#endif
#endif /* NO_PROMPTS */
shift_type non_terminals[] = {
  { 1, 1 },
  { 2, 2 },
  { 0, 0 },
  { 3, 16 },
  { 4, 17 },
  { 6, 18 },
  { 0, 0 },
  { 9, 21 },
  { 0, 0 },
  { 0, 24 },
  { 8, 27 },
  { 0, 0 },
  { 0, 30 },
  { 7, 47 },
  { 0, 0 },
  { 5, 115 },
  { 0, 0 },
  { 0, 119 },
  { 0, 120 },
  { 0, 139 },
  { 0, 271 },
  { 0, 272 },
  { 0, 273 },
  { 0, 275 }
};
state_type states[] = {
  { STFL_REDUCE, 4, -1, 0 },
  { STFL_REDUCE, 0, -1, 2 },
  { STFL_WORD, 0, 0, 3 },
  { STFL_REDUCE, 6, -1, 2 },
  { STFL_WORD, 79, 2, 7 },
  { STFL_WORD, 86, 3, 2 },
  { STFL_WORD, 89, 4, 2 },
  { STFL_VARIABLE, VAR_s, 5, 9 },
  { STFL_WORD, 94, 6, 10 },
  { STFL_WORD, 106, 7, 2 },
  { STFL_WORD, 109, 8, 2 },
  { STFL_VARIABLE, VAR_s, 9, 12 },
  { STFL_WORD, 118, 10, 13 },
  { STFL_WORD, 191, 13, 2 },
  { STFL_WORD, 199, 14, 2 },
  { STFL_WORD, 445, 23, 15 },
  { STFL_REDUCE, 2, -1, 2 },
  { STFL_REDUCE, 5, -1, 2 },
  { STFL_REDUCE, 13, -1, 2 },
  { STFL_REDUCE, 166, -1, 2 },
  { STFL_REDUCE, 165, -1, 2 },
  { STFL_WORD, 458, 24, 2 },
  { STFL_REDUCE, 3, -1, 2 },
  { STFL_WORD, 461, 25, 2 },
  { STFL_WORD, 470, 26, 2 },
  { STFL_VARIABLE, VAR_w, 27, 17 },
  { STFL_VARIABLE, VAR_w, 28, 18 },
  { STFL_REDUCE, 160, -1, 2 },
  { STFL_REDUCE, 1, -1, 2 },
  { STFL_WORD, 473, 29, 2 },
  { STFL_WORD, 476, 30, 2 },
  { STFL_WORD, 479, 31, 2 },
  { STFL_WORD, 489, 32, 2 },
  { STFL_WORD, 499, 33, 2 },
  { STFL_WORD, 509, 34, 2 },
  { STFL_WORD, 519, 35, 2 },
  { STFL_WORD, 529, 36, 2 },
  { STFL_WORD, 539, 37, 2 },
  { STFL_WORD, 549, 38, 2 },
  { STFL_WORD, 559, 39, 2 },
  { STFL_WORD, 569, 40, 2 },
  { STFL_WORD, 579, 41, 2 },
  { STFL_WORD, 589, 42, 2 },
  { STFL_WORD, 599, 43, 2 },
  { STFL_WORD, 609, 44, 2 },
  { STFL_WORD, 619, 45, 2 },
  { STFL_WORD, 629, 46, 2 },
  { STFL_VARIABLE, VAR_lf, 47, 19 },
  { STFL_WORD, 639, 48, 2 },
  { STFL_WORD, 645, 49, 2 },
  { STFL_WORD, 652, 50, 2 },
  { STFL_WORD, 659, 51, 2 },
  { STFL_WORD, 666, 52, 2 },
  { STFL_WORD, 673, 53, 2 },
  { STFL_WORD, 680, 54, 2 },
  { STFL_WORD, 687, 55, 2 },
  { STFL_WORD, 694, 56, 2 },
  { STFL_WORD, 701, 57, 2 },
  { STFL_WORD, 708, 58, 2 },
  { STFL_WORD, 715, 59, 2 },
  { STFL_WORD, 722, 60, 2 },
  { STFL_WORD, 729, 61, 2 },
  { STFL_WORD, 736, 62, 2 },
  { STFL_WORD, 743, 63, 2 },
  { STFL_WORD, 750, 64, 2 },
  { STFL_WORD, 757, 65, 2 },
  { STFL_WORD, 764, 66, 2 },
  { STFL_WORD, 771, 67, 2 },
  { STFL_WORD, 778, 68, 2 },
  { STFL_WORD, 785, 69, 2 },
  { STFL_WORD, 792, 70, 2 },
  { STFL_WORD, 799, 71, 2 },
  { STFL_WORD, 806, 72, 2 },
  { STFL_WORD, 813, 73, 2 },
  { STFL_WORD, 820, 74, 2 },
  { STFL_WORD, 827, 75, 2 },
  { STFL_WORD, 834, 76, 2 },
  { STFL_WORD, 841, 77, 2 },
  { STFL_WORD, 848, 78, 2 },
  { STFL_WORD, 855, 79, 2 },
  { STFL_WORD, 862, 80, 2 },
  { STFL_WORD, 869, 81, 2 },
  { STFL_WORD, 876, 82, 2 },
  { STFL_WORD, 883, 83, 2 },
  { STFL_WORD, 890, 84, 2 },
  { STFL_WORD, 897, 85, 2 },
  { STFL_WORD, 904, 86, 2 },
  { STFL_WORD, 911, 87, 2 },
  { STFL_WORD, 918, 88, 2 },
  { STFL_WORD, 925, 89, 2 },
  { STFL_WORD, 932, 90, 2 },
  { STFL_WORD, 939, 91, 2 },
  { STFL_WORD, 946, 92, 2 },
  { STFL_WORD, 953, 93, 2 },
  { STFL_WORD, 960, 94, 2 },
  { STFL_WORD, 967, 95, 2 },
  { STFL_WORD, 974, 96, 2 },
  { STFL_WORD, 981, 97, 2 },
  { STFL_WORD, 988, 98, 2 },
  { STFL_WORD, 995, 99, 2 },
  { STFL_WORD, 1002, 100, 2 },
  { STFL_WORD, 1009, 101, 2 },
  { STFL_WORD, 1016, 102, 2 },
  { STFL_WORD, 1023, 103, 2 },
  { STFL_WORD, 1030, 104, 2 },
  { STFL_WORD, 1037, 105, 2 },
  { STFL_WORD, 1044, 106, 2 },
  { STFL_WORD, 1051, 107, 2 },
  { STFL_WORD, 1058, 108, 2 },
  { STFL_WORD, 1065, 109, 2 },
  { STFL_WORD, 1072, 110, 2 },
  { STFL_WORD, 1079, 111, 2 },
  { STFL_WORD, 1086, 112, 2 },
  { STFL_WORD, 1093, 113, 2 },
  { STFL_WORD, 1099, 114, 2 },
  { STFL_REDUCE, 7, -1, 2 },
  { STFL_REDUCE, 164, -1, 2 },
  { STFL_VARIABLE, VAR_w, 115, 20 },
  { STFL_REDUCE, 8, -1, 2 },
  { STFL_VARIABLE, VAR_s, 116, 21 },
  { STFL_VARIABLE, VAR_d, 117, 22 },
  { STFL_REDUCE, 12, -1, 2 },
  { STFL_REDUCE, 11, -1, 2 },
  { STFL_REDUCE, 26, -1, 2 },
  { STFL_REDUCE, 23, -1, 2 },
  { STFL_REDUCE, 22, -1, 2 },
  { STFL_REDUCE, 25, -1, 2 },
  { STFL_REDUCE, 27, -1, 2 },
  { STFL_REDUCE, 24, -1, 2 },
  { STFL_REDUCE, 31, -1, 2 },
  { STFL_REDUCE, 30, -1, 2 },
  { STFL_REDUCE, 18, -1, 2 },
  { STFL_REDUCE, 28, -1, 2 },
  { STFL_REDUCE, 29, -1, 2 },
  { STFL_REDUCE, 16, -1, 2 },
  { STFL_REDUCE, 21, -1, 2 },
  { STFL_REDUCE, 19, -1, 2 },
  { STFL_REDUCE, 20, -1, 2 },
  { STFL_REDUCE, 17, -1, 2 },
  { STFL_WORD, 1102, 118, 2 },
  { STFL_VARIABLE, VAR_d, 119, 23 },
  { STFL_WORD, 1105, 120, 2 },
  { STFL_WORD, 1108, 121, 2 },
  { STFL_WORD, 1111, 122, 2 },
  { STFL_WORD, 1114, 123, 2 },
  { STFL_WORD, 1117, 124, 2 },
  { STFL_WORD, 1120, 125, 2 },
  { STFL_WORD, 1123, 126, 2 },
  { STFL_WORD, 1126, 127, 2 },
  { STFL_WORD, 1129, 128, 2 },
  { STFL_WORD, 1132, 129, 2 },
  { STFL_WORD, 1135, 130, 2 },
  { STFL_WORD, 1138, 131, 2 },
  { STFL_WORD, 1141, 132, 2 },
  { STFL_WORD, 1144, 133, 2 },
  { STFL_WORD, 1147, 134, 2 },
  { STFL_WORD, 1150, 135, 2 },
  { STFL_WORD, 1153, 136, 2 },
  { STFL_WORD, 1156, 137, 2 },
  { STFL_WORD, 1159, 138, 2 },
  { STFL_WORD, 1162, 139, 2 },
  { STFL_WORD, 1165, 140, 2 },
  { STFL_WORD, 1168, 141, 2 },
  { STFL_WORD, 1171, 142, 2 },
  { STFL_WORD, 1174, 143, 2 },
  { STFL_WORD, 1177, 144, 2 },
  { STFL_WORD, 1180, 145, 2 },
  { STFL_WORD, 1183, 146, 2 },
  { STFL_WORD, 1186, 147, 2 },
  { STFL_WORD, 1189, 148, 2 },
  { STFL_WORD, 1192, 149, 2 },
  { STFL_WORD, 1195, 150, 2 },
  { STFL_WORD, 1198, 151, 2 },
  { STFL_WORD, 1201, 152, 2 },
  { STFL_WORD, 1204, 153, 2 },
  { STFL_WORD, 1207, 154, 2 },
  { STFL_WORD, 1210, 155, 2 },
  { STFL_WORD, 1213, 156, 2 },
  { STFL_WORD, 1216, 157, 2 },
  { STFL_WORD, 1219, 158, 2 },
  { STFL_WORD, 1222, 159, 2 },
  { STFL_WORD, 1225, 160, 2 },
  { STFL_WORD, 1228, 161, 2 },
  { STFL_WORD, 1231, 162, 2 },
  { STFL_WORD, 1234, 163, 2 },
  { STFL_WORD, 1237, 164, 2 },
  { STFL_WORD, 1240, 165, 2 },
  { STFL_WORD, 1243, 166, 2 },
  { STFL_WORD, 1246, 167, 2 },
  { STFL_WORD, 1249, 168, 2 },
  { STFL_WORD, 1252, 169, 2 },
  { STFL_WORD, 1255, 170, 2 },
  { STFL_WORD, 1258, 171, 2 },
  { STFL_WORD, 1261, 172, 2 },
  { STFL_WORD, 1264, 173, 2 },
  { STFL_WORD, 1267, 174, 2 },
  { STFL_WORD, 1270, 175, 2 },
  { STFL_WORD, 1273, 176, 2 },
  { STFL_WORD, 1276, 177, 2 },
  { STFL_WORD, 1279, 178, 2 },
  { STFL_WORD, 1282, 179, 2 },
  { STFL_WORD, 1285, 180, 2 },
  { STFL_WORD, 1288, 181, 2 },
  { STFL_WORD, 1291, 182, 2 },
  { STFL_WORD, 1294, 183, 2 },
  { STFL_WORD, 1297, 184, 2 },
  { STFL_WORD, 1300, 185, 2 },
  { STFL_WORD, 1303, 186, 2 },
  { STFL_WORD, 1306, 187, 2 },
  { STFL_WORD, 1309, 188, 2 },
  { STFL_WORD, 1312, 189, 2 },
  { STFL_WORD, 1315, 190, 2 },
  { STFL_WORD, 1318, 191, 2 },
  { STFL_WORD, 1321, 192, 2 },
  { STFL_WORD, 1324, 193, 2 },
  { STFL_WORD, 1327, 194, 2 },
  { STFL_WORD, 1330, 195, 2 },
  { STFL_WORD, 1333, 196, 2 },
  { STFL_WORD, 1336, 197, 2 },
  { STFL_WORD, 1339, 198, 2 },
  { STFL_WORD, 1342, 199, 2 },
  { STFL_WORD, 1345, 200, 2 },
  { STFL_WORD, 1348, 201, 2 },
  { STFL_WORD, 1351, 202, 2 },
  { STFL_WORD, 1354, 203, 2 },
  { STFL_WORD, 1357, 204, 2 },
  { STFL_WORD, 1360, 205, 2 },
  { STFL_WORD, 1363, 206, 2 },
  { STFL_WORD, 1366, 207, 2 },
  { STFL_WORD, 1369, 208, 2 },
  { STFL_WORD, 1372, 209, 2 },
  { STFL_WORD, 1375, 210, 2 },
  { STFL_WORD, 1378, 211, 2 },
  { STFL_WORD, 1381, 212, 2 },
  { STFL_WORD, 1384, 213, 2 },
  { STFL_WORD, 1387, 214, 2 },
  { STFL_WORD, 1390, 215, 2 },
  { STFL_WORD, 1393, 216, 2 },
  { STFL_WORD, 1396, 217, 2 },
  { STFL_WORD, 1399, 218, 2 },
  { STFL_WORD, 1402, 219, 2 },
  { STFL_WORD, 1405, 220, 2 },
  { STFL_WORD, 1408, 221, 2 },
  { STFL_WORD, 1411, 222, 2 },
  { STFL_WORD, 1414, 223, 2 },
  { STFL_WORD, 1417, 224, 2 },
  { STFL_WORD, 1420, 225, 2 },
  { STFL_WORD, 1423, 226, 2 },
  { STFL_WORD, 1426, 227, 2 },
  { STFL_WORD, 1429, 228, 2 },
  { STFL_WORD, 1432, 229, 2 },
  { STFL_WORD, 1435, 230, 2 },
  { STFL_WORD, 1438, 231, 2 },
  { STFL_WORD, 1441, 232, 2 },
  { STFL_WORD, 1444, 233, 2 },
  { STFL_WORD, 1447, 234, 2 },
  { STFL_WORD, 1450, 235, 2 },
  { STFL_WORD, 1453, 236, 2 },
  { STFL_WORD, 1456, 237, 2 },
  { STFL_WORD, 1459, 238, 2 },
  { STFL_WORD, 1462, 239, 2 },
  { STFL_WORD, 1465, 240, 2 },
  { STFL_WORD, 1468, 241, 2 },
  { STFL_WORD, 1471, 242, 2 },
  { STFL_WORD, 1474, 243, 2 },
  { STFL_WORD, 1477, 244, 2 },
  { STFL_WORD, 1480, 245, 2 },
  { STFL_WORD, 1483, 246, 2 },
  { STFL_WORD, 1486, 247, 2 },
  { STFL_WORD, 1489, 248, 2 },
  { STFL_REDUCE, 9, -1, 2 },
  { STFL_WORD, 1492, 249, 2 },
  { STFL_WORD, 1495, 250, 2 },
  { STFL_WORD, 1498, 251, 2 },
  { STFL_REDUCE, 15, -1, 2 },
  { STFL_WORD, 1501, 252, 2 },
  { STFL_REDUCE, 51, -1, 2 },
  { STFL_REDUCE, 50, -1, 2 },
  { STFL_REDUCE, 53, -1, 2 },
  { STFL_REDUCE, 52, -1, 2 },
  { STFL_REDUCE, 57, -1, 2 },
  { STFL_REDUCE, 56, -1, 2 },
  { STFL_REDUCE, 59, -1, 2 },
  { STFL_REDUCE, 58, -1, 2 },
  { STFL_REDUCE, 55, -1, 2 },
  { STFL_REDUCE, 54, -1, 2 },
  { STFL_REDUCE, 61, -1, 2 },
  { STFL_REDUCE, 60, -1, 2 },
  { STFL_REDUCE, 49, -1, 2 },
  { STFL_REDUCE, 48, -1, 2 },
  { STFL_REDUCE, 63, -1, 2 },
  { STFL_REDUCE, 62, -1, 2 },
  { STFL_REDUCE, 137, -1, 2 },
  { STFL_REDUCE, 136, -1, 2 },
  { STFL_REDUCE, 139, -1, 2 },
  { STFL_REDUCE, 138, -1, 2 },
  { STFL_REDUCE, 33, -1, 2 },
  { STFL_REDUCE, 32, -1, 2 },
  { STFL_REDUCE, 35, -1, 2 },
  { STFL_REDUCE, 34, -1, 2 },
  { STFL_REDUCE, 37, -1, 2 },
  { STFL_REDUCE, 36, -1, 2 },
  { STFL_REDUCE, 39, -1, 2 },
  { STFL_REDUCE, 38, -1, 2 },
  { STFL_REDUCE, 41, -1, 2 },
  { STFL_REDUCE, 40, -1, 2 },
  { STFL_REDUCE, 43, -1, 2 },
  { STFL_REDUCE, 42, -1, 2 },
  { STFL_REDUCE, 45, -1, 2 },
  { STFL_REDUCE, 44, -1, 2 },
  { STFL_REDUCE, 47, -1, 2 },
  { STFL_REDUCE, 46, -1, 2 },
  { STFL_REDUCE, 121, -1, 2 },
  { STFL_REDUCE, 120, -1, 2 },
  { STFL_REDUCE, 115, -1, 2 },
  { STFL_REDUCE, 114, -1, 2 },
  { STFL_REDUCE, 119, -1, 2 },
  { STFL_REDUCE, 118, -1, 2 },
  { STFL_REDUCE, 113, -1, 2 },
  { STFL_REDUCE, 112, -1, 2 },
  { STFL_REDUCE, 103, -1, 2 },
  { STFL_REDUCE, 102, -1, 2 },
  { STFL_REDUCE, 99, -1, 2 },
  { STFL_REDUCE, 98, -1, 2 },
  { STFL_REDUCE, 107, -1, 2 },
  { STFL_REDUCE, 106, -1, 2 },
  { STFL_REDUCE, 105, -1, 2 },
  { STFL_REDUCE, 104, -1, 2 },
  { STFL_REDUCE, 101, -1, 2 },
  { STFL_REDUCE, 100, -1, 2 },
  { STFL_REDUCE, 127, -1, 2 },
  { STFL_REDUCE, 126, -1, 2 },
  { STFL_REDUCE, 129, -1, 2 },
  { STFL_REDUCE, 128, -1, 2 },
  { STFL_REDUCE, 131, -1, 2 },
  { STFL_REDUCE, 130, -1, 2 },
  { STFL_REDUCE, 133, -1, 2 },
  { STFL_REDUCE, 132, -1, 2 },
  { STFL_REDUCE, 135, -1, 2 },
  { STFL_REDUCE, 134, -1, 2 },
  { STFL_REDUCE, 125, -1, 2 },
  { STFL_REDUCE, 124, -1, 2 },
  { STFL_REDUCE, 141, -1, 2 },
  { STFL_REDUCE, 140, -1, 2 },
  { STFL_REDUCE, 143, -1, 2 },
  { STFL_REDUCE, 142, -1, 2 },
  { STFL_REDUCE, 123, -1, 2 },
  { STFL_REDUCE, 122, -1, 2 },
  { STFL_REDUCE, 145, -1, 2 },
  { STFL_REDUCE, 144, -1, 2 },
  { STFL_REDUCE, 147, -1, 2 },
  { STFL_REDUCE, 146, -1, 2 },
  { STFL_REDUCE, 149, -1, 2 },
  { STFL_REDUCE, 148, -1, 2 },
  { STFL_REDUCE, 151, -1, 2 },
  { STFL_REDUCE, 150, -1, 2 },
  { STFL_REDUCE, 153, -1, 2 },
  { STFL_REDUCE, 152, -1, 2 },
  { STFL_REDUCE, 155, -1, 2 },
  { STFL_REDUCE, 154, -1, 2 },
  { STFL_REDUCE, 157, -1, 2 },
  { STFL_REDUCE, 156, -1, 2 },
  { STFL_REDUCE, 159, -1, 2 },
  { STFL_REDUCE, 158, -1, 2 },
  { STFL_REDUCE, 65, -1, 2 },
  { STFL_REDUCE, 64, -1, 2 },
  { STFL_REDUCE, 67, -1, 2 },
  { STFL_REDUCE, 66, -1, 2 },
  { STFL_REDUCE, 69, -1, 2 },
  { STFL_REDUCE, 68, -1, 2 },
  { STFL_REDUCE, 71, -1, 2 },
  { STFL_REDUCE, 70, -1, 2 },
  { STFL_REDUCE, 73, -1, 2 },
  { STFL_REDUCE, 72, -1, 2 },
  { STFL_REDUCE, 75, -1, 2 },
  { STFL_REDUCE, 74, -1, 2 },
  { STFL_REDUCE, 77, -1, 2 },
  { STFL_REDUCE, 76, -1, 2 },
  { STFL_REDUCE, 79, -1, 2 },
  { STFL_REDUCE, 78, -1, 2 },
  { STFL_REDUCE, 81, -1, 2 },
  { STFL_REDUCE, 80, -1, 2 },
  { STFL_REDUCE, 83, -1, 2 },
  { STFL_REDUCE, 82, -1, 2 },
  { STFL_REDUCE, 85, -1, 2 },
  { STFL_REDUCE, 84, -1, 2 },
  { STFL_REDUCE, 87, -1, 2 },
  { STFL_REDUCE, 86, -1, 2 },
  { STFL_REDUCE, 89, -1, 2 },
  { STFL_REDUCE, 88, -1, 2 },
  { STFL_REDUCE, 91, -1, 2 },
  { STFL_REDUCE, 90, -1, 2 },
  { STFL_REDUCE, 93, -1, 2 },
  { STFL_REDUCE, 92, -1, 2 },
  { STFL_REDUCE, 95, -1, 2 },
  { STFL_REDUCE, 94, -1, 2 },
  { STFL_REDUCE, 117, -1, 2 },
  { STFL_REDUCE, 116, -1, 2 },
  { STFL_REDUCE, 111, -1, 2 },
  { STFL_REDUCE, 110, -1, 2 },
  { STFL_REDUCE, 109, -1, 2 },
  { STFL_REDUCE, 108, -1, 2 },
  { STFL_REDUCE, 97, -1, 2 },
  { STFL_REDUCE, 96, -1, 2 },
  { STFL_REDUCE, 10, -1, 2 },
  { STFL_REDUCE, 163, -1, 2 },
  { STFL_REDUCE, 162, -1, 2 },
  { STFL_REDUCE, 161, -1, 2 },
  { STFL_REDUCE, 14, -1, 2 }
};
static int rule_action(unsigned short rule) {
  switch (rule) {
    default:
	  CMD_ERROR("Unexpected Rule in rule_action");
    case 0:
	  /* &start */
	  nterm_shift(0, 0, PP(0,P(1,tsp)));
	  return(1);
    case 1:
	  /* &start : &commands Quit * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { msg(0,"Shutting down"); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(1, 1, PP(0,P(3,tsp)));
	  return(0);
    case 2:
	  /* &start : &commands &&Exit */
	  nterm_shift(1, 2, PP(0,P(0,P(1,tsp))));
	  return(0);
    case 3:
	  /* &&Exit : Exit * */
	  #ifdef CLIENT_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { cgc_forwarding = 0; }
	  #endif
	  nterm_shift(3, 3, PP(3,tsp));
	  return(0);
    case 4:
	  /* &commands : */
	  nterm_shift(2, 4, PP(1,tsp));
	  return(0);
    case 5:
	  /* &commands : &commands &command */
	  nterm_shift(2, 5, PP(0,P(0,P(1,tsp))));
	  return(0);
    case 6:
	  /* &command : * */
	  nterm_shift(4, 6, PP(2,tsp));
	  return(0);
    case 7:
	  /* &command : Telemetry &tm_cmd */
	  nterm_shift(4, 7, PP(1,P(1,tsp)));
	  return(0);
    case 8:
	  /* &command : Log %s ( Enter String to Log to Memo ) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    {}
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 8, PP(4,tsp));
	  return(0);
    case 9:
	  /* &tm_cmd : Start * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_DG.Turf( "TMc\n" ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(5, 9, PP(3,tsp));
	  return(0);
    case 10:
	  /* &tm_cmd : Single Step * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_DG.Turf( "TMs\n" ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(5, 10, PP(4,tsp));
	  return(0);
    case 11:
	  /* &command : Savelog %s (Enter Log Message) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { write_savelog(V(2,tsp).vu00); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 11, PP(4,tsp));
	  return(0);
    case 12:
	  /* &command : Request Restart * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { write_restart(); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 12, PP(4,tsp));
	  return(0);
    case 13:
	  /* &command : &HFEMScmdset */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_dccc.Turf( "D%d\n", V(1,tsp).vu04 ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 13, PP(0,P(1,tsp)));
	  return(0);
    case 14:
	  /* &command : Soldrv select mode %d (Enter Mode Number) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_SoldrvA.Turf("S%d\n", V(2,tsp).vu01 ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 14, PP(6,tsp));
	  return(0);
    case 15:
	  /* &command : Set &daspt_cmd %lf (Enter Setpoint Value in Volts) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    {
		  double N = V(2,tsp).vu02 * 409.6;
		  unsigned short bits;
		  if ( N > 4095. ) bits = 4095;
		  else if ( N < 0 ) bits = 0;
		  else bits = (unsigned short)N;
		  sbwr(V(3,tsp).vu03,bits);
	    }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 15, PP(1,P(3,tsp)));
	  return(0);
    case 16:
	  /* &daspt_cmd : Pman setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = Pman_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 16, PP(3,tsp));
	  return(0);
    case 17:
	  /* &daspt_cmd : PrCO2p setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = PrCO2p_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 17, PP(3,tsp));
	  return(0);
    case 18:
	  /* &daspt_cmd : FlCO2p setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = FlCO2p_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 18, PP(3,tsp));
	  return(0);
    case 19:
	  /* &daspt_cmd : PrCO2e1 setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = PrCO2e1_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 19, PP(3,tsp));
	  return(0);
    case 20:
	  /* &daspt_cmd : PrCO2e2 setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = PrCO2e2_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 20, PP(3,tsp));
	  return(0);
    case 21:
	  /* &daspt_cmd : PrCO setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = PrCO_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 21, PP(3,tsp));
	  return(0);
    case 22:
	  /* &daspt_cmd : fcNO_NOx setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = fcNO_NOx_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 22, PP(3,tsp));
	  return(0);
    case 23:
	  /* &daspt_cmd : fcNO2_NOx setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = fcNO2_NOx_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 23, PP(3,tsp));
	  return(0);
    case 24:
	  /* &daspt_cmd : fc_CO2e setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = fc_CO2e_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 24, PP(3,tsp));
	  return(0);
    case 25:
	  /* &daspt_cmd : fcNO_NOy setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = fcNO_NOy_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 25, PP(3,tsp));
	  return(0);
    case 26:
	  /* &daspt_cmd : fcEff_NOy setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = fcEff_NOy_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 26, PP(3,tsp));
	  return(0);
    case 27:
	  /* &daspt_cmd : fcZer_NOy setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = fcZer_NOy_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 27, PP(3,tsp));
	  return(0);
    case 28:
	  /* &daspt_cmd : FlNOx setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = FlNOx_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 28, PP(3,tsp));
	  return(0);
    case 29:
	  /* &daspt_cmd : FlNOy setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = FlNOy_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 29, PP(3,tsp));
	  return(0);
    case 30:
	  /* &daspt_cmd : FlCO2e3 setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = FlCO2e3_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 30, PP(3,tsp));
	  return(0);
    case 31:
	  /* &daspt_cmd : FlCO setpoint */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu03 = FlCO_SP_Address; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(7, 31, PP(3,tsp));
	  return(0);
    case 32:
	  /* &HFEMScmdset : Solenoid Lvl1 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 0; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 32, PP(5,tsp));
	  return(0);
    case 33:
	  /* &HFEMScmdset : Solenoid Lvl1 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 1 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 33, PP(5,tsp));
	  return(0);
    case 34:
	  /* &HFEMScmdset : Solenoid Lvl2 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 2 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 34, PP(5,tsp));
	  return(0);
    case 35:
	  /* &HFEMScmdset : Solenoid Lvl2 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 3 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 35, PP(5,tsp));
	  return(0);
    case 36:
	  /* &HFEMScmdset : Solenoid Lvl3 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 4 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 36, PP(5,tsp));
	  return(0);
    case 37:
	  /* &HFEMScmdset : Solenoid Lvl3 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 5 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 37, PP(5,tsp));
	  return(0);
    case 38:
	  /* &HFEMScmdset : Solenoid Lvl4 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 6 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 38, PP(5,tsp));
	  return(0);
    case 39:
	  /* &HFEMScmdset : Solenoid Lvl4 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 7 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 39, PP(5,tsp));
	  return(0);
    case 40:
	  /* &HFEMScmdset : Solenoid Lvl5 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 8 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 40, PP(5,tsp));
	  return(0);
    case 41:
	  /* &HFEMScmdset : Solenoid Lvl5 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 9 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 41, PP(5,tsp));
	  return(0);
    case 42:
	  /* &HFEMScmdset : Solenoid Lvl6 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 10 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 42, PP(5,tsp));
	  return(0);
    case 43:
	  /* &HFEMScmdset : Solenoid Lvl6 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 11 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 43, PP(5,tsp));
	  return(0);
    case 44:
	  /* &HFEMScmdset : Solenoid Lvl7 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 12 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 44, PP(5,tsp));
	  return(0);
    case 45:
	  /* &HFEMScmdset : Solenoid Lvl7 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 13 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 45, PP(5,tsp));
	  return(0);
    case 46:
	  /* &HFEMScmdset : Solenoid Lvl8 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 14 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 46, PP(5,tsp));
	  return(0);
    case 47:
	  /* &HFEMScmdset : Solenoid Lvl8 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 15 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 47, PP(5,tsp));
	  return(0);
    case 48:
	  /* &HFEMScmdset : Solenoid eCO2cal_on ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 16 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 48, PP(5,tsp));
	  return(0);
    case 49:
	  /* &HFEMScmdset : Solenoid eCO2cal_on OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 17 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 49, PP(5,tsp));
	  return(0);
    case 50:
	  /* &HFEMScmdset : Solenoid CO2add1 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 18 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 50, PP(5,tsp));
	  return(0);
    case 51:
	  /* &HFEMScmdset : Solenoid CO2add1 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 19 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 51, PP(5,tsp));
	  return(0);
    case 52:
	  /* &HFEMScmdset : Solenoid CO2add2 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 20 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 52, PP(5,tsp));
	  return(0);
    case 53:
	  /* &HFEMScmdset : Solenoid CO2add2 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 21 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 53, PP(5,tsp));
	  return(0);
    case 54:
	  /* &HFEMScmdset : Solenoid CO_smpl ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 22 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 54, PP(5,tsp));
	  return(0);
    case 55:
	  /* &HFEMScmdset : Solenoid CO_smpl OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 23 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 55, PP(5,tsp));
	  return(0);
    case 56:
	  /* &HFEMScmdset : Solenoid CO_cal1 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 24 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 56, PP(5,tsp));
	  return(0);
    case 57:
	  /* &HFEMScmdset : Solenoid CO_cal1 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 25 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 57, PP(5,tsp));
	  return(0);
    case 58:
	  /* &HFEMScmdset : Solenoid CO_cal2 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 26 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 58, PP(5,tsp));
	  return(0);
    case 59:
	  /* &HFEMScmdset : Solenoid CO_cal2 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 27 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 59, PP(5,tsp));
	  return(0);
    case 60:
	  /* &HFEMScmdset : Solenoid CO_zer ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 28 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 60, PP(5,tsp));
	  return(0);
    case 61:
	  /* &HFEMScmdset : Solenoid CO_zer OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 29 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 61, PP(5,tsp));
	  return(0);
    case 62:
	  /* &HFEMScmdset : Solenoid eff_Hg ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 30 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 62, PP(5,tsp));
	  return(0);
    case 63:
	  /* &HFEMScmdset : Solenoid eff_Hg OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 31 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 63, PP(5,tsp));
	  return(0);
    case 64:
	  /* &HFEMScmdset : Solenoid SpCmd_17 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 32 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 64, PP(5,tsp));
	  return(0);
    case 65:
	  /* &HFEMScmdset : Solenoid SpCmd_17 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 33 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 65, PP(5,tsp));
	  return(0);
    case 66:
	  /* &HFEMScmdset : Solenoid SpCmd_18 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 34 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 66, PP(5,tsp));
	  return(0);
    case 67:
	  /* &HFEMScmdset : Solenoid SpCmd_18 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 35 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 67, PP(5,tsp));
	  return(0);
    case 68:
	  /* &HFEMScmdset : Solenoid SpCmd_19 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 36 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 68, PP(5,tsp));
	  return(0);
    case 69:
	  /* &HFEMScmdset : Solenoid SpCmd_19 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 37 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 69, PP(5,tsp));
	  return(0);
    case 70:
	  /* &HFEMScmdset : Solenoid SpCmd_20 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 38 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 70, PP(5,tsp));
	  return(0);
    case 71:
	  /* &HFEMScmdset : Solenoid SpCmd_20 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 39 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 71, PP(5,tsp));
	  return(0);
    case 72:
	  /* &HFEMScmdset : Solenoid SpCmd_21 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 40 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 72, PP(5,tsp));
	  return(0);
    case 73:
	  /* &HFEMScmdset : Solenoid SpCmd_21 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 41 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 73, PP(5,tsp));
	  return(0);
    case 74:
	  /* &HFEMScmdset : Solenoid SpCmd_22 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 42 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 74, PP(5,tsp));
	  return(0);
    case 75:
	  /* &HFEMScmdset : Solenoid SpCmd_22 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 43 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 75, PP(5,tsp));
	  return(0);
    case 76:
	  /* &HFEMScmdset : Solenoid SpCmd_23 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 44 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 76, PP(5,tsp));
	  return(0);
    case 77:
	  /* &HFEMScmdset : Solenoid SpCmd_23 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 45 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 77, PP(5,tsp));
	  return(0);
    case 78:
	  /* &HFEMScmdset : Solenoid SpCmd_24 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 46 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 78, PP(5,tsp));
	  return(0);
    case 79:
	  /* &HFEMScmdset : Solenoid SpCmd_24 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 47 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 79, PP(5,tsp));
	  return(0);
    case 80:
	  /* &HFEMScmdset : Solenoid SpCmd_25 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 48 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 80, PP(5,tsp));
	  return(0);
    case 81:
	  /* &HFEMScmdset : Solenoid SpCmd_25 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 49 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 81, PP(5,tsp));
	  return(0);
    case 82:
	  /* &HFEMScmdset : Solenoid SpCmd_26 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 50 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 82, PP(5,tsp));
	  return(0);
    case 83:
	  /* &HFEMScmdset : Solenoid SpCmd_26 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 51 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 83, PP(5,tsp));
	  return(0);
    case 84:
	  /* &HFEMScmdset : Solenoid SpCmd_27 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 52 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 84, PP(5,tsp));
	  return(0);
    case 85:
	  /* &HFEMScmdset : Solenoid SpCmd_27 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 53 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 85, PP(5,tsp));
	  return(0);
    case 86:
	  /* &HFEMScmdset : Solenoid SpCmd_28 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 54 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 86, PP(5,tsp));
	  return(0);
    case 87:
	  /* &HFEMScmdset : Solenoid SpCmd_28 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 55 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 87, PP(5,tsp));
	  return(0);
    case 88:
	  /* &HFEMScmdset : Solenoid SpCmd_29 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 56 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 88, PP(5,tsp));
	  return(0);
    case 89:
	  /* &HFEMScmdset : Solenoid SpCmd_29 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 57 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 89, PP(5,tsp));
	  return(0);
    case 90:
	  /* &HFEMScmdset : Solenoid SpCmd_30 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 58 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 90, PP(5,tsp));
	  return(0);
    case 91:
	  /* &HFEMScmdset : Solenoid SpCmd_30 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 59 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 91, PP(5,tsp));
	  return(0);
    case 92:
	  /* &HFEMScmdset : Solenoid SpCmd_31 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 60 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 92, PP(5,tsp));
	  return(0);
    case 93:
	  /* &HFEMScmdset : Solenoid SpCmd_31 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 61 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 93, PP(5,tsp));
	  return(0);
    case 94:
	  /* &HFEMScmdset : Solenoid SpCmd_32 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 62 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 94, PP(5,tsp));
	  return(0);
    case 95:
	  /* &HFEMScmdset : Solenoid SpCmd_32 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 63 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 95, PP(5,tsp));
	  return(0);
    case 96:
	  /* &HFEMScmdset : Solenoid zNOy_Hg ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 64 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 96, PP(5,tsp));
	  return(0);
    case 97:
	  /* &HFEMScmdset : Solenoid zNOy_Hg OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 65 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 97, PP(5,tsp));
	  return(0);
    case 98:
	  /* &HFEMScmdset : Solenoid NO_NOy_on ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 66 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 98, PP(5,tsp));
	  return(0);
    case 99:
	  /* &HFEMScmdset : Solenoid NO_NOy_on OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 67 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 99, PP(5,tsp));
	  return(0);
    case 100:
	  /* &HFEMScmdset : Solenoid NPN_on ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 68 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 100, PP(5,tsp));
	  return(0);
    case 101:
	  /* &HFEMScmdset : Solenoid NPN_on OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 69 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 101, PP(5,tsp));
	  return(0);
    case 102:
	  /* &HFEMScmdset : Solenoid NO_NOy_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 70 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 102, PP(5,tsp));
	  return(0);
    case 103:
	  /* &HFEMScmdset : Solenoid NO_NOy_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 71 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 103, PP(5,tsp));
	  return(0);
    case 104:
	  /* &HFEMScmdset : Solenoid NPN_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 72 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 104, PP(5,tsp));
	  return(0);
    case 105:
	  /* &HFEMScmdset : Solenoid NPN_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 73 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 105, PP(5,tsp));
	  return(0);
    case 106:
	  /* &HFEMScmdset : Solenoid NOy_eff_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 74 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 106, PP(5,tsp));
	  return(0);
    case 107:
	  /* &HFEMScmdset : Solenoid NOy_eff_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 75 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 107, PP(5,tsp));
	  return(0);
    case 108:
	  /* &HFEMScmdset : Solenoid zNOy_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 76 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 108, PP(5,tsp));
	  return(0);
    case 109:
	  /* &HFEMScmdset : Solenoid zNOy_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 77 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 109, PP(5,tsp));
	  return(0);
    case 110:
	  /* &HFEMScmdset : Solenoid zNOx_Hg ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 78 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 110, PP(5,tsp));
	  return(0);
    case 111:
	  /* &HFEMScmdset : Solenoid zNOx_Hg OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 79 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 111, PP(5,tsp));
	  return(0);
    case 112:
	  /* &HFEMScmdset : Solenoid NO_NOx_on ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 80 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 112, PP(5,tsp));
	  return(0);
    case 113:
	  /* &HFEMScmdset : Solenoid NO_NOx_on OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 81 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 113, PP(5,tsp));
	  return(0);
    case 114:
	  /* &HFEMScmdset : Solenoid NO2_on ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 82 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 114, PP(5,tsp));
	  return(0);
    case 115:
	  /* &HFEMScmdset : Solenoid NO2_on OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 83 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 115, PP(5,tsp));
	  return(0);
    case 116:
	  /* &HFEMScmdset : Solenoid zNOx_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 84 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 116, PP(5,tsp));
	  return(0);
    case 117:
	  /* &HFEMScmdset : Solenoid zNOx_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 85 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 117, PP(5,tsp));
	  return(0);
    case 118:
	  /* &HFEMScmdset : Solenoid NO_NOx_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 86 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 118, PP(5,tsp));
	  return(0);
    case 119:
	  /* &HFEMScmdset : Solenoid NO_NOx_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 87 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 119, PP(5,tsp));
	  return(0);
    case 120:
	  /* &HFEMScmdset : Solenoid NO2_add ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 88 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 120, PP(5,tsp));
	  return(0);
    case 121:
	  /* &HFEMScmdset : Solenoid NO2_add OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 89 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 121, PP(5,tsp));
	  return(0);
    case 122:
	  /* &HFEMScmdset : Solenoid Shutter ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 90 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 122, PP(5,tsp));
	  return(0);
    case 123:
	  /* &HFEMScmdset : Solenoid Shutter OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 91 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 123, PP(5,tsp));
	  return(0);
    case 124:
	  /* &HFEMScmdset : Solenoid pCO2_smpl ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 92 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 124, PP(5,tsp));
	  return(0);
    case 125:
	  /* &HFEMScmdset : Solenoid pCO2_smpl OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 93 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 125, PP(5,tsp));
	  return(0);
    case 126:
	  /* &HFEMScmdset : Solenoid pCO2_cal1 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 94 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 126, PP(5,tsp));
	  return(0);
    case 127:
	  /* &HFEMScmdset : Solenoid pCO2_cal1 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 95 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 127, PP(5,tsp));
	  return(0);
    case 128:
	  /* &HFEMScmdset : Solenoid pCO2_cal2 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 96 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 128, PP(5,tsp));
	  return(0);
    case 129:
	  /* &HFEMScmdset : Solenoid pCO2_cal2 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 97 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 129, PP(5,tsp));
	  return(0);
    case 130:
	  /* &HFEMScmdset : Solenoid pCO2_cal3 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 98 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 130, PP(5,tsp));
	  return(0);
    case 131:
	  /* &HFEMScmdset : Solenoid pCO2_cal3 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 99 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 131, PP(5,tsp));
	  return(0);
    case 132:
	  /* &HFEMScmdset : Solenoid pCO2_cala ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 100 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 132, PP(5,tsp));
	  return(0);
    case 133:
	  /* &HFEMScmdset : Solenoid pCO2_cala OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 101 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 133, PP(5,tsp));
	  return(0);
    case 134:
	  /* &HFEMScmdset : Solenoid pCO2_calR ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 102 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 134, PP(5,tsp));
	  return(0);
    case 135:
	  /* &HFEMScmdset : Solenoid pCO2_calR OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 103 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 135, PP(5,tsp));
	  return(0);
    case 136:
	  /* &HFEMScmdset : Solenoid Hub_sp1 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 104 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 136, PP(5,tsp));
	  return(0);
    case 137:
	  /* &HFEMScmdset : Solenoid Hub_sp1 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 105 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 137, PP(5,tsp));
	  return(0);
    case 138:
	  /* &HFEMScmdset : Solenoid Hub_sp2 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 106 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 138, PP(5,tsp));
	  return(0);
    case 139:
	  /* &HFEMScmdset : Solenoid Hub_sp2 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 107 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 139, PP(5,tsp));
	  return(0);
    case 140:
	  /* &HFEMScmdset : Solenoid Shk_sp1 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 108 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 140, PP(5,tsp));
	  return(0);
    case 141:
	  /* &HFEMScmdset : Solenoid Shk_sp1 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 109 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 141, PP(5,tsp));
	  return(0);
    case 142:
	  /* &HFEMScmdset : Solenoid Shk_sp2 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 110 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 142, PP(5,tsp));
	  return(0);
    case 143:
	  /* &HFEMScmdset : Solenoid Shk_sp2 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 111 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 143, PP(5,tsp));
	  return(0);
    case 144:
	  /* &HFEMScmdset : Solenoid Sol_41 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 112 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 144, PP(5,tsp));
	  return(0);
    case 145:
	  /* &HFEMScmdset : Solenoid Sol_41 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 113 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 145, PP(5,tsp));
	  return(0);
    case 146:
	  /* &HFEMScmdset : Solenoid Sol_42 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 114 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 146, PP(5,tsp));
	  return(0);
    case 147:
	  /* &HFEMScmdset : Solenoid Sol_42 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 115 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 147, PP(5,tsp));
	  return(0);
    case 148:
	  /* &HFEMScmdset : Solenoid Sol_43 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 116 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 148, PP(5,tsp));
	  return(0);
    case 149:
	  /* &HFEMScmdset : Solenoid Sol_43 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 117 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 149, PP(5,tsp));
	  return(0);
    case 150:
	  /* &HFEMScmdset : Solenoid Sol_44 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 118 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 150, PP(5,tsp));
	  return(0);
    case 151:
	  /* &HFEMScmdset : Solenoid Sol_44 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 119 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 151, PP(5,tsp));
	  return(0);
    case 152:
	  /* &HFEMScmdset : Solenoid Sol_45 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 120 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 152, PP(5,tsp));
	  return(0);
    case 153:
	  /* &HFEMScmdset : Solenoid Sol_45 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 121 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 153, PP(5,tsp));
	  return(0);
    case 154:
	  /* &HFEMScmdset : Solenoid Sol_46 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 122 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 154, PP(5,tsp));
	  return(0);
    case 155:
	  /* &HFEMScmdset : Solenoid Sol_46 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 123 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 155, PP(5,tsp));
	  return(0);
    case 156:
	  /* &HFEMScmdset : Solenoid Sol_47 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 124 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 156, PP(5,tsp));
	  return(0);
    case 157:
	  /* &HFEMScmdset : Solenoid Sol_47 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 125 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 157, PP(5,tsp));
	  return(0);
    case 158:
	  /* &HFEMScmdset : Solenoid Sol_48 ON * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 126 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 158, PP(5,tsp));
	  return(0);
    case 159:
	  /* &HFEMScmdset : Solenoid Sol_48 OFF * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu04 = 127 ; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(6, 159, PP(5,tsp));
	  return(0);
    case 160:
	  /* &command : PhRTG &phrtg_cmd */
	  nterm_shift(4, 160, PP(1,P(1,tsp)));
	  return(0);
    case 161:
	  /* &phrtg_cmd : File %w (Enter Word Terminated by <space>) %d (Enter Integer (Decimal: 123, Hex: 0x123F, Octal: 0123)) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_phrtg.Turf( "MLF %s %d\n", V(3,tsp).vu00, V(2,tsp).vu01 ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(8, 161, PP(5,tsp));
	  return(0);
    case 162:
	  /* &phrtg_cmd : Datum %w (Enter Word Terminated by <space>) %s (Enter Text Terminated by <CR>) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_phrtg.Turf( "TR %s %s\n", V(3,tsp).vu00, V(2,tsp).vu00 ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(8, 162, PP(5,tsp));
	  return(0);
    case 163:
	  /* &command : getcon end session %w (Enter Session ID) * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { if_getcon.Turf("%s\n", V(2,tsp).vu00 ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 163, PP(6,tsp));
	  return(0);
    case 164:
	  /* &command : CMDENBL &on_off * */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { set_cmdenbl( V(2,tsp).vu05 ); }
	  #else
	    saw_server_action = 1;
	  #endif
	  nterm_shift(4, 164, PP(1,P(2,tsp)));
	  return(0);
    case 165:
	  /* &on_off : On */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu05 = 1; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(9, 165, PP(2,tsp));
	  return(0);
    case 166:
	  /* &on_off : Off */
	  #ifdef SERVER_ACTIONS
	    if (ioflags & IOF_EXECUTE)
	    { V(0,tsp).vu05 = 0; }
	  #else
	    saw_server_action = 1;
	  #endif
	  vsp++;
	  nterm_shift(9, 166, PP(2,tsp));
	  return(0);
  }
}

#ifdef QNX_CONS
  #include <sys/stat.h>

static char con_clr[] = {
  62, PROMPT_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR,
  32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR, 32, CMD_ATTR
};

/* con_col is the current position of the cursor
 * con_high is the highest column that is currently non-blank
 * con_low is the lowest column that should be blank
 */
static int con_col, con_high, con_low;
static char con_buf[CG_IBUF_SIZE*2+2];
static int con_nchars = 0;
#ifndef NO_PROMPTS
  static char *con_cur_prmt, *con_new_prmt;
#endif

/* con_puts() outputs n bytes from buf at the specified byte_offset
   of the specified row on all defined consoles.
   row_offset of 0 is the typing line and 1 is the prompt line.
   byte_offset starts at 0 and advances 2 for each char.
   n is now n_chars, byte_offset changes to char_offset
*/
static void
con_puts(char *buf, int row_offset, int char_offset, int n_chars) {
  int i;
  struct _console_ctrl *cc;
  
  for (i = 0; i < MAXCONS; i++) {
    if (nlcon_ctrl(i, &cc)) {
      nl_con_def *nlcd = &nl_cons[i];
      if ( char_offset < nlcd->columns ) {
	int crow, ccol, out_offset;
	int nc;

	if ( char_offset + n_chars > nlcd->columns )
	  nc = nlcd->columns - char_offset;
	else nc = n_chars;
	crow = nlcd->rows-2;
	ccol = con_col;
	out_offset =
	  (nlcd->rows - 2 + row_offset) * nlcd->columns * 2 + char_offset*2;
	console_write(cc, 0, out_offset, buf, nc*2,
			  &crow, &ccol, NULL);
      }
    }
  }
}

static void con_update(void) {
  #ifndef NO_PROMPTS
	if (con_cur_prmt != con_new_prmt && (ioflags & IOF_INTERACTIVE))
	  con_puts(con_cur_prmt = con_new_prmt, 1, 0, 80);
  #endif
  if (ioflags & IOF_UPDATE) {
    if (con_col == 79)
      con_puts(con_buf+con_nchars-78*2, 0, 1, 78);
    else if (con_col == 1)
      con_puts(con_clr, 0, 0, 80);
    else {
      if (con_low < con_col) {
	int nchars;
	nchars = (con_col - con_low);
	con_puts(con_buf+con_nchars-(nchars*2), 0, con_low, nchars);
      }
      if (con_col < con_high) {
	int nchars;
	nchars = (con_high - con_col);
	con_puts(con_clr+2, 0, con_col, nchars);
      }
    }
    con_low = con_high = con_col;
    ioflags &= ~IOF_UPDATE;
  }
}

#ifndef NO_PROMPTS
  static void con_prompt(char *c) {
    con_new_prmt = c;
  }
#endif

static void con_dispc(char c) {
  con_buf[con_nchars++] = c;
  con_buf[con_nchars++] = CMD_ATTR;
  if (con_col < 79) con_col++;
  ioflags |= IOF_UPDATE;
}

static void con_undispc(void) {
  con_nchars -= 2;
  if (con_nchars < 78*2 && --con_col < con_low)
	con_low = con_col;
  ioflags |= IOF_UPDATE;
}

static void con_cleanup( void ) {
  int i;
  struct _console_ctrl *cc;
  int row, col;
  
  for (i = 0; i < MAXCONS; i++) {
    if (nlcon_ctrl(i, &cc)) {
      nl_con_def *nlcd = &nl_cons[i];
      row = nlcd->rows - 1;
      col = nlcd->columns;
      console_write(cc, 0, 0, NULL, 0, &row, &col, NULL);
      write( nl_cons[i].fd, "\n", 1 );
    }
  }
}

#define FINAL_CLEANUP con_cleanup();

#endif	/* QNX_CONS */

#if PHOTON_INTERFACE
  static char nlph_buf[CG_IBUF_SIZE+1];
  static int nlph_nchars = 0;
  static const char *nlph_cur_prmt, *nlph_new_prmt;

  //define GETCH() nlph_getch() defined in nlphcmdclient
  static void nlph_dispc(char c) {
    assert(nlph_nchars <= CG_IBUF_SIZE);
    nlph_buf[nlph_nchars++] = c;
    nlph_buf[nlph_nchars] = '\0';
    ioflags |= IOF_UPDATE;
  }
  static void nlph_undispc(void) {
    assert(nlph_nchars > 0);
    nlph_buf[--nlph_nchars] = '\0';
    ioflags |= IOF_UPDATE;
  }
  static void nlph_clearline(void) {
    nlph_nchars = 0;
    nlph_buf[0] = '\0';
    ioflags |= IOF_UPDATE;
  }

  #ifndef NO_PROMPTS
    static void nlph_prompt(const char *c) {
      nlph_new_prmt = c;
    }
  #endif
  static void nlph_update(void) {
    if ( (ioflags & IOF_UPDATE)
	 || (nlph_cur_prmt != nlph_new_prmt &&
	     (ioflags & IOF_INTERACTIVE)) ) {
      nlph_update_cmdtext( nlph_buf, nlph_new_prmt );
      ioflags &= ~IOF_UPDATE;
    }
  }
#endif /* PHOTON_INTERFACE */

#if NCT_INTERFACE
  static int nct_win;
  static int nct_col;

  void nct_dispc(char c) {
    // simply stop displaying characters after
    // 80
    if ( nct_col < 80 )
      mvaddch( 0, nct_col, c);
    ++nct_col;
  }

  void nct_undispc(void) {
    if ( --nct_col < 80 ) {
      mvaddch( 0, nct_col, ' ');
      move( 0, nct_col );
    }
  }

  void nct_prompt(const char *text) {
    mvaddstr( 1, 0, text );
    clrtoeol();
    move( 0, nct_col );
  }
#endif /* NCT_INTERFACE */

#ifndef NO_PROMPTS
  static short cur_prompt = -1;

  static void new_prompt(short pn) {
    if (pn >= 0 && pn != cur_prompt) {
      if (cur_prompt < 0
	  || prompts[pn].txt_idx != prompts[cur_prompt].txt_idx)
	DISPLAY_PROMPT(prompts[pn].txt_idx);
      cur_prompt = pn;
    }
  }

  static void next_prompt(void) {
    if (cur_prompt >= 0)
      new_prompt(cur_prompt + prompts[cur_prompt].more);
  }
#else /* NO_PROMPTS */
  #define new_prompt(x)
  #define next_prompt()
#endif /* NO_PROMPTS */

#ifdef CMD_INTERACT_MODE
  static unsigned short command_getch(void) {
    unsigned short rv;
    
    UPDATE_OUTPUT;
    rv = GETCH();
    if (rv == 0) rv = 0xFF00 | GETCH();
    return(rv);
  }
#endif

#ifdef CMD_BATCH_MODE
  static char *cmd_input;
#endif

static unsigned short input(void) {
  unsigned short rv;
  
  if (ioflags & IOF_UNGOTNL) {
    rv = '\n';
    ioflags &= ~IOF_UNGOTNL;
  }
  #ifdef CMD_BATCH_MODE
    #ifdef CMD_INTERACT_MODE
      else if (cmd_input != NULL) {
    #else
      else {
	assert(cmd_input != NULL);
    #endif
	rv = *cmd_input;
	if (rv) cmd_input++;
      }
  #endif
  #ifdef CMD_INTERACT_MODE
    else rv = command_getch();
  #endif
  return(rv);
}

#define UNPUTNL { ioflags |= IOF_UNGOTNL; }

static void _shift(cg_token_type st, unsigned short val, short prev) {
  tsp++;
  if (tsp >= TSTACK_SIZE) { CMD_ERROR("Token Stack Overflow"); }
  tstack[tsp].state = st;
  tstack[tsp].prev = prev;
  tstack[tsp].value = val;
  #ifdef CLIENT
    tstack[tsp].saw_srvr = saw_server_action;
  #endif
  unshift_value = 0;
  #ifdef NEED_VALUES
    tstack[tsp].valpos = vsp;
  #endif
  tstack[tsp].reversible = 1;
}

static int unshift(void) {
  if (!tstack[tsp].reversible) return(0);
  do {
    #ifdef NEED_VALUES
      vsp = tstack[tsp].valpos;
    #endif
    #ifdef CLIENT
      saw_server_action = tstack[tsp].saw_srvr;
    #endif
    unshift_value = tstack[tsp].value;
  } while (tstack[tsp--].prev >= 0 && tstack[tsp].reversible);
  return(1);
}

/* This routine is used for both non_terminals and variables.
   The difference is that variables have .prev == -1 while
   non_terminals have real previous values set. Shifting for
   nts is relative to the previous state while variables shift
   relative to the current state. nt is zero for variables,
   non-zero for non-terminals.
*/
static void nterm_shift(cg_nonterm_type nt, unsigned short val, short prev) {
  short ntsp;

  ntsp = nt ? prev : tsp;
  ntsp = states[tstack[ntsp].state].nterm_offset;
  {
    cg_nonterm_type cnt;

    for (;;) {
      cnt = non_terminals[ntsp].nt;
      if (cnt == 0 || cnt == nt) break;
      ntsp++;
    }
    assert(cnt == nt);
  }
  _shift(non_terminals[ntsp].shift, val, prev);
}

#if defined VAR_s || defined VAR_w
  #define VAR_strings
#endif
#if defined VAR_d || defined VAR_ld || defined VAR_x || defined VAR_lx \
 || defined VAR_o || defined VAR_lo || defined VAR_f || defined VAR_lf
  #define VAR_numerics
#endif
#if defined VAR_strings && defined VAR_numerics
  #define VAR_both
#endif
#if defined VAR_strings || defined VAR_numerics
  #define VAR_some
#endif

#ifdef VAR_some
static int read_variable(short vartype, unsigned short n_chars) {
  unsigned short getword = 1;
  short c;
  char *text;
  
  #ifdef VAR_s
    if (vartype == VAR_s) getword = 0;
  #endif
  if ((ioflags & IOF_INTERACTIVE) && n_chars > 0) {
    RUBOUT;
    n_chars--;
  }
  do {
	c = input();
	switch (c) {
	  case 0:
		unshift_value = n_chars;
		return(0);
	  case KG_RUBOUT:
	  case KG_DEL:
		#ifdef CMD_BATCH_MODE
		  #ifdef CMD_INTERACT_MODE
			if (~(ioflags & IOF_INTERACTIVE))
		  #endif
			  return(1);
		#endif
		#ifdef CMD_INTERACT_MODE
		  if (n_chars > 0) {
			RUBOUT;
			n_chars--;
		  } else if (unshift()) return(0);
		  else REJECT_CHAR;
		  continue;
		#endif
	  case KG_TAB:
		next_prompt();
		continue;
	  case KG_ESCAPE:
		CANCEL_LINE;
	  case '\n':
	  case '\r':
		UNPUTNL;
		c = 0;
		break;
	  case ' ':
		if (getword) c = 0;
		break;
	  default:
		if (isprint(c) || c == 0) break;
		SPECIAL_CHAR_FUNC(c);
		continue;
	}
	
	/* We should only get here when we want to display a char. */
	ACCEPT_CHAR(c);
	n_chars++;
	
	if (c == 0) {
	  text = ibuf + ibufidx - n_chars;

	  #ifdef VAR_both
		switch (vartype) {
		  #ifdef VAR_w
			case VAR_w:
		  #endif
		  #ifdef VAR_s
			case VAR_s:
		  #endif
	  #endif /* VAR_both */
		  #ifdef VAR_strings
			vstack[vsp].VTP_STR = text;
		  #endif
	  #ifdef VAR_both
			continue;
		  default:
	  #endif
	  #ifdef VAR_numerics
			if (n_chars == 1) {
			  #if defined CMD_BATCH_MODE && defined CMD_INTERACT_MODES
				if (!(ioflags & IOF_INTERACTIVE))
			  #endif
			  #ifdef CMD_BATCH_MODE
				  return(1);
			  #endif
			  #ifdef CMD_INTERACT_MODE
				REJECT_CHAR;
				RUBOUT;
				ioflags &= ~IOF_UNGOTNL;
				n_chars--;
				c = '\b';
				continue;
			  #endif
			}
	  #endif
	  #ifdef VAR_both
		}
	  #endif /* VAR_both */
	  
	  #ifdef VAR_numerics
	  { char *ep; /* numeric vartypes: strings CONTINUE beyond here */
	  
		ep = ibuf + ibufidx - 1;
		switch (vartype) {
		  #ifdef VAR_d
			case VAR_d:
			  vstack[vsp].VTP_SHRT = (short) strtol(text, &ep, 0);
			  break;
		  #endif
		  #ifdef VAR_ld
			case VAR_ld:
			  vstack[vsp].VTP_LONG = strtol(text, &ep, 0);
			  break;
		  #endif
		  #ifdef VAR_x
			case VAR_x:
			  vstack[vsp].VTP_SHRT = (short) strtol(text, &ep, 16);
			  break;
		  #endif
		  #ifdef VAR_lx
			case VAR_lx:
			  vstack[vsp].VTP_LONG = strtol(text, &ep, 16);
			  break;
		  #endif
		  #ifdef VAR_o
			case VAR_o:
			  vstack[vsp].VTP_SHRT = (short) strtol(text, &ep, 8);
			  break;
		  #endif
		  #ifdef VAR_lo
			case VAR_lo:
			  vstack[vsp].VTP_LONG = strtol(text, &ep, 8);
			  break;
		  #endif
		  #ifdef VAR_f
			case VAR_f:
			  vstack[vsp].VTP_FLT = (float) strtod(text, &ep);
			  break;
		  #endif
		  #ifdef VAR_lf
			case VAR_lf:
			  vstack[vsp].VTP_DBL = strtod(text, &ep);
			  break;
		  #endif
		  default: CMD_ERROR("Unexpected vartype in read_variable");
		}
		assert(text <= ep && ep <= ibuf+ibufidx-1);
		if (*ep != '\0') {
		  #if defined CMD_BATCH_MODE && defined CMD_INTERACT_MODES
			if (!(ioflags & IOF_INTERACTIVE))
		  #endif
		  #ifdef CMD_BATCH_MODE
			return(1);
		  #endif
		  #ifdef CMD_INTERACT_MODE
			REJECT_CHAR;
			ioflags &= ~IOF_UNGOTNL;
			do {
			  RUBOUT;
			  n_chars--;
			} while (n_chars > 0 && ep < ibuf + ibufidx);
			c = '\b';
			continue;
		  #endif
		}
	  } /* numeric vartypes block */
	  #endif /* VAR_numerics */
	} /* (c==0) */
  } while (c != 0);
  vsp++;
  nterm_shift(0, n_chars, -1);
  return(0);
}
#endif /* VAR_some */

/* advance as far as is unambiguous, but not beyond EOW or newline.
   We accept EOW and display and store it, but we do not
   accept newline: it must be explicit. Returns TRUE if some
   advancing was actually done.
   for (;;) {
     if current char is EOW break;
	 if next is unambiguous and not newline {
	   display it
	   store it
	 } else break;
   }
*/
static int advance(unsigned short *triepos) {
  unsigned short ntp;
  
  if (iomode & IO_WORD) {
	ntp = *triepos;
	for (;;) {
	  if ((trie[ntp].code & 0x7F) == 0) break;
	  ntp += trie[ntp].next;
	  if ((trie[ntp].code & 0x80) == 0
		  || (trie[ntp].code & 0x7F) == '\n') break;
	}
	if (trie[ntp].code != 0x80) return(0);
  }
  ntp = *triepos;
  for (;;) {
	if ((trie[ntp].code & 0x7F) == 0) break;
	ntp += trie[ntp].next;
	if ((trie[ntp].code & 0x80) == 0
		|| (trie[ntp].code & 0x7F) == '\n') {
	  ntp -= trie[ntp].prev;
	  break;
	}
	ACCEPT_CHAR(trie[ntp].code & 0x7F); /* Could be 0 */
	ioflags &= ~IOF_NO_ADV;
  }
  if (ntp != *triepos) {
	*triepos = ntp;
	return(1);
  } else return(0);
}

#ifdef CMD_INTERACT_MODE
/* retreat returns 1 if we backed up out of the current state. */
static int retreat(unsigned short *triepos) {
  int once = 0;
  
  ioflags |= IOF_NO_ADV;
  do {
	if (trie[*triepos].code == T_ROOT) {
	  if (unshift()) return(1);
	  else if (!once) REJECT_CHAR;
	  return(0);
	}
	once = 1;
	RUBOUT;
	*triepos -= trie[*triepos].prev;
  } while ((iomode & IO_BACKSPACE)
		   && (trie[*triepos+trie[*triepos].next].code & 0x80));
  return(0);
}
#endif

/* read_words returns zero on success, non-zero if an unrecognized
   character is encountered.
*/
static int read_words(unsigned short trieroot, unsigned short trie_offset) {
  unsigned short triepos, ntp;
  int c, cl;
  
  triepos = trieroot + trie_offset;

  #ifdef CMD_INTERACT_MODE
	if ((ioflags & IOF_INTERACTIVE)
		&& trie[triepos].code != T_ROOT && retreat(&triepos))
	  return(0);
  #endif

  /* Now triepos points to the previous node. We must
     advance to next to find the first matching character.
	 First advance at the beginning if specified.
  */
  if (!(ioflags & IOF_NO_ADV)
	  && (iomode & IO_WORDSKIP)) advance(&triepos);

  for (;;) {
    /* When should we advance?
	    ALWAYS
	      while there is an unambiguous character not '\n'
	      0 translates to space
	    SPACE not now
	    ALWAYS | WORD
	      if unambiguous to EOW
    */
    if (!(ioflags & IOF_NO_ADV)
	    && (iomode & IO_ALWAYS)) advance(&triepos);
    if ((trie[triepos].code & 0x7F) == 0) break;
    c = input();
    switch (c) {
      case 0:
	    unshift_value = triepos - trieroot;
	    return(0);
      case KG_RUBOUT:
      case KG_DEL:
	    #ifdef CMD_BATCH_MODE
	      #ifdef CMD_INTERACT_MODE
		    if (~(ioflags & IOF_INTERACTIVE))
	      #endif
		      return(1);
	    #endif
	    #ifdef CMD_INTERACT_MODE
	      if (retreat(&triepos)) return(0);
	      continue;
	    #endif
      case ' ':
	    if ((iomode & IO_SPACE) && advance(&triepos)) continue;
	    c = 0;
	    break;
      case '\n':
      case '\r':
	    if ((iomode & IO_SPACE) && advance(&triepos)) {
	      UNPUTNL;
	      continue;
	    }
	    /* newlines are only OK at the root of a trie. Otherwise
	       we need to advance through EOW */
	    if (trie[triepos].code != T_ROOT) {
	      UNPUTNL;
	      c = 0;
	    } else c = '\n';
	    break;
      case KG_TAB:
	    next_prompt();
	    continue;
      case KG_ESCAPE:
	    CANCEL_LINE;
      default:
	if (isprint(c)) break;
	SPECIAL_CHAR_FUNC(c);
	continue;
    }
    cl = tolower(c);
    ntp = triepos + trie[triepos].next;
    do {
      if (tolower(T_CHAR(ntp)) == cl) {
	triepos = ntp;
	ntp = 0;
	break;
      }
    } while ((trie[ntp++].code & 0x80) == 0);
    if (ntp) {
      #ifdef CMD_BATCH_MODE
	#ifdef CMD_INTERACT_MODE
	  if (!(ioflags & IOF_INTERACTIVE))
	#endif
	return(1);
      #endif
      #ifdef CMD_INTERACT_MODE
	REJECT_CHAR;
	ioflags &= ~IOF_UNGOTNL;
      #endif
    } else if (c == '\n') {
      triepos += trie[triepos].next;
      DISPLAY_EOL
      UPDATE_OUTPUT;
      full_reduce = 1;
    } else {
      ACCEPT_CHAR(c); /* c could be \0 */
      ioflags &= ~IOF_NO_ADV;
    }
  }
  _shift(trie[triepos].next, triepos - trieroot, -1);
  return(0);
}

/* Returns non-zero if the root non-terminal is reduced */
static int reduce_rule(unsigned short rule) {
  unsigned short ntsp;
  
  /* rule_action is generated in output_rules().
	 It returns the non-zero if the root non-terminal is reduced.
  */
  { int oldresp, action_result;
    oldresp = set_response( 1 );
    action_result = rule_action(rule);
    set_response( oldresp );
    if ( action_result ) return(1);
  }
  if (full_reduce) { /* <move back to prev location +1> */
    tstack[tsp].reversible = 0;
    ntsp = tstack[tsp].prev+1;
    assert(ntsp <= tsp);
    if (ntsp < tsp) {
      #ifdef NEED_VALUES
	if (tstack[ntsp-1].valpos < tstack[tsp-1].valpos) {
	  if (vsp > tstack[tsp-1].valpos) {
		vsp = tstack[ntsp-1].valpos;
		vstack[vsp] = vstack[tstack[tsp-1].valpos];
		tstack[tsp].valpos = ++vsp;
	  } else tstack[tsp].valpos = vsp = tstack[ntsp].valpos;
	}
      #endif
      tstack[ntsp] = tstack[tsp];
      tsp = ntsp;
    }
  }
  return(0);
}

void cmd_init(void) {
  ioflags = IOF_UPDATE | IOF_EXECUTE | IOF_INTERACTIVE;
  iomode = IOMODE_INIT;
  #ifdef CMD_BATCH_MODE
    cmd_input = NULL;
  #endif
  tsp = -1;
  #ifdef NEED_VALUES
    vsp = 0;
  #endif
  _shift(0,0,-1);
  tstack[tsp].reversible = 0;
  full_reduce = 1;
}

static int cmd_exec(void) {
  state_type *st;
  tstack_type *stktop;
  cg_token_type cur_state;

  for (;;) {
    stktop = &tstack[tsp];
    cur_state = stktop->state;
    st = &states[cur_state];
    if (st->flag == STFL_REDUCE) {
      if (reduce_rule(st->offset)) {
	#ifdef CLIENT
	  cic_transmit(ibuf, ibufidx, saw_server_action);
	  saw_server_action = 0;
	#endif
	break;
      }
    } else {
      if (full_reduce) {
	#ifdef CLIENT
	  cic_transmit(ibuf, ibufidx, saw_server_action);
	  saw_server_action = 0;
	#endif
	CLEAR_DISPLAY_LINE;
	DISPLAY_INPUT_PROMPT
	ibufidx = 0;
	full_reduce = 0;
      }
      #ifdef CMD_BATCH_MODE
	if (!(ioflags & (IOF_INTERACTIVE|IOF_UNGOTNL))
		&& *cmd_input == '\0') {
	  UPDATE_OUTPUT;
	  return(0);
	}
      #endif
      assert(st->prompt >= 0);
      new_prompt(st->prompt);
      #ifdef VAR_some
	if (st->flag == STFL_VARIABLE) {
	  if (read_variable(st->offset, unshift_value))
	    return(CMDREP_SYNERR);
	} else
      #else
	assert(st->flag != STFL_VARIABLE);
      #endif
	if (read_words(st->offset, unshift_value))
	  return(CMDREP_SYNERR);
    }
  }
  CLEAR_DISPLAY_LINE;
  UPDATE_OUTPUT;
  return(CMDREP_QUIT);
}

#ifdef CMD_BATCH_MODE
  /* Parses the specified command, executing if test == 0.
     Returns non-zero if an error occurred. Possible errors:
       CMDREP_QUIT Command execution resulted in termination
		(not exactly an error: more a status indication)
       CMDREP_SYNERR - (CMDREP_EXECERR-1)
		    Syntax error. Error value minus 1000 is the
		    character position where the error occurred.
       >=CMDREP_EXECERR Execution error. Error code + CMDREP_EXECERR
  */
  int cmd_batch(char *cmd, int test) {
    short flaghold;
    short old_iomode;
    int retval;

    assert(cmd != NULL);
    assert(ioflags & IOF_INTERACTIVE);
    assert(cmd_input == NULL);
    old_iomode = iomode;
    iomode = 0;
    cmd_input = cmd;
    ioflags &= ~IOF_INTERACTIVE;
    flaghold = ioflags & IOF_EXECUTE;
    if (test) ioflags &= ~IOF_EXECUTE;
    else ioflags |= IOF_EXECUTE;
    retval = cmd_exec();
    if (retval == CMDREP_SYNERR) retval += (cmd_input - cmd);
    ioflags = (ioflags & ~IOF_EXECUTE) | flaghold | IOF_INTERACTIVE;
    iomode = old_iomode;
    cmd_input = NULL;
    return retval;
  }
#endif

#ifdef CMD_INTERACT_MODE
  void cmd_interact(void) {
    cmd_init();
    cmd_exec();
  }
#endif

void cmd_report(cmd_state *s) {
  s->state = tstack[tsp].state;
  s->value = unshift_value;
}

/* Compares the current command state to the designated structure
 * returning zero if the states match.
 */
int cmd_check(cmd_state *s) {
  return(s->state != tstack[tsp].state
	  || s->value != unshift_value);
}

#if defined( SERVER_ACTIONS )
  #if defined( SERVER_INIT )
    #include <string.h>
    #ifndef _NORTLIB_H_INCLUDED
      #error Must include nortlib.h
    #endif
    /* solp_init() returns a non-zero value only if there is a
       parsing error.
    */
    int solp_init(unsigned char selector, unsigned char ID, char *cmd) {
      int rv;

      cmd_init();
      rv = cmd_batch(cmd, 1);
      if (rv != 0) switch (CMDREP_TYPE(rv)) {
	case CMDREP_TYPE(CMDREP_QUIT):
	  nl_error(2, "Termination Command Illegal in a proxy");
	  nl_error(2, "%s", cmd);
	  break;
	case CMDREP_TYPE(CMDREP_SYNERR):
	  nl_error(2, "Syntax Error in Proxy");
	  nl_error(2, "%s", cmd);
	  nl_error(2, "%*s", rv - CMDREP_SYNERR, "^");
	  break;
	case CMDREP_TYPE(CMDREP_EXECERR):
	default:
	  nl_error(2, "Error %d parsing proxy command:");
	  nl_error(2, "%s", cmd);
	  break;
      }
      if (rv == 0) {
	ci_msg mymsg;
	int size;

	mymsg.msg_type = CMDINTERP_SEND_QUIET;
	strcpy(mymsg.prefix, "Proxy");
	size = strlen(cmd);
	if (size >= CMD_INTERP_MAX)
	  return(CMDREP_SYNERR + CMD_INTERP_MAX);
	strcpy(mymsg.command, cmd);
	/* add 1 for msg_type, and 1 for '\0' */
	size += CMD_PREFIX_MAX + 1 + 1;
	rv = set_response(1);
	Soldrv_set_proxy(selector, ID, &mymsg, size);
	set_response(rv);
	rv = 0;
      }
      return(rv);
    }
  #else
    void cis_initialize(void) {}
    void cis_terminate(void) {}
  #endif
#endif

#if defined (CLIENT) || defined (SERVER)

  #if PHOTON_INTERFACE
    static void *nlph_interact(void *arg) {
      do cmd_interact(); while ( cgc_forwarding != 0 );
      PtEnter(0);
      PtExit(0);
      return NULL;
    }
  #endif

  static void cmd_exit( void ) {
    const char *name;

    #if ! PHOTON_INTERFACE
      CLEAR_DISPLAY_LINE;
      UPDATE_OUTPUT;
    #endif
    #ifdef FINAL_CLEANUP
      FINAL_CLEANUP
    #endif
    name = getlogin();
    if (name == NULL) name = "NULL";
    nl_error(0, "Shutdown (%s)", name);
  }

  int main(int argc, char **argv) {
    const char *name;
    oui_init_options(argc, argv);
    name = getlogin();
    if (name == NULL) name = "NULL";
    nl_error(0, "Startup (%s)", name);
    atexit( cmd_exit );
    #ifdef CLIENT
      #if PHOTON_INTERFACE
        nlph_cmdclt_init( &nlph_interact );
        return 0;
      #else
	#ifdef NCT_INTERFACE
	  nct_win = nct_cmdclt_init();
	#endif
        do cmd_interact(); while ( cgc_forwarding != 0 );
        return cgc_exit_code;
      #endif
    #else
      ci_server();
      return 0;
    #endif
  }
#endif
