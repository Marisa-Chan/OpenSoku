#include "global_types.h"
#include <math.h>
#include "archive.h"
#include "file_read.h"
#include "graph_efx.h"


gfx_sprite::gfx_sprite()
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

gfx_sprite::~gfx_sprite()
{
    delete sprite;
}

uint32_t gfx_sprite::get_cur_frame()
{
    return cur_frame;
}

uint32_t gfx_sprite::get_cur_subseq()
{
    return cur_subseq;
}

uint32_t gfx_sprite::get_cur_frame_time()
{
    return cur_frame_time;
}

uint32_t gfx_sprite::get_elaps_frames()
{
    return elaps_frames;
}

gfx_frame *gfx_sprite::get_pframe()
{
    return pframe;
}

bool gfx_sprite::set_seq(gfx_seq *sq)
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

void gfx_sprite::reset_seq()
{
    if (cur_seq == NULL)
        return;

    cur_subseq   = 0;
    elaps_frames = 0;
    _cur_sseq   = &cur_seq->subseqs[cur_subseq];
    _num_frames = _cur_sseq->frames.size();

    set_frame(0);
}

void gfx_sprite::frame_val_set()
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
        setRotate(0,0,0);
        setScale(1.0,1.0);
        setColor(255,255,255,255);
    }
}

void gfx_sprite::set_frame(uint32_t frm)
{
    if (cur_seq == NULL || frm >= _num_frames)
        return;

    cur_frame = frm;
    frame_val_set();
}

void gfx_sprite::set_elaps_frames(uint32_t frm)
{
    elaps_frames = frm;
}

bool gfx_sprite::next_frame(bool ignore_loop)
{
    cur_frame = (cur_frame + 1) % _num_frames;
    frame_val_set();

    return (cur_frame == 0) && ((_cur_sseq->looped == 0) || ignore_loop);
}

bool gfx_sprite::next_subseq()
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

bool gfx_sprite::set_subseq(uint32_t idx)
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

bool gfx_sprite::process(bool ignore_loop)
{
    elaps_frames++;
    cur_frame_time++;
    if (cur_frame_time >= cur_duration)
        if (next_frame(ignore_loop))
            return next_subseq();
    return false;
}

void gfx_sprite::draw(uint8_t plane)
{
    gr_draw_sprite(sprite,blend,plane);
}



void gfx_sprite::setXY(float x, float y)
{
    gr_setxy_sprite(sprite,x,-y);
}

void gfx_sprite::setScale(float x, float y)
{
    if (pframe)
    {
        gr_setscale_sprite(sprite,x*pframe->scale_x,y*pframe->scale_y);
    }
    else
        gr_setscale_sprite(sprite,x,y);
}

void gfx_sprite::setOrigin(float x, float y)
{
    if (pframe)
    {
        gr_setorigin_sprite(sprite,pframe->x_offset+x/pframe->scale_x,pframe->y_offset+y/pframe->scale_y);
    }
    else
        gr_setorigin_sprite(sprite,x,y);
}

void gfx_sprite::setBlend(gr_blend _blend)
{
    blend = _blend;
}

void gfx_sprite::setRotate(float angl)
{
    if (pframe)
    {
        if (pframe->scale_x < 0)
            angl*=-1;
        gr_setrotate_sprite(sprite,angl+pframe->angle_z);
    }
    else
        gr_setrotate_sprite(sprite,angl);
}

void gfx_sprite::setRotate(float x, float y, float z)
{
    if (pframe)
    {
        float rx,ry,rz;
        if (pframe->scale_x < 0)
            z*=-1;
        euler_mult(pframe->angle_x,pframe->angle_y,pframe->angle_z,x,y,z,rx,ry,rz);
        gr_setrotate_sprite(sprite,rx,ry,rz);
    }
    else
        gr_setrotate_sprite(sprite,x,y,z);
}

uint32_t gfx_sprite::get_seq_id()
{
    return cur_seq->id;
}


void gfx_sprite::setColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
    if (pframe)
        gr_setcolor_sprite(sprite, (r*pframe->c_R) / 255,
                                   (g*pframe->c_G) / 255,
                                   (b*pframe->c_B) / 255,
                                   (a*pframe->c_A) / 255);
    else
        gr_setcolor_sprite(sprite, r,g,b,a);
}


