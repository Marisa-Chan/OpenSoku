#include "global_types.h"


#include "archive.h"
#include "file_read.h"
#include "graph.h"
#include "framedata.h"
#include "background.h"
#include <unistd.h>


void camera(float x1, float y1, float x2, float y2)
{
        gr_reset_state(1);

        gr_plane_translate(1,0,420);
        float scale = 640.0/(x2-x1);
        if (scale > 1.0)
            scale = 1.0;
        if (scale < 0.5)
            scale = 0.5;

        float xpos = (x1 + x2)/2.0 - ((640.0/2.0)*scale);
        gr_plane_scale(1,scale,scale);
        gr_plane_translate(1,-xpos,0);

        gr_reset_state(2);

        gr_plane_translate(2,0,420);
        gr_plane_scale(2,scale,scale);
        gr_plane_translate(2,-xpos,0);
        gr_plane_translate(2,-60,-960);
}


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
//    float y=0,poy=16,gr=0.75;

    marisa->set_seq(0);
    alice->set_seq(0);
    background_11  bkg;

    //float a =1;

    float x1=480,x2=800,y1=00,y2=00;

    while(1)
    {

        gr_clear();

        camera(x1,y1,x2,y2);


        //x2+=1;
        if (x2 >= 1240)
            x2 = 1240;

       // a+=0.0001;

        bkg.draw();

        gr_draw_box(x1,y1,255,0,0,1);
        gr_draw_box(x2,y2,255,0,0,1);

        marisa->draw(x1,y1,1,1);

        alice->draw(x2,y2,1,-1);

        //marisa->draw(200,500,0);


//        if (y<0)
//        {
//            y=0;
//            poy = 16;
//            gr=0.75;
//        }


        //y+=poy;z
        //poy-=gr;

        gr_flip();

        marisa->process_anim();
        alice->process_anim();

        //sleep(1);
    }



    return EXIT_SUCCESS;
}
