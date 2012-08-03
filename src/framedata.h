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
	uint16_t unk2;
    int16_t  tx_width;
    int16_t  tx_height;
    int16_t  x_offset;
    int16_t  y_offset;
    uint16_t  durate;
	uint8_t  type;

	int16_t  blend_mode;
	uint32_t unk3;
	uint16_t unk4;
    int16_t  scale;
	uint16_t unk5;
	uint16_t unk6;
    int16_t  angle;


	int16_t  damage;
	int16_t  proration;
	uint16_t unk7;
	uint16_t unk8;
	int16_t  untech;
	uint16_t unk9;
	int16_t  limit;
	uint16_t unk10;
	uint16_t unk11;
	uint16_t unk12;
	uint16_t unk13;
	uint16_t unk14;
	uint16_t unk15;
	uint16_t unk16;
	uint16_t unk17;
	int16_t  velocity_x;
	int16_t  velocity_y;
	uint16_t unk18;
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
    uint16_t    prior;
    uint16_t    prior_for_cancel;
};

typedef map<int32_t, seq *> mapseq;

class char_graph
{
    private:

    vector<gr_tex *> imgs;
    gr_sprite *sprite;

    mapseq seqs;

    bool load_pal_pal(const char *file, uint32_t *pal);

    //bool load_pal_bmp(const char *file, uint32_t *pal);

    seq *   cur_seq;
    uint32_t cur_subseq;
    uint32_t cur_frame;
    uint32_t cur_frame_time;
    char_frame * pframe;

    public:

    bool load_dat(const char *name, uint8_t pal);

    void set_img(uint32_t idx);
    void draw(float x, float y);

    void set_seq(uint32_t idx);
    void process_anim();

    char_graph();
  //  ~char_graph();
};


#endif // FRAMEDATA_H_INCLUDED
