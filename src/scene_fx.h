#ifndef SCENE_FX_H_INCLUDED
#define SCENE_FX_H_INCLUDED

using namespace std;

struct sc_fx_frame
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

struct sc_subseq
{
    vector<sc_fx_frame *> frames; //Frames of that ATOM seq
    uint8_t     looped;
};

struct sc_seq
{
    vector<sc_subseq>   subseqs;
    uint32_t    id;
    uint32_t    refcount;
};


class sc_fx_sprite
{
    protected:

    gr_sprite  *sprite;
    gr_blend    blend;

    sc_seq     *cur_seq;
    sc_fx_frame *pframe;

    uint32_t cur_subseq;
    uint32_t cur_frame;
    uint32_t cur_frame_time;
    uint32_t cur_duration;
    uint32_t elaps_frames;

    uint32_t  _num_frames;
    sc_subseq   *_cur_sseq;

    void frame_val_set();

    public:

    sc_fx_sprite();
    ~sc_fx_sprite();

    uint32_t get_cur_subseq();
    uint32_t get_cur_frame();
    uint32_t get_cur_frame_time();
    uint32_t get_elaps_frames();
    sc_fx_frame * get_pframe();
    uint32_t get_seq_id();

    bool set_seq(sc_seq *sq);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool set_subseq(uint32_t idx);
    bool process(bool ignore_loop = false);

    void setXY(float x, float y);
    void setScale(float x, float y);
    void setOrigin(float x, float y);
    void setBlend(gr_blend blend);
    void setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void setRotate(float angl);
    void setRotate(float x, float y, float z);

    void draw(uint8_t plane = 0);
};

class char_c;

class c_scene_fx
{
    public:
    c_scene_fx(sc_seq *sq, char_c *chr, float x, float y, int8_t dir, int8_t order);
    sc_fx_sprite viz;

    float x;
    float y;
    int8_t dir;
    int8_t order;
    float h_inerc;
    float v_inerc;
    float v_force;

    float angX;
    float angY;
    float angZ;

    float scaleX;
    float scaleY;

    bool  active;

	uint8_t  c_A;
	uint8_t  c_R;
	uint8_t  c_G;
	uint8_t  c_B;

	char_c *parent;

    void func10();
    void set_seq_params(); //func15
    void draw(int8_t plane);
};

typedef map<int32_t, sc_seq *> map_c_seq;

class c_scene_sp
{
    private:

    bool load_pal_pal(const char *file, uint32_t *pal);
    sc_seq *get_seq(uint32_t idx);

    public:

    vector<gr_tex *> imgs;
    map_c_seq seqs;

    vector<c_scene_fx *> fx;

    bool load_dat();

    void addeffect(char_c *chr, int32_t idx, float x, float y, int8_t dir, int8_t order);
    void update();
    void draw(int8_t order);

};

#endif // SCENE_FX_H_INCLUDED
