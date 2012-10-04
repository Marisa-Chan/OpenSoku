#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "fxsprite/fxSprite.hpp"

#define MAX_STATES  8

class filehandle;

typedef sf::Texture gr_tex;
typedef sf::fxSprite  gr_sprite;
typedef sf::RenderStates gr_state;

enum gr_blend
{
    gr_alpha  = 0,
    gr_add    = 1,
    gr_mult   = 2,
    gr_none   = 3
};

void gr_init(uint32_t width, uint32_t height, const char *caption);

void gr_clear();

void gr_flip();

void gr_tex_update(gr_tex *tex, void *buf, uint32_t wi, uint32_t hi);

gr_tex * gr_create_tex(uint32_t width, uint32_t height);

gr_tex *gr_load_cv2(filehandle *f, uint32_t *pal);

gr_sprite * gr_create_sprite();

void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex);

void gr_setxy_sprite(gr_sprite *spr, float x, float y);
void gr_setscale_sprite(gr_sprite *spr, float x, float y);
void gr_setscale_sprite(gr_sprite *spr, float x, float y);
void gr_setorigin_sprite(gr_sprite *spr, float x, float y);
void gr_setrotate_sprite(gr_sprite *spr, float angl);
void gr_setrotate_sprite(gr_sprite *spr, float x, float y, float z);

void gr_draw_sprite(gr_sprite *spr, gr_blend blend = gr_alpha, uint8_t plane = 0);

void gr_reset_state(uint8_t plane);
void gr_plane_scale(uint8_t plane, float x, float y);
void gr_plane_rotate(uint8_t plane, float angle);
void gr_plane_translate(uint8_t plane, float x, float y);

void gr_draw_box(float x1,float y1, int r, int g, int b,uint8_t plane);
void gr_draw_box(float x1,float y1,float w, float h, int r, int g, int b,int a,uint8_t plane);

void gr_setcolor_sprite(gr_sprite *spr, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
void gr_setcolor_sprite(gr_sprite *spr, uint8_t R, uint8_t G, uint8_t B);

#endif // GRAPH_H_INCLUDED
