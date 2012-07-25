#include "global_types.h"
#include "file_read.h"
#include "graph.h"

sf::RenderWindow *window = NULL;

void gr_init(uint32_t width, uint32_t height, const char *caption)
{
    window = new sf::RenderWindow(sf::VideoMode(width,height), caption);
    window->setFramerateLimit(60);
}

void gr_clear()
{
    window->clear();
}

void gr_flip()
{
    window->display();
}

void gr_tex_update(gr_tex *tex, void *buf, uint32_t wi, uint32_t hi)
{
    tex->update((uint8_t *)buf,wi,hi,0,0);
}

gr_tex * gr_create_tex(uint32_t width, uint32_t height)
{
    gr_tex * tmp = new gr_tex;
    tmp->create(width, height);
    return tmp;
}

gr_tex *gr_load_cv2(filehandle *f, uint32_t *pal)
{
    gr_tex *tex = NULL;

    struct header_t {
			uint8_t bpp;
			uint32_t width;
			uint32_t height;
			uint32_t pitch;
			uint8_t  unknown;
			uint16_t unknown2;
			uint8_t  unknown3;
		} __attribute__((packed)) hdr;

    f->read(sizeof(hdr), &hdr);

    tex = gr_create_tex(hdr.width, hdr.height);

    uint32_t *img = (uint32_t *)malloc(hdr.width * hdr.height * 4);

    if (hdr.bpp == 8)
    {
        uint8_t *buf = (uint8_t *)malloc(hdr.pitch * hdr.height);
        f->read(hdr.pitch * hdr.height, buf);

        for (uint32_t j=0; j < hdr.height; j++)
            for (uint32_t i=0; i < hdr.width; i++)
            {
                img[i+j*hdr.width] = pal[buf[j*hdr.pitch+i]];
            }
        free(buf);
    }
    else if (hdr.bpp == 24 || hdr.bpp == 32)
    {
        uint32_t *buf = (uint32_t *)malloc(hdr.pitch * hdr.height * 4);
        f->read(hdr.pitch * hdr.height * 4, buf);

        for (uint32_t j=0; j < hdr.height; j++)
            for (uint32_t i=0; i < hdr.width; i++)
            {
                img[i+j*hdr.width] = (buf[i+j*hdr.pitch] & 0xFF00FF00)       |
                                     ((buf[i+j*hdr.pitch] & 0x0000FF) << 16) |
                                     ((buf[i+j*hdr.pitch] & 0xFF0000) >> 16) ;
            }
        free(buf);
    }
    else
    {
        printf("16bit!!!\n");
    }

    gr_tex_update(tex, img, hdr.width, hdr.height);

    free(img);

    return tex;
}

gr_sprite * gr_create_sprite()
{
    return new gr_sprite;
}

void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex)
{
    if (tex != NULL)
        spr->setTexture(*tex, true);
}

void gr_draw_sprite(gr_sprite *spr, float x, float y)
{
    if (spr->getTexture() != NULL)
    {
        spr->setPosition(x,y);
        window->draw(*spr);
    }
}
