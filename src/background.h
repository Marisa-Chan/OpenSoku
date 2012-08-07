#ifndef BACKGROUND_H_INCLUDED
#define BACKGROUND_H_INCLUDED

using namespace std;

struct bkg_chunk
{
    gr_tex * tex;
    float x;
    float y;
};

class background
{
    protected:

    vector<bkg_chunk> imgs;
    gr_sprite       *spr;

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


#endif // BACKGROUND_H_INCLUDED
