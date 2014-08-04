/*#include <MemoryFree.h>*/

#define DELAYSHORT 6
#define DELAYMEDIUM 12

#define DELAYEND 25

byte default_display[20*142] =
"\x00\x01\x01\x01\x01\x01\x01\x00\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x08\x08\x08\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x04\x04\x04\x04\x04\x04\x00\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x02\x02\x02\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x40\x40\x40\x40\x40\x40\x00\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x80\x80\x80\x80\x80\x80\x00\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x10\x10\x10\x10\x10\x10\x00\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x20\x20\x20\x20\x20\x20\x00\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x01\x01\x01\x01\x01\x01\x00\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x02\x02\x02\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x04\x04\x04\x04\x04\x04\x00\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x08\x08\x08\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08"
"\x00\x80\x80\x80\x80\x80\x80\x00\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x40\x40\x40\x40\x40\x40\x00\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x20\x20\x20\x20\x20\x20\x00\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x10\x10\x10\x10\x10\x10\x00\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x01\x01\x01\x01\x01\x01\x00\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x02\x02\x02\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x04\x04\x04\x04\x04\x04\x00\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x08\x08\x08\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x10\x10\x10\x10\x10\x10\x00\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\xa0\xa0\xa0\xa0\xa0\xa0\x00\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0\xa0"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\xc0\xc0\xc0\xc0\xc0\xc0\x00\xc0\xc0\xc0\xc0\xc0\xc0\xc0\xc0\xc0\xc0\xc0\xc0"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\xe0\xe0\xe0\xe0\xe0\xe0\x00\xe0\xe0\xe0\xe0\xe0\xe0\xe0\xe0\xe0\xe0\xe0\xe0"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x08\x08\x08\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x04\x04\x04\x04\x04\x04\x00\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x02\x02\x02\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x01\x01\x01\x01\x01\x01\x00\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x02\x02\x02\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x01\x01\x01\x01\x01\x01\x00\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x08\x08\x08\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x04\x04\x04\x04\x04\x04\x00\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x80\x80\x80\x80\x80\x80\x00\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
"\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\xff\xff\xff\xff\xff\xff\xbf\xff\xff\xff\xff\x40\x40\x40\x40\x40\x40\x40\x40"
"\x00\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\xff\xff\xff\xff\x00\x00\x00\x00"
"\x00\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\xff\xff\xff\xff\x00\x00\x00\x00"
"\x00\xff\xff\xff\xff\xff\xff\xdf\x20\x20\x20\x20\xff\xff\xff\xff\x20\x20\x20\x20"
"\x00\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff"
"\x00\xff\xff\xff\xff\xff\xff\xff\x00\x00\x00\x00\x00\x00\x00\x00\xff\xff\xff\xff"
"\x00\xff\xff\xff\xff\xff\xff\xef\x10\x10\x10\x10\x10\x10\x10\x10\xff\xff\xff\xff"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x01\x01\x01\x01\x01\x01\x00\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01\x01"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x02\x02\x02\x02\x02\x02\x00\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02\x02"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x04\x04\x04\x04\x04\x04\x00\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04\x04"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x08\x08\x08\x08\x08\x08\x00\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08\x08"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x40\x40\x40\x40\x40\x40\x00\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40\x40"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x20\x20\x20\x20\x20\x20\x00\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20\x20"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x10\x10\x10\x10\x10\x10\x00\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10\x10"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x80\x80\x80\x80\x80\x80\x00\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x80\x80\x80\x80\x80\x80\x00\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80\x80"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x50\x50\x50\x50\x50\x50\x00\x50\x50\x50\x50\x50\x50\x50\x50\x50\x50\x50\x50"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x30\x30\x30\x30\x30\x30\x00\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30\x30"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
"\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00"
;


String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

byte portl[48*20];

uint32_t lights_array[48][24];
byte loopCount = 0;

void setup() {
  Serial.begin(1000000);
  //Serial.println("hello world");
  // reserve 200 bytes for the inputString:
  inputString.reserve(2820);

  DDRA = 0xFF; // open pins for writing
  DDRB = 0xFF; // open pins for writing
  DDRC = 0xFF; // open pins for writing
  DDRF = 0xFF; // open pins for writing
  DDRK = 0xFF; // open pins for writing
  DDRL = 0xFF; // open pins for writing

  //initialize screen to give bulbs specific addresses
  //for (int j=0; j<24; j++) {
  byte j=0;
    for (int i=24; i>-1; i--) {
      sendsome_left(i, 0b00000001000011001000 + 4096*j);
    }
    for (int i=47; i>24; i--) {
      sendsome_right(i, 0b00000001000011001000 + 4096*j);
    }
  //}
  // paint default picture
  paint_default_array();
}

