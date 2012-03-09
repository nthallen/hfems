#ifndef SONIC_H_INCLUDED
#define SONIC_H_INCLUDED

#ifdef __cplusplus
#include "SerSelector.h"
typedef struct {
  short U, V, W, T;
  unsigned char SC_stat;
} sonic_t;
#define SC_PRESENT 1
#define SC_FRESH 2

enum SC_next { Q1, R1 };

class Sonic : public Ser_Sel {
  public:
    Sonic( const char *path, Sonic_t *data );
    int ProcessData(int flag);
  private:
    void IssueQuery(bool synch);
    SC_next state;
    bool query_pending;
    Sonic_t *TMdata;
};

/* This is a magic number... */
#define SONIC_PROXY 5

#endif
#endif
