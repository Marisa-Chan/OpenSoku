#ifndef GUI_H_INCLUDED
#define GUI_H_INCLUDED

struct gui_tex
{
    int32_t l,t,r,b; //margins
    gr_tex * tex;
};

class gui_holder;

class gui_element
{
    friend
    gui_holder;

    protected:

    float x = 0;
    float y = 0;
    float dx = 0;
    float dy = 0;
    float angle = 0;
    int32_t ox = 0;
    int32_t oy = 0;

    uint8_t c_A = 255;
    uint8_t c_R = 255;
    uint8_t c_G = 255;
    uint8_t c_B = 255;

    gui_tex   *tex    = NULL;
    gr_sprite *sprite = NULL;

    float sx = 1.0;
    float sy = 1.0;

    public:

    bool renderable = false;

    const int32_t guid;

    gui_element(int32_t guid);

    void setXY(float x, float y);
    void setDXDY(float x, float y);
    void setOrigin(int32_t x, int32_t y);
    void setScale(float x, float y);
    void setRotate(float angle);
    void setColor(uint8_t a,uint8_t r,uint8_t g,uint8_t b);
    float getDX();
    float getDY();
    float getX();
    float getY();


    virtual void draw(int8_t plane) = 0;
    virtual void draw(float dx, float dy, int8_t plane) = 0;

    virtual int8_t get_type()
    {
        return -1;
    }
};

class gui_el_t6: public gui_element
{
    private:
    int32_t frames;
    int32_t w;
    int32_t h;
    int32_t dw;
    int32_t flt;
    int32_t intg;

    float   varf = -8.1;
    int32_t vard = 36;

    void draw_d(float dx, float dy, int8_t plane);
    void draw_f(float dx, float dy, int8_t plane);
    void draw_frame(int32_t frame, float dx, float dy, int8_t plane);

    public:

    gui_el_t6(gui_tex *tex, int32_t w, int32_t h, int32_t frames, int32_t dx, int32_t intg, int32_t flt);
    gui_el_t6(int32_t _guid, gui_tex *tex, int32_t w, int32_t h, int32_t frames, int32_t dx, int32_t intg, int32_t flt);
    void draw(int8_t plane);
    void draw(float dx, float dy, int8_t plane);

    void setFloat(float f);
    void setInt(int32_t d);

    virtual int8_t get_type()
    {
        return 2;
    }
};

class gui_el_t1: public gui_element
{
    private:
    int32_t f_w = 0;
    int32_t f_h = 0;
    public:
    gui_el_t1();
    gui_el_t1(int32_t _guid);
    void draw(int8_t plane);
    void draw(float dx, float dy, int8_t plane);
    void draw(float x, float y, float w, float h, int8_t plane);
    void draw(float dx, float dy, float x, float y, float w, float h, int8_t plane);
    void draw_frame(int32_t col, int32_t row,int8_t plane);
    void draw_frame(float dx, float dy, int32_t col, int32_t row,int8_t plane);

    void set_frame_size(int32_t w, int32_t h);

    void setTexture(gr_tex *tex);
    void setTexture(gr_tex *tex,float x, float y, float w, float h);
    void setTextureFramed(gr_tex *_tex, int32_t w, int32_t h);

    virtual int8_t get_type()
    {
        return 1;
    }
};

class gui_el_t0: public gui_element
{
    public:

    gui_el_t0(gui_tex *tex);
    gui_el_t0(int32_t _guid, gui_tex *tex);
    void draw(int8_t plane);
    void draw(float dx, float dy, int8_t plane);

    virtual int8_t get_type()
    {
        return 0;
    }
};


class gui_holder
{
    protected:
    vector<gui_tex> imgs;
    vector<gui_element *> elmnt;

    public:
    //gui_holder();
    //~gui_holder();

    bool load_dat(const char *path, const char *file);

    void draw_all(int8_t plane);
    void draw_by_id(int32_t id, int8_t plane);

    gui_el_t0 *get_gui_t0(int32_t id);
    gui_el_t6 *get_gui_t6(int32_t id);
    gui_el_t1 *get_gui_t1(int32_t id);

};




#endif // GUI_H_INCLUDED
