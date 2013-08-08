#include "global_types.h"
#include "graph.h"
#include "tail.h"

c_tail::c_tail(gr_tex *tex, uint8_t a, uint8_t r,uint8_t g, uint8_t b, float _width, int32_t _segs, int32_t _subdiv, gr_blend _blending)
{
    strip = gr_tristrip_new(_segs * _subdiv * 2 + 2);

    if (tex)
        gr_tristrip_set_tex(strip, tex);

    gr_tristrip_set_color(strip, a, r, g, b);

    blending = _blending;

    segs = _segs;
    subdiv = _subdiv;
    width = _width;

    vtx_cnt = segs * subdiv * 2 + 2;

    pts.clear();
    vtx.clear();
}

void c_tail::update(float x, float y)
{
    vec2d pos;
    pos.x = x;
    pos.y = -y;

    pts.push_front(pos);

    int32_t sz = pts.size();

    switch(sz)
    {
        case 0:
            break;
        case 1:
            vtx.push_back(pts[0]);
            vtx.push_back(pts[0]);
            break;
        case 2:
            {
                vec2d tmp;
                tmp.x = pts[0].y - pts[1].y;
                tmp.y = pts[1].x - pts[0].x;

                vec2d tmp2;
                vec2d_normolize(&tmp2, &tmp);

                vtx[1].x += tmp2.x * width;
                vtx[1].y += tmp2.y * width;

                vtx[0].x -= tmp2.x * width;
                vtx[0].y -= tmp2.y * width;

                vec2d t1, t2;
                t1.x = 0;
                t1.y = 0;
                t2.x = 0;
                t2.y = 0;

                vec2d pred;
                pred = pts[1];

                for (int32_t i = subdiv - 1; i >= 0; i--)
                {
                    vec2d pout;
                    vec2d_hermit(&pout, &pts[0], &t1, &pts[1], &t2, (float)i / (float)subdiv);

                    tmp.x = pout.y - pred.y;
                    tmp.y = pred.x - pout.x;
                    vec2d_normolize(&tmp2, &tmp);

                    tmp.x = pout.x + tmp2.x * width;
                    tmp.y = pout.y + tmp2.y * width;
                    vtx.push_front(tmp);

                    tmp.x = pout.x - tmp2.x * width;
                    tmp.y = pout.y - tmp2.y * width;
                    vtx.push_front(tmp);

                    pred = pout;
                }
            }
            break;
        case 3:
            {
                vec2d tmp2;
                tmp2.x = pts[2].x - pts[0].x;
                tmp2.y = pts[2].y - pts[0].y;

                vtx.erase(vtx.begin(), vtx.begin() + subdiv * 2);

                vec2d t1, t2;
                t1.x = 0;
                t1.y = 0;
                t2.x = 0;
                t2.y = 0;

                vec2d pred;
                pred = pts[2];

                for (int32_t i = subdiv - 1; i >= 0; i--)
                {
                    vec2d pout;
                    vec2d_hermit(&pout, &pts[1], &tmp2, &pts[2], &t2, (float)i / (float)subdiv);

                    vec2d tmp;
                    tmp.x = pout.y - pred.y;
                    tmp.y = pred.x - pout.x;

                    vec2d norm;
                    vec2d_normolize(&norm, &tmp);

                    tmp.x = pout.x + norm.x * width;
                    tmp.y = pout.y + norm.y * width;
                    vtx.push_front(tmp);

                    tmp.x = pout.x - norm.x * width;
                    tmp.y = pout.y - norm.y * width;
                    vtx.push_front(tmp);

                    pred = pout;
                }

                for (int32_t i = subdiv - 1; i >= 0; i--)
                {
                    vec2d pout;
                    vec2d_hermit(&pout, &pts[0], &t1, &pts[1], &tmp2, (float)i / (float)subdiv);

                    t1.x = pout.y - pred.y;
                    t1.y = pred.x - pout.x;

                    vec2d norm;
                    vec2d_normolize(&norm, &t1);

                    vec2d tmp;

                    tmp.x = pout.x + norm.x * width;
                    tmp.y = pout.y + norm.y * width;
                    vtx.push_front(tmp);

                    tmp.x = pout.x - norm.x * width;
                    tmp.y = pout.y - norm.y * width;
                    vtx.push_front(tmp);

                    pred = pout;
                }
            }
        break;
        default:
            {
                vec2d t1, t2;
                t1.x = pts[2].x - pts[0].x;
                t1.y = pts[2].y - pts[0].y;

                t2.x = pts[3].x - pts[1].x;
                t2.y = pts[3].y - pts[1].y;

                vtx.erase(vtx.begin(), vtx.begin() + subdiv * 2);

                vec2d pred;
                pred = pts[2];

                for (int32_t i = subdiv - 1; i >= 0; i--)
                {
                    vec2d pout;
                    vec2d_hermit(&pout, &pts[1], &t1, &pts[2], &t2, (float)i / (float)subdiv);

                    t2.x = pout.y - pred.y;
                    t2.y = pred.x - pout.x;

                    vec2d norm;
                    vec2d_normolize(&norm, &t2);

                    vec2d tmp;

                    tmp.x = pout.x + norm.x * width;
                    tmp.y = pout.y + norm.y * width;
                    vtx.push_front(tmp);

                    tmp.x = pout.x - norm.x * width;
                    tmp.y = pout.y - norm.y * width;
                    vtx.push_front(tmp);

                    pred = pout;
                }

                vec2d zero;
                zero.x = 0;
                zero.y = 0;

                for (int32_t i = subdiv - 1; i >= 0; i--)
                {
                    vec2d pout;
                    vec2d_hermit(&pout, &pts[0], &zero, &pts[1], &t1, (float)i / (float)subdiv);

                    zero.x = pout.y - pred.y;
                    zero.y = pred.x - pout.x;

                    vec2d norm;
                    vec2d_normolize(&norm, &zero);

                    vec2d tmp;

                    tmp.x = pout.x + norm.x * width;
                    tmp.y = pout.y + norm.y * width;
                    vtx.push_front(tmp);

                    tmp.x = pout.x - norm.x * width;
                    tmp.y = pout.y - norm.y * width;
                    vtx.push_front(tmp);

                    pred = pout;
                }

            }
        break;
    }

    if (pts.size() > (uint32_t)segs + 1)
        pts.erase(pts.begin() + segs + 1, pts.end());

    if (vtx.size() > (uint32_t)vtx_cnt)
        vtx.erase(vtx.begin() + vtx_cnt, vtx.end());
}

void c_tail::draw()
{
    int32_t num = vtx.size() & 0xFFFFFFFE;
    int32_t vseg = num / 2;

    for (int32_t i=0; i< num && i < vtx_cnt; i++)
    {
        int32_t vp = i/2;
        gr_tristrip_set_vtx(strip, i, vtx[i].x, vtx[i].y, i % 2, (float)vp / (float)vseg);
    }


    vec2d last[2];
    last[0] = vtx[num - 2];
    last[1] = vtx[num - 1];

    for (int32_t i=num; i< vtx_cnt; i++)
        gr_tristrip_set_vtx(strip, i, last[i % 2].x, last[i % 2].y, i % 2, 1.0);

    gr_tristrip_draw(strip, blending, 1);
}

void c_tail::set_alpha(uint8_t a)
{
    gr_tristrip_set_color(strip, a ,255 ,255, 255);
}

c_tail::~c_tail()
{
    gr_tristrip_free(strip);
    pts.clear();
    vtx.clear();
}
