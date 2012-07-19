#include "global_types.h"
#include <SFML/Graphics.hpp>

#include "file_read.h"

int main()
{
    // Create the main window
    sf::RenderWindow App(sf::VideoMode(800, 600), "SFML window");

    // Load a sprite to display
    sf::Texture Image;
    if (!Image.loadFromFile("cb.bmp"))
        return EXIT_FAILURE;
    sf::Sprite Sprite(Image);

	// Start the game loop

    return EXIT_SUCCESS;
}
