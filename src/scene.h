#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "framedata.h"
#include "scene_fx.h"
#include "weather.h"

using namespace std;


#define CHAR_PADDING  40
#define BKG_WIDTH     1280
#define BKG_HOR_PAD   60.0
#define BKG_VERT_POS  860.0

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

    void sub_478C30();
    void sub_470190();

    public:

    c_scene(background *bg, char_c *p1, char_c *p2);

    t_weather_manager *w_man;

    char_c      *chrs[2];
    background  *bkg;
    frame_box   ibox;  //box

    metalst     list1[2];
    metalst     list2[2];
    metalst     list3[2];
    int32_t     scn_p1[2];
    int32_t     scn_p2[2];

    //c_scene();

    int32_t get_stage_id();

    void set_camera(float x1, float y1, float x2, float y2);
    void upd_camera(float x1, float y1, float x2, float y2);
    void set_camera(char_c *p1,char_c *p2);
    void upd_camera(char_c *p1,char_c *p2);
    void apply_camera();

    void reset_ibox();

    void draw_scene();
    void update_char_anims();
    void players_input();

    void func11(char_c *pl);
    void func12();
    void func15();
    void func16();
    void update();
};



s_border get_border_near(char_c *chr);
float getlvl_height(moveable *chr);
float getlvl_height(moveable *chr, float dx);
void setlvl_height_rng(int32_t from, int32_t to, float lvl);

bool char_on_ground(char_c *chr);
bool char_on_ground_flag(char_c *chr);
bool char_on_ground_down(char_c *chr);
void char_xy_pos_calculation(char_c *chr);


void scene_load_sounds();
void scene_play_sfx(uint32_t idx);

void scene_add_effect(c_meta *chr, int32_t idx, float x, float y, int8_t dir, int8_t order);
void scene_add_effect_ibox(c_scene *scn, int32_t idx, int8_t dir);
c_scene_sp *scene_get_sp();


uint32_t scene_rand();
uint32_t scene_rand_rng(uint32_t rng);
float scene_rand_rngf(uint32_t rng);

int32_t time_count_get();
void time_count_inc();
void time_count_set(int32_t st);

c_scene *scene_new_scene(background *bg, char_c *p1, char_c *p2);
c_scene *scene_get_scene();

#endif // SCENE_H_INCLUDED
