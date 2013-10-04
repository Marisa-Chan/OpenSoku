#include "global_types.h"


#include "archive.h"
#include "file_read.h"
#include "graph.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"
#include "music.h"
#include "scene.h"
#include <math.h>
#include <unistd.h>
#include "gui.h"
#include "profile.h"
#include "menu/menus.h"
#include "battle_ui.h"
#include "weather.h"
#include "bullets.h"


int main(int argc, char *argv[])
{
    // Create the main window

    //Nyan Shinki, nyan
    FILE *dats = NULL;
    const char *path = ".";
    char buf[256];

    if (argc == 2)
    {
        path = argv[1];
        sprintf(buf,"%s/%s",path,"dat_files.txt");
        dats = fopen(buf,"rb");
    }

    if (argc != 2 || !dats )
        dats = fopen("dat_files.txt","rb");

    if (!dats)
    {
        printf("No dat_files.txt found!\n");
        exit(-1);
    }


    while(!feof(dats))
    {
        char rbuf[256];
        fgets(rbuf,255,dats);

        char *trimed = TrimRight(TrimLeft(rbuf));
        if (strlen(trimed) > 0)
        {
            sprintf(buf,"%s/%s",path,trimed);

            if (!arc_add_dat(buf))
                if (!arc_add_dat(trimed))
                    printf("Can't load %s, ignore.\n",trimed);
        }
    }

    fclose(dats);


    // Start the game loop
    //arc_add_dat("th105a.dat");
    //arc_add_dat("th105b.dat");
    //arc_add_dat("th105c.dat");
    //arc_add_dat("th123a.dat");
    //arc_add_dat("th123b.dat");
    //arc_add_dat("th123c.dat");

    gr_init(640,480,"OpenSoku");
    sfx_init();
    scene_load_sounds();

     //playmusic();

    bullets_init_common();

    char_c *marisa = new char_cirno(inp_createinput(INP_TYPE_BOTH));

    sprintf(buf,"%s/profile/profile1p.pf",path);
    s_profile *prof = profile_load_from_file(buf);
    sprintf(buf,"%s/profile/profile2p.pf",path);
    s_profile *prof2 = profile_load_from_file(buf);
    if (prof)
    {
        marisa->set_input_profile(prof);
        marisa->set_cards_deck(prof,0);
    }


    char_c *alice = new char_marisa(inp_createinput(INP_TYPE_KB),7);

    if (prof2)
    {
        alice->set_cards_deck(prof2,0);
        alice->set_input_profile(prof2);
    }

//    uint32_t i = 0;
//

    inp_both *inp = get_global_input();

    marisa->set_seq(0);
    alice->set_seq(0);
    srand(time(NULL));
    background  *bkg = bkg_create(12);

    scene_new_scene(bkg,marisa,alice);

//    int32_t ii = 0;
    int32_t aa = 0;
    int32_t bb = 0;

    weather_change(WEATHER_CLEAR,1);
    weather_time_set(0);

    marisa->add_card(111);
    marisa->add_card();
    marisa->add_card();
    marisa->add_card();
    marisa->add_card();

    alice->add_card();
    alice->add_card();


    screen *scr = NULL;
    id_screen scr_id = SCREEN_UNK;
    id_screen scr_next_id = SCREEN_GAMEPLAY;

    fader       glob_fader;
    menu_fader  *loc_fader = menu_get_fader();

    bool game_run = true;

    while(game_run)
    {
        inp->update();

        if (inp->rawPressed(kC_F1))
            game_run = false;

        aa++;
        if (aa > 10 && inp->rawPressed(kC_Q))
        {
            aa = 0;
            marisa->add_card(bb);
            //weather_time_set(999);
            //weather_change((WEATHER_ID)bb,true);

            bb++;
            bb %= 21;
        }


        if (scr_id == scr_next_id)
        {
            loc_fader->update();
            glob_fader.fade_in();

            if (scr)
                scr_next_id = scr->update();
        }

        if (scr_next_id != SCREEN_UNK)
        {
            if (scr_id != scr_next_id)
            if (glob_fader.fade_out())
            {
                if (scr)
                {
                    scr->onExit();
                    delete scr;
                }
                scr = screen_create(scr_next_id);
                scr_id = scr_next_id;
                scr->onStart();
            }

            bool scr_drawed = false;

            if (scr)
                scr_drawed = scr->draw();

            loc_fader->draw();

            if (scr_drawed)
                glob_fader.draw();
        }
        else
        {
            game_run = false;
            continue;
        }

        gr_flip();
    }

    delete bkg;


    return EXIT_SUCCESS;
}