void loop() {

  while (1) {
    while (Serial.available()<1) {}

    // get the new byte:
    char inChar = Serial.read(); 
    if (inputString.length() < 2819) {
      // add it to the inputString:
      inputString += inChar;
    } else {
      // we have enough bytes to send them to a string
      //Serial.print(loopCount);
      //Serial.print("-");
      for (int j=0; j<2820; j++) {
        default_display[j] = inputString[j];
	  }
      inputString = "";
      paint_default_array();
    }
  }

  /*
  while (1) {
    while (Serial.available()<1) {}

    // get the new byte:
    char inChar = Serial.read(); 
    if (inputString.length() < 59) {
      // add it to the inputString:
      inputString += inChar;
    } else {
      // we have enough bytes to send them to a string
      //Serial.print(loopCount);
      //Serial.print("-");
      byte inputStringByteA[20];
      byte inputStringByteB[20];
      byte inputStringByteC[20];
      byte inputStringByteF[20];
      byte inputStringByteL[20];
      byte inputStringByteK[20];

      for (int j=0; j<20; j++) {
        if (loopCount<24) {
          inputStringByteB[j] = inputString[j+0];
          inputStringByteK[j] = inputString[j+20];
          inputStringByteL[j] = inputString[j+40];
        } else {
          inputStringByteA[j] = inputString[j+0];
          inputStringByteC[j] = inputString[j+20];
          inputStringByteF[j] = inputString[j+40];
        }
      }
      //Serial.print("prelen:");
      //Serial.println(inputString.length());
      //Serial.println(sizeof(inputStringByteL));
      if (loopCount < 24) { // left bank
        processBulb(loopCount, inputStringByteB, inputStringByteK, inputStringByteL);
      } else { // right bank
        processBulb(loopCount, inputStringByteA, inputStringByteC, inputStringByteF);
      }

      inputString = "";
      // we're done with our page, so reset
      loopCount++;
      if (loopCount>46) loopCount = 0;
    }
  }
  */
  //while(1){}
}

void paint_default_array() {
  // fade test picture in
  byte inputStringByteX[20];
  byte inputStringByteY[20];
  byte inputStringByteZ[20];
  for (loopCount=0; loopCount<47; loopCount++) {
    for (int j=0; j<20; j++) {
      inputStringByteX[j] = default_display[(loopCount * 60) + j+0];
      inputStringByteY[j] = default_display[(loopCount * 60) + j+20];
      inputStringByteZ[j] = default_display[(loopCount * 60) + j+40];
    }
    processBulb(loopCount, inputStringByteX, inputStringByteY, inputStringByteZ);
  }
  loopCount = 0;
}

void processBulb(byte loopCount, byte *inputString1, byte *inputString2, byte *inputString3) {
/*
  Serial.print ("len:");
  Serial.print (loopCount);
  Serial.print ("-");
  Serial.print (sizeof(inputStringD));
  Serial.print ("-");
  Serial.print (sizeof(inputStringG));
  Serial.print ("-");
  Serial.println (sizeof(inputStringL));
  //Serial.println (inputStringL.length());
  for (int j=0; j<20; j++) {
    //Serial.print ("#");
    //Serial.print (j);
    Serial.print (";");
    Serial.print ((byte)inputStringL[j]);
  }
  Serial.println("!");
*/

  // convert bulb number to six digit bits
  byte bank_1[26];
  byte bank_2[26];
  byte bank_3[26];

  for (int j=5; j>-1; j--) {
    byte nth_bit = 0;
    if ((loopCount+1) & (1 << j) ) nth_bit = 255;
    bank_1[5-j] = nth_bit;
    bank_2[5-j] = nth_bit;
    bank_3[5-j] = nth_bit;
  }
  // convert bulb data into 20 digit bits
  for (int j=0; j<20; j++) {
    //byte nth_bit = (byte)inputStringL[j];
    bank_1[j+6] = (byte)inputString1[j];
    bank_2[j+6] = (byte)inputString2[j];
    bank_3[j+6] = (byte)inputString3[j];
  }
  if (loopCount < 24) {
    send_string_data_left(bank_1, bank_2, bank_3);
    //send_string_data_left(bank_b, bank_k, bank_l);
  } else {
    send_string_data_right(bank_1, bank_2, bank_3);
    //send_string_data_right(bank_a, bank_c, bank_f);
  }
  //Serial.print ("array():");
  //for (int j=0; j<26; j++) {
  //  Serial.print (",");
  //  Serial.print (bank_l[j]);
  //}
  //Serial.println();
}

