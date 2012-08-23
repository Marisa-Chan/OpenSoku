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



    char_c *marisa = new char_marisa(inp_createinput(INP_TYPE_NONE));

    char_c *alice = new char_alice(inp_createinput(INP_TYPE_KB));


//    uint32_t i = 0;
//

    inp_kb kb;

    marisa->set_seq(0);
    alice->set_seq(0);
    background  *bkg = new background_11;



    c_scene *scn = new c_scene(bkg,marisa,alice);


    while(!kb.rawPressed(kC_Escape))
    {
        kb.update();

        gr_clear();

        scn->players_input();

        //scn.players_collisions();
        scn->update();

        scn->draw_scene();

        scn->update_char_anims();

        gr_flip();

    }



    return EXIT_SUCCESS;
}
