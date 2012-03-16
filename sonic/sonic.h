#ifndef SONIC_H_INCLUDED
#define SONIC_H_INCLUDED

typedef struct __attribute__((__packed__)) {
  short U, V, W, T;
  signed char SC_stale;
} Sonic_t;

#endif
