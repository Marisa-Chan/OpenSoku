#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "framedata.h"
#include "scene_fx.h"
#include "weather.h"
#include "battle_ui.h"

using namespace std;


#define CHAR_PADDING  40
#define BKG_HOR_PAD   60.0
#define BKG_VERT_POS  860.0



struct s_camera
{
    float x;
    float y;
    float scale;
};

class char_c;
class background;

struct spell_bkg_images
{
    gr_tex *spell_image[2];
    uint8_t alpha;
    float dx[2];
    float dy[2];
    int8_t alpha_delta;
};

class pause_menu;

class c_scene
{
    protected:
    friend pause_menu;

    btl_ui *ui;

    s_camera cam;
    int32_t game_state;
    int32_t frames;
    int32_t field_8;
    int32_t cur_game_state;

    void upd_wfx_bkg_sky();

    bool sub_47AD60(c_meta *plr, c_meta *enm);
    bool sub_479D50(c_meta *p1, c_meta *p2);
    bool sub_479720(frame_box *a1, frame_box *a2, frame_box *b1, frame_box *b2);
    void sub_479250(frame_box *a2, frame_box *a3, frame_box *a4, frame_box *a5);
    void scene_set_ibox(frame_box *a2, frame_box *a3);
    void sub_479200(frame_box *a1, frame_box *a2, frame_box *a3);
    bool sub_479420(frame_box *a1, frame_box *a2, frame_box *a3);
    bool sub_479650(c_meta *p1, c_meta *p2);
    bool sub_479BC0(c_meta *p1, c_meta *p2);
    bool sub_47BD80(c_meta *plr, char_c *enm);
    bool sub_47ABE0(c_meta *plr, c_meta *enm);
    bool sub_47AAA0(c_meta *plr, char_c *enm);
    void scene_add_effect_ibox(int32_t idx, int8_t dir);
    bool sub_47BBA0(c_meta *plr, char_c *enm);
    void sub_47A060(c_meta *plr, char_c *enm);
    void sub_478FC0(char_c *plr, char_c *enm);
    bool sub_47B5A0(c_meta *plr, char_c *enm);
    void sub_47A980(c_meta *plr, char_c *enm);
    bool sub_47B8F0(c_meta *plr, char_c *enm);
    void sub_47BE70(c_meta *plr, char_c *enm);
    bool sub_47C080(c_meta *plr, c_meta *enm);
    char sub_47AC70(c_meta *plr, c_meta *enm);
    void sub_47BFA0(c_meta *plr, c_meta *enm);
    bool sub_47AD00(c_meta *plr, c_meta *enm);
    bool scene_collid(box_box *b1, box_box *b2);
    void sub_47C180();
    void sub_47C430();
    void clear_action_keys();
    void clear_all_keys();

    void scene_subfunc1();
    void scene_subfunc2();
    void scene_check_collisions();
    void scene_subfunc4();
    void scene_subfunc5();

    public:

    c_scene();
    virtual ~c_scene();

    t_weather_manager *w_man;

    char_c      *chrs[2];
    background  *bkg;
    frame_box   ibox;  //box

    metalst     list1[2];
    metalst     list2[2];
    metalst     list3[2];
    int32_t     scn_p1[2];
    int32_t     scn_p2[2];
    int8_t      field_904;

    spell_bkg_images spell_images;

    //c_scene();

    int32_t get_stage_id();

    void set_camera(float x1, float y1, float x2, float y2);
    void upd_camera(float x1, float y1, float x2, float y2);
    void set_camera(char_c *p1,char_c *p2);
    void upd_camera(char_c *p1,char_c *p2);
    void apply_camera();
    void set_start_flag(int8_t flag);
    void sub_47A7E0(c_meta *plr, char_c *enemy, int32_t a4, int32_t a5, int32_t a6, int32_t a7);

    void reset_ibox();

    void draw_scene();
    void players_input();

    virtual void init(background *bg, char_c *p1, char_c *p2) = 0;
    virtual int8_t update() = 0;        //Func3
    virtual int8_t state0_update() = 0; //Func4
    virtual int8_t state1_update() = 0; //Func5
    virtual int8_t state2_update() = 0; //Func6
    virtual int8_t state3_update() = 0; //Func7
    virtual int8_t state5_update() = 0; //Func8
    virtual int8_t state6_update() = 0; //Func9
    virtual int8_t state7_update() = 0; //Func10
    virtual void func11(char_c *pl) = 0;
    virtual void func12() = 0;
    virtual void func13(int32_t val) = 0;
    virtual void func14();
    virtual void func15();
    virtual void func16() = 0;
};


bool char_on_ground_flag(char_c *chr);
bool char_on_ground_down(char_c *chr);
void char_xy_pos_calculation(char_c *chr);


void scene_load_sounds();
void scene_play_sfx(uint32_t idx);

void scene_add_effect(c_meta *chr, int32_t idx, float x, float y, int8_t dir, int8_t order);
c_scene_sp *scene_get_sp();


uint32_t scene_rand();
uint32_t scene_rand_rng(uint32_t rng);
float scene_rand_rngf(uint32_t rng);

int32_t time_count_get();
void time_count_inc();
void time_count_set(int32_t st);

c_scene *scene_new_scene(background *bg, char_c *p1, char_c *p2);
c_scene *scene_get_scene();

bool sub_479510(frame_box *a1, frame_box *a2, int32_t x, int32_t y);
bool sub_4795A0(int32_t x11, int32_t y11, int32_t x12, int32_t y12, int32_t x21, int32_t y21, int32_t x22, int32_t y22);

void scene_set_spell_img(uint8_t idx, gr_tex *img);


#endif // SCENE_H_INCLUDED
