#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "framedata.h"

static const uint8_t color_v_to_viii [32] =
{
    0, 8, 16, 24, 32, 40, 48, 56, 64, 72, 80, 88, 96, 104, 112, 120,
    128, 136, 144, 152, 160, 168, 176, 184, 192, 200, 208, 216, 224, 232, 240, 248
};

static void delete_seq(seq *sq)
{
    for(uint32_t i = 0; i < sq->subseqs.size(); i++)
    {
        for (uint32_t j = 0; j < sq->subseqs[i].frames.size(); j++)
        {
            delete sq->subseqs[i].frames[j];
        }
    }

    delete sq;
}

bool char_graph::load_dat(const char *name, uint8_t pal)
{
    char buf[CHRBUF];

    sprintf(buf, "data/character/%s/palette%3.3d.pal", name, pal);

    uint32_t plt[256];

    if (!load_pal_pal(buf,plt))
        return false;

    sprintf(buf, "data/character/%s/%s.pat", name, name);

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
        sprintf(buf2,"data/character/%s/%s",name,buf);

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

        //printf("%x\n",f->tell());
        f->read(4, &id);

        if (id == -1)
        {
            uint32_t unk1 = 0;
            uint32_t unk2 = 0;
            f->read(4, &unk1);
            f->read(4, &unk2);

            //printf("0x%x  0x%x\n",unk1,unk2);
        }
        else
        {
            seq *sq         = NULL;

            if (id != -2) // new sequences
            {
                mapseq::iterator tmp = seqs.find(id);

                if (tmp != seqs.end())
                {
                   // if (id == 0)
                       // printf("aaa\n");
                    delete_seq(tmp->second);
                }


                sq = new seq;

                seqs[id] = sq;

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

            subseq ssq;

            f->read(2, &ssq.prior);
            f->read(2, &ssq.prior_for_cancel);
            f->read(1, &ssq.looped);

            if (id != -2)
            {
                sq->prior = ssq.prior;
                sq->prior_for_cancel = ssq.prior_for_cancel;
            }

            uint32_t nframes = 0;

            f->read(4, &nframes);

            ssq.frames.resize(nframes);

            for (uint32_t j = 0; j < nframes; j++)
            {
                char_frame *frm = new char_frame;

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
                    f->read(4, &frm->unk3);
                    f->read(2, &frm->unk4);
                    f->read(2, &frm->scale);
                    f->read(2, &frm->unk5);
                    f->read(2, &frm->unk6);
                    f->read(2, &frm->angle);

                }

                f->read(2, &frm->damage);
                f->read(2, &frm->proration);
                f->read(2, &frm->unk7);
                f->read(2, &frm->unk8);
                f->read(2, &frm->untech);
                f->read(2, &frm->unk9);
                f->read(2, &frm->limit);
                f->read(2, &frm->unk10);
                f->read(2, &frm->unk11);
                f->read(2, &frm->unk12);
                f->read(2, &frm->unk13);
                f->read(2, &frm->unk14);
                f->read(2, &frm->unk15);
                f->read(2, &frm->unk16);
                f->read(2, &frm->unk17);
                f->read(2, &frm->velocity_x);
                f->read(2, &frm->velocity_y);
                f->read(2, &frm->unk18);
                f->read(2, &frm->unk19);
                f->read(2, &frm->attack_type);
                f->read(1, &frm->unk20);
                f->read(4, &frm->fflags);
                f->read(4, &frm->aflags);

                uint8_t nb = 0;
                f->read(1, &nb);

                for (uint32_t k = 0; k < nb; k++)
                {
                    frame_box box;
                    f->read(4, &box.x1);
                    f->read(4, &box.y1);
                    f->read(4, &box.x2);
                    f->read(4, &box.y2);

                    frm->box_coll.push_back(box);
                }

                nb = 0;
                f->read(1, &nb);

                for (uint32_t k = 0; k < nb; k++)
                {
                    frame_box box;
                    f->read(4, &box.x1);
                    f->read(4, &box.y1);
                    f->read(4, &box.x2);
                    f->read(4, &box.y2);

                    frm->box_hit.push_back(box);
                }

                nb = 0;
                f->read(1, &nb);

                for (uint32_t k = 0; k < nb; k++)
                {
                    frame_box box;
                    f->read(4, &box.x1);
                    f->read(4, &box.y1);
                    f->read(4, &box.x2);
                    f->read(4, &box.y2);

                    frm->box_atk.push_back(box);

                    uint8_t s = 0;
                    f->read(1 , &s);
                    if (s)
                    {
                        f->read(4, &box.x1);
                        f->read(4, &box.y1);
                        f->read(4, &box.x2);
                        f->read(4, &box.y2);
                    }
                }

                if (pat_version == 5)
                {
                    f->read(24, frm->unk21);
                    f->read(6, frm->unk22);
                }

                ssq.frames[j] = frm;
            }

            sq->subseqs.push_back(ssq);
        }
    }


    delete f;
    return true;
}



bool char_graph::load_pal_pal(const char *file,uint32_t *pal)
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

char_graph::char_graph()
{
    sprite = gr_create_sprite();
    sprite->setScale(2.0,2.0);
}

void char_graph::set_seq(uint32_t idx)
{
    mapseq::iterator tmp = seqs.find(idx);
    if (tmp != seqs.end())
    {
        cur_seq = tmp->second;
        cur_frame = 0;
        cur_frame_time = 0;
        cur_subseq = 0;
        pframe = cur_seq->subseqs[cur_subseq].frames[cur_frame];
        gr_set_spr_tex(sprite, pframe->img);
    }
}

void char_graph::process_anim()
{
    cur_frame_time++;
    if (cur_frame_time >= pframe->durate)
    {
        cur_frame_time = 0;
        cur_frame++;

        if (cur_frame >= cur_seq->subseqs[cur_subseq].frames.size())
        {
            cur_frame = 0;
            cur_subseq++;

            if (cur_subseq >= cur_seq->subseqs.size())
            {
                cur_subseq = 0;
            }
        }
        pframe = cur_seq->subseqs[cur_subseq].frames[cur_frame];
        gr_set_spr_tex(sprite, pframe->img);
    }
}

void char_graph::set_img(uint32_t idx)
{
    if (idx < imgs.size())
        gr_set_spr_tex(sprite,imgs[idx]);
}

void char_graph::draw(float x, float y)
{
    gr_draw_sprite(sprite, x-pframe->x_offset, y-pframe->y_offset);
}

