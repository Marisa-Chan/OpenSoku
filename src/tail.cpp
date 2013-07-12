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

    if (pts.size() >= (uint32_t)segs)
        pts.pop_back();

    int32_t sz = pts.size();

    switch(sz)
    {
        case 0:
        break;
        case 1:
            for (int32_t i=0; i<vtx_cnt; i++)
                gr_tristrip_set_vtx(strip, i, pts[0].x, pts[0].y);
            break;
        case 2:
            {
                vec2d tmp;
                tmp.x = pts[1].x - pts[0].x;
                tmp.y = pts[1].y - pts[0].y;

                vec2d tmp2;
                vec2d_normolize(&tmp2, &tmp);

                tmp.x = -tmp2.y;
                tmp.y = tmp2.x;

                gr_tristrip_set_vtx(strip, 0, pts[0].x - tmp.x * width , pts[0].y - tmp.y * width,0,0);
                gr_tristrip_set_vtx(strip, 1, pts[0].x + tmp.x * width , pts[0].y + tmp.y * width,1,0);
                gr_tristrip_set_vtx(strip, 2, pts[1].x - tmp.x * width , pts[1].y - tmp.y * width,0,1);
                gr_tristrip_set_vtx(strip, 3, pts[1].x + tmp.x * width , pts[1].y + tmp.y * width,1,1);

                vec2d ed[2];
                ed[0].x = pts[1].x - tmp.x * width;
                ed[0].y = pts[1].y - tmp.y * width;
                ed[1].x = pts[1].x + tmp.x * width;
                ed[1].y = pts[1].y + tmp.y * width;

                for (int32_t i=4; i<vtx_cnt; i+=2)
                {
                    gr_tristrip_set_vtx(strip, i,   ed[0].x, ed[0].y);
                    gr_tristrip_set_vtx(strip, i+1, ed[1].x, ed[1].y);
                }
            }
            break;
        case 3:
            {
                vec2d tmp;
                tmp.x = pts[1].x - pts[0].x;
                tmp.y = pts[1].y - pts[0].y;

                vec2d tmp2;
                vec2d_normolize(&tmp2, &tmp);

                tmp.x = -tmp2.y;
                tmp.y = tmp2.x;

                gr_tristrip_set_vtx(strip, 0, pts[0].x - tmp.x * width , pts[0].y - tmp.y * width,0,0);
                gr_tristrip_set_vtx(strip, 1, pts[0].x + tmp.x * width , pts[0].y + tmp.y * width,1,0);

                tmp.x = pts[2].x - pts[1].x;
                tmp.y = pts[2].y - pts[1].y;

                vec2d_normolize(&tmp2, &tmp);

                tmp.x = -tmp2.y;
                tmp.y = tmp2.x;

                gr_tristrip_set_vtx(strip, 2, pts[1].x - tmp.x * width , pts[1].y - tmp.y * width,0,0.5);
                gr_tristrip_set_vtx(strip, 3, pts[1].x + tmp.x * width , pts[1].y + tmp.y * width,1,0.5);
                gr_tristrip_set_vtx(strip, 4, pts[2].x - tmp.x * width , pts[2].y - tmp.y * width,0,1);
                gr_tristrip_set_vtx(strip, 5, pts[2].x + tmp.x * width , pts[2].y + tmp.y * width,1,1);

                vec2d ed[2];
                ed[0].x = pts[2].x - tmp.x * width;
                ed[0].y = pts[2].y - tmp.y * width;
                ed[1].x = pts[2].x + tmp.x * width;
                ed[1].y = pts[2].y + tmp.y * width;

                for (int32_t i=6; i<vtx_cnt; i+=2)
                {
                    gr_tristrip_set_vtx(strip, i,   ed[0].x, ed[0].y);
                    gr_tristrip_set_vtx(strip, i+1, ed[1].x, ed[1].y);
                }
            }
        break;
        default:
            {
                vec2d lastv;

                for (int32_t i=0; i < sz - 1; i++)
                {
                    vec2d tmp;
                    tmp.x = pts[i+1].x - pts[i].x;
                    tmp.y = pts[i+1].y - pts[i].y;

                    vec2d tmp2;
                    vec2d_normolize(&tmp2, &tmp);

                    tmp.x = -tmp2.y;
                    tmp.y = tmp2.x;

                    lastv = tmp;

                    float tx_v = (float)i/(float)sz;

                    gr_tristrip_set_vtx(strip, i*2,   pts[i].x - tmp.x * width , pts[i].y - tmp.y * width,0,tx_v);
                    gr_tristrip_set_vtx(strip, i*2+1, pts[i].x + tmp.x * width , pts[i].y + tmp.y * width,1,tx_v);
                }
                int32_t id = sz - 1;

                gr_tristrip_set_vtx(strip, id*2,   pts[id].x - lastv.x * width , pts[id].y - lastv.y * width,0,1);
                gr_tristrip_set_vtx(strip, id*2+1, pts[id].x + lastv.x * width , pts[id].y + lastv.y * width,1,1);

                vec2d ed[2];
                ed[0].x = pts[id].x - lastv.x * width;
                ed[0].y = pts[id].y - lastv.y * width;
                ed[1].x = pts[id].x + lastv.x * width;
                ed[1].y = pts[id].y + lastv.y * width;

                for (int32_t i=(id+1)*2; i<vtx_cnt; i+=2)
                {
                    gr_tristrip_set_vtx(strip, i,   ed[0].x, ed[0].y);
                    gr_tristrip_set_vtx(strip, i+1, ed[1].x, ed[1].y);
                }
            }
        break;
    }
}

void c_tail::draw()
{
    gr_tristrip_draw(strip, blending, 1);
}

c_tail::~c_tail()
{
    gr_tristrip_free(strip);
    pts.clear();
    vtx.clear();
}
