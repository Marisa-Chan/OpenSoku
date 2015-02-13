#ifndef TAIL_H_INCLUDED
#define TAIL_H_INCLUDED

#include <deque>

using namespace std;

class c_tail
{
private:
    gr_tristrip *strip;
    float width;
    int32_t segs;
    int32_t subdiv;
    int32_t vtx_cnt;
    gr_blend blending;

    deque<vec2d>  pts;
    deque<vec2d>  vtx;

public:

    c_tail(gr_tex *tex, uint8_t a, uint8_t r,uint8_t g, uint8_t b, float width, int32_t segs, int32_t subdiv, gr_blend blending);
    ~c_tail();

    void update(float x, float y);
    void draw();
    void set_alpha(uint8_t a);
};


#endif // TAIL_H_INCLUDED
