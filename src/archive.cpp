#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "mt.h"
#include "crc32.h"
#include <ctype.h>
#include <map>

using namespace std;

typedef map<uint32_t,arc_node>  tarcs;

static tarcs arc_files;
static vector<char *> archives;

static void dexorcrypt(uint8_t *data, uint32_t size, uint8_t v1, uint8_t v2, uint8_t v3)
{
	for (uint32_t i = 0; i < size; ++i)
	{
		*data ^= v1;
		v1 += v2;
		v2 += v3;
		data++;
	}
}

static void tolowerstr(char *str, uint32_t size)
{
    for (uint32_t i = 0; i < size; i++)
    {
        *str = tolower(*str);
        if (*str == '\\')
            *str = '/';
        str++;
    }
}

bool arc_add_dat(const char *filepath)
{
    filehandle ff;

    if (!ff.open(filepath))
        return false;

    uint32_t asize  = 0;
    uint16_t acount = 0;

    ff.read(2,&acount);
    ff.read(4,&asize);

    if (acount == 0 || asize == 0)
        return false;

    char *arcname = (char *)malloc(strlen(filepath) + 1);
    strcpy(arcname,filepath);

    archives.push_back(arcname);

    uint8_t *table = (uint8_t *)malloc(asize);

    ff.read(asize, table);

    mtwist rgen(asize + 6);

    uint8_t *pend, *p = table;
    for (uint32_t i = 0; i < asize; i++)
    {
        *p ^= (uint8_t)rgen.get_next();
        p++;
    }

    dexorcrypt(table, asize, 0xc5, 0x83, 0x53);


    p    = table;
    pend = p + asize;

    while (p < pend)
    {
        arc_node nod;

        nod.afile = arcname;

        memcpy(&nod.offset,p,4);
        p += 4;

        memcpy(&nod.size,p,4);
        p += 4;

        uint8_t slen = *p;
        p++;

        tolowerstr((char *)p, slen);

        uint32_t name = crc32(p,slen);

        p += slen;

        nod.key = ((nod.offset >> 1) | 0x23) & 0xff;

        arc_files[name] = nod;
    }

    free(table);

    return true;
}

filehandle *arc_get_file(const char *filepath)
{
    filehandle *fil = new (filehandle);

    if (fil->open(filepath))
        return fil;

    uint32_t slen = strlen(filepath);

    char buf[CHRBUF];
    strcpy(buf, filepath);
    tolowerstr(buf,slen);

    uint32_t crc = crc32(buf,slen);

    tarcs::iterator inod = arc_files.find(crc);

    if (inod != arc_files.end())
    {
        arc_node nod = (*inod).second;
        if (fil->open(nod.afile,nod.offset,nod.size,nod.key))
            return fil;
    }

    delete fil;

    return NULL;
}
