/** Data structure for transfer of data from sonic anemometer 
  * transferred is not a data value, but is used to indicate that
  * data was successfully transferred to collection. In
  * collection, after the data is entered into the frame,
  * transferred is set to 0. sonic will always set this value to
  * 1, so when it comes time to fill the frame again, we can see
  * whether new data has arrived or not
*/

#ifndef _SONIC_H_INCLUDED


#include "Selector.h"
#include "collect.h"

#define _SONIC_H_INCLUDED
typedef struct {
  short U, V, W, T;
  short transferred;
} sonic_t;
class sonic_ctrl;
class TMcollect : public Selectee {
  public:
    TMcollect();
    int ProcessData(int flag);
    int init(sonic_ctrl *par, const char *name, void *data, int data_size);
    int send();
  private:
    send_id TMid;
	sonic_ctrl *par;
};

class Quitter : public Selectee {
  public:
    Quitter();
    int ProcessData(int flag);
};


class sonic_ctrl : public Selectee {
  public:
    TMcollect TM;
	struct termios termios_p;
	sonic_ctrl(int serdevice);
	int ProcessData(int flag);
	void sonic_record( short U, short V, short W, short T );
	void sonic_fillbuf( void );
	int sonic_getc( void );
	int sonic_not_c( int c )
	int sonic_not_num( signed short *num )
		
  private:
	char *buf;
	sonic_t TMdata;
	int sonic_fd;
	int buf_high, buf_low;
	int chars_accepted;
	pid_t collect_proxy;
	pid_t quit_proxy;
	pid_t serdev_proxy;
	send_id col_id;
	sonic_t collect_buf;
	long resynchs
	long untransferred;
	long retransferred;
};

/* This is a magic number... */
#define SONIC_PROXY 5
#endif