void paint_array() {
  // read by string?
  uint32_t current_column[24];
  for (int i=47; i>-1; i--) { // will be 48
    //lights_array[i][j];
    for (int j=0; j<24; j++) {
      current_column[j] = lights_array[i][j];
      //Serial.println(lights_array[i][j]);
    }
    // fire them off?
    //Serial.print("line:");
    //Serial.println(i);
    send_a_column(i, current_column);
    //delay (1000);
  }
  
  
}

void send_a_column(int bulb, uint32_t *current_column) {
  //byte bit_data[24][26];
  //Serial.print ("bulb:");
  //Serial.println (bulb);
  bulb++;
  //for (int j=0; j<8; j++) { // 24 for each of the lights
  //  Serial.print ("col:");
  //  Serial.println (current_column[j]);
  //}
  //delay(100);
  //int string_byte_lines[26];
  int light_bank = 0;
  if (bulb>24) {
    light_bank = 1;
    //bulb = bulb - 23;//why 17?
    //Serial.println ("one bigger");
  }
  
  int bank_a[26];
  int bank_b[26];
  int bank_c[26];
  int bank_d[26];
  int bank_e[26];
  int bank_g[26];
  int bank_h[26];
  int bank_j[26];
  int bank_k[26];
  int bank_l[26];

  //noInterrupts();
  for (int i=0; i<26; i++) { // for each of the bits
    byte bit_line[24] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    //Serial.print("bulb:");
    //Serial.println(bulb);
    //Serial.print("i:");
    //Serial.println(i);
    for (int j=0; j<24; j++) { // 24 for each of the lights
      uint32_t this_lil_light = current_column[j];
      //if (light_bank==1) this_lil_light = current_column[j+24];
      //Serial.print("this_lil_light=");
      //Serial.println(this_lil_light);
      //Serial.print('=');

      // get the nth bit on all lights
      byte nth_bit = 0;
      if (i<6) { // the bulb part of the data
        byte this_i = 5-i; // reverse the order of the bulb's binary ID
        //if ( bulb & (1 << i) ) bit_line[5-i] = 1;
        if ( bulb & (1 << this_i) ) nth_bit = 1;
        bit_line[j] = nth_bit;
      } else { // the content part of the data
        //if ( this_lil_light & ((uint32_t)1 << i) ) bit_line[25-i] = 1; //cast 1 as uint32_t
        if ( this_lil_light & ((uint32_t)1 << (25-i)) ) nth_bit = 1; //cast 1 as uint32_t, reverse order
        bit_line[j] = nth_bit;
      }
    }
    //boolean bittest = 1;
    //for (int k=0; k<24; k++) {
    //  Serial.print(bit_line[k]);
    //}
    //Serial.println('!');
    int mybyte_a = 0b00000000;
    int mybyte_b = 0b00000000;
    int mybyte_c = 0b00000000;
    int mybyte_d = 0b00000000;
    int mybyte_e = 0b00000000;
    int mybyte_g = 0b00000000;
    int mybyte_h = 0b00000000;
    int mybyte_j = 0b00000000;
    int mybyte_k = 0b00000000;
    int mybyte_l = 0b00000000;

    if (light_bank==0) {
      // translate lights to ports (ie. mybyte_g's 5th position, 0b00000100)
      if (bit_line[0]==1) mybyte_g = mybyte_g | 0b00000100;
      if (bit_line[1]==1) mybyte_d = mybyte_d | 0b10000000;
      if (bit_line[2]==1) mybyte_g = mybyte_g | 0b00000001;
      if (bit_line[3]==1) mybyte_g = mybyte_g | 0b00000010;
      if (bit_line[4]==1) mybyte_l = mybyte_l | 0b01000000;
      if (bit_line[5]==1) mybyte_l = mybyte_l | 0b10000000;
      if (bit_line[6]==1) mybyte_l = mybyte_l | 0b00010000;
      if (bit_line[7]==1) mybyte_l = mybyte_l | 0b00100000;
      if (bit_line[8]==1) mybyte_l = mybyte_l | 0b00000001;
      if (bit_line[9]==1) mybyte_l = mybyte_l | 0b00000010;
      if (bit_line[10]==1) mybyte_l = mybyte_l | 0b00000100;
      if (bit_line[11]==1) mybyte_l = mybyte_l | 0b00001000;
      if (bit_line[12]==1) mybyte_b = mybyte_b | 0b10000000;
      if (bit_line[13]==1) mybyte_b = mybyte_b | 0b01000000;
      if (bit_line[14]==1) mybyte_b = mybyte_b | 0b00100000;
      if (bit_line[15]==1) mybyte_b = mybyte_b | 0b00010000;
      if (bit_line[16]==1) mybyte_e = mybyte_e | 0b00001000;
      if (bit_line[17]==1) mybyte_g = mybyte_g | 0b00100000;
      if (bit_line[18]==1) mybyte_e = mybyte_e | 0b00100000;
      if (bit_line[19]==1) mybyte_e = mybyte_e | 0b00010000;
      if (bit_line[20]==1) mybyte_k = mybyte_k | 0b01000000;
      if (bit_line[21]==1) mybyte_k = mybyte_k | 0b00100000;
      if (bit_line[22]==1) mybyte_k = mybyte_k | 0b00010000;
      if (bit_line[23]==1) mybyte_k = mybyte_k | 0b00001000;
    } else {
      if (bit_line[0]==1) mybyte_a = mybyte_a | 0b00001000;
      if (bit_line[1]==1) mybyte_a = mybyte_a | 0b00000100;
      if (bit_line[2]==1) mybyte_a = mybyte_a | 0b00000010;
      if (bit_line[3]==1) mybyte_a = mybyte_a | 0b00000001;
      if (bit_line[4]==1) mybyte_k = mybyte_k | 0b00000101;
      if (bit_line[5]==1) mybyte_k = mybyte_k | 0b10000010;
      if (bit_line[6]==1) mybyte_b = mybyte_b | 0b00000001;
      if (bit_line[7]==1) mybyte_b = mybyte_b | 0b00000010;
      if (bit_line[8]==1) mybyte_d = mybyte_d | 0b00000001;
      if (bit_line[9]==1) mybyte_d = mybyte_d | 0b00000010;
      if (bit_line[10]==1) mybyte_d = mybyte_d | 0b00000100;
      if (bit_line[11]==1) mybyte_d = mybyte_d | 0b00001000;
      if (bit_line[12]==1) mybyte_c = mybyte_c | 0b00000001;
      if (bit_line[13]==1) mybyte_c = mybyte_c | 0b00000010;
      if (bit_line[14]==1) mybyte_c = mybyte_c | 0b00000100;
      if (bit_line[15]==1) mybyte_c = mybyte_c | 0b00001000;
      if (bit_line[16]==1) mybyte_c = mybyte_c | 0b01000000;
      if (bit_line[17]==1) mybyte_c = mybyte_c | 0b00100000;
      if (bit_line[18]==1) mybyte_c = mybyte_c | 0b00010000;
      if (bit_line[19]==1) mybyte_c = mybyte_c | 0b10000000;
      if (bit_line[20]==1) mybyte_a = mybyte_a | 0b10000000;
      if (bit_line[21]==1) mybyte_a = mybyte_a | 0b01000000;
      if (bit_line[22]==1) mybyte_a = mybyte_a | 0b00100000;
      if (bit_line[23]==1) mybyte_a = mybyte_a | 0b00010000;
    }

    mybyte_a = mybyte_a ^ 0b11111111;
    mybyte_b = mybyte_b ^ 0b11111111;
    mybyte_c = mybyte_c ^ 0b11111111;
    mybyte_d = mybyte_d ^ 0b11111111;
    mybyte_e = mybyte_e ^ 0b11111111;
    mybyte_k = mybyte_k ^ 0b11111111;
    mybyte_g = mybyte_g ^ 0b11111111;
    mybyte_h = mybyte_h ^ 0b11111111;
    mybyte_j = mybyte_j ^ 0b11111111;
    mybyte_l = mybyte_l ^ 0b11111111;

    bank_a[i] = mybyte_a;
    bank_b[i] = mybyte_b;
    bank_c[i] = mybyte_c;
    bank_d[i] = mybyte_d;
    bank_e[i] = mybyte_e;
    bank_k[i] = mybyte_k;
    bank_g[i] = mybyte_g;
    bank_h[i] = mybyte_h;
    bank_j[i] = mybyte_j;
    bank_l[i] = mybyte_l;
    //Serial.println (mybyte, BIN);
    //for (int k=0; k<8; k++) {
    //  Serial.print(bit_line[k]);
    //}
    //Serial.println('.');
    // now we have the 8 loaded up, let's send 'em
    //if (bit_data[i]) {
    //  Serial.print ('1');
    //} else {
    //  Serial.print ('0');
    //}
  }
  send_string_data(bank_a,bank_b,bank_c,bank_d,bank_e,bank_g,bank_h,bank_j,bank_k,bank_l);
}

