#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "gui.h"

bool gui_holder::load_dat(const char *path, const char *file)
{
    char buf[CHRBUF];

    sprintf(buf, "%s/%s", path, file);

    filehandle *f = arc_get_file(buf);

    if (!f)
        return false;

    uint32_t gui_version;

    f->read(4, &gui_version);

    uint32_t tex_count;

    f->read(4, &tex_count);

    imgs.resize(tex_count);

    for (uint32_t i=0; i<tex_count; i++)
    {
        gui_tex tmp;

        char name[260];

        uint32_t len;
        f->read(4, &len);

        f->read(len,name);

        for (uint32_t j=len-1; j>0; j--)
            if (name[j] == '.')
            {
                name[j+1] = 'c';
                name[j+2] = 'v';
                name[j+3] = '2';
                name[j+4] = 0;
                break;
            }

        sprintf(buf, "%s/%s", path, name);

        tmp.tex = NULL;

        filehandle *ft = arc_get_file(buf);
        if (ft)
        {
            tmp.tex = gr_load_cv2(ft, NULL);
            delete ft;
        }

        f->read(4, &tmp.l);
        f->read(4, &tmp.t);
        f->read(4, &tmp.r);
        f->read(4, &tmp.b);

        imgs[i] = tmp;
    }

    uint32_t items;
    f->read(4, &items);

    elmnt.resize(items);

    for (uint32_t i=0; i<items; i++)
    {
        int32_t guid;
        int8_t  type;
        f->read(4, &guid);
        f->read(1, &type);

        gui_element *lmnt = NULL;
        int32_t tmp;
        switch(type)
        {
        case 0:
        case 2:
        case 3:
        case 4:
        case 5:
        {
            int32_t tid, x, y, invert;
            f->read(4, &tid);
            f->read(4, &x);
            f->read(4, &y);
            f->read(4, &invert);
            gui_el_t0 *t0 = new gui_el_t0(guid, &imgs[tid]);
            t0->setXY(x,y);
            if (invert & 1)
                t0->setScale(-1,1);
            else
                t0->setScale(1,1);
            lmnt = t0;
        }
        break;

        case 1:
            //lmnt = new gui_element;
            //lmnt->tex = NULL;
            f->read(4, &tmp);
            //lmnt->x = tmp;
            f->read(4, &tmp);
            //lmnt->y = tmp;
            break;

        case 6:
        {
            int32_t tid, w, h, x, y, frames, dw, intg, flt;
            f->read(4, &tid);
            f->read(4, &x);
            f->read(4, &y);
            f->read(4, &w);
            f->read(4, &h);
            f->read(4, &frames);
            f->read(4, &dw);
            f->read(4, &intg);
            f->read(4, &flt);

            gui_el_t6 *t6 = new gui_el_t6(guid, &imgs[tid],w,h,frames,dw, intg, flt);
            t6->setXY(x,y);
            t6->setScale(1,1);

            lmnt = t6;
        }
        break;

        default:
            lmnt = NULL;
        }

        elmnt[i] = lmnt;
    }

    return true;
}

void gui_holder::draw_all(int8_t plane)
{
    for (uint32_t i=0; i<elmnt.size(); i++)
    {
        if (elmnt[i])
            elmnt[i]->draw(plane);
    }
}

gui_el_t6 * gui_holder::get_gui_t6(int32_t id)
{
    for (uint32_t i=0; i< elmnt.size(); i++)
        if (elmnt[i])
            if (elmnt[i]->guid == id && elmnt[i]->get_type() == 2)
                return (gui_el_t6 *)elmnt[i];

    return NULL;
}

gui_el_t0 * gui_holder::get_gui_t0(int32_t id)
{
    for (uint32_t i=0; i< elmnt.size(); i++)
        if (elmnt[i])
            if (elmnt[i]->guid == id && elmnt[i]->get_type() == 0)
                return (gui_el_t0 *)elmnt[i];

    return NULL;
}


gui_element::gui_element(int32_t _guid):
    guid (_guid)
{
    sprite = new gr_sprite;
}

void gui_element::setScale(float x, float y)
{
    sx = x;
    sy = y;
}

void gui_element::setXY(float _x, float _y)
{
    x = _x;
    y = _y;
}



