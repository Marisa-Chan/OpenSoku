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

uint32_t char_sprite::get_cur_frame()
{
    return cur_frame;
}

uint32_t char_sprite::get_cur_subseq()
{
    return cur_subseq;
}

uint32_t char_sprite::get_cur_frame_time()
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

    if (pframe->img)
    {
        gr_set_spr_tex(sprite,pframe->img);

        cur_frame_time = 0;
        cur_duration   = pframe->durate;

        setOrigin(pframe->x_offset,pframe->y_offset);
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
    cur_subseq = (cur_subseq + 1) % cur_seq->subseqs.size();

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

void char_sprite::draw(uint8_t plane)
{
    gr_draw_sprite(sprite,blend,plane);
}



void char_sprite::setXY(float x, float y)
{
    gr_setxy_sprite(sprite,x,-y);
}

void char_sprite::setScale(float x, float y)
{
    gr_setscale_sprite(sprite,x,y);
}

void char_sprite::setOrigin(float x, float y)
{
    gr_setorigin_sprite(sprite,x,y);
}

void char_sprite::setBlend(gr_blend _blend)
{
    blend = _blend;
}

uint16_t char_sprite::get_cprior()
{
    return cur_seq->prior_for_cancel;
}

uint16_t char_sprite::get_prior()
{
    return cur_seq->prior;
}

uint32_t char_sprite::get_seq_id()
{
    return cur_seq->id;
}
