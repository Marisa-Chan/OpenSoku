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
    delete spr;
}

void background::update()
{
    return;
}

void background::draw_mid()
{
    return;
}

void background::draw_near()
{
    return;
}

void background::draw_shadow(c_meta *chr)
{
    shd_trans shadow;
    shadow.a = 127;
    shadow.r = 0;
    shadow.g = 0;
    shadow.b = 0;
    shadow.ax = 106;
    shadow.ay = 0;
    shadow.az = 0;
    shadow.x = chr->x;
    shadow.y = (chr->y + chr->y_off) * cos_deg(106);
    shadow.sx = 1.0;
    shadow.sy = 1.0;

    chr->draw_shadow(&shadow);
}

void background::render(bkg_chunk *chunk)
{
    gr_set_spr_tex(spr,chunk->tex);
    gr_setxy_sprite(spr,chunk->x,chunk->y);
    gr_setrotate_sprite(spr,chunk->ax,chunk->ay,chunk->az);
    gr_setorigin_sprite(spr,chunk->ofx,chunk->ofy);
    gr_setscale_sprite(spr,chunk->sx,chunk->sy);
    gr_setcolor_sprite(spr,255,255,255,chunk->alpha*255);
    gr_draw_sprite(spr,chunk->blend,2);
}

void background::render_move(bkg_chunk *chunk, float x, float y)
{
    gr_set_spr_tex(spr,chunk->tex);
    gr_setxy_sprite(spr,chunk->x,chunk->y);
    gr_setrotate_sprite(spr,chunk->ax,chunk->ay,chunk->az);
    gr_setorigin_sprite(spr,chunk->ofx,chunk->ofy);
    gr_setscale_sprite(spr,chunk->sx,chunk->sy);
    gr_setcolor_sprite(spr,255,255,255,chunk->alpha*255);
    gr_sprite_skew(spr,x,y);
    gr_draw_sprite(spr,chunk->blend,2);
}

void background::draw_back()
{
    for (uint32_t i = 0; i < imgs.size(); i++)
    {
        render(&imgs[i]);
    }
}

void background::loadbkg_t1(int32_t id, float y_off)
{
    for(uint32_t i=0; i < 30; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg%02d/0000_%02d.cv2",id,i);
        filehandle *f = arc_get_file(buf);
        if (f)
        {
            chunk.tex = gr_load_cv2(f,NULL);
            delete f;
            chunk.x = (i % 6) * 256;
            chunk.y = y_off + (i / 6) * 256.0;
            chunk.ax = 0;
            chunk.ay = 0;
            chunk.az = 0;
            chunk.ofx = 0;
            chunk.ofy = 0;
            chunk.sx = 1.0;
            chunk.sy = 1.0;
            chunk.blend = gr_alpha;
            imgs.push_back(chunk);
        }
    }

}

void background::loadbkg_t2(int32_t id, float y_off)
{
    for(uint32_t i=0; i < 30; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg%02d/0000[%02d][%02d].cv2",id, (i/6) + 1, (i%6) + 1);
        filehandle *f = arc_get_file(buf);
        if (f)
        {
            chunk.tex = gr_load_cv2(f,NULL);
            delete f;
            chunk.x = (i % 6) * 256;
            chunk.y = y_off + (i / 6) * 256.0;
            chunk.ax = 0;
            chunk.ay = 0;
            chunk.az = 0;
            chunk.ofx = 0;
            chunk.ofy = 0;
            chunk.sx = 1.0;
            chunk.sy = 1.0;
            chunk.blend = gr_alpha;
            imgs.push_back(chunk);
        }
    }
}

uint32_t background::get_idx()
{
    return idx;
}


background_0::background_0()
{
    idx = 0;
    loadbkg_t1(0,0);
}

background_1::background_1()
{
    idx = 1;
    loadbkg_t1(1,0);
}

