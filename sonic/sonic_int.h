#ifndef SONIC_H_INT_INCLUDED
#define SONIC_H_INT_INCLUDED

extern const char *sonic_path;
extern const char *sonic_name;

#ifdef __cplusplus
#include "sonic.h"
#include "SerSelector.h"

enum SC_next { Q1, R1 };

class Sonic : public Ser_Sel {
  public:
    Sonic( const char *path, Sonic_t *data );
    int ProcessData(int flag);
  private:
    int not_sign(int &val);
    int not_signed_ffloat( int &val );
	
    Sonic_t *TMdata;
};

/* This is a magic number... */
#define SONIC_PROXY 5

#endif
#endif