void send_string_data_left(byte *bank_b, byte *bank_k, byte *bank_l) {
  /*for (int i=0; i<26; i++) { // for each of the bits
    Serial.print (">");
    Serial.print (bank_l[i]);
  }
  Serial.println("!");*/
  noInterrupts();
  for (int i=0; i<26; i++) { // for each of the bits
    byte mybyte_b = bank_b[i] ^ 0b11111111;
    byte mybyte_k = bank_k[i] ^ 0b11111111;
    byte mybyte_l = bank_l[i] ^ 0b11111111;
    // all on start packet
    PORTB = 0b11111111; PORTK = 0b11111111; PORTL = 0b11111111;
    delayMicroseconds(DELAYSHORT);

    // all off
    PORTB = 0b00000000; PORTK = 0b00000000; PORTL = 0b00000000;
    delayMicroseconds(DELAYSHORT);

    // on or off bit
    PORTB = mybyte_b; 
    PORTK = mybyte_k; 
    PORTL = mybyte_l;
    delayMicroseconds(DELAYMEDIUM);

    // all on
    PORTB = 0b11111111; PORTK = 0b11111111; PORTL = 0b11111111;
    delayMicroseconds(DELAYSHORT);
  }

  // all off for long end packet
  PORTB = 0b00000000; PORTK = 0b00000000; PORTL = 0b00000000;
  delayMicroseconds(DELAYEND);
  interrupts();
}

