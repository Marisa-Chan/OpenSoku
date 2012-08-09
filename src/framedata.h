#ifndef FRAMEDATA_H_INCLUDED
#define FRAMEDATA_H_INCLUDED


using namespace std;

struct frame_box
{
	int32_t		x1;
	int32_t     y1;
	int32_t     x2;
	int32_t     y2;
};

struct char_frame
{
	gr_tex * img;
	uint16_t unk1;
	int16_t unk2;
    int16_t  tx_width;
    int16_t  tx_height;
    int16_t  x_offset;
    int16_t  y_offset;
    uint16_t  durate;
	uint8_t  type;

	int16_t  blend_mode;
	uint32_t color;
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
	int16_t  velocity_x;
	int16_t  velocity_y;
	uint16_t hit_sfx;
	uint16_t unk19;
	int16_t  attack_type;
	uint8_t  unk20;
    uint32_t fflags;
    uint32_t aflags;

	vector<frame_box> box_coll;
	vector<frame_box> box_hit;
	vector<frame_box> box_atk;

    uint16_t unk21[12];
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
    private:

    gr_sprite  *sprite;
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

    char_sprite();
    ~char_sprite();

    inline uint32_t get_cur_subseq();
    inline uint32_t get_cur_frame();
    inline uint32_t get_cur_frame_time();
    inline uint32_t get_elaps_frames();
    char_frame * get_pframe();

    bool set_seq(seq *sq);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool process(bool ignore_loop = false);

    void setXY(float x, float y);
    void setScale(float x, float y);
    void setOrigin(float x, float y);
    void setBlend(gr_blend blend);

    void draw(uint8_t plane = 0);
};



typedef map<int32_t, seq *> mapseq;

class char_graph
{
    private:

    vector<gr_tex *> imgs;

    mapseq seqs;

    bool load_pal_pal(const char *file, uint32_t *pal);
    //bool load_pal_bmp(const char *file, uint32_t *pal);

    char_sprite sprite;

    public:

    bool load_dat(const char *name, uint8_t pal, char pal_rev = 0);

    void draw(float x, float y, uint8_t plane,int8_t direct);

    void set_seq(uint32_t idx);
    void process_anim();

    char_graph();
  //  ~char_graph();
};


#endif // FRAMEDATA_H_INCLUDED