background_2::background_2()
{
    idx = 2;
    loadbkg_t1(2,0);

    frame = 0;

    for(uint32_t i=0; i < 16; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg02/left/a%02d.cv2",i);
        filehandle *f = arc_get_file(buf);
        chunk.tex = gr_load_cv2(f,NULL);
        delete f;
        chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD - 332.0;
        chunk.y = BKG_VERT_POS -472.0;
        chunk.ax = 0;
        chunk.ay = 0;
        chunk.az = 0;
        chunk.ofx = 0;
        chunk.ofy = 0;
        chunk.sx = 2.0;
        chunk.sy = 2.0;
        chunk.blend = gr_add;
        left.push_back(chunk);
    }
    for(uint32_t i=0; i < 16; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg02/center/b%02d.cv2",i);
        filehandle *f = arc_get_file(buf);
        chunk.tex = gr_load_cv2(f,NULL);
        delete f;
        chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD + 54.0;
        chunk.y = BKG_VERT_POS -472.0;
        chunk.ax = 0;
        chunk.ay = 0;
        chunk.az = 0;
        chunk.ofx = 0;
        chunk.ofy = 0;
        chunk.sx = 2.0;
        chunk.sy = 2.0;
        chunk.blend = gr_add;
        center.push_back(chunk);
    }
    for(uint32_t i=0; i < 16; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg02/right/c%02d.cv2",i);
        filehandle *f = arc_get_file(buf);
        chunk.tex = gr_load_cv2(f,NULL);
        delete f;
        chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD + 312.0;
        chunk.y = BKG_VERT_POS -472.0;
        chunk.ax = 0;
        chunk.ay = 0;
        chunk.az = 0;
        chunk.ofx = 0;
        chunk.ofy = 0;
        chunk.sx = 2.0;
        chunk.sy = 2.0;
        chunk.blend = gr_add;
        right.push_back(chunk);
    }
}

background_2::~background_2()
{
    for(uint32_t i=0; i<left.size(); i++)
        delete left[i].tex;
    for(uint32_t i=0; i<center.size(); i++)
        delete center[i].tex;
    for(uint32_t i=0; i<right.size(); i++)
        delete right[i].tex;
}

void background_2::draw_back()
{
    background::draw_back();
    uint32_t rframe = (frame / 2 ) % 16;
    render(&left[rframe]);
    render(&center[rframe]);
    render(&right[rframe]);
}

void background_2::update()
{
    frame++;
}

background_3::background_3()
{
    idx = 3;
    loadbkg_t1(3,0);
}

background_4::background_4()
{
    idx = 4;
    loadbkg_t1(4,0);

    posit = 0;

    filehandle *f = arc_get_file("data/background/bg04/cloud2.cv2");
    cloud.tex = gr_load_cv2(f,NULL);
    delete f;
    cloud.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud.y = BKG_VERT_POS;
    cloud.ax = 0;
    cloud.ay = 0;
    cloud.az = 0;
    cloud.ofx = 256;
    cloud.ofy = 76;
    cloud.sx = 2.5;
    cloud.sy = 3.0;
    cloud.blend = gr_alpha;

    gr_set_repeate(cloud.tex, true);
}

background_4::~background_4()
{
    delete cloud.tex;
}

void background_4::draw_near()
{
    render_move(&cloud,posit / 4.0  ,0);
}

void background_4::update()
{
    posit++;
}

background_5::background_5()
{
    idx = 5;
    loadbkg_t1(5,0);
}

background_6::background_6()
{
    idx = 6;
    loadbkg_t1(6,0);
}

background_10::background_10()
{
    idx = 10;
    loadbkg_t1(10,-86);
}

background_11::background_11()
{
    idx = 11;
    loadbkg_t1(11,-86);
}

background_12::background_12()
{
    idx = 12;
    angle = 0;
    loadbkg_t1(12,-86);

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
    chunk.sx = 1.0;
    chunk.sy = 1.0;
    chunk.blend = gr_alpha;
    delete f;
    decor.push_back(chunk);
    f = arc_get_file("data/background/bg12/tori2.cv2");
    chunk.tex = gr_load_cv2(f, NULL);
    delete f;
    decor.push_back(chunk);
}