void send_string_data_right(byte *bank_a, byte *bank_c, byte *bank_f) {
  /*for (int i=0; i<26; i++) { // for each of the bits
    Serial.print (">");
    Serial.print (bank_l[i]);
  }
  Serial.println("!");*/
  noInterrupts();
  for (int i=0; i<26; i++) { // for each of the bits
    byte mybyte_a = bank_a[i] ^ 0b11111111;
    byte mybyte_c = bank_c[i] ^ 0b11111111;
    byte mybyte_f = bank_f[i] ^ 0b11111111;
    // all on start packet
    PORTA = 0b11111111; PORTC = 0b11111111; PORTF = 0b11111111; 
    delayMicroseconds(DELAYSHORT);

    // all off
    PORTA = 0b00000000; PORTC = 0b00000000; PORTF = 0b00000000; 
    delayMicroseconds(DELAYSHORT);

    // on or off bit
    PORTA = mybyte_a; PORTC = mybyte_c; PORTF = mybyte_f; 
    delayMicroseconds(DELAYMEDIUM);

    // all on
    PORTA = 0b11111111; PORTC = 0b11111111; PORTF = 0b11111111; 
    delayMicroseconds(DELAYSHORT);
  }

  // all off for long end packet
  PORTA = 0b00000000; PORTC = 0b00000000; PORTF = 0b00000000; 
  delayMicroseconds(DELAYEND);
  interrupts();
}

