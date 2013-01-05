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
};

class background
{
    protected:

    vector<bkg_chunk> imgs;
    gr_sprite        *spr;
    vector<bkg_chunk >  decor;

    void render(bkg_chunk *);

    public:

    background();
    ~background();

    virtual void draw();
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
    public:
    background_12();

    void draw();
};

#endif // BACKGROUND_H_INCLUDED
