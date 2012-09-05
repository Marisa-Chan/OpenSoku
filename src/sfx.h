#ifndef SFX_H_INCLUDED
#define SFX_H_INCLUDED

#include <SFML/Audio.hpp>

typedef sf::SoundBuffer sfxc;


void sfx_init();
void sfx_play(sfxc *snd);

sfxc *sfx_load_cv3(filehandle *f);

#endif // SFX_H_INCLUDED
