#ifndef FILE_READ_H_INCLUDED
#define FILE_READ_H_INCLUDED

class filehandle
{
    private:

    bool inarchive;
    bool opened;
    FILE *file;
    uint8_t xorkey;
    uint32_t size;
    uint32_t pos;
    uint32_t spos;

    public:

    filehandle();

    bool open(const char *file);
    bool open(const char *file, uint32_t pos, uint32_t size, uint8_t key);

    void close();

    bool eof();

    bool read(uint32_t count, void *dst);
    uint32_t tell();
    bool seek(uint32_t offset);
    uint32_t get_size();

    ~filehandle();

};

#endif // FILE_READ_H_INCLUDED

