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

    arc_add_dat("th123a.dat");
    arc_add_dat("th123b.dat");

    gr_init(640,480,"OpenSoku");

    char_graph *marisa = new char_graph;

    marisa->load_dat("alice",2);

    uint32_t i = 0;

    while(1)
    {
        marisa->set_img(i++ / 3);
        printf("%d\n",i/3);

        i %= 2000;

        gr_clear();
        marisa->draw(1,1);
        gr_flip();

        //sleep(1);
    }



    return EXIT_SUCCESS;
}
