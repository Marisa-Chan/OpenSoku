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

class c_meta : public moveable
{
    private:
    int32_t index;
    public:
    char_graph *pgp; //Pointer Graph Parent

    c_meta(char_graph *pgp);
    c_meta();

    c_meta  *parent_mlist;
    metalst childs;
    int32_t field_190;
    int8_t  field_194;
    int16_t hit_stop;
    int8_t  field_1A0;
    int8_t  field_1A1;
    int16_t field_1A2;
    float   field_1A4;
    float   field_1A8;
    int8_t  field_1AC;
    int16_t field_1B4;
    int8_t  field_1B8;
    int16_t field_1BC;
    int16_t field_394;

    int16_t field_1C8;
    int8_t  field_1CA;
    int8_t  atk_box_cnt; //0x1CB
    int8_t  hit_box_cnt; //0x1CC

    int16_t health;
    int16_t max_health;

    char_c *enemy;
    char_c *chrt;  //for char classes - it's self, for bullets - char caster

    char_sprite sprite;

    //boxes

    frame_box hit_area_2o[5];
    frame_box atk_area_2o[16];

    frame_box *atk_area_of[5];
    frame_box *hit_area_flags[6];

    frame_box *field_348;

    custom_box *cust_box;

    //////////

    virtual void set_seq(uint32_t idx);

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

    seq *get_seq(uint32_t idx);

};

#endif // META_H_INCLUDED