background_12::~background_12()
{
    for (uint32_t i = 0; i < decor.size(); i++)
        delete decor[i].tex;
}

void background_12::draw_back()
{
    background::draw_back();
    for (int8_t i=0; i < 2; i++)
    {
        decor[i].ay = (angle + i * 45) * 2 - 8;
        render(&decor[i]);
    }
}

void background_12::update() //HACK
{
    /*
    int v1; // edx@2

    if ( weather != 14 )
    {
      ++this->field_64;
      v1 = weather;
      if ( weather == 10 || weather == 11 )
      {
        this->field_64 += 3;
        v1 = weather;
      }
      if ( v1 == 13 )
        this->field_64 += 10;
    }*/
    angle += 3;
}

background_13::background_13()
{
    idx = 13;
    loadbkg_t1(13,-86);
}

background_14::background_14()
{
    idx = 14;
    loadbkg_t1(14,0);
}

background_15::background_15()
{
    idx = 15;
    loadbkg_t1(15,-86);
}

background_16::background_16()
{
    idx = 16;
    angle = 0;
    loadbkg_t1(16,0);

    filehandle *f = arc_get_file("data/background/bg16/0001.cv2");
    bkg_chunk chunk;
    chunk.tex = gr_load_cv2(f, NULL);
    chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    chunk.y = BKG_VERT_POS;
    chunk.ax = 86.4;
    chunk.ay = 0;
    chunk.az = 0;
    chunk.ofx = 128;
    chunk.ofy = 128;
    chunk.sx = 3.5;
    chunk.sy = 3.5;
    chunk.blend = gr_add;
    gr_set_smoth(chunk.tex,true);
    delete f;
    decor.push_back(chunk);



    f = arc_get_file("data/background/bg16/0002.cv2");
    chunk.tex = gr_load_cv2(f, NULL);
    delete f;
    chunk.sx = 4.0;
    chunk.sy = 4.0;
    gr_set_smoth(chunk.tex,true);
    decor.push_back(chunk);


    f = arc_get_file("data/background/bg16/0003.cv2");
    chunk.tex = gr_load_cv2(f, NULL);
    delete f;
    chunk.ax = 0;
    chunk.ay = 0;
    chunk.az = 0;
    chunk.ofx = 0;
    chunk.ofy = 64;
    chunk.sx = 1.0;
    chunk.sy = 1.0;
    chunk.alpha = 0.4;
    gr_set_smoth(chunk.tex,true);
    decor.push_back(chunk);


    f = arc_get_file("data/background/bg16/0004.cv2");
    chunk.tex = gr_load_cv2(f, NULL);
    delete f;
    chunk.ofx = 32;
    chunk.ofy = 32;
    chunk.alpha = 1.0;
    gr_set_smoth(chunk.tex,true);
    decor.push_back(chunk);
}

background_16::~background_16()
{
    for (uint32_t i = 0; i < decor.size(); i++)
        delete decor[i].tex;
}

void background_16::update() //HACK
{
    angle++;
}

void background_16::draw_mid()
{
    decor[0].az = angle/5;
    decor[1].az = angle/5;
    render(&decor[0]);
    render(&decor[1]);

    float scl[4] = {0.8,1.2,1.2,0.8};
    float px[4] = {190,546,852,1209};
    float py[4] = {511,582,582,511};

    for (int8_t i=0; i<4; i++)
    {
        decor[3].sy = decor[3].sx = scl[i] + 0.1 * sin_deg(i * 90 + angle * ( i + 4));
        decor[3].x = px[i];
        decor[3].y = py[i];
        render(&decor[3]);
    }
}

