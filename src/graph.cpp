#include "global_types.h"
#include "file_read.h"
#include "archive.h"
#include "graph.h"
#include <locale>
#include <math.h>

static sf::RenderWindow *window = NULL;

static gr_state zerostate;
static gr_state states[MAX_STATES];

static gr_events poller;

void gr_init(uint32_t width, uint32_t height, const char *caption, gr_events pollers)
{
    window = new sf::RenderWindow(sf::VideoMode(width,height), caption);

    window->setFramerateLimit(60);

    poller = pollers;
}

void gr_poll_events()
{
    sf::Event event;
    while (window->pollEvent(event))
    {
        // Request for closing the window
        //if (event.type == sf::Event::Closed)
            //window.close();
        // The escape key was pressed
        if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
        {
            if (poller.keyb_events)
                poller.keyb_events(event.key.code , event.type == sf::Event::KeyPressed);
        }
        // The window was resized
        //if (event.type == sf::Event::Resized)
            //doSomethingWithTheNewSize(event.size.width, event.size.height);
        // etc ...
    }
}

void gr_clear(uint8_t r, uint8_t g, uint8_t b)
{
    window->clear(sf::Color(r,g,b, 255));
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

gr_tex *gr_load_cv2(const char *filename, uint32_t *pal)
{
    filehandle *f = arc_get_file(filename);
    if (f)
    {
        gr_tex *tx = gr_load_cv2(f,pal);
        delete f;
        return tx;
    }
    return NULL;
}

gr_tex *gr_load_cv2(filehandle *f, uint32_t *pal)
{
    gr_tex *tex = NULL;

    struct header_t
    {
        uint8_t bpp;
        uint32_t width;
        uint32_t height;
        uint32_t pitch;
        uint8_t  unknown;
        uint16_t unknown2;
        uint8_t  unknown3;
    } __attribute__((packed)) hdr;

    f->read(1, &hdr.bpp);
    f->read(4, &hdr.width);
    f->read(4, &hdr.height);
    f->read(4, &hdr.pitch);
    f->read(1, &hdr.unknown);
    f->read(2, &hdr.unknown2);
    f->read(1, &hdr.unknown3);

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
    //gr_set_smoth(tex, true);

    free(img);

    return tex;
}

void gr_delete_tex(gr_tex *tex)
{
    delete tex;
}

gr_sprite * gr_create_sprite()
{
    return new gr_sprite;
}

void gr_delete_sprite(gr_sprite *spr)
{
    delete spr;
}

void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex)
{
    if (tex != NULL)
        spr->setTexture(*tex, true);
}

void gr_set_spr_tex(gr_sprite *spr, gr_tex *tex,int32_t x, int32_t y, int32_t w, int32_t h)
{
    if (tex != NULL)
    {
        spr->setTexture(*tex, false);
        spr->setTextureRect(sf::IntRect(x,y,w,h));
    }
}

void gr_set_spr_box(gr_sprite *spr,int32_t x, int32_t y, int32_t w, int32_t h)
{
    spr->setTextureRect(sf::IntRect(x,y,w,h));
}

