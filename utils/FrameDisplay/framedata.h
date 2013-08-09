#ifndef FRAMEDATA_H_INCLUDED
#define FRAMEDATA_H_INCLUDED

#define FF_STAND        0x1
#define FF_CROUCH       0x2
#define FF_AIRBORNE     0x4
#define FF_UNK8         0x8
#define FF_GUARDCANC    0x10
#define FF_CANCELLEABLE 0x20
#define FF_CH_ON_HIT    0x40
#define FF_SUPERARMOR   0x80
#define FF_GUARD        0x100
#define FF_GUARD2       0x200
#define FF_GRAZE        0x400
#define FF_UNK800       0x800
#define FF_UNK1000      0x1000
#define FF_MEL_INV_GND  0x2000
#define FF_INV_FIRE     0x4000
#define FF_INV_AIRBORNE 0x8000
#define FF_INV_MID_BLOW 0x10000
#define FF_INV_LOW_BLOW 0x20000
#define FF_INV_SHOOT    0x40000
#define FF_UNK80000     0x80000
#define FF_UNK100000    0x100000
#define FF_HJC          0x200000
#define FF_UNK400000    0x400000
#define FF_UNK800000    0x800000
#define FF_ATK_AS_HIT   0x1000000

#define AF_UNK1         0x1
#define AF_MID_HIT      0x2
#define AF_LOW_HIT      0x4
#define AF_AIR_HIT      0x8
#define AF_U_HIT        0x10
#define AF_UNK20        0x20
#define AF_UNK40        0x40       //TRANSLATE
#define AF_UNK80        0x80       //TRANSLATE!
#define AF_UNK100       0x100
#define AF_UNK200       0x200
#define AF_CRASH_HIT    0x400
#define AF_UNK800       0x800
#define AF_UNK1000      0x1000
#define AF_UNK2000      0x2000
#define AF_UNK4000      0x4000
#define AF_KNOCK_BACK   0x8000
#define AF_UNK10000     0x10000
#define AF_UNK20000     0x20000
#define AF_UNK40000     0x40000
#define AF_GUARDCRUSH   0x80000
#define AF_HITSALL      0x100000   //TRANSLATE
#define AF_STAGGER      0x200000
#define AF_UNK400000    0x400000   //TRANSLATE
#define AF_UNK800000    0x800000   //TRANSLATE
#define AF_UNK1000000   0x1000000

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

struct char_frame
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


	int16_t  damage;
	int16_t  proration;
	uint16_t health_smval;
	uint16_t sp_smval;
	int16_t  untech;
	uint16_t unk9;
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
	uint16_t unk19;
	int16_t  attack_type;
	uint8_t  unk20;
    uint32_t fflags;
    uint32_t aflags;

	frame_box *box_coll;
	vector<frame_box> box_hit;
	vector<frame_box> box_atk;
	vector<frame_box *> box_unk_atk;

    int32_t  extra1[6];
    uint16_t unk22[3];
};

struct subseq
{
    vector<char_frame *> frames; //Frames of that ATOM seq
    uint16_t    prior;
    uint16_t    prior_for_cancel;
    uint8_t     looped;
};

struct seq
{
    vector<subseq>   subseqs;
    uint32_t    id;
    uint16_t    prior;
    uint16_t    prior_for_cancel;
    uint32_t    refcount;
};



class char_sprite
{
    protected:
    gr_blend    blend;

    seq        *cur_seq;
    char_frame *pframe;

    uint32_t cur_subseq;
    uint32_t cur_frame;
    uint32_t cur_frame_time;
    uint32_t cur_duration;
    uint32_t elaps_frames;

    uint32_t  _num_frames;
    subseq   *_cur_sseq;

    void frame_val_set();

    public:

    gr_sprite  *sprite;

    char_sprite();
    ~char_sprite();

    uint32_t get_subseq();
    uint32_t get_frame();
    uint32_t get_frame_time();
    uint32_t get_elaps_frames();
    char_frame * get_pframe();
    uint32_t get_seq_id();
    uint16_t get_cprior();
    uint16_t get_prior();

    bool set_seq(seq *sq);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool set_subseq(uint32_t idx);
    bool process(bool ignore_loop = false);

    void setXY(float x, float y);
    void setScale(float x, float y);
    void setAScale(float w, float h);
    void setOrigin(float x, float y);
    void setBlend(gr_blend blend);
    void setRotate(float angl);
    void setRotate(float x, float y, float z);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

    gr_info getInfo();
    void draw(uint8_t plane = 0, gr_shader *shader = NULL);
};



typedef map<int32_t, seq *> mapseq;

class char_graph
{
    private:

    public:

    vector<gr_tex *> imgs;

    mapseq seqs;

    bool load_pal_pal(const char *file, uint32_t *pal);

    bool load_dat(const char *name, uint8_t pal, char pal_rev = 0);

    uint16_t get_cprior(uint32_t idx);
    uint16_t get_prior(uint32_t idx);

    seq *get_seq(uint32_t idx);

    //char_graph();
    ~char_graph();
};


#endif // FRAMEDATA_H_INCLUDED
