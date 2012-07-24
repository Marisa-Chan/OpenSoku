#include "global_types.h"
#include <SFML/Graphics.hpp>


#include "archive.h"
#include "file_read.h"

int main()
{
    // Create the main window

	// Start the game loop

    arc_add_dat("th123a.dat");
    arc_add_dat("th123b.dat");

    filehandle *aa = arc_get_file("data/scene/select/scenario/sc.dat");

    if (aa != NULL)
    {
        printf("Found\n");

    }

    return EXIT_SUCCESS;
}
