#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "framedata.h"
#include "meta.h"


c_meta::c_meta(char_graph *_pgp)
{
    pgp  = _pgp;
    chrt = NULL;

    cust_box  = NULL;
    parent_mlist = NULL;
    atk_box_cnt = 0;
    hit_box_cnt = 0;
    field_1A0 = 0;
    field_1A1 = 0;
    field_1A2 = 0;
    has_shadow = 1;
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

void c_meta::draw_shadow(shd_trans *trans, gr_shader *shader)
{
}

void c_meta::draw(gr_shader *shader)
{
}

void set_custom_box(c_meta *met, int32_t x1, int32_t y1, int32_t x2, int32_t y2, float angl, int32_t dx, int32_t dy)
{
  if (!met->cust_box)
    met->cust_box = new custom_box;

  if (x1 <= x2)
  {
      met->cust_box->box.x1 = x1;
      met->cust_box->box.x2 = x2;
  }
  else
  {
      met->cust_box->box.x1 = x2;
      met->cust_box->box.x2 = x1;
  }

  if (y1 <= y2)
  {
      met->cust_box->box.y1 = y1;
      met->cust_box->box.y2 = y2;
  }
  else
  {
      met->cust_box->box.y1 = y2;
      met->cust_box->box.y2 = y1;
  }

  met->cust_box->angle = angl;
  met->cust_box->c_x = dx;
  met->cust_box->c_y = dy;
}

