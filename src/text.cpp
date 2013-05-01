#include "global_types.h"
#include "file_read.h"

char *txt_load_cv1(filehandle *f)
{
    uint32_t fsz = f->get_size();

    char *buf = (char *)malloc(fsz+1);

    f->read(fsz, buf);
    buf[fsz] = 0;

    uint8_t p1 = 0x8B;
    uint8_t p2 = 0x71;

    for(uint32_t i=0; i<fsz; i++)
    {
        buf[i] ^= p1;
        p1 += p2;
        p2 -= 0x6B;
    }

    return buf;
}
