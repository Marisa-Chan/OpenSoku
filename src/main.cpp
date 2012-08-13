#include "global_types.h"


#include "archive.h"
#include "file_read.h"
#include "graph.h"
#include "framedata.h"
#include "background.h"
#include "input.h"
#include "music.h"
#include "scene.h"
#include <math.h>
#include <unistd.h>



int main()
{
    // Create the main window

	// Start the game loop
    arc_add_dat("th105a.dat");
    arc_add_dat("th105b.dat");
    arc_add_dat("th105c.dat");
    arc_add_dat("th123a.dat");
    arc_add_dat("th123b.dat");
    arc_add_dat("th123c.dat");

    gr_init(640,480,"OpenSoku");

    char_graph *marisa = new char_graph;

    marisa->load_dat("marisa",0);

    char_graph *alice = new char_graph;

    alice->load_dat("alice",0);

//    uint32_t i = 0;
//
    float poy=0,gr=0;
    float poy2=0,gr2=0;

    inp_kb kb;

    marisa->set_seq(0);
    alice->set_seq(0);
    background_11  bkg;

    //float a =1;

    uint32_t a = 0;

    float x1=40,x2=400,y1=000,y2=000;

    c_scene scn;

    scn.set_camera(x1,y1,x2,y2);

    playmusic();

    while(!kb.rawPressed(kC_Escape))
    {

        gr_clear();

        scn.upd_camera(x1,y1,x2,y2);

        if (kb.rawPressed(kC_A))
            x1-=5;

        if (kb.rawPressed(kC_D))
            x1+=5;

        if (kb.rawPressed(kC_Left))
            x2-=5;

        if (kb.rawPressed(kC_Right))
            x2+=5;

        //x2+=2;

        if (x2 >= 1240)
            x2 = 1240;
        if (x2 <= 40)
            x2 = 40;

        if (x1 >= 1240)
            x1 = 1240;
        if (x1 <= 40)
            x1 = 40;

       // a+=0.0001;



        bkg.draw();

        gr_draw_box(x1,-y1,255,0,0,1);
        gr_draw_box(x2,-y2,255,0,0,1);


        marisa->draw(x1,y1,1,1);

        alice->draw(x2,y2,1,-1);

        //marisa->draw(200,500,0);


        if (y1<=0)
        {
            y1=0;
            poy = 0;
            gr=0.0;

            if (kb.rawPressed(kC_W))
            {
                poy = 20;
                gr = 0.3;
            }
        }

        a = (a + 1) % 3;

        y1+=poy;
        poy-=gr;

        if (y2<=0)
        {
            y2=0;
            poy2 = 0;
            gr2=0.0;

            if (kb.rawPressed(kC_Up))
            {
                poy2 = 20;
                gr2 = 0.3;
            }
        }


        y2+=poy2;
        poy2-=gr2;

        gr_flip();

        marisa->process_anim();
        alice->process_anim();

        //sleep(1);
        kb.update();
    }



    return EXIT_SUCCESS;
}
