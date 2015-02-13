#ifndef META_H_INCLUDED
#define META_H_INCLUDED


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

#define PMOVE_NRNR      0x1
#define PMOVE_NLNL      0x2
#define PMOVE_N08       0x4
#define PMOVE_N07       0x8
#define PMOVE_N09       0x10
#define PMOVE_DD        0x20

#define PCOMB_236A      0x1
#define PCOMB_236B      0x2
#define PCOMB_236C      0x4
#define PCOMB_236D      0x8
#define PCOMB_214A      0x10
#define PCOMB_214B      0x20
#define PCOMB_214C      0x40
#define PCOMB_214D      0x80
#define PCOMB_623A      0x100
#define PCOMB_623B      0x200
#define PCOMB_623C      0x400
#define PCOMB_623D      0x800
#define PCOMB_421A      0x1000
#define PCOMB_421B      0x2000
#define PCOMB_421C      0x4000
#define PCOMB_421D      0x8000
#define PCOMB_412A      0x10000
#define PCOMB_412B      0x20000
#define PCOMB_412C      0x40000
#define PCOMB_412D      0x80000
#define PCOMB_4136A     0x100000
#define PCOMB_4136B     0x200000
#define PCOMB_4136C     0x400000
#define PCOMB_4136D     0x800000
#define PCOMB_6314A     0x1000000
#define PCOMB_6314B     0x2000000
#define PCOMB_6314C     0x4000000
#define PCOMB_6314D     0x8000000
#define PCOMB_2N2A      0x10000000
#define PCOMB_2N2B      0x20000000
#define PCOMB_2N2C      0x40000000
#define PCOMB_2N2D      0x80000000



#include "framedata.h"

class char_c;

class c_meta;

typedef list<c_meta *> metalst;
typedef list<c_meta *>::iterator metalst_iter;

struct shd_trans
{
    gr_transform trans;

    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};

class c_meta : public moveable
{
private:
    int32_t index;

protected:

public:
    char_graph *pgp; //Pointer Graph Parent

    c_meta(char_graph *pgp);
    c_meta();
    virtual ~c_meta();


//-------------------------------------------
    int32_t shader_type;    //0x110
    uint8_t  shader_cB;     //0x114
    uint8_t  shader_cG;     //0x115
    uint8_t  shader_cR;     //0x116
    uint8_t  shader_cA;     //0x117

    //charstruct_with_vector_1 *char_images_vector; //0x130
    //char y_to_down;           //0x134 y axis directed to up  Implimented in moveable
    int8_t  has_shadow;         //0x135
    //__int16 field_136;
    float  field_138;           //Shadow vertical offset
    //__int16 playing_seq;      //0x13C
    //__int16 viz.get_subseq;   //0x13E
    //__int16 viz.get_frame;    //0x140
    //__int16 viz.get_frame_time; //0x142
    //int viz.get_elaps_frames; //0x144
    //__int16 seq_frames_count; //0x148
    //__int16 field_14A;
    //__int16 cur_frame_duration;//0x14C
    //__int16 field_14E;
    //frame_head *rendering_frame; //0x150
    //struc_154 *field_154;         //0x154
    //frame_head *current_frame_params; //0x158
    //num_of_seqs *current_seq_frames_vector; //0x15C
    //mapstru* pat_map   ;      //0x160
    //int sounds_max_256;       //0x164
    char_c  *chrt;  //for char classes - it's self, for bullets - char caster  0x168
    char_c  *chrt_changeable;  //holder of parent class  0x16C
    char_c  *enemy;          //0x170
    c_meta  *parent;  //0x174
    metalst childs;         //0x178 + 0xC
    int16_t health;         //0x184
    int16_t max_health;     //0x186
    int32_t field_188;
    int8_t  field_18C;
    //char  field_18D;
    //char  field_18E;
    //char  field_18F;
    int32_t field_190;
    int8_t  field_194;
    //char  field_195;
    int16_t hit_stop;
    float   field_198;
    float   field_19C;
    int8_t  field_1A0;
    int8_t  field_1A1;
    int16_t field_1A2;
    float   field_1A4;
    float   field_1A8;
    int8_t  field_1AC;
    //char  field_1AD;
    //char  field_1AE;
    //char  field_1AF;
    custom_box *cust_box; //0x1B0
    int16_t field_1B4;
    //__int16 field_1B6;
    int32_t field_1B8;
    int16_t field_1BC;
    //char  field_1BD;
    //char  field_1BE;
    //char  field_1BF;
    //frame_head *current_frame_params2?;   //0x1C0
    //num_of_seqs *num_of_seqs?;        //0x1C4
    int16_t field_1C8;
    int8_t  field_1CA;
    int8_t  atk_box_cnt; //0x1CB
    int8_t  hit_box_cnt; //0x1CC
    //char  field_1CD;
    //char  field_1CE;
    //char  field_1CF;
    frame_box hit_area_2o[5];   //0x1D0 + 0x50
    frame_box atk_area_2o[16];  //0x220 + 0x100
    frame_box *atk_area_of[5];  //0x320 + 0x14
    frame_box *hit_area_flags[6];   //0x334 + 0x18
//-------------------------------------------


    char_sprite sprite;

    frame_box *pcoll_box; //hit_area_flags[5] !!! HACK? $%%@#$

    bool process(bool ignore_loop = false);
    void reset_seq();
    void set_frame(uint32_t frm);
    bool next_frame(bool ignore_loop = false);
    bool next_subseq();
    bool set_subseq(uint32_t idx);
    uint32_t get_subseq();
    uint32_t get_frame();
    uint32_t get_frame_time();
    uint32_t get_elaps_frames();
    char_frame * get_pframe();
    uint32_t get_seq();
    uint16_t get_cprior();
    uint16_t get_prior();

    uint16_t get_cprior(uint32_t idx);
    uint16_t get_prior(uint32_t idx);

    void set_mlist_hitflag(int8_t flag );
    int32_t sub_464240();
    double sub_4636B0();
    float sub_464270();
    void sub_4647B0(c_meta *enm);
    void sub_464890(c_meta *enm);
    float sub_4634F0();
    void sub_464110(int32_t a2, int32_t a3, int32_t a4, int32_t a5);

    void box_coll_get(box_box *box);

    void set_custom_box(int32_t x1, int32_t y1, int32_t x2, int32_t y2, float angl, int32_t dx, int32_t dy);

    void frame_box_fullflip( frame_box *src, frame_box *dst);
    void frame_box_flip(frame_box *src, frame_box *dst);

    void scn_char_ss2();

    seq *get_seq(uint32_t idx);


    virtual void set_seq(uint32_t idx);

    virtual void draw_shadow(shd_trans *trans, gr_shader *shader = NULL);
    virtual void draw(gr_shader *shader = NULL);

    virtual void func10() = 0;
    virtual void set_seq_params() = 0; //func15
    virtual void func16() = 0;
};

void frame_box_move_rotate(frame_box *src, int16_t angle, int16_t x_c, int16_t y_c, frame_box *dst1, frame_box *dst2);



#endif // META_H_INCLUDED
