#include "global_types.h"
#include "archive.h"
#include "file_read.h"
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

void background::draw()
{

    for (uint32_t i = 0; i < imgs.size(); i++)
    {
        gr_set_spr_tex(spr,imgs[i].tex);
        gr_setxy_sprite(spr,imgs[i].x,imgs[i].y);
        gr_draw_sprite(spr,gr_alpha,1);
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
            imgs.push_back(chunk);
        }
}
