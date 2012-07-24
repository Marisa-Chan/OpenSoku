#ifndef ARCHIVE_H_INCLUDED
#define ARCHIVE_H_INCLUDED

class filehandle;

struct arc_node
{
    char *afile;
    uint32_t offset;
    uint32_t size;
    uint8_t key;
};

bool arc_add_dat(const char *filepath);

filehandle *arc_get_file(const char *filepath);

#endif // ARCHIVE_H_INCLUDED
