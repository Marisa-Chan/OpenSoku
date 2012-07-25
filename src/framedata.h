#ifndef FRAMEDATA_H_INCLUDED
#define FRAMEDATA_H_INCLUDED


using namespace std;

struct char_frame
{

};

class char_graph
{
    private:

    vector<gr_tex *> imgs;
    gr_sprite *sprite;

    bool load_pal_pal(const char *file, uint32_t *pal);

    //bool load_pal_bmp(const char *file, uint32_t *pal);


    public:

    bool load_dat(const char *name, uint8_t pal);

    void set_img(uint32_t idx);
    void draw(float x, float y);

    char_graph();
  //  ~char_graph();
};


#endif // FRAMEDATA_H_INCLUDED
