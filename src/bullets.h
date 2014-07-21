#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

#include "tail.h"

class char_c;
class c_bullet;

typedef list<c_bullet *> bullist;
typedef list<c_bullet *>::iterator bullist_iter;

class c_bullet : public c_meta
{
    friend void updatebullet(char_c *chr);
    friend void drawbullet(char_c *chr, int8_t order);
    friend class marisa_bullets;
    friend class alice_bullets;

    protected:


    int8_t order;

    float addition[12];

    public:

    c_bullet *bul_parent;
    bullist   bul_childs;

    bool  active;

    bool sub_48C640(int32_t p);
    bool sub_48C6A0(int32_t p1, int32_t p2, int32_t p3);
    void sub_48C4B0(float p1, float p2, float p3);
    bool sub_48C5F0(int32_t a2);
    void sub_438450(int32_t x, int32_t y, int32_t w, int32_t h);
    void tail_add(int32_t idx, float width, int32_t segments, int32_t seg_subd, gr_blend blending);
    void tail_alpha(uint8_t a);
    void sub_48BF60(int32_t angle);

    c_tail *tail;


    int16_t field_360;
    int16_t field_368;
    int16_t field_36C;
    int16_t field_36E;
    int16_t field_370;
    int16_t field_372;
    int16_t field_374;
    float   field_378;
    float   field_37C;
    float   field_380;
    float   field_384;
    float   field_388;
    int16_t field_394;
    int16_t field_396;


    c_bullet();
    virtual ~c_bullet();

    //call this after creation
    void init(char_c *parent,c_bullet *bul, int32_t idx, float x, float y, int8_t dir, int8_t order, float *addit, int8_t num, char_graph *pgp = NULL);

    void set_seq(uint32_t idx);

    void sub_4B0750();

    virtual void func10();
    virtual void set_seq_params(); //func15
    virtual void func16();


    virtual void draw_shadow(shd_trans *trans, gr_shader *shader = NULL);
    virtual void draw(gr_shader *shader = NULL);
};



void addbullet(char_c *chr,c_bullet *bul, int32_t idx, float x, float y, int8_t dir, int8_t order,float *addit, int8_t num);
void updatebullet(char_c *chr);
void drawbullet(char_c *chr, int8_t order);

void bul_follow_char(c_bullet *bul, int32_t h_inerc, int32_t v_inerc);
void bullets_init_common();

#include "chars/marisa_bullets.h"
#include "chars/alice_bullets.h"
#include "chars/cirno_bullets.h"

#endif // BULLETS_H_INCLUDED
