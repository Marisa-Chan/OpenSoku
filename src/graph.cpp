#include "global_types.h"
#include "file_read.h"
#include "graph.h"

static sf::RenderWindow *window = NULL;


static gr_state zerostate;
static gr_state states[MAX_STATES];

void gr_init(uint32_t width, uint32_t height, const char *caption)
{
    window = new sf::RenderWindow(sf::VideoMode(width,height), caption);
    window->setFramerateLimit(60);
}

void gr_clear()
{
    window->clear(sf::Color(128,128,128, 255));
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

    if (hdr.bpp == 8 && pal != NULL)
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

void gr_setxy_sprite(gr_sprite *spr, float x, float y)
{
    spr->setPosition(x,y);
}

void gr_setscale_sprite(gr_sprite *spr, float x, float y)
{
    spr->setScale(x,y);
}

void gr_draw_sprite(gr_sprite *spr,gr_blend blend,uint8_t plane)
{
    if (plane < MAX_STATES)
    {
        sf::BlendMode tmp = states[plane].blendMode;
        switch(blend)
        {
            case gr_add:
                states[plane].blendMode = sf::BlendAdd;
                break;
            case gr_mult:
                states[plane].blendMode = sf::BlendMultiply;
                break;
            case gr_alpha:
                states[plane].blendMode = sf::BlendAlpha;
                break;
            case gr_none:
                states[plane].blendMode = sf::BlendNone;
                break;
        };

        window->draw(*spr,states[plane]);
        states[plane].blendMode = tmp;
    }
}

void gr_setorigin_sprite(gr_sprite *spr, float x, float y)
{
    spr->setOrigin(x,y);
}

void gr_reset_state(uint8_t plane)
{
    if (plane < MAX_STATES)
        states[plane] = zerostate;
}

void gr_plane_scale(uint8_t plane, float x, float y)
{
    if (plane < MAX_STATES)
        states[plane].transform.scale(x,y);
}

void gr_plane_rotate(uint8_t plane, float angle)
{
    if (plane < MAX_STATES)
        states[plane].transform.rotate(angle);
}

void gr_plane_translate(uint8_t plane, float x, float y)
{
    if (plane < MAX_STATES)
        states[plane].transform.translate(x,y);
}

void gr_draw_box(float x1,float y1, int r, int g, int b,uint8_t plane)
{
    sf::RectangleShape box(sf::Vector2f(10,10));
    box.setFillColor(sf::Color(r,g,b,255));
    box.setPosition(x1-5,y1-5);
    window->draw(box,states[plane]);
}
