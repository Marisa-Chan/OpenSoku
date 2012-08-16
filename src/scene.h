#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

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
};


#endif // SCENE_H_INCLUDED