gui_el_t6::gui_el_t6(int32_t _guid, gui_tex *_tex, int32_t _w, int32_t _h, int32_t _frames, int32_t _dw, int32_t _intg, int32_t _flt):
    gui_element(_guid)
{
    tex = _tex;
    w = _w;
    h = _h;
    frames = _frames;
    intg = _intg;
    flt = _flt;
    dw = _dw;
}

void gui_el_t6::draw_d(float _dx, float _dy, int8_t plane)
{
    int32_t pl = 1;
    float xx = -w * sx + _dx;

    if (intg > 0)
    {
        for (int8_t i=0; i<intg; i++)
        {
            if (vard < 0 && pl > abs(vard) && i == (intg-1))
            {
                draw_frame(11, xx, _dy, plane);
            }
            else
            {
                int32_t cf = abs(vard / pl) % 10;
                draw_frame(cf, xx, _dy, plane);
                pl *= 10;
                xx -= (w + dw) * sx;
            }
        }
    }
    else
    {
        while ( pl <= abs(vard) || pl == 1)
        {
            int32_t cf = abs(vard / pl) % 10;
            draw_frame(cf, xx, _dy, plane);
            pl *= 10;
            xx -= (w + dw) * sx;
        }
        if (vard < 0)
            draw_frame(11, xx, _dy, plane);
    }
}

void gui_el_t6::draw_f(float _dx, float _dy, int8_t plane)
{
    int32_t pl = 1;
    for (int8_t i=0; i<flt; i++)
        pl *= 10;

    float xx = -w * sx + _dx;

    for (int8_t i=0; i<flt; i++)
    {
        int32_t cf = (int32_t)abs(varf * pl) % 10;
        draw_frame(cf, xx, _dy, plane);
        pl /= 10;
        xx -= (w + dw) * sx;
    }

    xx += (w + dw) * sx * 0.65;
    draw_frame(12, xx, _dy, plane);
    xx -= (w + dw) * sx;

    pl = 1;
    if (intg > 0)
    {
        for (int8_t i=0; i<intg; i++)
        {
            if (varf < 0 && pl > abs(varf) && i == (intg-1))
            {
                draw_frame(11, xx, _dy, plane);
            }
            else
            {
                int32_t cf = (int32_t)abs(varf / pl) % 10;
                draw_frame(cf, xx, _dy, plane);
                pl *= 10;
                xx -= (w + dw) * sx;
            }
        }
    }
    else
    {
        while ( pl <= abs(varf) || pl == 1)
        {
            int32_t cf = (int32_t)abs(varf / pl) % 10;
            draw_frame(cf, xx, _dy, plane);
            pl *= 10;
            xx -= (w + dw) * sx;
        }
        if (varf < 0)
            draw_frame(11, xx, _dy, plane);
    }
}

void gui_el_t6::draw_frame(int32_t frm, float _dx, float _dy, int8_t plane)
{
    if (frm >= 0 && frm < frames)
    {
    gr_set_spr_tex(sprite, tex->tex, frm* w, 0, w, h);
    gr_setxy_sprite(sprite,x + _dx, y + _dy);
    gr_setscale_sprite(sprite,sx,sy);
    gr_draw_sprite(sprite,gr_alpha,plane);
    }
}

void gui_el_t6::draw(int8_t plane)
{
    if (flt > 0)
        draw_f(0,0,plane);
    else
        draw_d(0,0,plane);
}

void gui_el_t6::draw(float dx, float dy, int8_t plane)
{
    if (flt > 0)
        draw_f(dx,dy,plane);
    else
        draw_d(dx,dy,plane);
}

void gui_el_t6::setFloat(float f)
{
    varf = f;
}

void gui_el_t6::setInt(int32_t d)
{
    vard = d;
}

gui_el_t0::gui_el_t0(int32_t _guid, gui_tex *_tex):
    gui_element(_guid)
{
    tex = _tex;
}

void gui_el_t0::draw(int8_t plane)
{
    gr_set_spr_tex(sprite, tex->tex);
    gr_setxy_sprite(sprite,x, y);
    gr_setscale_sprite(sprite,sx,sy);
    gr_draw_sprite(sprite,gr_alpha,plane);
}

void gui_el_t0::draw(float dx, float dy, int8_t plane)
{
    gr_set_spr_tex(sprite, tex->tex);
    gr_setxy_sprite(sprite,x + dx, y + dy);
    gr_setscale_sprite(sprite,sx,sy);
    gr_draw_sprite(sprite,gr_alpha,plane);
}