void send_string_data(int *bank_a, int *bank_b, int *bank_c, int *bank_d, int *bank_e, int *bank_f, int *bank_g, int *bank_h, int *bank_j, int *bank_l) {
  /*for (int i=0; i<26; i++) { // for each of the bits
    Serial.print ('=');
    Serial.println (bank_g[i]);
  }*/
  noInterrupts();
  for (int i=0; i<26; i++) { // for each of the bits
    // all on start packet
    PORTA = 0b11111111; PORTB = 0b11111111; PORTC = 0b11111111; PORTD = 0b11111111; PORTE = 0b11111111; PORTK = 0b11111111; PORTG = 0b11111111; PORTH = 0b11111111; PORTJ = 0b11111111; PORTL = 0b11111111;
    delayMicroseconds(DELAYSHORT);

    // all off
    PORTA = 0b00000000; PORTB = 0b00000000; PORTC = 0b00000000; PORTD = 0b00000000; PORTE = 0b00000000; PORTK = 0b00000000; PORTG = 0b00000000; PORTH = 0b00000000; PORTJ = 0b00000000; PORTL = 0b00000000;
    delayMicroseconds(DELAYSHORT);

    // on or off bit
    PORTA = bank_a[i];
    PORTB = bank_b[i];
    PORTC = bank_c[i];
    PORTD = bank_d[i];
    PORTE = bank_e[i];
    PORTK = bank_c[i];
    PORTG = bank_g[i];
    PORTH = bank_h[i];
    PORTJ = bank_j[i];
    PORTL = bank_l[i];
    delayMicroseconds(DELAYMEDIUM);

    // all on
    PORTA = 0b11111111; PORTB = 0b11111111; PORTC = 0b11111111; PORTD = 0b11111111; PORTE = 0b11111111; PORTK = 0b11111111; PORTG = 0b11111111; PORTH = 0b11111111; PORTJ = 0b11111111; PORTL = 0b11111111;
    delayMicroseconds(DELAYSHORT);
  }

  // all off for long end packet
  PORTA = 0b00000000; PORTB = 0b00000000; PORTC = 0b00000000; PORTD = 0b00000000; PORTE = 0b00000000; PORTK = 0b00000000; PORTG = 0b00000000; PORTH = 0b00000000; PORTJ = 0b00000000; PORTL = 0b00000000;
  delayMicroseconds(DELAYEND);
  interrupts();
}

void sendsome_right(int bulb, uint32_t this_bulb) {
  byte bit_data[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  //Serial.println (bulb, BIN);
  for (int i=0; i<6; i++) { // make specific bulb id bits into array
    if ( bulb & (1 << i) ) bit_data[5-i] = 1;
  }
  for (uint32_t i=0; i<20; i++) { // make specific brightness, color bits into array
    if ( this_bulb & ((uint32_t)1 << i) ) bit_data[25-i] = 1; //cast 1 as uint32_t
  }
  noInterrupts();
  for (byte i=0; i<26; i++) {
    // all on start packet
    PORTA = 0b11111111; PORTC = 0b11111111; PORTF = 0b11111111; 
    delayMicroseconds(DELAYSHORT);
    // all off
    PORTA = 0b00000000; PORTC = 0b00000000; PORTF = 0b00000000; 
    delayMicroseconds(DELAYSHORT);
    // on or off bit
    if (bit_data[i]==1) {
      PORTA = 0b00000000; PORTC = 0b00000000; PORTF = 0b00000000; 
    } else {
      PORTA = 0b11111111; PORTC = 0b11111111; PORTF = 0b11111111; 
    }
    delayMicroseconds(DELAYMEDIUM);
  }
  // all off for long end packet
  PORTA = 0b00000000; PORTC = 0b00000000; PORTF = 0b00000000; 
  delayMicroseconds(DELAYEND);
  interrupts();
}
void sendsome_left(int bulb, uint32_t this_bulb) {
  byte bit_data[26] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
  for (int i=0; i<6; i++) { // make specific bulb id bits into array
    if ( bulb & (1 << i) ) bit_data[5-i] = 1;
  }
  for (uint32_t i=0; i<20; i++) { // make specific brightness, color bits into array
    if ( this_bulb & ((uint32_t)1 << i) ) bit_data[25-i] = 1; //cast 1 as uint32_t
  }
  noInterrupts();
  for (byte i=0; i<26; i++) {
    // all on start packet
    PORTB = 0b11111111; PORTK = 0b11111111; PORTL = 0b11111111;
    delayMicroseconds(DELAYSHORT);
  
    // all off
    PORTB = 0b00000000; PORTK = 0b00000000; PORTL = 0b00000000;
    delayMicroseconds(DELAYSHORT);
    // on or off bit
    if (bit_data[i]==1) {
      PORTB = 0b00000000; PORTK = 0b00000000; PORTL = 0b00000000;
    } else {
      PORTB = 0b11111111; PORTK = 0b11111111; PORTL = 0b11111111;
    }
    delayMicroseconds(DELAYMEDIUM);
  }
  // all off for long end packet
  PORTB = 0b00000000; PORTK = 0b00000000; PORTL = 0b00000000;
  delayMicroseconds(DELAYEND);
  interrupts();
}

