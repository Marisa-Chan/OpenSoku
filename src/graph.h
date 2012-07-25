#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <SFML/Graphics.hpp>

class filehandle;

typedef sf::Texture gr_tex;
typedef sf::Sprite  gr_sprite;

void gr_init(uint32_t width, uint32_t height, const char *caption);

void gr_clear();

void gr_flip();

void gr_tex_update(gr_tex *tex, void *buf, uint32_t wi, uint32_t hi);

gr_tex * gr_create_tex(uint32_t width, uint32_t height);

gr_tex *gr_load_cv2(filehandle *f, uint32_t *pal);

gr_sprite * gr_create_sprite();

void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex);

void gr_draw_sprite(gr_sprite *spr, float x, float y);

#endif // GRAPH_H_INCLUDED
