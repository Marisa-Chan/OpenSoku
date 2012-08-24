#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#define CHAR_PADDING  40
#define BKG_WIDTH     1280

enum s_border
{
    BORD_LEFT  = 1,
    BORD_CENT  = 0,
    BORD_RIGHT = -1
};

struct s_camera
{
    float x;
    float y;
    float scale;
};

class char_c;
class background;

class c_scene
{
    private:

    s_camera cam;

    public:

    c_scene(background *bg, char_c *p1, char_c *p2);

    char_c      *chrs[2];
    background  *bkg;

    //c_scene();


    void set_camera(float x1, float y1, float x2, float y2);
    void upd_camera(float x1, float y1, float x2, float y2);
    void set_camera(char_c *p1,char_c *p2);
    void upd_camera(char_c *p1,char_c *p2);
    void apply_camera();

    void draw_scene();
    void update_char_anims();
    void players_input();


    void func16();
    void func12();
    void update();
};



s_border get_border_near(char_c *chr);
float getlvl_height(char_c *chr);
float getlvl_height(char_c *chr, float dx);
bool char_on_ground(char_c *chr);
bool char_on_ground_down(char_c *chr);
void char_xy_pos_calculation(char_c *chr);

#endif // SCENE_H_INCLUDED
