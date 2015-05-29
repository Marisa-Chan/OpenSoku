#ifndef FRAMEDATA_H_INCLUDED
#define FRAMEDATA_H_INCLUDED

#include <deque>

#include "graph_efx.h"

using namespace std;

struct frame_box
{
    int32_t		x1;
    int32_t     y1;
    int32_t     x2;
    int32_t     y2;
};

struct custom_box
{
    frame_box box;
    int16_t angle;
    int16_t c_x;
    int16_t c_y;
    //int16_t unk1;
};

struct box_box
{
    float		x1;
    float       y1;
    float       x2;
    float       y2;
};

struct CharFrameData: FrameData
{
    CharFrameData();
    ~CharFrameData();

    int16_t  damage;
    int16_t  proration;
    uint16_t health_smval;
    uint16_t sp_smval;
    int16_t  untech;
    uint16_t props_newunk5;
    int16_t  limit;
    uint16_t flag196_char;
    uint16_t flag196_enemy;
    uint16_t flag196_char2;
    uint16_t flag196_enemy2;
    uint16_t card_energy;
    uint16_t card_energy2;
    uint16_t fall_seq;
    uint16_t fall_seq2;
    float  velocity_x;
    float  velocity_y;
    uint16_t hit_sfx;
    uint16_t props_unk16;
    int16_t  attack_type;
    uint8_t  props_unk18;
    uint32_t fflags;
    uint32_t aflags;

    frame_box *box_coll;
    vector<frame_box> box_hit;
    vector<frame_box> box_atk;
    vector<frame_box *> box_unk_atk;

    int32_t  extra1[6];
    uint16_t extra2[3];
};

struct Char_SubSequence;

typedef deque<Char_SubSequence> Char_Seq;

struct Char_SubSequence
{
    vector<CharFrameData> frames; //Frames of that ATOM seq
    uint16_t    prior;
    uint16_t    prior_for_cancel;
    uint8_t     looped;

    Char_Seq  * _parent;
    uint32_t    _id;
};

struct Char_IdSeq
{
    Char_IdSeq();
    Char_IdSeq(int32_t _id, Char_Seq *point);

    int32_t id;
    Char_Seq *seq;
};

typedef map<int32_t, Char_IdSeq> Char_MapSeq;

class Char_SeqData
{
private:

protected:

    vector<gr_tex *> _imgs; //Holder for self loaded images

    deque<Char_Seq *> _sequences; //Holder for loaded sequences

    Char_MapSeq seqs;

    bool load_pal_pal(const char *file, uint32_t *pal);

public:

    bool load_dat(const char *name, uint8_t pal, char pal_rev = 0);

    uint16_t get_cprior(uint32_t idx);
    uint16_t get_prior(uint32_t idx);

    Char_IdSeq get_seq(uint32_t idx);
    bool has_seq(uint32_t idx);

    Char_SeqData(Char_SeqData * parent);
    Char_SeqData();
    ~Char_SeqData();
};

class char_sprite
{
protected:
    gr_blend    blend;

    Char_IdSeq  cur_seq;
    CharFrameData *pframe;

    uint32_t cur_subseq;
    uint32_t cur_frame;
    uint32_t cur_frame_time;
    uint32_t cur_duration;
    uint32_t elaps_frames;

    uint32_t  _num_frames;
    Char_SubSequence *_cur_sseq;

    void frame_val_set();

    gr_transform m_transform;

public:

    gr_sprite  *sprite;

    char_sprite();
    ~char_sprite();

    uint32_t get_subseq();
    uint32_t get_frame();
    uint32_t get_frame_time();
    uint32_t get_elaps_frames();
    CharFrameData * get_pframe();
    uint32_t get_seq_id();
    uint16_t get_cprior();
    uint16_t get_prior();

    bool set_seq(Char_IdSeq sq);
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

    gr_info getInfo();
    void draw(uint8_t plane = 0, gr_shader *shader = NULL);
};

#endif // FRAMEDATA_H_INCLUDED