void gr_set_spr_box_perc(gr_sprite *spr,float x, float y, float w, float h)
{
    sf::Vector2u a =  spr->getTexture()->getSize();
    w -= x;
    h -= y;
    spr->setTextureRect(sf::IntRect(x*a.x,y*a.y,w*a.x,h*a.y));
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

void gr_setrotate_sprite(gr_sprite *spr, float angl)
{
    spr->setRotationZ(angl);
}

void gr_setrotate_sprite(gr_sprite *spr, float x, float y, float z)
{
    spr->setRotation(x,y,z);
}

void gr_settransform_sprite(gr_sprite *spr, gr_transform *trans)
{
    spr->setTransform(*trans);
}

void gr_setscale_sprite(gr_sprite *spr, float x, float y)
{
    spr->setScale(x,y);
}

void gr_draw_sprite(gr_sprite *spr,gr_blend blend,uint8_t plane, gr_shader *shader)
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

        states[plane].shader = shader;
        window->draw(*spr,states[plane]);
        states[plane].blendMode = tmp;
        states[plane].shader = NULL;
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

void gr_draw_box(float x1,float y1,float w, float h, int r, int g, int b,int a,uint8_t plane)
{
    sf::RectangleShape box(sf::Vector2f(w,h));
    box.setFillColor(sf::Color(r,g,b,a));
    box.setPosition(x1,y1);
    window->draw(box,states[plane]);
}

void gr_setcolor_sprite(gr_sprite *spr, uint8_t R, uint8_t G, uint8_t B, uint8_t A)
{
    spr->setColor(sf::Color(R,G,B,A));
}

void gr_setcolor_sprite(gr_sprite *spr, uint8_t R, uint8_t G, uint8_t B)
{
    spr->setColor(sf::Color(R,G,B));
}

void gr_load_shader(gr_shader *shd, const char *vertex, const char *pixel)
{
    if (vertex != NULL && pixel != NULL)
        shd->loadFromFile(vertex,pixel);
    else if (vertex == NULL && pixel)
        shd->loadFromFile(pixel,sf::Shader::Fragment);
    else if (pixel == NULL && vertex)
        shd->loadFromFile(vertex,sf::Shader::Vertex);
}

void gr_load_shader_from_mem(gr_shader *shd, const char *vertex,const char *pixel)
{
    if (vertex != NULL && pixel != NULL)
        shd->loadFromMemory(vertex,pixel);
    else if (vertex == NULL && pixel)
        shd->loadFromMemory(pixel,sf::Shader::Fragment);
    else if (pixel == NULL && vertex)
        shd->loadFromMemory(vertex,sf::Shader::Vertex);
}

void gr_shader_set_texture(gr_shader *shd, const char *param, gr_tex *tex)
{
    if (tex == NULL)
        shd->setParameter(param,sf::Shader::CurrentTexture);
    else
        shd->setParameter(param,*tex);
}

void gr_shader_set(gr_shader *shd, const char *param, float x)
{
    shd->setParameter(param,x);
}

void gr_shader_set(gr_shader *shd, const char *param, float x, float y)
{
    shd->setParameter(param,x,y);
}

void gr_shader_set(gr_shader *shd, const char *param, float x, float y, float z)
{
    shd->setParameter(param,x,y,z);
}

void gr_shader_set(gr_shader *shd, const char *param, float x, float y, float z, float w)
{
    shd->setParameter(param,x,y,z,w);
}

gr_info gr_get_info(gr_sprite *spr)
{
    gr_info tmp;
    sf::FloatRect v = spr->getGlobalBounds();
    tmp.x = v.left;
    tmp.y = v.top;
    tmp.w = v.width;
    tmp.h = v.height;
    return tmp;
}

gr_info gr_get_info(gr_tex *tex)
{
    gr_info tmp;
    sf::Vector2u a =  tex->getSize();
    tmp.x = 0;
    tmp.y = 0;
    tmp.w = a.x;
    tmp.h = a.y;
    return tmp;
}

void gr_set_repeate(gr_tex *tex, bool rpt)
{
    tex->setRepeated(rpt);
}
void gr_set_smoth(gr_tex *tex, bool smoth)
{
    tex->setSmooth(smoth);
}

void gr_sprite_setuv(gr_sprite *spr, float x1, float y1, float x2, float y2)
{
    sf::Vector2u sz = spr->getTexture()->getSize();
    spr->setTextureRect(sf::IntRect(x1*sz.x,y1*sz.y, x2*sz.x, y2*sz.y));
}

void gr_sprite_skew(gr_sprite *spr, float x, float y)
{
    sf::Vector2u sz = spr->getTexture()->getSize();
    spr->setTextureRect(sf::IntRect(x, y, sz.x, sz.y));
}


sf::Text *ttx = NULL;
sf::Font *fnt = NULL;

void debug_str(float x, float y, const char *str)
{
    if (!fnt)
    {
        fnt = new sf::Font();
        fnt->loadFromFile("/usr/share/fonts/TTF/DejaVuSans.ttf");
    }

    if (!ttx)
        ttx = new sf::Text(str, *fnt, 10);

    ttx->setString(str);
    ttx->setPosition(x,y);
    window->draw(*ttx);
}

void gr_draw_tex_box(gr_tex_box *box, gr_blend blend,uint8_t plane, gr_shader *shader)
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

        states[plane].shader = shader;

        sf::Vector2u tx_sz =  box->tex->getSize();

        float box_w, box_h;
        if (box->autosize)
        {
            box_w = tx_sz.x;
            box_h = tx_sz.y;
        }
        else
        {
            box_w = box->w;
            box_h = box->h;
        }

        sf::RectangleShape sbox(sf::Vector2f(box_w,box_h));
        sbox.setPosition(box->x,box->y);

        sbox.setFillColor(sf::Color(box->r,box->g,box->b,box->a));
        sbox.setTexture(box->tex);

        float skew_x = box->skew_x;
        float skew_y = box->skew_y;

        if (!box->skew_in_pix)
        {
            skew_x *= tx_sz.x;
            skew_y *= tx_sz.y;
        }

        float tex_scl_x = 1.0;
        float tex_scl_y = 1.0;

        if (box->overlay_tex)
        {
            tex_scl_x = box_w / tx_sz.x;
            tex_scl_y = box_h / tx_sz.y;
        }
        else
        {
            tex_scl_x = box->tex_scl_x;
            tex_scl_y = box->tex_scl_y;
        }


        sbox.setTextureRect(sf::IntRect(skew_x, skew_y, tx_sz.x * tex_scl_x,  tx_sz.y * tex_scl_y));

        window->draw(sbox,states[plane]);

        states[plane].blendMode = tmp;
        states[plane].shader = NULL;
    }
}


