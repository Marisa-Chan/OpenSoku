#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

using namespace std;

struct bkg_chunk
{
    gr_tex * tex;
    float x;
    float y;
    float ofx;
    float ofy;

    float ax;
    float ay;
    float az;

    float sx;
    float sy;

    float alpha = 1.0;

    gr_blend blend;
};

class background
{
protected:

    vector<bkg_chunk> imgs;
    gr_sprite        *spr;

    void render(bkg_chunk *);
    void render_move(bkg_chunk *chunk, float x, float y);

    void loadbkg_t1(int32_t id, float y_off);
    void loadbkg_t2(int32_t id, float y_off);

public:
    virtual void update();

    background();
    virtual ~background();

    virtual void draw_back();
    virtual void draw_mid();
    virtual void draw_near();
    virtual void draw_shadow(c_meta *chr);
};

class background_0: public background
{
public:
    background_0();
};

class background_1: public background
{
public:
    background_1();
};

class background_2: public background
{
private:
    vector<bkg_chunk >  left;
    vector<bkg_chunk >  center;
    vector<bkg_chunk >  right;
    uint32_t frame; //828 days capacity xD
public:
    background_2();
    ~background_2();
    void update();
    void draw_back();
};

class background_3: public background
{
public:
    background_3();
};

class background_4: public background
{
private:
    float posit;
    bkg_chunk cloud;
public:
    background_4();
    ~background_4();

    void update();
    void draw_near();
};

class background_5: public background
{
public:
    background_5();
};

class background_6: public background
{
public:
    background_6();
};

class background_10: public background
{
public:
    background_10();
};

class background_11: public background
{
public:
    background_11();
};

class background_12: public background
{
private:
    float angle;
    vector<bkg_chunk >  decor;
public:
    background_12();
    ~background_12();

    void update();
    void draw_back();
};

class background_13: public background
{
public:
    background_13();
};

class background_14: public background
{
public:
    background_14();
};

class background_15: public background
{
public:
    background_15();
};

class background_16: public background
{
private:
    float angle;
    vector<bkg_chunk >  decor;
public:
    background_16();
    ~background_16();

    void update();
    void draw_near();
    void draw_mid();
    void draw_shadow(c_meta *chr);
};

class background_17: public background
{
public:
    background_17();
};

class background_18: public background
{
public:
    background_18();
};

class background_30: public background
{
public:
    background_30();
};

class background_31: public background
{
public:
    background_31();
};

class background_32: public background
{
public:
    background_32();
};

class background_33: public background
{
private:
    int32_t posit;
    bkg_chunk floor;
    bkg_chunk effect;
public:
    background_33();
    ~background_33();

    void update();
    void draw_back();
};

class background_34: public background
{
private:
    int32_t frame;
    bkg_chunk floor;
    bkg_chunk effect;
    bkg_chunk shadow;
    bkg_chunk gradient;
    vector<bkg_chunk >  reaction;
public:
    background_34();
    ~background_34();

    void update();
    void draw_back();
    void draw_near();
    void draw_shadow(c_meta *chr);
};

class background_36: public background
{
private:
    float angle;
    bkg_chunk tori[2];
    float     pos[2];
    bkg_chunk cloud[2];
public:
    background_36();
    ~background_36();

    void update();
    void draw_back();
};

class background_37: public background
{
private:
    float angle;
    bkg_chunk tori;
    float     pos[2];
    bkg_chunk cloud[2];
public:
    background_37();
    ~background_37();

    void update();
    void draw_back();
};

class background_38: public background
{
private:
    float     pos[2];
    bkg_chunk cloud[2];
public:
    background_38();
    ~background_38();

    void update();
    void draw_back();
};


background * bkg_create(uint32_t idx);

#endif // BACKGROUND_H_INCLUDED
