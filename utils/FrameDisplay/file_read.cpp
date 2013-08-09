#include "global_types.h"
#include "file_read.h"

filehandle::filehandle()
{
    xorkey = 0;
    file = NULL;
    opened = false;
    inarchive = false;
    size = 0;
    pos = 0;
    spos = 0;
}

filehandle::~filehandle()
{
    if (file || opened)
        close();
}

bool filehandle::open(const char *filepath)
{
    if (file || opened)
        close();

    file = fopen(filepath,"rb");
    if (file)
    {
        inarchive = false;
        pos = 0;
        opened = true;

        fseek(file,0,SEEK_END);
        size = ftell(file);
        fseek(file,0,SEEK_SET);

        return true;
    }
    return false;
}

bool filehandle::open(const char *filepath, uint32_t vpos, uint32_t vsize, uint8_t key)
{
    if (file || opened)
        close();

    file = fopen(filepath,"rb");
    if (file)
    {
        inarchive = true;
        pos = 0;
        spos = vpos;
        opened = true;
        size = vsize;
        xorkey = key;

        fseek(file,vpos,SEEK_SET);

        return true;
    }
    return false;
}

void filehandle::close()
{
    if (file)
    {
        fclose(file);
        file = NULL;
    }
    opened = false;
}

bool filehandle::eof()
{
    return pos >= size;
}

bool filehandle::read(uint32_t count, void *dst)
{
    if (opened && (count + pos <= size))
    {
        uint32_t rid = fread(dst,count,1,file);
        pos += count;
        if (inarchive)
        {
            uint8_t *p = (uint8_t *)dst;
            for (uint32_t k=0; k < count; k++)
            {
                *p ^= xorkey;
                p++;
            }
        }
        return rid == count;
    }
    return false;
}

uint32_t filehandle::tell()
{
    if (opened)
        return pos;
    return 0;
}


bool filehandle::seek(uint32_t offset)
{
    if (opened && offset < size)
    {
        pos = offset;

        if (inarchive)
            return fseek(file,spos + offset, SEEK_SET) == 0;
        else
            return fseek(file,offset,SEEK_SET) == 0;
    }
    return false;
}

uint32_t filehandle::get_size()
{
    if (opened)
        return size;
    return 0;
}
