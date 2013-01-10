#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "framedata.h"

char_sprite::char_sprite()
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

char_sprite::~char_sprite()
{
    delete sprite;
}

uint32_t char_sprite::get_frame()
{
    return cur_frame;
}

uint32_t char_sprite::get_subseq()
{
    return cur_subseq;
}

uint32_t char_sprite::get_frame_time()
{
    return cur_frame_time;
}

uint32_t char_sprite::get_elaps_frames()
{
    return elaps_frames;
}

char_frame *char_sprite::get_pframe()
{
    return pframe;
}

bool char_sprite::set_seq(seq *sq)
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

void char_sprite::reset_seq()
{
    if (cur_seq == NULL)
        return;

    cur_subseq   = 0;
    elaps_frames = 0;
    _cur_sseq   = &cur_seq->subseqs[cur_subseq];
    _num_frames = _cur_sseq->frames.size();

    set_frame(0);
}

void char_sprite::frame_val_set()
{
    pframe = cur_seq->subseqs[cur_subseq].frames[cur_frame];

    //if (pframe)
    if (pframe->img)
    {
        gr_set_spr_tex(sprite,pframe->img);

        cur_frame_time = 0;
        cur_duration   = pframe->durate;

        setOrigin(0,0);
        if (pframe->type == 2)
        {
            if (pframe->blend_mode == 1)
                setBlend(gr_add);
            else if (pframe->blend_mode == 2)
                setBlend(gr_add);
            else if (pframe->blend_mode == 3)
                setBlend(gr_add);
        }
        else
        {
            setBlend(gr_alpha);
        }
        setRotate(0,0,0);
        setScale(1.0,1.0);
        setColor(255,255,255,255);
    }
}

void char_sprite::set_frame(uint32_t frm)
{
    if (cur_seq == NULL || frm >= _num_frames)
        return;

    cur_frame = frm;
    frame_val_set();
}

bool char_sprite::next_frame(bool ignore_loop)
{
    cur_frame = (cur_frame + 1) % _num_frames;
    frame_val_set();

    return (cur_frame == 0) && ((_cur_sseq->looped == 0) || ignore_loop);
}

bool char_sprite::next_subseq()
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

bool char_sprite::set_subseq(uint32_t idx)
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

bool char_sprite::process(bool ignore_loop)
{
    elaps_frames++;
    cur_frame_time++;
    if (cur_frame_time >= cur_duration)
        if (next_frame(ignore_loop))
            return next_subseq();
    return false;
}

void char_sprite::draw(uint8_t plane, gr_shader *shader)
{
    gr_draw_sprite(sprite,blend,plane,shader);
}



void char_sprite::setXY(float x, float y)
{
    gr_setxy_sprite(sprite,x,-y);
}

void char_sprite::setScale(float x, float y)
{
    if (pframe)
        gr_setscale_sprite(sprite,x*pframe->scale_x,y*pframe->scale_y);
    else
        gr_setscale_sprite(sprite,x,y);
}

void char_sprite::setAScale(float w, float h)
{
    if (pframe)
    {
        //gr_setorigin_sprite(sprite,0,0);
        gr_setscale_sprite(sprite,w / pframe->tx_width, h / pframe->tx_height);
    }
}

void char_sprite::setOrigin(float x, float y)
{
    if (pframe)
    {
        gr_setorigin_sprite(sprite,pframe->x_offset+x/pframe->scale_x,pframe->y_offset+y/pframe->scale_y);
    }
    else
        gr_setorigin_sprite(sprite,x,y);
}

void char_sprite::setBlend(gr_blend _blend)
{
    blend = _blend;
}

void char_sprite::setRotate(float angl)
{
    if (pframe)
    {
        float rx,ry,rz;
        euler_mult(pframe->angle_x,pframe->angle_y,pframe->angle_z,0,0,angl,rx,ry,rz);
        gr_setrotate_sprite(sprite,rx,ry,rz);
    }
    else
        gr_setrotate_sprite(sprite,0,0,angl);
}

void char_sprite::setRotate(float x, float y, float z)
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

uint16_t char_sprite::get_cprior()
{
    if (cur_seq)
        return cur_seq->prior_for_cancel;
    return 0xFFFF;
}

uint16_t char_sprite::get_prior()
{
    if (cur_seq)
        return cur_seq->prior;
    return 0xFFFF;
}

uint32_t char_sprite::get_seq_id()
{
    if (cur_seq)
        return cur_seq->id;
    return 0xFFFFFFFF;
}


void char_sprite::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (pframe)
        gr_setcolor_sprite(sprite, (r*pframe->c_R) / 255,
                           (g*pframe->c_G) / 255,
                           (b*pframe->c_B) / 255,
                           (a*pframe->c_A) / 255);
    else
        gr_setcolor_sprite(sprite, r,g,b,a);
}

gr_info char_sprite::getInfo()
{
    return gr_get_info(sprite);
}