gfx_meta::gfx_meta()
{
    index = -1;
    active = true;
    order = 1;
}

uint32_t gfx_meta::get_subseq()
{
    return sprite.get_cur_subseq();
}
uint32_t gfx_meta::get_frame()
{
    return sprite.get_cur_frame();
}
uint32_t gfx_meta::get_frame_time()
{
    return sprite.get_cur_frame_time();
}
uint32_t gfx_meta::get_elaps_frames()
{
    return sprite.get_elaps_frames();
}
gfx_frame * gfx_meta::get_pframe()
{
    return sprite.get_pframe();
}
void gfx_meta::set_frame(uint32_t frm)
{
    sprite.set_frame(frm);
}

void gfx_meta::set_elaps_frames(uint32_t frm)
{
    sprite.set_elaps_frames(frm);
}

uint32_t gfx_meta::get_seq()
{
    return index;
}

bool gfx_meta::process(bool ignore_loop)
{
    return sprite.process(ignore_loop);
}


void gfx_meta::func10()
{
}

void gfx_meta::set_seq_params()
{
}

void gfx_meta::draw(int8_t plane)
{
    if (active)
    {
        sprite.setXY(x,y);
        sprite.setColor(c_R,c_G,c_B,c_A);

        sprite.setOrigin(x_off,y_off);
        sprite.setScale(dir*scaleX,scaleY);

        if (scaleX < 0)
            sprite.setRotate(angX,angY,-angZ*dir);
        else
            sprite.setRotate(angX,angY,angZ*dir);

        sprite.draw(plane);
    }
}

gfx_meta::~gfx_meta()
{

}








static const uint8_t color_v_to_viii [32] =
{
    0, 8, 16, 24, 32, 41, 49, 57, 65, 74, 82, 90, 98, 106, 115, 123,
    131, 139, 148, 156, 164, 172, 180, 189, 197, 205, 213, 222, 230, 238, 246, 255
};

static void delete_seq(gfx_seq *sq)
{
    if (sq->refcount > 0)
    {
        sq->refcount--;
        return;
    }

    for(uint32_t i = 0; i < sq->subseqs.size(); i++)
    {
        for (uint32_t j = 0; j < sq->subseqs[i].frames.size(); j++)
        {
            delete sq->subseqs[i].frames[j];
        }
    }

    delete sq;
}