void background_16::draw_near()
{
    decor[2].sy = 0.1 * (6.0 + sin_deg(angle * 2));
    decor[2].sx = 2;
    render(&decor[2]);
    decor[2].sx = -2;
    render(&decor[2]);
}

void background_16::draw_shadow(c_meta *chr)
{
    shd_trans shadow;
    shadow.a = 64;
    shadow.r = 255;
    shadow.g = 255;
    shadow.b = 255;
    shadow.ax = 106;
    shadow.ay = 0;
    shadow.az = 0;
    shadow.x = chr->x;
    shadow.y = (chr->y + chr->y_off) * cos_deg(106);
    shadow.sx = 1.0;
    shadow.sy = 1.0;

    chr->draw_shadow(&shadow);
}

background_17::background_17()
{
    idx = 17;
    loadbkg_t1(17,-86);
}

background_18::background_18()
{
    idx = 18;
    loadbkg_t1(18,0);
}

background_30::background_30()
{
    idx = 30;
    loadbkg_t2(30,-86);
}

background_31::background_31()
{
    idx = 31;
    loadbkg_t2(31,-86);
}

background_32::background_32()
{
    idx = 32;
    loadbkg_t2(32,-86);
}

background_33::background_33()
{
    idx = 33;
    loadbkg_t2(33,0);
    posit = 0;

    filehandle *f = arc_get_file("data/background/bg33/0001.cv2");
    floor.tex = gr_load_cv2(f,NULL);
    delete f;
    floor.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    floor.y = BKG_VERT_POS;
    floor.ax = 0;
    floor.ay = 0;
    floor.az = 0;
    floor.ofx = 700;
    floor.ofy = 228;
    floor.sx = 1.0;
    floor.sy = 1.0;
    floor.blend = gr_alpha;

    f = arc_get_file("data/background/bg33/0002.cv2");
    effect.tex = gr_load_cv2(f,NULL);
    delete f;
    effect.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    effect.y = BKG_VERT_POS;
    effect.ax = 0;
    effect.ay = 0;
    effect.az = 0;
    effect.ofx = 350;
    effect.ofy = 152;
    effect.sx = 2.0;
    effect.sy = 2.0;
    effect.blend = gr_add;
}

background_33::~background_33()
{
    delete floor.tex;
    delete effect.tex;
}

void background_33::update()
{
    posit = (posit + 1) & 0x3FF;
}

void background_33::draw_back()
{
    int32_t j = posit / 256;
    int32_t j2= posit % 256;

    for (uint32_t i=0; i<30; i++)
    {
        bkg_chunk tmp = imgs[(i + j*6) % 24];
        tmp.y = (int32_t)((i / 6) * 256 - j2);
        render(&tmp);
    }

    effect.sx = 2.0;
    render(&effect);
    effect.sx = -2.0;
    render(&effect);
    render(&floor);
}

