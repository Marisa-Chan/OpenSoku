#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "framedata.h"
#include "meta.h"


c_meta::c_meta(char_graph *_pgp)
{
    pgp  = _pgp;
    chrt = NULL;
}

c_meta::c_meta():
c_meta(NULL)
{

}

void c_meta::set_seq(uint32_t idx)
{
    // printf("%d\n",idx);
    if (pgp->get_seq(idx))
    {
        index = idx;
        sprite.set_seq(pgp->get_seq(idx));
    }
}

seq *c_meta::get_seq(uint32_t idx)
{
    return pgp->get_seq(idx);
}

bool c_meta::process(bool ignore_loop)
{
    return sprite.process(ignore_loop);
}

bool c_meta::next_frame(bool ignore_loop)
{
    return sprite.next_frame(ignore_loop);
}

bool c_meta::next_subseq()
{
    return sprite.next_subseq();
}

bool c_meta::set_subseq(uint32_t idx)
{
    return sprite.set_subseq(idx);
}

void c_meta::reset_seq()
{
    sprite.reset_seq();
}

void c_meta::set_frame(uint32_t frm)
{
    sprite.set_frame(frm);
}



uint32_t c_meta::get_subseq()
{
    return sprite.get_subseq();
}
uint32_t c_meta::get_frame()
{
    return sprite.get_frame();
}
uint32_t c_meta::get_frame_time()
{
    return sprite.get_frame_time();
}
uint32_t c_meta::get_elaps_frames()
{
    return sprite.get_elaps_frames();
}

char_frame * c_meta::get_pframe()
{
    return sprite.get_pframe();
}


uint32_t c_meta::get_seq()
{
    return index;
}

uint16_t c_meta::get_prior()
{
    return sprite.get_prior();
}
uint16_t c_meta::get_cprior()
{
    return sprite.get_cprior();
}

uint16_t c_meta::get_cprior(uint32_t idx)
{
    if (pgp)
        return pgp->get_cprior(idx);
    else
        return 0xFFFF;
}
uint16_t c_meta::get_prior(uint32_t idx)
{
    if (pgp)
        return pgp->get_prior(idx);
    else
        return 0xFFFF;
}
