#ifndef SONIC_H_INCLUDED
#define SONIC_H_INCLUDED

typedef struct sonicdata{
  short U, V, W, T;
  unsigned char SC_stat;
} Sonic_t;
#define SC_PRESENT 1
#define SC_FRESH 2

#endif