background_34::background_34()
{
    idx = 34;
    //loadbkg_t2(34,0);
    for(uint32_t i=0; i < 30; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg%02d/0001[%02d][%02d].cv2",34, (i/6) + 1, (i%6) + 1);
        filehandle *f = arc_get_file(buf);
        if (f)
        {
            chunk.tex = gr_load_cv2(f,NULL);
            delete f;
            chunk.x = (i % 6) * 256;
            chunk.y =  ((i / 6) - 1) * 256.0;
            chunk.ax = 0;
            chunk.ay = 0;
            chunk.az = 0;
            chunk.ofx = 0;
            chunk.ofy = 0;
            chunk.sx = 1.0;
            chunk.sy = 1.0;
            chunk.blend = gr_alpha;
            imgs.push_back(chunk);
        }
    }
    frame = 0;

    filehandle *f = arc_get_file("data/background/bg34/0001.cv2");
    floor.tex = gr_load_cv2(f,NULL);
    delete f;
    floor.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    floor.y = BKG_VERT_POS;
    floor.ax = 0;
    floor.ay = 0;
    floor.az = 0;
    floor.ofx = 700;
    floor.ofy = 187;
    floor.sx = 1.0;
    floor.sy = 1.0;
    floor.blend = gr_alpha;

    f = arc_get_file("data/background/bg34/0002.cv2");
    effect.tex = gr_load_cv2(f,NULL);
    delete f;
    effect.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    effect.y = BKG_VERT_POS;
    effect.ax = 0;
    effect.ay = 0;
    effect.az = 0;
    effect.ofx = 350;
    effect.ofy = 230;
    effect.sx = 2.0;
    effect.sy = 2.0;
    effect.blend = gr_add;

    f = arc_get_file("data/background/bg34/0003.cv2");
    shadow.tex = gr_load_cv2(f,NULL);
    delete f;
    shadow.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    shadow.y = BKG_VERT_POS;
    shadow.ax = 0;
    shadow.ay = 0;
    shadow.az = 0;
    shadow.ofx = 350;
    shadow.ofy = 480;
    shadow.sx = 2.0;
    shadow.sy = 2.0;
    shadow.alpha = 0.5;
    shadow.blend = gr_alpha;

    f = arc_get_file("data/background/bg34/0004.cv2");
    gradient.tex = gr_load_cv2(f,NULL);
    delete f;
    gradient.x = BKG_WIDTH/2 + BKG_HOR_PAD;
    gradient.y = BKG_VERT_POS + 32;
    gradient.ax = 0;
    gradient.ay = 0;
    gradient.az = 0;
    gradient.ofx = 32;
    gradient.ofy = 32;
    gradient.sx = 25.0;
    gradient.sy = 3.0;
    gradient.alpha = 0.6;
    gradient.blend = gr_add;

    for(uint32_t i=0; i < 30; i++)
    {
        bkg_chunk chunk;
        char buf[CHRBUF];
        sprintf(buf,"data/background/bg34/object/objectFa0%02d.cv2",i);
        filehandle *f = arc_get_file(buf);
        if (f)
        {
            chunk.tex = gr_load_cv2(f,NULL);
            delete f;
            chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD;
            chunk.y = BKG_VERT_POS;
            chunk.ax = 0;
            chunk.ay = 0;
            chunk.az = 0;
            chunk.ofx = 256;
            chunk.ofy = 64-20;
            chunk.sx = 3.0;
            chunk.sy = 3.0;
            chunk.blend = gr_add;
            reaction.push_back(chunk);
        }
    }
}

background_34::~background_34()
{
    delete floor.tex;
    delete effect.tex;
    delete shadow.tex;
    delete gradient.tex;
    for (uint32_t i = 0; i < reaction.size(); i++)
        delete reaction[i].tex;
}

void background_34::update()
{
    frame ++;
}

void background_34::draw_near()
{
    render(&gradient);
}

void background_34::draw_back()
{
    background::draw_back();

    shadow.sx = 2.0;
    render(&shadow);
    shadow.sx = -2.0;
    render(&shadow);

    render(&reaction[(frame / 2) % 30]);

    effect.sx = 2.0;
    render(&effect);
    effect.sx = -2.0;
    render(&effect);

    floor.sx = 1.0;
    render(&floor);
    floor.sx = -1.0;
    render(&floor);
}

void background_34::draw_shadow(c_meta */*chr*/)
{ //no shadow in this location
    return;
}

