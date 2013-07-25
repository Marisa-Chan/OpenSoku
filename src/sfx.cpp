#include "global_types.h"
#include "file_read.h"
#include "sfx.h"

#define SFX_CHANNELS    32

sf::Sound   chnls[SFX_CHANNELS];
bool        fchnls[SFX_CHANNELS];



void sfx_init()
{
    for (uint32_t i=0; i<SFX_CHANNELS; i++)
        fchnls[i] = false;
}

void sfx_check()
{
    for (uint32_t i=0; i<SFX_CHANNELS; i++)
        if (fchnls[i])
            if (chnls[i].getStatus() == sf::Sound::Stopped || chnls[i].getStatus() == sf::Sound::Paused)
            {
                chnls[i].stop();
                fchnls[i] = false;
            }
}

int32_t sfx_get_freechn()
{
    for (uint32_t i=0; i<SFX_CHANNELS; i++)
        if (!fchnls[i])
        {
            fchnls[i] = true;
            return i;
        }
    return -1;
}



void sfx_play(sfxc *snd)
{
    sfx_check();

    int32_t t = sfx_get_freechn();
    if (t >= 0)
    {
        chnls[t].setBuffer(*snd);
        chnls[t].setVolume(0.75);
        chnls[t].play();
    }

}


sfxc *sfx_load_cv3(filehandle *f)
{
    uint16_t tmp2 = 0;
    uint32_t tmp4 = 0;
    f->read(2,&tmp2);

    uint16_t chn = 0;
    f->read(2,&chn);

    uint32_t smplr = 0;
    f->read(4,&smplr);

    f->read(4,&tmp4);

    f->read(2,&tmp2);
    f->read(2,&tmp2);
    f->read(2,&tmp2);

    int32_t sz = f->get_size() - 0x12;

    int16_t *smpls = (int16_t *)malloc(sz);

    f->read(sz, smpls);

    sfxc *tmp = new sfxc;

    tmp->loadFromSamples(smpls,sz/2, chn, smplr);

    free(smpls);

    return tmp;
}


