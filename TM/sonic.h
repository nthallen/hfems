/* Data structure for transfer of data from sonic anemometer */
/* transferred is not a data value, but is used to indicate that
   data was successfully transferred to collection. In
   collection, after the data is entered into the frame,
   transferred is set to 0. sonic will always set this value to
   1, so when it comes time to fill the frame again, we can see
   whether new data has arrived or not
*/
typedef struct {
  short U, V, W, T;
  short transferred;
} sonic_t;

/* This is a magic number... */
#define SONIC_PROXY 5
