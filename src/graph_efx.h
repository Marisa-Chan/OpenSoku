#ifndef GRAPH_EFX_H_INCLUDED
#define GRAPH_EFX_H_INCLUDED

#include "moveable.h"

using namespace std;

struct gfx_frame
{
    gr_tex * img;
    uint16_t unk1;
    int16_t  unk2;
    int16_t  tx_width;
    int16_t  tx_height;
    int16_t  x_offset;
    int16_t  y_offset;
    uint16_t  durate;
    uint8_t  type;

    int16_t  blend_mode;
    uint8_t  c_A;
    uint8_t  c_R;
    uint8_t  c_G;
    uint8_t  c_B;

    float    scale_x;
    float    scale_y;
    int16_t  angle_x;
    int16_t  angle_y;
    int16_t  angle_z;
};

struct gfx_subseq
{
    vector<gfx_frame *> frames; //Frames of that ATOM seq
    uint8_t     looped;
};

struct gfx_seq
{
    vector<gfx_subseq>   subseqs;
    uint32_t    id;
    uint32_t    refcount;
};


class gfx_sprite
{
protected:

    gr_transform m_transform;

    gr_sprite  *sprite;
    gr_blend    blend;

    gfx_seq     *cur_seq;
    gfx_frame   *pframe;

    uint32_t cur_subseq;
    uint32_t cur_frame;
    uint32_t cur_frame_time;
    uint32_t cur_duration;
    uint32_t elaps_frames;

    uint32_t  _num_frames;
    gfx_subseq   *_cur_sseq;

    void frame_val_set();

public:

    gfx_sprite();
    virtual ~gfx_sprite();

    uint32_t get_cur_subseq();
    uint32_t get_cur_frame();
    uint32_t get_cur_frame_time();
    uint32_t get_elaps_frames();
    gfx_frame * get_pframe();
    uint32_t get_seq_id();

    bool set_seq(gfx_seq *sq);
    void reset_seq();
    void set_frame(uint32_t frm);
    void set_elaps_frames(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool set_subseq(uint32_t idx);
    bool process(bool ignore_loop = false);

    void setBlend(gr_blend blend);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void setTransform(gr_transform *trans);

    void setSkew(float x, float y);

    void draw(uint8_t plane = 0);
};

class c_meta;

class gfx_meta: public moveable
{
protected:
    int32_t index;

    float skew_x;
    float skew_y;

public:
    gfx_meta();
    gfx_sprite sprite;

    int8_t order;

    bool  active;

    virtual void func10();
    virtual void set_seq_params(); //func15
    virtual void draw(int8_t plane);
    virtual ~gfx_meta();

    uint32_t get_subseq();
    uint32_t get_frame();
    void set_frame(uint32_t frm);
    void set_elaps_frames(uint32_t frm);
    uint32_t get_frame_time();
    uint32_t get_elaps_frames();
    gfx_frame * get_pframe();
    uint32_t get_seq();

    void setSkew(float x, float y);

    bool process(bool ignore_loop = false);
};


typedef map<int32_t, gfx_seq *> map_gfx_seq;

class gfx_holder
{
protected:

    bool load_pal_pal(const char *file, uint32_t *pal);
    bool load_dat(const char *file, const char *dir);

    map_gfx_seq seqs;
    vector<gfx_meta *> fx;
    vector<gr_tex *> imgs;

public:
    virtual ~gfx_holder();

    gfx_seq *get_seq(uint32_t idx);

    virtual void update();
    virtual void draw(int8_t order, int8_t plane = 0 );
    void clear();
};

#endif //GRAPH_EFX_H_INCLUDED
