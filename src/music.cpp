#include "global_types.h"
#include "archive.h"
#include "file_read.h"
#include "music.h"

sf::Music mus;

void *bf = NULL;

void playmusic()
{
    filehandle *f = arc_get_file("data/bgm/st11.ogg");
    if (f)
    {
        bf = malloc(f->get_size());
        f->read(f->get_size(),bf);

        mus.openFromMemory(bf,f->get_size());

        mus.setVolume(90);
        mus.play();


        delete f;
    }
}
