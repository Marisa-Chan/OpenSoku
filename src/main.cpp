#include "global_types.h"


#include "archive.h"
#include "file_read.h"
#include "graph.h"
#include "framedata.h"
#include <unistd.h>


int main()
{
    // Create the main window

	// Start the game loop
    //arc_add_dat("th105a.dat");
    //arc_add_dat("th105b.dat");
    arc_add_dat("th123a.dat");
    arc_add_dat("th123b.dat");

    gr_init(640,480,"OpenSoku");

    char_graph *marisa = new char_graph;

    marisa->load_dat("marisa",1);

//    uint32_t i = 0;

    float y=0,poy=16,gr=0.75;

    marisa->set_seq(310);

    while(1)
    {

        gr_clear();
        marisa->draw(200,480-y);

        if (y<0)
        {
            y=0;
            poy = 16;
            gr=0.75;
        }


        y+=poy;
        poy-=gr;

        gr_flip();

        marisa->process_anim();

        //sleep(1);
    }



    return EXIT_SUCCESS;
}