gr_tristrip *gr_tristrip_new(uint32_t cnt)
{
    gr_tristrip *tmp = new gr_tristrip;
    tmp->privat.setPrimitiveType(sf::TrianglesStrip);
    tmp->privat.resize(cnt);
    tmp->a = 255;
    tmp->r = 255;
    tmp->g = 255;
    tmp->b = 255;
    tmp->tex = NULL;
    return tmp;
}

void gr_tristrip_free(gr_tristrip *strip)
{
    delete strip;
}

void gr_tristrip_set_color(gr_tristrip *strip, uint8_t a, uint8_t r, uint8_t g, uint8_t b)
{
    strip->a = a;
    strip->r = r;
    strip->g = g;
    strip->b = b;
    sf::Color clr(r,g,b,a);
    for(uint32_t i=0; i<strip->privat.getVertexCount(); i++)
        strip->privat[i].color = clr;
}
void gr_tristrip_set_tex(gr_tristrip *strip, gr_tex *tex)
{
    strip->tex = tex;
}

void gr_tristrip_set_vtx(gr_tristrip *strip, int32_t idx, float x, float y)
{
    strip->privat[idx].position = sf::Vector2f(x,y);
}

void gr_tristrip_set_vtx(gr_tristrip *strip, int32_t idx, float x, float y, float u, float v)
{
    if (strip->tex)
    {
        sf::Vector2u sz = strip->tex->getSize();
        strip->privat[idx].texCoords = sf::Vector2f(sz.x * u, sz.y * v);
    }
    else
        strip->privat[idx].texCoords = sf::Vector2f(u,v);
    strip->privat[idx].position = sf::Vector2f(x,y);
}

void gr_tristrip_draw(gr_tristrip *strip, gr_blend blend , uint8_t plane , gr_shader *shader)
{
        if (plane < MAX_STATES)
    {
        gr_state tmp = states[plane];

        switch(blend)
        {
        case gr_add:
            tmp.blendMode = sf::BlendAdd;
            break;
        case gr_mult:
            tmp.blendMode = sf::BlendMultiply;
            break;
        case gr_alpha:
            tmp.blendMode = sf::BlendAlpha;
            break;
        case gr_none:
            tmp.blendMode = sf::BlendNone;
            break;
        };

        tmp.shader = shader;

        if (strip->tex)
            tmp.texture = strip->tex;

        window->draw(strip->privat,tmp);
    }
}

