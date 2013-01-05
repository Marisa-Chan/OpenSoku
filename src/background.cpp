#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "scene.h"
#include "background.h"

background::background()
{
    spr = gr_create_sprite();
}

background::~background()
{
    for (uint32_t i = 0; i < imgs.size(); i++)
        delete imgs[i].tex;
}

void background::render(bkg_chunk *chunk)
{
    gr_set_spr_tex(spr,chunk->tex);
    gr_setxy_sprite(spr,chunk->x,chunk->y);
    gr_setrotate_sprite(spr,chunk->ax,chunk->ay,chunk->az);
    gr_setorigin_sprite(spr,chunk->ofx,chunk->ofy);
    gr_draw_sprite(spr,gr_alpha,2);
}

void background::draw()
{

    for (uint32_t i = 0; i < imgs.size(); i++)
    {
        render(&imgs[i]);
    }
}





background_10::background_10()
{
    spr = gr_create_sprite();

    for(uint32_t i=0; i < 30; i++)
        if (i != 2)
        {
            bkg_chunk chunk;
            char buf[CHRBUF];
            sprintf(buf,"data/background/bg10/0000_%2.2d.cv2",i);
            filehandle *f = arc_get_file(buf);
            chunk.tex = gr_load_cv2(f,NULL);
            delete f;
            chunk.x = (i % 6) * 256;
            chunk.y = (i / 6) * 256;
            chunk.ax = 0;
            chunk.ay = 0;
            chunk.az = 0;
            chunk.ofx = 0;
            chunk.ofy = 0;
            imgs.push_back(chunk);
        }
}

background_11::background_11()
{
    spr = gr_create_sprite();

    for(uint32_t i=0; i < 30; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg11/0000_%2.2d.cv2",i);
        filehandle *f = arc_get_file(buf);
        chunk.tex = gr_load_cv2(f,NULL);
        delete f;
        chunk.x = (i % 6) * 256;
        chunk.y = (i / 6) * 256;
        chunk.ax = 0;
        chunk.ay = 0;
        chunk.az = 0;
        chunk.ofx = 0;
        chunk.ofy = 0;
        imgs.push_back(chunk);
    }
}

background_12::background_12()
{
    spr = gr_create_sprite();
    angle = 0;

    for(uint32_t i=0; i < 30; i++)
        if (i >=2 && i != 5 && i != 6 && i != 11)
        {
            bkg_chunk chunk;
            char buf[CHRBUF];
            sprintf(buf,"data/background/bg12/0000_%2.2d.cv2",i);
            filehandle *f = arc_get_file(buf);
            chunk.tex = gr_load_cv2(f,NULL);
            delete f;
            chunk.x = (i % 6) * 256;
            chunk.y = (i / 6) * 256;
            chunk.ax = 0;
            chunk.ay = 0;
            chunk.az = 0;
            chunk.ofx = 0;
            chunk.ofy = 0;
            imgs.push_back(chunk);
        }

    filehandle *f = arc_get_file("data/background/bg12/tori1.cv2");
    bkg_chunk chunk;
    chunk.tex = gr_load_cv2(f, NULL);
    chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD + 492;
    chunk.y = BKG_VERT_POS - 401;
    chunk.ax = 0;
    chunk.ay = 0;
    chunk.az = 0;
    chunk.ofx = 16;
    chunk.ofy = 41;
    delete f;
    decor.push_back(chunk);
    f = arc_get_file("data/background/bg12/tori2.cv2");
    chunk.tex = gr_load_cv2(f, NULL);
    delete f;
    decor.push_back(chunk);
}

void background_12::draw()
{
    angle += 10; // HACK
    background::draw();
    for (int8_t i=0; i < 2; i++)
    {
        decor[i].ay = (angle + i * 45) * 2 - 8;
        render(&decor[i]);
    }
}
