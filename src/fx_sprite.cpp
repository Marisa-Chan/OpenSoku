#include "global_types.h"
#include <math.h>
#include "archive.h"
#include "file_read.h"
#include "scene_fx.h"


sc_fx_sprite::sc_fx_sprite()
{
    sprite  = gr_create_sprite();
    pframe  = NULL;
    cur_seq = NULL;
    cur_subseq = 0;
    cur_frame  = 0;
    cur_frame_time = 0;
    elaps_frames = 0;
    _num_frames = 0;
    _cur_sseq = NULL;
}

sc_fx_sprite::~sc_fx_sprite()
{
    delete sprite;
}

uint32_t sc_fx_sprite::get_cur_frame()
{
    return cur_frame;
}

uint32_t sc_fx_sprite::get_cur_subseq()
{
    return cur_subseq;
}

uint32_t sc_fx_sprite::get_cur_frame_time()
{
    return cur_frame_time;
}

uint32_t sc_fx_sprite::get_elaps_frames()
{
    return elaps_frames;
}

sc_fx_frame *sc_fx_sprite::get_pframe()
{
    return pframe;
}

bool sc_fx_sprite::set_seq(sc_seq *sq)
{
    cur_seq = NULL;

    if (sq == NULL)
        return false;

    if (sq->subseqs.size() <= 0)
        return false;

    if (sq->subseqs[0].frames.size() <= 0)
        return false;

    cur_seq = sq;

    reset_seq();

    return true;
}

void sc_fx_sprite::reset_seq()
{
    if (cur_seq == NULL)
        return;

    cur_subseq   = 0;
    elaps_frames = 0;
    _cur_sseq   = &cur_seq->subseqs[cur_subseq];
    _num_frames = _cur_sseq->frames.size();

    set_frame(0);
}

void sc_fx_sprite::frame_val_set()
{
    pframe = cur_seq->subseqs[cur_subseq].frames[cur_frame];

    //if (pframe)
    if (pframe->img)
    {
        gr_set_spr_tex(sprite,pframe->img);

        cur_frame_time = 0;
        cur_duration   = pframe->durate;

        setOrigin(pframe->x_offset,pframe->y_offset);
        if (pframe->type == 2)
        {
            if (pframe->blend_mode == 1)
                setBlend(gr_add);
            else if (pframe->blend_mode == 2)
                setBlend(gr_add);
            else if (pframe->blend_mode == 3)
                setBlend(gr_add);

        }
        setRotate(0,0,0);
        setScale(1.0,1.0);
        setColor(255,255,255,255);
    }
}

void sc_fx_sprite::set_frame(uint32_t frm)
{
    if (cur_seq == NULL || frm >= _num_frames)
        return;

    cur_frame = frm;
    frame_val_set();
}

bool sc_fx_sprite::next_frame(bool ignore_loop)
{
    cur_frame = (cur_frame + 1) % _num_frames;
    frame_val_set();

    return (cur_frame == 0) && ((_cur_sseq->looped == 0) || ignore_loop);
}

bool sc_fx_sprite::next_subseq()
{
    uint32_t tmp = cur_subseq;
    cur_subseq = (cur_subseq + 1) % cur_seq->subseqs.size();

    if (tmp != cur_subseq)
        elaps_frames = 0;


    _cur_sseq   = &cur_seq->subseqs[cur_subseq];
    _num_frames = _cur_sseq->frames.size();

    set_frame(0);

    if (cur_subseq == 0)
    {
        elaps_frames = 0;
        return true;
    }

    return false;
}

bool sc_fx_sprite::set_subseq(uint32_t idx)
{
    uint32_t tmp = cur_subseq;
    cur_subseq = idx % cur_seq->subseqs.size();

    if (tmp != cur_subseq)
        elaps_frames = 0;


    _cur_sseq   = &cur_seq->subseqs[cur_subseq];
    _num_frames = _cur_sseq->frames.size();

    set_frame(0);

    if (cur_subseq == 0)
    {
        elaps_frames = 0;
        return true;
    }

    return false;
}

bool sc_fx_sprite::process(bool ignore_loop)
{
    elaps_frames++;
    cur_frame_time++;
    if (cur_frame_time >= cur_duration)
        if (next_frame(ignore_loop))
            return next_subseq();
    return false;
}

void sc_fx_sprite::draw(uint8_t plane)
{
    gr_draw_sprite(sprite,blend,plane);
}



void sc_fx_sprite::setXY(float x, float y)
{
    gr_setxy_sprite(sprite,x,-y);
}

void sc_fx_sprite::setScale(float x, float y)
{
    if (pframe)
    {
        gr_setscale_sprite(sprite,x*pframe->scale_x,y*pframe->scale_x);
    }
    else
        gr_setscale_sprite(sprite,x,y);
}

void sc_fx_sprite::setOrigin(float x, float y)
{
    gr_setorigin_sprite(sprite,x,y);
}

void sc_fx_sprite::setBlend(gr_blend _blend)
{
    blend = _blend;
}

void sc_fx_sprite::setRotate(float angl)
{
    if (pframe)
        gr_setrotate_sprite(sprite,angl+pframe->angle_z);
    else
        gr_setrotate_sprite(sprite,angl);
}

void sc_fx_sprite::setRotate(float x, float y, float z)
{
    if (pframe)
    {
        float rx,ry,rz;
        euler_mult(pframe->angle_x,pframe->angle_y,pframe->angle_z,x,y,z,rx,ry,rz);
        gr_setrotate_sprite(sprite,rx,ry,rz);
    }
    else
        gr_setrotate_sprite(sprite,x,y,z);
}

uint32_t sc_fx_sprite::get_seq_id()
{
    return cur_seq->id;
}


void sc_fx_sprite::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (pframe)
        gr_setcolor_sprite(sprite, (r*pframe->c_R) / 255,
                                   (g*pframe->c_G) / 255,
                                   (b*pframe->c_B) / 255,
                                   (a*pframe->c_A) / 255);
    else
        gr_setcolor_sprite(sprite, r,g,b,a);
}
