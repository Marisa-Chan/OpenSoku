#include "global_types.h"


#include "archive.h"
#include "file_read.h"
#include "graph.h"
#include "framedata.h"
#include "background.h"
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

//    uint32_t i = 0;
//
//    float y=0,poy=16,gr=0.75;

    marisa->set_seq(0);
    background_10  bkg;

    float a =1;

    float x1=300,x2=800,y1=400,y2=400;

    while(1)
    {

        gr_clear();



        gr_reset_state(1);

        gr_plane_scale(1,640.0/((x2+40)-(x1-40)),640.0/((x2+40)-(x1-40)));
        gr_plane_translate(1,-x1+40,100);


        x2+=a;

        a+=0.0001;

        bkg.draw();

        marisa->draw(x1,y1,1);

        marisa->draw(x2,y2,1);

        marisa->draw(200,500,0);


//        if (y<0)
//        {
//            y=0;
//            poy = 16;
//            gr=0.75;
//        }


        //y+=poy;
        //poy-=gr;

        gr_flip();

        marisa->process_anim();

        //sleep(1);
    }



    return EXIT_SUCCESS;
}
