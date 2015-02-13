#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <SFML/Graphics.hpp>
#include "fxsprite/fxSprite.hpp"

#define MAX_STATES  8

class filehandle;

typedef sf::Texture gr_tex;
typedef sf::fxSprite  gr_sprite;
typedef sf::RenderStates gr_state;
typedef sf::Shader gr_shader;
typedef sf::fxTransform gr_transform;

struct gr_tristrip
{
    sf::VertexArray privat;
    uint8_t a,r,g,b;
    gr_tex *tex;
};

enum gr_blend
{
    gr_alpha  = 0,
    gr_add    = 1,
    gr_mult   = 2,
    gr_none   = 3
};

struct gr_info
{
    float x;
    float y;
    float w;
    float h;
};

struct gr_tex_box
{
    float x;
    float y;
    float w;
    float h;
    bool autosize;
    uint8_t r,g,b,a;
    gr_tex *tex;
    float skew_x;
    float skew_y;
    bool skew_in_pix;
    bool overlay_tex;
    float tex_scl_x;
    float tex_scl_y;
};

struct gr_events
{
    void (*keyb_events)(int32_t, bool);
};

void gr_init(uint32_t width, uint32_t height, const char *caption, gr_events pollers);
void gr_poll_events();
void gr_clear(uint8_t r = 128, uint8_t g = 128, uint8_t b = 128);

void gr_flip();

void gr_tex_update(gr_tex *tex, void *buf, uint32_t wi, uint32_t hi);

gr_tex * gr_create_tex(uint32_t width, uint32_t height);

gr_tex *gr_load_cv2(filehandle *f, uint32_t *pal);
gr_tex *gr_load_cv2(const char *filename, uint32_t *pal);
void gr_delete_tex(gr_tex *tex);

gr_sprite * gr_create_sprite();
void gr_delete_sprite(gr_sprite *spr);
void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex);
void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex,int32_t x, int32_t y, int32_t w, int32_t h);
void gr_set_spr_box(gr_sprite *spr,int32_t x, int32_t y, int32_t w, int32_t h);
void gr_set_spr_box_perc(gr_sprite *spr,float x, float y, float x2, float y2);

void gr_setxy_sprite(gr_sprite *spr, float x, float y);
void gr_setscale_sprite(gr_sprite *spr, float x, float y);
void gr_setscale_sprite(gr_sprite *spr, float x, float y);
void gr_setorigin_sprite(gr_sprite *spr, float x, float y);
void gr_setrotate_sprite(gr_sprite *spr, float angl);
void gr_setrotate_sprite(gr_sprite *spr, float x, float y, float z);
void gr_settransform_sprite(gr_sprite *spr, gr_transform *trans);

void gr_draw_sprite(gr_sprite *spr, gr_blend blend = gr_alpha, uint8_t plane = 0, gr_shader *shader = NULL);

void gr_reset_state(uint8_t plane);
void gr_plane_scale(uint8_t plane, float x, float y);
void gr_plane_rotate(uint8_t plane, float angle);
void gr_plane_translate(uint8_t plane, float x, float y);

void gr_draw_box(float x1,float y1, int r, int g, int b,uint8_t plane);
void gr_draw_box(float x1,float y1,float w, float h, int r, int g, int b,int a,uint8_t plane);

void gr_setcolor_sprite(gr_sprite *spr, uint8_t R, uint8_t G, uint8_t B, uint8_t A);
void gr_setcolor_sprite(gr_sprite *spr, uint8_t R, uint8_t G, uint8_t B);

void gr_load_shader(gr_shader *shd, const char *vertex, const char *pixel);
void gr_load_shader_from_mem(gr_shader *shd, const char *vertex,const char *pixel);
void gr_shader_set_texture(gr_shader *shd, const char *param, gr_tex *tex);
void gr_shader_set(gr_shader *shd, const char *param, float x);
void gr_shader_set(gr_shader *shd, const char *param, float x, float y);
void gr_shader_set(gr_shader *shd, const char *param, float x, float y, float z);
void gr_shader_set(gr_shader *shd, const char *param, float x, float y, float z, float w);

gr_info gr_get_info(gr_sprite *spr);
gr_info gr_get_info(gr_tex *tex);
void gr_set_repeate(gr_tex *tex, bool rpt);
void gr_set_smoth(gr_tex *tex, bool smoth);
void gr_sprite_setuv(gr_sprite *spr, float x1, float y1, float x2, float y2);
void gr_sprite_skew(gr_sprite *spr, float x, float y);

void debug_str(float x, float y, const char *str);
void gr_draw_tex_box(gr_tex_box *box, gr_blend blend = gr_alpha, uint8_t plane = 0, gr_shader *shader = NULL);


gr_tristrip *gr_tristrip_new(uint32_t cnt);
void gr_tristrip_free(gr_tristrip *strip);
void gr_tristrip_set_color(gr_tristrip *strip, uint8_t a, uint8_t r, uint8_t g, uint8_t b);
void gr_tristrip_set_tex(gr_tristrip *strip, gr_tex *tex);
void gr_tristrip_set_vtx(gr_tristrip *strip, int32_t idx, float x, float y);
void gr_tristrip_set_vtx(gr_tristrip *strip, int32_t idx, float x, float y, float u, float v);
void gr_tristrip_draw(gr_tristrip *strip, gr_blend blend = gr_alpha, uint8_t plane = 0, gr_shader *shader = NULL);

#endif // GRAPH_H_INCLUDED