background_36::background_36()
{
    idx = 36;
    loadbkg_t2(36,-86);

    angle = 0;

    filehandle *f = arc_get_file("data/background/bg36/tori1.cv2");
    bkg_chunk chunk;
    chunk.tex = gr_load_cv2(f, NULL);
    chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD + 492;
    chunk.y = BKG_VERT_POS - 401;
    chunk.ax = 0;
    chunk.ay = 0;
    chunk.az = 0;
    chunk.ofx = 16;
    chunk.ofy = 41;
    chunk.sx = 1.0;
    chunk.sy = 1.0;
    chunk.blend = gr_alpha;
    delete f;
    tori[0] = chunk;

    f = arc_get_file("data/background/bg36/tori2.cv2");
    chunk.tex = gr_load_cv2(f, NULL);
    delete f;
    tori[1] = chunk;

    pos[0] = -400;
    pos[1] = -300;

    f = arc_get_file("data/background/bg36/clowd_l.cv2");
    cloud[0].tex = gr_load_cv2(f, NULL);
    cloud[0].x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud[0].y = BKG_VERT_POS - 750;
    cloud[0].ax = 0;
    cloud[0].ay = 0;
    cloud[0].az = 0;
    cloud[0].ofx = 0;
    cloud[0].ofy = 0;
    cloud[0].sx = 1.0;
    cloud[0].sy = 1.0;
    cloud[0].blend = gr_alpha;
    delete f;

    f = arc_get_file("data/background/bg36/clowd_s.cv2");
    cloud[1].tex = gr_load_cv2(f, NULL);
    cloud[1].x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud[1].y = BKG_VERT_POS - 320;
    cloud[1].ax = 0;
    cloud[1].ay = 0;
    cloud[1].az = 0;
    cloud[1].ofx = 96;
    cloud[1].ofy = 128;
    cloud[1].sx = 1.0;
    cloud[1].sy = 1.0;
    cloud[1].blend = gr_alpha;
    delete f;
}

background_36::~background_36()
{
    for (uint32_t i = 0; i < 2; i++)
    {
        delete cloud[i].tex;
        delete tori[i].tex;
    }
}

void background_36::update()
{
    angle += 1;
    pos[0] -= 1.5;
    pos[1] -= 1.0;
    if (pos[0] < -1200)
        pos[0] = 800;
    if (pos[1] < -800)
        pos[1] = 800;
}

void background_36::draw_back()
{
    cloud[0].x = BKG_WIDTH/2 + BKG_HOR_PAD + pos[0];
    render(&cloud[0]);

    cloud[1].x = BKG_WIDTH/2 + BKG_HOR_PAD + pos[1];
    render(&cloud[1]);

    background::draw_back();

    for (int8_t i=0; i < 2; i++)
    {
        tori[i].ay = (angle + i * 45) * 2 - 8;
        render(&tori[i]);
    }
}


background_37::background_37()
{
    idx = 37;
    loadbkg_t2(37,-86);

    angle = 0;

    filehandle *f = arc_get_file("data/background/bg37/tori1.cv2");
    bkg_chunk chunk;
    chunk.tex = gr_load_cv2(f, NULL);
    chunk.x = BKG_WIDTH/2 + BKG_HOR_PAD + 492;
    chunk.y = BKG_VERT_POS - 401;
    chunk.ax = 0;
    chunk.ay = 0;
    chunk.az = 0;
    chunk.ofx = 16;
    chunk.ofy = 46;
    chunk.sx = 1.0;
    chunk.sy = 1.0;
    chunk.blend = gr_alpha;
    delete f;
    tori = chunk;


    pos[0] = -400;
    pos[1] = -300;

    f = arc_get_file("data/background/bg37/clowd_l.cv2");
    cloud[0].tex = gr_load_cv2(f, NULL);
    cloud[0].x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud[0].y = BKG_VERT_POS - 750;
    cloud[0].ax = 0;
    cloud[0].ay = 0;
    cloud[0].az = 0;
    cloud[0].ofx = 0;
    cloud[0].ofy = 0;
    cloud[0].sx = 1.0;
    cloud[0].sy = 1.0;
    cloud[0].blend = gr_alpha;
    delete f;

    f = arc_get_file("data/background/bg37/clowd_s.cv2");
    cloud[1].tex = gr_load_cv2(f, NULL);
    cloud[1].x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud[1].y = BKG_VERT_POS - 320;
    cloud[1].ax = 0;
    cloud[1].ay = 0;
    cloud[1].az = 0;
    cloud[1].ofx = 96;
    cloud[1].ofy = 128;
    cloud[1].sx = 1.0;
    cloud[1].sy = 1.0;
    cloud[1].blend = gr_alpha;
    delete f;
}

