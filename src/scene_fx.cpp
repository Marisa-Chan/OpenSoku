#include "global_types.h"
#include <math.h>
#include "scene.h"
#include "graph.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"
#include "archive.h"
#include "file_read.h"

static const uint8_t color_v_to_viii [32] =
{
    0, 8, 16, 24, 32, 41, 49, 57, 65, 74, 82, 90, 98, 106, 115, 123,
    131, 139, 148, 156, 164, 172, 180, 189, 197, 205, 213, 222, 230, 238, 246, 255
};

static void delete_seq(sc_seq *sq)
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


bool c_scene_sp::load_dat()
{
    const char *name = "effect";

    char buf[CHRBUF];

    uint32_t plt[256];


    sprintf(buf, "data/%s/%s.pat", name, name);

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
        sprintf(buf2,"data/%s/%s",name,buf);

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

            map_c_seq::iterator tmp = seqs.find(seq_maps);

            if (tmp != seqs.end())
            {
                tmp->second->refcount++;
                seqs[seq_new] = tmp->second;
            }
        }
        else
        {
            sc_seq *sq         = NULL;

            if (id != -2) // new sequences
            {
                map_c_seq::iterator tmp = seqs.find(id);

                if (tmp != seqs.end())
                {
                    delete_seq(tmp->second);
                }


                sq = new sc_seq;

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

            sc_subseq ssq;

            f->read(1, &ssq.looped);


            uint32_t nframes = 0;

            f->read(4, &nframes);

            ssq.frames.resize(nframes);

            for (uint32_t j = 0; j < nframes; j++)
            {

                sc_fx_frame *frm = new sc_fx_frame;

                uint32_t frame = 0;
                f->read(4, &frame);

                if (frame < imgs.size() && frame >= 0)
                    frm->img = imgs[frame];
                else
                    frm->img = NULL;

                f->read(2, &frm->unk1);
                f->read(2, &frm->unk2);

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

                ssq.frames[j] = frm;
            }

            sq->subseqs.push_back(ssq);
        }
    }


    delete f;
    return true;
}



bool c_scene_sp::load_pal_pal(const char *file,uint32_t *pal)
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


sc_seq * c_scene_sp::get_seq(uint32_t idx)
{
    map_c_seq::iterator tmp = seqs.find(idx);
    if (tmp != seqs.end())
       return (tmp->second);
    return NULL;
}

void c_scene_sp::addeffect(int32_t idx, float x, float y, int8_t dir)
{
    sc_seq *sq = get_seq(idx);
    if (sq)
    {
        c_scene_fx *ff = new c_scene_fx;

        ff->viz.set_seq(sq);
        ff->x = x;
        ff->y = y;
        ff->dir = dir;
        ff->scaleX = 1.0;
        ff->scaleY = 1.0;
        ff->c_A = 255;
        ff->c_R = 255;
        ff->c_G = 255;
        ff->c_B = 255;
        ff->set_seq_params();
        ff->active = true;

        fx.push_back(ff);
    }
}

void c_scene_sp::update()
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

void c_scene_sp::draw()
{
    for(uint32_t i=0; i<fx.size(); i++)
        fx[i]->draw(1);
}












void c_scene_fx::func10()
{
    int32_t sqid = viz.get_seq_id();

    switch(sqid)
    {
        case 62:
        if (viz.get_elaps_frames() == 0)
        {
            scene_play_sfx(45);
            scene_add_effect(113,x,y,dir);
        }
            scaleX+=0.2;
            scaleY+=0.2;

            if (c_R > 25)
            {
                c_R -= 25;
                c_G -= 25;
                c_B -= 25;
                if (viz.process())
                    active = false;
            }
            else
                active = false;

        break;

        case 113:

            scaleX+=0.4;
            scaleY+=0.4;
            if (c_R > 15)
            {
                c_R -= 15;
                c_G -= 15;
                c_B -= 15;
                if (viz.process())
                    active = false;
            }
            else
                active = false;

        break;
    }
}

void c_scene_fx::set_seq_params()
{
    int32_t sqid = viz.get_seq_id();

    switch(sqid)
    {
        case 62:
            scaleX =0.1;
            scaleY =0.1;
        break;

    }
}




void c_scene_fx::draw(int8_t plane)
{
    viz.setXY(x,y);
    viz.setScale(dir*scaleX,scaleY);
    viz.setColor(c_R,c_G,c_B,c_A);
    viz.draw(1);
}

