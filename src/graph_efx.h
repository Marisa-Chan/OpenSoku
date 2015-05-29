#ifndef GRAPH_EFX_H_INCLUDED
#define GRAPH_EFX_H_INCLUDED

#include "moveable.h"

using namespace std;

struct FrameData
{
    FrameData();

    gr_tex * img;
    uint16_t unk1;
    int16_t  unk2;
    int16_t  tx_width;
    int16_t  tx_height;
    int16_t  x_offset;
    int16_t  y_offset;
    uint16_t  duration;
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

struct gfx_SubSequence;

typedef deque<gfx_SubSequence> gfx_Seq;

struct gfx_SubSequence
{
    vector<FrameData> frames; //Frames of that ATOM seq
    uint16_t    prior;
    uint16_t    prior_for_cancel;
    uint8_t     looped;

    gfx_Seq  * _parent;
    uint32_t    _id;
};

struct gfx_IdSeq
{
    gfx_IdSeq();
    gfx_IdSeq(int32_t _id, gfx_Seq *point);

    int32_t id;
    gfx_Seq *seq;
};

typedef map<int32_t, gfx_IdSeq> gfx_MapSeq;


class gfx_sprite
{
protected:

    gr_transform m_transform;

    gr_sprite  *sprite;
    gr_blend    blend;

    gfx_IdSeq    cur_seq;
    FrameData   *pframe;

    uint32_t cur_subseq;
    uint32_t cur_frame;
    uint32_t cur_frame_time;
    uint32_t cur_duration;
    uint32_t elaps_frames;

    uint32_t  _num_frames;
    gfx_SubSequence  *_cur_sseq;

    void frame_val_set();

public:

    gfx_sprite();
    virtual ~gfx_sprite();

    uint32_t get_cur_subseq();
    uint32_t get_cur_frame();
    uint32_t get_cur_frame_time();
    uint32_t get_elaps_frames();
    FrameData * get_pframe();
    uint32_t get_seq_id();

    bool set_seq(gfx_IdSeq sq);
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

class gfx_meta: public moveable
{
protected:

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
    FrameData * get_pframe();
    uint32_t get_seq();

    void setSkew(float x, float y);

    bool process(bool ignore_loop = false);
};

class gfx_SeqData
{
private:

protected:

    vector<gr_tex *> _imgs; //Holder for self loaded images

    deque<gfx_Seq *> _sequences; //Holder for loaded sequences

    gfx_MapSeq seqs;

    bool load_pal_pal(const char *file, uint32_t *pal);

    vector<gfx_meta *> fx;

public:

    bool load_dat(const char *file, const char *dir);

    virtual void update();
    virtual void draw(int8_t order, int8_t plane = 0 );
    void clear();

    uint16_t get_cprior(uint32_t idx);
    uint16_t get_prior(uint32_t idx);

    gfx_IdSeq get_seq(uint32_t idx);
    bool has_seq(uint32_t idx);

    gfx_SeqData(gfx_SeqData * parent);
    gfx_SeqData();
    virtual ~gfx_SeqData();
};

#endif //GRAPH_EFX_H_INCLUDED