background_37::~background_37()
{
    delete tori.tex;

    for (uint32_t i = 0; i < 2; i++)
        delete cloud[i].tex;
}

void background_37::update()
{
    angle += 1;
    pos[0] -= 1.5;
    pos[1] -= 1.0;
    if (pos[0] < -1200)
        pos[0] = 800;
    if (pos[1] < -800)
        pos[1] = 800;
}

void background_37::draw_back()
{
    cloud[0].x = BKG_WIDTH/2 + BKG_HOR_PAD + pos[0];
    render(&cloud[0]);

    cloud[1].x = BKG_WIDTH/2 + BKG_HOR_PAD + pos[1];
    render(&cloud[1]);

    background::draw_back();

    tori.ay = angle * 2 - 8;
    render(&tori);
}

background_38::background_38()
{
    idx = 38;
    loadbkg_t2(38,0);

    pos[0] = -400;
    pos[1] = -300;

    filehandle *f = arc_get_file("data/background/bg38/clowd_l.cv2");
    cloud[0].tex = gr_load_cv2(f, NULL);
    cloud[0].x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud[0].y = BKG_VERT_POS - 750;
    cloud[0].ax = 0;
    cloud[0].ay = 0;
    cloud[0].az = 0;
    cloud[0].ofx = 0;
    cloud[0].ofy = 0;
    cloud[0].sx = 1.0;
    cloud[0].sy = 1.0;
    cloud[0].blend = gr_alpha;
    delete f;

    f = arc_get_file("data/background/bg38/clowd_s.cv2");
    cloud[1].tex = gr_load_cv2(f, NULL);
    cloud[1].x = BKG_WIDTH/2 + BKG_HOR_PAD;
    cloud[1].y = BKG_VERT_POS - 320;
    cloud[1].ax = 0;
    cloud[1].ay = 0;
    cloud[1].az = 0;
    cloud[1].ofx = 96;
    cloud[1].ofy = 128;
    cloud[1].sx = 1.0;
    cloud[1].sy = 1.0;
    cloud[1].blend = gr_alpha;
    delete f;
}

background_38::~background_38()
{
    for (uint32_t i = 0; i < 2; i++)
        delete cloud[i].tex;
}

void background_38::update()
{
    pos[0] -= 1.5;
    pos[1] -= 1.0;
    if (pos[0] < -1200)
        pos[0] = 800;
    if (pos[1] < -800)
        pos[1] = 800;
}

void background_38::draw_back()
{
    background::draw_back();

    cloud[0].x = BKG_WIDTH/2 + BKG_HOR_PAD + pos[0];
    render(&cloud[0]);

    cloud[1].x = BKG_WIDTH/2 + BKG_HOR_PAD + pos[1];
    render(&cloud[1]);
}

background * bkg_create(uint32_t idx)
{
    switch(idx)
    {
    case 0:
    default:
        return new background_0;
    case 1:
        return new background_1;
    case 2:
        return new background_2;
    case 3:
        return new background_3;
    case 4:
        return new background_4;
    case 5:
        return new background_5;
    case 6:
        return new background_6;
    case 10:
        return new background_10;
    case 11:
        return new background_11;
    case 12:
        return new background_12;
    case 13:
        return new background_13;
    case 14:
        return new background_14;
    case 15:
        return new background_15;
    case 16:
        return new background_16;
    case 17:
        return new background_17;
    case 18:
        return new background_18;
    case 30:
        return new background_30;
    case 31:
        return new background_31;
    case 32:
        return new background_32;
    case 33:
        return new background_33;
    case 34:
        return new background_34;
    case 36:
        return new background_36;
    case 37:
        return new background_37;
    case 38:
        return new background_38;
    }
}