bool gfx_holder::load_dat(const char *file, const char *dir)
{
    char buf[CHRBUF];

    uint32_t plt[256];


    sprintf(buf, "%s/%s", dir, file);

    filehandle *f = arc_get_file(buf);

    if (!f)
        return false;

    uint16_t pat_count = 0;

    uint8_t pat_version = 0;

    f->read(1, &pat_version);

    /*if (pat_version != 5)
    {
        delete f;
        return false;
    }*/

    f->read(2, &pat_count);

    imgs.resize(pat_count);

    for (uint32_t i = 0; i < pat_count; i++)
    {
        f->read(0x80, buf);

        uint8_t slen = strlen(buf);

        buf[slen-1] = '2';
        buf[slen-2] = 'v';
        buf[slen-3] = 'c';

        char buf2[CHRBUF];
        sprintf(buf2,"%s/%s",dir,buf);

        filehandle *ft = arc_get_file(buf2);
        if (!ft)
        {
            imgs[i] = NULL;
            continue;
        }

        gr_tex *tex = gr_load_cv2(ft, plt);

        imgs[i] = tex;

        delete ft;
    }

    uint32_t num_seq = 0;

    f->read(4, &num_seq);

    uint32_t lastid = -1;

    for (uint32_t i=0; i < num_seq && !f->eof(); i++)
    {
        int32_t id = 0;

        f->read(4, &id);

        if (id == -1) // mapping
        {
            uint32_t seq_new  = 0;
            uint32_t seq_maps = 0;
            f->read(4, &seq_new);
            f->read(4, &seq_maps);

            map_gfx_seq::iterator tmp = seqs.find(seq_maps);

            if (tmp != seqs.end())
            {
                tmp->second->refcount++;
                seqs[seq_new] = tmp->second;
            }
        }
        else
        {
            gfx_seq *sq         = NULL;

            if (id != -2) // new sequences
            {
                map_gfx_seq::iterator tmp = seqs.find(id);

                if (tmp != seqs.end())
                {
                    delete_seq(tmp->second);
                }


                sq = new gfx_seq;

                sq->refcount = 0;

                seqs[id] = sq;

                sq->id = id;

                lastid = id;
            }
            else if (lastid >= 0) //it's new part of current
            {
                sq = seqs[lastid];
            }
            else
            {
                delete f;
                return false;
            }
            if (sq == NULL)
            {
                delete f;
                return false;
            }

            gfx_subseq ssq;

            f->read(1, &ssq.looped);


            uint32_t nframes = 0;

            f->read(4, &nframes);

            ssq.frames.resize(nframes);

            for (uint32_t j = 0; j < nframes; j++)
            {

                gfx_frame *frm = new gfx_frame;

                uint32_t frame = 0;
                f->read(4, &frame);

                if (frame < imgs.size() && frame >= 0)
                    frm->img = imgs[frame];
                else
                    frm->img = NULL;

                f->read(2, &frm->unk1);
                f->read(2, &frm->unk2);

                frm->scale_x = 2.0;
                frm->scale_y = 2.0;

                f->read(2, &frm->tx_width);
                f->read(2, &frm->tx_height);
                f->read(2, &frm->x_offset);
                f->read(2, &frm->y_offset);
                f->read(2, &frm->durate);

                f->read(1, &frm->type);

                if (frm->type == 2)
                {
                    f->read(2, &frm->blend_mode);

                    f->read(1, &frm->c_A);
                    f->read(1, &frm->c_R);
                    f->read(1, &frm->c_G);
                    f->read(1, &frm->c_B);

                    int16_t tscale = 0;
                    f->read(2, &tscale);
                    frm->scale_x = tscale / 100.0;

                    tscale = 0;
                    f->read(2, &tscale);
                    frm->scale_y = tscale / 100.0;

                    f->read(2, &frm->angle_x);
                    f->read(2, &frm->angle_y);
                    f->read(2, &frm->angle_z);
                }
                else
                {
                    frm->x_offset /= frm->scale_x;
                    frm->x_offset /= frm->scale_y;
                }

                ssq.frames[j] = frm;
            }

            sq->subseqs.push_back(ssq);
        }
    }


    delete f;
    return true;
}



bool gfx_holder::load_pal_pal(const char *file,uint32_t *pal)
{
    filehandle *f = arc_get_file(file);

    if (f)
    {
        uint8_t bits;

        f->read(1,&bits);

        if (bits == 16)
        {
            uint16_t temppal[256];
            f->read(0x200, temppal);
            pal[0] = 0;
            for (uint32_t i = 1; i < 256; i++)
                pal[i] = 0xFF000000 |
                         color_v_to_viii[temppal[i] & 0x1F] << 16          |
                         (color_v_to_viii[(temppal[i] >> 5) & 0x1F] << 8 ) |
                         (color_v_to_viii[(temppal[i] >> 10) & 0x1F] );
        }
        else if (bits == 24 || bits == 32)
            f->read(0x400, pal);
        else
        {
            delete f;
            return false;
        }



        delete f;
        return true;
    }
    return false;
}


gfx_seq * gfx_holder::get_seq(uint32_t idx)
{
    map_gfx_seq::iterator tmp = seqs.find(idx);
    if (tmp != seqs.end())
        return (tmp->second);
    return NULL;
}

void gfx_holder::update()
{
    for(int32_t i=fx.size()-1; i>=0; i--)
        if (fx[i]->active)
            fx[i]->func10();
        else
        {
            delete fx[i];
            fx.erase(fx.begin() + i);
        }

}

void gfx_holder::draw(int8_t order,int8_t plane)
{
    for(uint32_t i=0; i<fx.size(); i++)
        if (fx[i]->order == order)
            fx[i]->draw(plane);
}
