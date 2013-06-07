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

const char *txt_mgets(const char *mem, char *buf, int32_t bufsz)
{
    int32_t num = 0;
    for (int32_t i=0; i<bufsz-1; i++)
        if (mem[i] == 0 || mem[i] == 0xA || mem[i] == 0xD)
        {
            num = i;
            break;
        }
        else if (i == bufsz - 2) // if line great than buffer
        {
            num = bufsz - 1;
            break;
        }

    if (num > 0)
    {
        strncpy(buf,mem, num);
        buf[num] = 0;
    }
    else
        buf[0] = 0;

    const char *newpos = mem + num;

    if (newpos[0] == 0xA)
    {
        if (newpos[1] == 0xD)
            newpos ++;
        newpos ++;
    }
    else if (newpos[0] == 0xD)
    {
        if (newpos[1] == 0xA)
            newpos ++;
        newpos ++;
    }
    if (newpos[0] == 0)
        return NULL;

    return newpos;
}
