#ifndef BULLETS_H_INCLUDED
#define BULLETS_H_INCLUDED

class char_c;
class c_bullet;

typedef list<c_bullet *> bullist;
typedef list<c_bullet *>::iterator bullist_iter;

class c_bullet : public c_meta
{
    friend void updatebullet(char_c *chr);
    friend void drawbullet(char_c *chr, int8_t order);

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


    int16_t field_360;
    int16_t field_36C;
    int16_t field_370;
    float   field_378;
    float   field_37C;
    float   field_380;
    int16_t field_396;
    int16_t field_36E;

    c_bullet();
    void init(char_c *parent,c_bullet *bul, seq *sq,int32_t idx, float x, float y, int8_t dir, int8_t order, float *addit, int8_t num); //call this after creation

    virtual void func10();
    virtual void set_seq_params(); //func15
    //virtual void func16();
    //virtual void func18();
    //virtual void func20();
    virtual void draw(int8_t plane = 0);
    virtual ~c_bullet();
};



void addbullet(char_c *chr,c_bullet *bul, int32_t idx, float x, float y, int8_t dir, int8_t order,float *addit, int8_t num);
void updatebullet(char_c *chr);
void drawbullet(char_c *chr, int8_t order);

#include "chars/marisa_bullets.h"
#include "chars/alice_bullets.h"

#endif // BULLETS_H_INCLUDED
