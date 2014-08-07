#include "global_types.h"
#include "framedata.h"
#include "input.h"
#include "character_def.h"
#include "scene.h"
#include "archive.h"
#include "file_read.h"
#include "weather.h"
#include <math.h>

int8_t dummy_block_type = 0; //HACK

char_c::char_c(inp_ab *func)
{
    if (!pgp)
        pgp = new char_graph;

    player_face_tex = NULL;    //texture
    player_face = NULL;        //sprite
    stand_gfx = new stand_graph();
    chr_cards.cards_holder.clear();
    chr_cards.card_mapping.clear();
    cards_deck.clear();
    cards_shuffle.clear();
    cards_active.clear();
    cards_used.clear();
    //graph_3.tex_id = 0;                                   //HACK
    //graph_3.vtbl = (graph_2dui_vtbl *)&graph_2dui_vtbl_;

    //all_seq__deque.clear()        // HACK NOT USED

    //create_default_struc714(&_this->struc714);  //HACK    USED FOR SANAE-GUI?

    spell_images.clear();
    //input__input__deque

    chrt = this;
    chrt_changeable = this;

    //pat_map = (mapstru *)v4; //HACK?  USED PGP with global common seq's
    //char_images_vector       //HACK?  USED PGP with global common seq's

    for (uint32_t i=0; i<MAX_CHR_SFX; i++)
        sfx[i] = NULL;

    input_function = 1; //HACK

    input = func;       //HACK!?
    input->set_devid(0); //HACK!?

    //char_id = sel_char->character_number;
    char_id = CHAR_ID_UNKNOW;                 //HACK!?
    //pallete_number = sel_char->pallete_index;     //HACK!?
    //player_index = sel_char->player_index         //HACK!?
    player_index = 0;                             //HACK!?


    //additional init

    field_80C = 0;
    field_1BC = 1;
}

char_c::~char_c()
{
    for (int32_t i=0; i<MAX_CHR_SFX; i++)
        if (sfx[i])
            sfx_delete(sfx[i]);

    if (player_face_tex)
        gr_delete_tex(player_face_tex);

    if (player_face)
        gr_delete_sprite(player_face);

    if (stand_gfx)
        delete stand_gfx;

    if (pgp)
        delete pgp; //DELETE ONLY IN CHARACTER

    bullist_iter iter = bullets.begin();
    while(iter != bullets.end())
    {
        c_bullet *blt = *iter;
        delete blt;

        iter++;
    }

    bullets.clear();

    deque<gr_tex *>::iterator spit = spell_images.begin();
    while(spit != spell_images.end())
    {
        gr_delete_tex( *spit);
        spit++;
    }

    spell_images.clear();

}

void char_c::init_vars()
{
    init_vars_base();
    field_7DC = 0.0;
    dash_angle = 0.0;
    field_7D0 = 0;
    field_7E4 = 0.0;
    field_7D2 = 0;
    field_7E8 = 0.0;
    field_7D4 = 0;
    field_7EC = 0.0;
    field_7D6 = 0;
    field_808 = 0.0;
    field_7D8 = 0;
    field_7FC = 0.0;
    not_charge_attack = 0;
    field_82C = 0.0;
    field_81A = 0;
    field_830 = 0.0;
    field_81C = 0;
    field_7F0 = 0.0;
    field_818 = 0;
    field_81E = 0;
    speed_mult = 1.0;
    field_820 = 0;
    field_822 = 0;
    field_824 = 0;
    field_826 = 0;
    field_838 = 0.0;
    field_828 = 0;
    field_844 = 0.0;
    x_delta = 0;
    field_840 = 0.0;
    y_delta = 0;
    field_848 = 0.0;
    field_524 = 0;
    field_854 = 0.0;
    field_526 = 0;
    field_858 = 0.0;
    bbarrier_show = false;
    field_85C = 0.0;
    damage_limited = 0;
    field_860 = 0.0;
    field_7F6 = 0;
    field_864 = 0.0;
    field_800 = 0;
    field_801 = 0;
    field_802 = 0;
    field_803 = 0;
    field_804 = 0;
    field_4C8 = 0;
    field_80D = 0;
    field_80E = 0;
    field_7F8 = 0;
    field_882 = 0;
    field_884 = 0;
    field_886 = 0;
    field_4C4 = 0;
    field_82A = 0;
    field_52A = 0;
    field_810 = 0;
    field_814 = 0;
    skills_2[0] = 0;
    skills_2[1] = 0;
    skills_2[2] = 0;
    skills_2[3] = 0;
    tengu_fan = 0;
    field_83C = 0;
    field_836 = 0;
    field_84C = 0;
    field_84E = 0;
    field_850 = 0;
    field_852 = 0;
    field_868 = 0;
    field_86A = 0;
    field_888 = 0;
    field_88A = 0;
    field_880 = 0;
    field_86C = 0;
    field_870 = 0;
    field_874 = 0;
    field_878 = 0;
    field_87C = 0;
}

void char_c::init_vars_base()
{
    //if ( input_function )                       //HACK
    //clear_input_substructure(v2->subinput);

    //((void (*)(void))  char_bullets->vtbl->func2)();
    bullets.clear(); //HACK?

    field_1AC = 0;
//    pressed_x_axis = 0;
//  pressed_y_axis = 0;
//  pressed_A = 0;
//  pressed_B = 0;
//  pressed_C = 0;
//  pressed_D = 0;
//  pressed_AB = 0;
//  pressed_BC = 0;
//  keyup_A = 0;
//  keyup_B = 0;
//  keyup_C = 0;
//  keyup_D = 0;
//  keyup_AB = 0;
//  keyup_BC = 0;
    //zero_input_charclass_ispressed_vars(v1); //HACK?
    //input_push_pressed_to_buf(v1); //HACK?

    dir = 1 - 2 * (player_index == 1); //HACK OR WILL SET?
    x = (player_index == 1) * 320 + 480;
    y = 0.0;
    h_inerc = 0.0;
    v_inerc = 0.0;
    field_744 = 0.0;
    field_748 = 0.0;
    field_74C = 0.0;
    field_1A4 = 0.0;
    field_1A8 = 0.0;
    //field_F8 = 0.0;     //HACK ?
    v_force = 0.0;
    reset_ofs();
    hit_stop = 0;
    field_4A6 = 0;
    time_stop = 0;
    field_51C = 0;
    field_51E = 0;
    field_520 = 0;
    field_522 = 0;
    field_524 = 0;
    field_526 = 0;
    weather_id = weather_get();
    field_19C = 0.0;
    field_4AA = 0;
    field_4BA = 0;
    field_4BC = 0;
    damage_limit = 0;
    field_4C2 = 0;
    field_1A2 = 0;
    field_49D = 0;
    field_4C6 = 0;
    field_4C0 = 0;
    field_4AC = 0;
    field_49A = 0;
    air_dash_cnt = 0;
    field_49C = 0;
    life_recovery = 0;
    field_4CC = 0;
    field_4CD = 0;
    field_4CE = 0;
    field_4D4 = 0;
    field_4D6 = 0;
    field_4D8 = 0;
    /*for (int8_t i=0; i<8; i++) // HACK    NOT USED?
    {
        lvl_hgt_1[i] = 0;
        lvl_hgt_2[i] = 0;
    }*/
    combo_rate = 1.0;
    field_530 = 1.0;
    current_card_energy = 0;
    field_534 = 1.0;
    spell_energy_stop = 0;
    field_538 = 1.0;
    crshd_sp_brdrs_timer = 0;
    field_544 = 1.0;
    field_740 = 0;
    field_548 = 1.0;
    combo_count = 0;
    field_54C = 1.0;
    combo_damage = 0;
    limit_multiply = 1.0;
    correction = 0;
    field_560 = 0;
    field_550 = 0.0;
    field_56C = 0;
    field_554 = 0.0;
    field_56D = 0;
    field_558 = 0.0;
    field_56E = 0;
    field_540 = 0.0;
    field_56F = 0;
    field_570 = 0;
    field_55C = 1.0;
    field_571 = 1;
    field_564 = 1.0;
    field_572 = 1;
    field_568 = 1.0;
    max_health = 10000;
    health = 10000;
    health_prev = 10000;
    max_spell_energy = 1000;
    spell_energy = 1000;
    combo_limit = 0;
    for(int8_t i=0; i<32; i++)
    {
        skills_1[i] = 0;
        skills_2[i] = -1;
    }
    field_194 = 0;
    field_190 = 0;
    set_seq(0);
    field_575 = 0;
    field_574 = 0;
    field_576 = 0;
    field_577 = 0;
    win_count = 0;
    field_578 = 0;
    pres_move = 0;
    pres_comb = 0;
    has_shadow = 1;
    field_728 = 0;
    field_710 = 0;
    field_6E8 = 0;
    field_6E4 = 0;
    field_6F4 = 0;
    field_6F5 = 0;
    field_6EC = -1;
    if (controlling_type == CONTROL_PC_STORY)
    {
        //HACK    PC STORY
        //prepare_player_cards_deck(player_cards_map_deque, 0);
        //card_slots = LOBYTE(player_cards_map_deque.cards_shuffle._Mysize);
        //cards_added = 0;
        //sub_468460(&cards_active);
        /*for ( i = 0; i < card_slots; ++i )
          char_c::add_card(v1);*/
        /*v7 = cards_active._Myoff;
        v8 = cards_active._Myoff;
        v9 = v7;
        v10 = cards_active._Mapsize;
        if ( v10 <= (unsigned int)v7 )
          v9 = v7 - v10;
        v11 = cardmap_get_cardstru_by_id(&player_cards_map_deque, cards_active._Map[v9]->id)->cost;
        meta.max_health = v11;
        meta.health = v11;*/
        //field_742 = 0;
        /*v12 = cards_active._Myoff;
        if ( cards_active._Map[v12]->id >= 200 )
        {
          field_6F0 = -1;
          set_seq(700);
        }
        else
        {
          v15 = cards_active._Myoff;
          field_6F0 = cardmap_get_cardstru_by_id(&player_cards_map_deque, cards_active._Map[v15]->id)->stage;
          set_seq(700);
        }*/
    }
    else
    {
        //prepare_player_cards_deck(v5, 1);  //HACK
        card_slots = 5;
        cards_added = 0;
        //sub_468460(&cards_active);  //HACK    NOT NEEDED?
        field_742 = 0;
        field_6EC = -1;
        field_6F0 = -1;
    }
}

void char_c::load_spells(const char *name)
{
    char buf[CHRBUF];
    for (int8_t i=0; i<10; i++)
    {
        sprintf(buf, "data/character/%s/back/spell%03d.cv2",name, i);

        gr_tex *tx = gr_load_cv2(buf, NULL);
        if (!tx)
            break;
        gr_set_repeate(tx, true);
        spell_images.push_back(tx);
    }
}

bool char_c::char_on_ground_flag()
{
    return getlvl_height() >= y && field_4C4 == 0;
}

bool char_c::char_on_ground_down()
{
    return getlvl_height() >= y && v_inerc < 0 && field_4C4 == 0;
}

void char_c::set_seq(uint32_t idx)
{
    c_meta::set_seq(idx);
    set_seq_params();
}

void char_c::draw_shadow(shd_trans *sh_trans, gr_shader *shader)
{
    sprite.setColor(sh_trans->r,sh_trans->g,sh_trans->b,sh_trans->a);

    float dx = 0.0;
    float dy = 0.0;

    char_frame *frm = get_pframe();
    if (frm)
    {
        dx = sprite.get_pframe()->x_offset;
        dy = sprite.get_pframe()->y_offset;
    }

    float cx = (x_off + dx) * dir;
    float cy = dy - y_off;

    gr_transform trans;
    trans.reset();
    trans.translate(x, -y - field_138);

    trans.translate(-dir * dx, -dy);

    trans.rotate3(angX,angY,angZ * dir, cx, cy, 0);
    trans.scale3(scaleX,scaleY,1.0,  cx, cy, 0.0);

    trans.scale3(dir,1,1);

    trans.rcombine(sh_trans->trans);

    sprite.setTransform(&trans);

    sprite.draw(PLANE_SCENE,shader);
//    float rx,ry,rz;
//    euler_mult(0,0,-angZ,trans->ax,trans->ay,trans->az,rx,ry,rz);
//
//    if (trans->sx < 0)
//        sprite.setRotate(rx,ry,-rz*dir);
//    else
//        sprite.setRotate(rx,ry,rz*dir);
//
//    sprite.setScale(trans->sx*dir,trans->sy);
//    sprite.setXY(trans->x,trans->y);
//    sprite.setOrigin(-x_off ,-y_off);
//    sprite.setColor(trans->r,trans->g,trans->b,trans->a);
//    sprite.draw(1,shader);
}

void char_c::draw(gr_shader *shader)
{
    sprite.setColor(255,255,255,255);

    float dx = 0.0;
    float dy = 0.0;

    char_frame *frm = get_pframe();
    if (frm)
    {
        dx = sprite.get_pframe()->x_offset;
        dy = sprite.get_pframe()->y_offset;
    }

    float cx = (x_off + dx) * dir;
    float cy = dy - y_off;

    gr_transform trans;
    trans.reset();
    trans.translate(x, -y);

    trans.translate(-dir * dx, -dy);

    trans.rotate3(angX,angY,angZ * dir, cx, cy, 0);
    trans.scale3(scaleX,scaleY,1.0,  cx, cy, 0.0);

    trans.scale3(dir,1,1);

    sprite.setTransform(&trans);

    sprite.draw(PLANE_SCENE,shader);
}

bool char_c::field_sq_check()
{
    uint32_t sq = get_seq();
    return (sq > 299 && field_190 != 0 && field_190 != 3) || sq < 300;
}

void char_c::input_update()
{
    input->update(get_seq() < 300 && !char_is_block_knock() && !char_is_shock());
}

void char_c::check_seq_input()
{
    pres_move = 0;
    pres_comb = 0;

    if (input->check_input_seq("NRNR", 15,dir))
        pres_move |= PMOVE_NRNR;
    if (input->check_input_seq("NLNL", 15,dir))
        pres_move |= PMOVE_NLNL;

    if (input->check_input_seq("N09", 20,dir))
        pres_move |= PMOVE_N09;
    if (input->check_input_seq("N07", 20,dir))
        pres_move |= PMOVE_N07;
    if (input->check_input_seq("N08", 20,dir))
        pres_move |= PMOVE_N08;

    if (input->check_input_seq("DD", 15,dir))
        pres_move |= PMOVE_DD;

    int8_t t = 0;

    t = input->check_input_seq("421X", 15,dir);
    if (t)
        pres_comb |= PCOMB_421A << (t - 1);

    t = input->check_input_seq("214X", 15,dir);
    if (t)
        pres_comb |= PCOMB_214A << (t - 1);

    t = input->check_input_seq("412X", 15,dir);
    if (t)
        pres_comb |= PCOMB_412A << (t - 1);

    t = input->check_input_seq("623X", 15,dir);
    if (t)
        pres_comb |= PCOMB_623A << (t - 1);

    t = input->check_input_seq("236X", 15,dir);
    if (t)
        pres_comb |= PCOMB_236A << (t - 1);

    t = input->check_input_seq("4136X", 20,dir);
    if (t)
        pres_comb |= PCOMB_4136A << (t - 1);

    t = input->check_input_seq("6314X", 20,dir);
    if (t)
        pres_comb |= PCOMB_6314A << (t - 1);

    t = input->check_input_seq("2N2X", 15,dir);
    if (t)
        pres_comb |= PCOMB_2N2A << (t - 1);

}


void char_c::func10()
{
    int32_t sq = get_seq();

    switch(sq)
    {
    case 50:
    case 51:
    case 52:
        sub10func();
        if ( h_inerc < 0.0 )
        {
            h_inerc += 3.0;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }

        if ( get_border_near() )
        {
            if ( field_4AC != 0)
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(0);

        break;
    case 53:
    case 59:
    case 65:
        sub10func();
        if ( h_inerc < 0.0 && !field_7D2 )
        {
            h_inerc += 1.5;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( h_inerc > 0.0 && field_7D2 == 1 )
        {
            h_inerc -= 0.75;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( get_border_near() && h_inerc < -8.0 )
        {
            h_inerc = -h_inerc;
            field_7D2 = 1;
            //shake_camera(2.0); //HACK
            scene_play_sfx(22);
        }
        if ( process() )
            set_seq(0);
        break;
    case 54:
    case 60:
        sub10func();
        if ( process() )
            set_seq(0);
        break;
    case 55:
    case 61:
        sub10func();
        if (h_inerc > 0)
        {
            h_inerc -= 1.5;
            if (h_inerc > 0)
                h_inerc = 0;
        }

        if ( get_border_near() )
        {
            if ( field_4AC )
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(0);
        break;
    case 56:
    case 57:
    case 58:
        sub10func();
        if (h_inerc < 0.0 )
        {
            h_inerc += 1.5;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }

        if ( get_border_near() )
        {
            if ( field_4AC != 0)
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(0);

        break;
    case 62:
    case 63:
    case 64:
        sub10func();
        if ( h_inerc < 0.0 )
        {
            h_inerc += 1.5;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( get_border_near() )
        {
            if ( field_4AC )
                field_74C = h_inerc * 0.75;
        }

        if ( process() )
            set_seq(2);
        break;
    case 66:
        sub10func();
        if ( process() )
            set_seq(2);
        break;
    case 67:
        sub10func();
        if ( h_inerc > 0.0 )
        {
            h_inerc -= 1.5;
            if ( h_inerc > 0 )
                h_inerc = 0;
        }
        if ( get_border_near() )
        {
            if ( field_4AC )
                field_74C = h_inerc * 0.75;
        }

        if ( process() )
            set_seq(2);
        break;
    case 70:
        if ( field_7D0 > 0 )
        {
            if ( h_inerc > 2.0 )
                h_inerc -= 0.5;
            if ( h_inerc < 2.0 )
                h_inerc = 2.0;
        }
        else if ( field_7D0 < 0 )
        {
            if ( h_inerc < -2.0 )
                h_inerc += 0.5;
            if (h_inerc > -2.0)
                h_inerc = -2.0;
        }

        v_inerc -= v_force;
        if ( get_border_near()  && h_inerc < 0.0 )
        {
            h_inerc++;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
            if ( field_4AC )
                field_74C = h_inerc;
        }
        if ( !char_on_ground_down() )
        {
            if ( process() )
                set_seq(9);
        }
        else
        {
            reset_forces();
            y = 0.0;
            set_seq(10);
        }
        break;
    case 71:
        if ( get_subseq() == 1 && v_inerc < 2.0 )
            next_subseq();
        else
        {
            v_inerc -= v_force;
            if ( v_inerc > 0.0 )
                v_inerc -= v_force;

            if ( char_on_ground_down() )
            {
                if ( field_80C == 0 )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(97);

                    //shake_camera(2.0); //HACK
                }
                else if ( weather_id != WEATHER_MONSOON )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(89);

                    //shake_camera(5.0); //HACK
                }
                else
                {
                    weather_time_mul(0.75);

                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(89);

                    //shake_camera(5.0); //HACK
                }

                scene_play_sfx(22);
            }
            else
            {
                if ( field_7D0 > 0 )
                    field_7D0--;
                if ( get_border_near() )
                {
                    if ( h_inerc < 0.0 )
                    {
                        h_inerc++;
                        if ( h_inerc > 0.0 )
                            h_inerc = 0.0;
                        if ( field_4AC != 0)
                            field_74C = -2.0 * field_7D0;
                    }
                }
                process();
            }
        }
        break;
    case 72:
        if ( get_subseq() == 1 && v_inerc < 2.0 )
        {
            next_subseq();
        }
        else
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                if ( !field_80C )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(97);

                    //shake_camera(2.0); //HACK
                }
                else if ( weather_id != WEATHER_MONSOON )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(89);

                    //shake_camera(5.0); //HACK
                }
                else
                {
                    weather_time_mul(0.75);

                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(89);

                    //shake_camera(5.0); //HACK
                }

                scene_play_sfx(22);
            }
            else
            {
                if ( get_border_near() && h_inerc < 0.0 )
                {
                    h_inerc++;

                    if ( h_inerc > 0.0 )
                        h_inerc = 0.0;
                    if ( field_4AC )
                        field_74C = h_inerc;
                }
                process();
            }
        }
        break;
    case 73:
        if ( char_on_ground_down() )
        {
            if ( field_80C == 0)
            {
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();

                y = 0;
                set_seq(97);
            }
            else
            {
                if (weather_id == WEATHER_MONSOON)
                    weather_time_mul(0.75);
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();

                y = getlvl_height();
                set_seq(89);
            }
            //shake_camera(5.0); // HACK
            scene_play_sfx(22);
        }
        else
        {
            process();

            if ( get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1 && v_inerc != 0)
            {
                if ( h_inerc == 0 )
                    set_subseq(3);
                else
                    set_subseq(2);
            }
            else
            {
                field_7D0--;
                if ( field_7D0 < 0 )
                    field_7D0 = 0;

                if ( get_border_near() )
                {
                    if ( h_inerc < 0.0 )
                    {
                        h_inerc += 2.5;
                        if ( h_inerc > 0.0 )
                            h_inerc = 0.0;

                        if ( field_4AC )
                            field_74C = field_7D0 * -2.0;
                    }
                }
            }
        }
        break;
    case 74:
        if ( get_subseq() == 1 && v_inerc < 2.0 )
        {
            next_subseq();
        }
        else
        {
            if ( get_border_near() && (h_inerc <= -25.0 || field_80C != 0) )
            {
                if ( weather_id != WEATHER_MONSOON ) // HACK?
                    weather_time_mul(0.75);

                set_seq(76);
            }
            else if ( get_border_near() && h_inerc <= -15.0 )
            {
                set_seq(78);
            }
            else
            {
                v_inerc -= v_force;

                if ( !char_on_ground_down() )
                {
                    process();
                }
                else if ( field_80C == 0 )
                {
                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(97);

                    //shake_camera(2.0); //HACK?
                    scene_play_sfx(22);
                }
                else
                {
                    if ( weather_id != WEATHER_MONSOON )
                        weather_time_mul(0.75);

                    field_7D0 = 100 * h_inerc;
                    field_7D2 = 100 * v_inerc;

                    reset_forces();

                    y = getlvl_height();
                    set_seq(89);
                    //shake_camera(5.0);    //HACK
                    scene_play_sfx(22);
                }
            }
        }
        break;
    case 75:
        if (char_on_ground_down() )
        {
            if ( field_80C )
            {
                if ( weather_id == WEATHER_MONSOON )
                    weather_time_mul(0.75);

                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();
                y = getlvl_height();
                set_seq(89);
            }
            else
            {
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();
                y = getlvl_height();
                set_seq(97);
            }

            //shake_camera(5.0); //HACK
            scene_play_sfx(22);
        }
        else
        {
            if ( get_border_near() && (h_inerc <= -25.0 || field_80C) )
            {
                if ( weather_id == WEATHER_MONSOON )
                    weather_time_mul(0.75);
                set_seq(76);
            }
            else if ( get_border_near() && h_inerc <= -15.0 )
            {
                set_seq(78);
            }
            else
            {
                process();

                if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 &&
                        v_inerc != 0)
                {
                    if ( h_inerc == 0)
                        set_subseq(3);
                    else
                        set_subseq(2);
                }
            }
        }
        break;

    case 76:
        if ( get_subseq() > 0 )
            angZ -= 30.0;

        v_inerc -= v_force;

        if ( char_on_ground_down() )
        {
            scene_play_sfx(22);

            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height();

            set_seq(97);
            angZ = 0;

            //shake_camera(2.0);
            reset_ofs();
        }
        else
        {
            process();

            if ( get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1)
            {
                h_inerc = -3.0;
                v_inerc = 10.0;
                v_force = 0.5;
                dir = -dir;
            }
        }
        break;
    case 77:
        angZ -= 30;
        v_inerc -= v_force;

        if ( !char_on_ground_down() )
            process();
        else
        {
            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height();

            if ( field_80C != 0)
                set_seq(89);
            else
                set_seq(97);

            angZ = 0;

            //shake_camera(2.0); //HACK
            reset_ofs();
            scene_play_sfx(22);
        }
        break;
    case 78:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            scene_play_sfx(22);

            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;

            reset_forces();

            y = getlvl_height();
            set_seq(97);
            //shake_camera(2.0); //HACK
        }
        else
        {
            process();
            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1 )
            {
                h_inerc = -5.0;
                v_inerc = 3.0;
                v_force = 0.5;
                dir = -dir;
            }
        }
        break;
    case 88:
        if ( char_on_ground_down() )
        {
            field_7D0 = 100.0 * h_inerc;
            field_7D2 = 100.0 * v_inerc;

            reset_forces();

            y = getlvl_height();

            set_seq(89);
            //shake_camera(5.0); //HACK
            scene_play_sfx(22);
        }
        else
        {
            process();

            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1 &&
                    v_inerc != 0)
            {
                if (h_inerc == 0)
                    set_subseq(3);
                else
                    set_subseq(2);
            }
            else
            {
                field_7D0--;
                if (field_7D0 < 0)
                    field_7D0 = 0;

                if ( get_border_near() )
                {
                    if ( h_inerc < 0.0 )
                    {
                        h_inerc += 2.5;
                        if ( h_inerc > 0.0 )
                            h_inerc = 0;
                        if ( field_4AC != 0)
                            field_74C = -2.0 * field_7D0;
                    }
                }
            }
        }
        break;
    case 89:
        if ( get_subseq() > 0)
        {
            angZ -= 40;
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                field_7D0 = 100.0 * h_inerc;
                field_7D2 = 100.0 * v_inerc;
                reset_forces();

                y = getlvl_height();
                set_seq(97);
                angZ = 0;
                //shake_camera(2.0); //HACK
                reset_ofs();
                scene_play_sfx(22);
                break;
            }
        }
        process();
        if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1)
        {
            h_inerc = field_7D0 * 0.0025;
            v_inerc = -field_7D2 * 0.0025;
            v_force = 0.25;
            x_off = x_delta;
            y_off = y_delta;
        }
        break;
    case 96:
    case 97:
        if ( get_subseq() == 3 )
            sub10func();

        if ( dX(dir) > 0 )
        {
            if ( keyDown(INP_A) || keyDown(INP_B) || keyDown(INP_C) || keyDown(INP_D)  )
                field_7D0 = 1;
        }
        else if ( dX(dir) < 0 )
        {
            if ( keyDown(INP_A) || keyDown(INP_B) || keyDown(INP_C) || keyDown(INP_D)  )
                field_7D0 = 2;
        }

        v_inerc -= v_force;

        if ( (get_subseq() == 1 || get_subseq() == 2) && char_on_ground_down())
        {
            y = getlvl_height();
            reset_forces();
            set_subseq(3);
        }
        else
        {
            if ( process() )
            {
                set_seq(98);
                if ( field_574 != 0 || field_880 != 0 )
                    set_seq(99);
            }

            if (get_elaps_frames() == 0 && get_frame_time() ==0 && get_frame() == 0 && get_subseq() == 1)
            {
                h_inerc = field_7D0 * 0.005;
                v_inerc = -field_7D2 * 0.005;
                v_force = 2.0;
            }
        }
        break;

    case 98:
        sub10func();
        if ( weather_id == WEATHER_DIAMOND_DUST )
        {
            if ( weather_time_get() > 10 ) //GLOBAL
                weather_time_sub(10);

            if ( health > 0 )
            {
                if ( health <= 50 )
                    health = 1;
                else
                    health -= 50;
            }
        }
        else
        {
            if ( dX(dir) > 0 )
            {
                if ( keyDown(INP_A) || keyDown(INP_B) || keyDown(INP_C) || keyDown(INP_D)  )
                    field_7D0 = 1;
            }
            else if ( dX(dir) < 0  )
            {
                if ( keyDown(INP_A) || keyDown(INP_B) || keyDown(INP_C) || keyDown(INP_D)  )
                    field_7D0 = 2;
            }
        }
        if ( process() )
        {
            set_seq(199);
            if (field_7D0 == 1)
                set_seq(197);
            else if (field_7D0 == 2)
                set_seq(198);
        }
        break;

    case 99:
        sub10func();
        if ( get_subseq() == 3 )
        {
            if(c_A <= 3)
                c_A = 0;
            else
                c_A -= 3;

            has_shadow = 0;
        }
        process();

        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2)
        {
            if (field_576 == 0 && field_880 == 0)
            {
                if ( cards_added > 0 && controlling_type == CONTROL_PC_STORY && cards_active[0]->id >= 248 )
                {
                    health_to_max();
                    field_868 = 0;
                }
                set_seq(199);
                field_574 = 0;
                field_577 = 1;
            }
            field_880 = 0;
        }
        break;
    case 112:
    case 113:
        process();
        break;
    case 115:
        angZ -= 30;
        process();
        break;
    case 140:
    case 144:
    case 150:
    case 151:
    case 152:
    case 153:
    case 159:
    case 160:
    case 161:
    case 162:
        sub10func();
        if ( h_inerc < 0.0 )
        {
            h_inerc += 0.6;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( get_border_near() )
        {
            if ( field_4AC )
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(0);
        break;
    case 143:
        sub10func();
        if ( h_inerc < 0.0 )
        {
            h_inerc += 0.6;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( get_subseq() != 1 || get_elaps_frames() < 40 )
        {
            if ( get_border_near() && field_4AC )
                field_74C = h_inerc * 0.75;

            if ( process() )
                set_seq(0);
        }
        else
            next_subseq();
        break;
    case 145:
        if ( get_subseq() != 1 || v_inerc >= 2.0 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                field_7D0 = 100 * h_inerc;
                field_7D2 = 100 * v_inerc;
                reset_forces();
                y = 0;
                set_seq(97);
                //shake_camera(2.0); //HACK
                scene_play_sfx(22u);
            }
            else
            {
                if ( process() )
                    set_subseq(5);
            }
        }
        else
            next_subseq();
        break;
    case 149:
        angZ -= 30;

        if (v_inerc <= 0)
            v_inerc -= v_force * 0.25;
        else
            v_inerc -= v_force;

        if (char_on_ground_down())
        {
            scene_play_sfx(22);
            field_7D0 = 100 * h_inerc;
            field_7D2 = 100 * v_inerc;
            reset_forces();
            y = 0.0;

            set_seq(97);

            angZ = 0;
            //shake_camera(2.0); //HACK
            reset_ofs();
        }
        else
            process();
        break;
    case 154:
    case 155:
    case 156:
    case 157:
    case 163:
    case 164:
    case 165:
    case 166:
        sub10func();
        if ( h_inerc < 0.0 )
        {
            h_inerc += 0.6;
            if ( h_inerc > 0.0 )
                h_inerc = 0.0;
        }
        if ( get_border_near() )
        {
            if ( field_4AC )
                field_74C = h_inerc * 0.75;
        }
        if ( process() )
            set_seq(2);
        break;
    case 158:
    case 167:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = 0.0;
            reset_forces();
        }
        else
        {
            if ( field_7D0 > 0 )
                field_7D0--;
            if ( get_border_near() )
            {
                if ( h_inerc < 0.0 )
                {
                    h_inerc++;
                    if ( h_inerc > 0.0 )
                        h_inerc = 0.0;
                    if ( field_4AC )
                        field_74C = field_7D0 * -2.0;
                }
            }

            if ( process() )
                set_seq(9);
        }
        break;
    case 180:
    case 181:
        v_inerc -= v_force;
        if ( char_on_ground_down() )
        {
            set_seq(10);
            y = 0.0;
            reset_forces();
        }
        else
        {
            process();
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 && field_4C4 )
                set_seq(9);
        }
        break;
    case 690:
        sub10func();
        if ( process() )
            set_seq(0);

    case 691:
        sub10func();
        if ( get_subseq() == 1 && field_7D0 == 14 )
        {
            field_51C = 1;
            field_520 = 1;
            if ( get_elaps_frames() % 7  == 0)
                scene_add_effect(this, 135, x, y, dir, -1);

            if ( get_elaps_frames() % 5 == 0 )
                scene_add_effect(this, 136, scene_rand_rng(200) + x - 100, y, dir, 1);
        }
        if ( process() )
        {
            set_seq(0);
            if ( field_7D0 == 2 )
            {
                float params[3];
                params[0] = 0.0;
                params[1] = 0.0;
                params[2] = 1.0;
                field_84C = 50;
                field_4A6 = 2;
                addbullet(this,NULL, 1002, 640, 480, 1, -2, params, 3);
                scene_play_sfx(73);
            }
        }
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
        {
            switch ( field_7D0 )
            {
            case 6:
            {
                float params[3];
                params[0] = 0.0;
                params[1] = 0.0;
                params[2] = 1.0;
                addbullet(this,NULL, 1006, x,y,dir, 1, params, 3);
            }
            break;
            case 7:
            {
                float params[3];
                for (int8_t i=0; i< 3; i++)
                {
                    params[0] = -105 - 30*i;
                    params[1] = i * 3 + 10;
                    params[2] = 1.0;
                    addbullet(this,NULL,1007, x, y+125, dir, 1, params, 3);
                }
            }
            break;
            case 14:
                scene_add_effect(this, 70, x , y, dir, 1);
                if ( weather_get() == WEATHER_CLEAR )
                {
                    weather_time_set(999);
                    if ( weather_index_for_name_get() != WEATHER_CLEAR )
                        weather_change(weather_index_for_name_get(), 1);
                }
                else
                    field_52A = 1;
                break;
            case 16:
            {
                float params[3];
                params[0] = 0.0;
                params[1] = 0.0;
                params[2] = 1.0;
                addbullet(this,NULL, 1016, dir*200 + x, y, dir, 1, params, 3);
            }
            break;
            case 20:
            {
                float params[3];
                params[0] = 0.0;
                params[1] = 0.0;
                params[2] = 1.0;
                addbullet(this,NULL, 1020, 200*dir + x, y+ 1024, dir, -1, params, 3);
            }
            break;
            default:
                break;
            }
        }
        break;
    case 692:
        sub10func();
        if ( get_subseq() == 1 )
        {
            current_card_energy += 15;

            if ( get_elaps_frames() % 15 == 0 )
                scene_add_effect(this, 153, x, y, dir, 1);

            if ( get_elaps_frames() % 10 == 0 )
                scene_add_effect(this, 152, x, y, dir, -1);
        }
        if ( get_elaps_frames() < 33 || get_subseq() != 1 )
        {
            if ( process() )
                set_seq(0);
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                current_card_energy += 500;
                scene_play_sfx(56);
            }
        }
        else
            next_subseq();
        break;
    case 693:
        sub10func();
        if ( get_elaps_frames() < 40 || get_subseq() != 1 )
        {
            if ( process() )
                set_seq(0);
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                life_recovery = 250;
                scene_play_sfx(56);
            }
        }
        else
            next_subseq();
        break;
    case 694:
        sub10func();
        if ( get_subseq() == 1 )
        {
            if ( max_spell_energy < 1000 )
                crshd_sp_brdrs_timer = 4799;
        }
        if ( get_elaps_frames() < 20  || get_subseq() != 1)
        {

            if ( process() )
                set_seq(0);
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                scene_play_sfx(56);
                field_848 = 360.0;
            }
        }
        else
            next_subseq();
        break;
    case 697:
        sub10func();
        if ( get_subseq() != 1 || get_elaps_frames() < 25 )
        {
            if ( get_subseq() >= 2 )
            {
                h_inerc -= 0.5;
                if ( h_inerc < 0.0 )
                    h_inerc = 0.0;
            }
            if ( process() )
                set_seq(0);

            if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
            {
                if (get_subseq() == 1)
                {
                    char_frame * frm = get_pframe();
                    scene_play_sfx(72);
                    float ty = y - frm->extra1[5];
                    float tx = x + frm->extra1[4] * dir;
                    scene_add_effect(this, 138, tx, ty, dir, 1);
                }
                else if (get_subseq() == 3)
                    scene_play_sfx(29);
            }
        }
        else
        {
            h_inerc = 15.0;
            next_subseq();
        }
        break;
    case 698:
        sub10func();

        if ( get_subseq() >= 1 )
        {
            h_inerc -= 0.5;
            if ( h_inerc < 0.0 )
                h_inerc = 0.0;
        }
        if ( get_subseq() == 2 && !field_7D0 && (field_190 == 1 || field_190 == 7) )
        {
            if ( enemy->controlling_type != 2)
            {
                enemy->sub_4689D0(500);
                field_7D0++;
            }
        }
        if ( process() )
            set_seq(0);
        if (get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0)
        {
            if (get_subseq() == 1)
            {
                h_inerc = 10;
            }
            else if (get_subseq() == 3)
                scene_play_sfx(29);
        }
        break;
    case 700:
        sub10func();
        if ( h_inerc == 0.0 )
            field_49A = 0;
        if ( field_49A )
        {
            if ( h_inerc > 0.0 )
            {
                h_inerc -= 0.5;
                if ( h_inerc < 0.0 )
                {
                    reset_forces();
                    field_49A = 0;
                }
            }
            if (h_inerc < 0)
            {
                h_inerc += 0.5;
                if (h_inerc > 0)
                {
                    reset_forces();
                    field_49A = 0;
                }
            }
        }
        else
            reset_forces();

        process();
        break;
    case 701:
    case 702:
    case 703:
        if ( get_subseq() != 0 )
        {
            v_inerc -= v_force;
            if ( char_on_ground_down() )
            {
                set_seq(700);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }
        else
            sub10func();

        if ( get_subseq() == 1 )
        {
            if ( v_inerc < 4.0 )
                next_subseq();
        }
        process();

        if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
        {
            h_inerc = field_85C;
            v_inerc = field_860;
            v_force = field_864;
        }
        break;
    case 704:
        v_inerc -= v_force;

        if ( char_on_ground_down() )
        {
            set_seq(709);
            reset_forces();
            y = getlvl_height();
        }
        else
            process();
        break;
    case 705:
        sub10func();
        h_inerc = field_854;
        process();
        break;
    case 706:
        sub10func();
        h_inerc = field_858;
        process();
        break;
    case 709:
        sub10func();
        if ( process() )
            set_seq(700);
        break;
    case 789:
        reset_forces();
        process();
        if ( get_frame() == 0 && get_frame_time() == 0 && field_82A)
        {
            set_seq(0);
            field_82A = 0;
        }
        break;
    case 790:
        if ( get_subseq() == 1 )
        {
            if ( y > 1580.0 )
            {
                v_inerc = 0;
                y = 1580.0;
            }
            if ( field_7D0 == 1 )
            {
                dir = 1;
                next_subseq();
            }
        }
        if (get_subseq() == 2)
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                scene_play_sfx(30);
                set_subseq(3);
                y = getlvl_height();
                reset_forces();
            }
        }
        else
        {
            if ( process() )
            {
                set_seq(0);
            }
            else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
            {
                v_inerc = 25.0;
                field_7D8 = 0;
                scene_add_effect(this, 63, x, y, dir, 1);
            }
        }
        break;
    case 796:
        if (get_subseq() > 0 && get_subseq() < 4)
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                scene_play_sfx(30);
                x = 800;
                dir = -1;
                set_subseq(4);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }

        if ( process() )
            set_seq(700);
        else
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                field_49A = 0;
                field_7DC = 800.0 - x;
                h_inerc = (800.0 - x) / 90.0 * dir;
                v_inerc = 11.5;
                v_force = 0.25555557;
            }
        }
        break;
    case 799:
        if (get_subseq() > 0 && get_subseq() < 4)
        {
            v_inerc -= v_force;
            if (char_on_ground_down())
            {
                scene_play_sfx(30);
                x = 480;
                dir = -1;
                set_subseq(4);
                y = getlvl_height();
                reset_forces();
                break;
            }
        }

        if ( process() )
            set_seq(789);
        else
        {
            if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
            {
                field_49A = 0;
                field_7DC = 480.0 - x;
                h_inerc = (480.0 - x) / 90.0 * dir;
                v_inerc = 11.5;
                v_force = 0.25555557;
            }
        }
        break;
    default:
        process(true);
    }
}


void char_c::func16()
{
    if (field_524 > 0  &&  time_stop == 0 &&
            hit_stop == 0  &&  field_524 % 15 == 0 )
    {
        float tmp[3];
        tmp[0] = 0.0;
        tmp[1] = 0.0;
        tmp[2] = 0.0;
        addbullet(this,NULL,1260, x + 100.0 - scene_rand_rngf(200), scene_rand_rngf(150) + y + 100.0, 1, 1, tmp,3);
    }

    if ( field_526 <= 0 || time_stop != 0 )
    {
        if ( field_814 <= 0 )
            field_80D = 0;
    }
    else
        field_80D = 1;


    field_80E = get_seq() >= 600 && get_seq() <= 689;

    if ( get_seq() >= 600 && get_seq() < 690 )
        field_7F8 = 120;

    if ( health <= 0 )
    {
        field_524 = 0;
        field_526 = 0;
        life_recovery = 0;
    }
    if ( enemy->health <= 0 )
    {
        field_524 = 0;
        field_526 = 0;
    }
    /*if ( health <= 0 )
    {
      if ( LOBYTE(v2->controlling_type) == CHAR_CTRL_PC_STORY )
      {
        if ( get_seq() >= 50 )
        {
          if ( get_seq() <= 149 )
          {
            sub_4685C0(this, 0); //HACK
            sub_46AB50(this, v12, 0, 0);
          }
        }
      }
    }*/
    if ( hit_stop  == 0  &&
            field_19C  > 0  &&
            field_4AC != 0 )
    {
        field_74C -= field_19C;
        field_19C -= 5.0;
        if ( field_19C < 0 )
            field_19C = 0;
    }

    if ( life_recovery > 0 )
    {
        if ( char_is_shock() )
            life_recovery = 0;

        health += 4;
        if ( health >= max_health )
            health = max_health;

        if ( life_recovery % 15 == 0 )
            scene_add_effect(this, 151, x, y, dir, 1);

        if ( life_recovery % 10 == 0 )
            if ( char_on_ground() )
                scene_add_effect(this, 150, x, y, dir, -1);

        life_recovery--;
    }
    if ( field_52A == 1 )
    {
        if ( weather_get() != WEATHER_CLEAR )
        {
            if ( weather_time_get() >= 3 )
                weather_time_sub(3);
            else
            {
                weather_time_set(0);
                field_52A = 0;
            }
        }
        else
            field_52A = 0;
    }

    if ( char_on_ground() )
        if ( (get_pframe()->fflags & FF_AIRBORNE) == 0 )
            air_dash_cnt = 0;


    if ( controlling_type == 0 && enemy->controlling_type == 2 )
    {
        if ( get_seq() >= 197 && get_seq() <= 199 )
        {
            field_4C2 = 60;
            damage_limit = 100;
        }

        if (get_subseq() == 0)
            if ((get_seq() == 70 && get_elaps_frames() >= 18) ||
                    (get_seq() >= 180 && get_seq() <= 181))
            {
                field_4C2 = 60;
                damage_limit = 100;
            }

        if ( field_4C2 > 0 )
        {
            field_4C2--;
            field_51C = 2;
            field_520 = 2;
        }
        if ( field_4C4 != 0 )
        {
            if ( get_seq() == 9 )
                flip_with_force();

            field_572 = 0;
            air_dash_cnt = 0;

            if ( char_is_shock() )
            {
                if ( y < -600 )
                {
                    if ( health > 0 )
                    {
                        set_seq(9);
                        angZ = 0.0;
                        v_inerc = 0.0;
                        h_inerc = 0.0;
                        field_4C2 = 60;
                        damage_limit = 100;
                        return;
                    }

                    if ( y < -600.0 )
                        y = -600.0;
                    if ( get_elaps_frames() >= 300 )
                    {
                        set_seq(9);
                        angZ = 0.0;
                        v_inerc = 0.0;
                        h_inerc = 0.0;
                        field_4C2 = 60;
                        damage_limit = 100;
                        field_574 = 0;
                        field_577 = 1;
                        return;
                    }
                }
                else if ( health <= 0 )
                {
                    if ( y < -600.0 )
                        y = -600.0;
                    if ( get_elaps_frames() >= 300 )
                    {
                        set_seq(9);
                        angZ = 0.0;
                        v_inerc = 0.0;
                        h_inerc = 0.0;
                        field_4C2 = 60;
                        damage_limit = 100;
                        field_574 = 0;
                        field_577 = 1;
                        return;
                    }
                }
            }
            else
            {
                v_inerc *= 0.98;
                v_force *= 0.9;
                if ( hit_stop == 0 || enemy->time_stop == 0 )
                {
                    if (y < -200.0)
                    {
                        v_force = 0;
                        if (v_inerc < 0)
                            v_inerc *= 0.9;
                    }

                    float tmp = (240.0 - y) * 0.025;

                    if ( tmp < - 12.0 )
                        y -= 12.0;
                    else if (tmp > 12.0)
                        y += 12.0;
                    else
                        y += tmp;

                    if ( get_seq() <= 9 || (get_seq() >= 20 && get_seq() <= 299) )
                    {

                        if (dX(dir) == 0)
                        {
                            if ( 0 < h_inerc )
                            {
                                h_inerc -= 0.5;
                                if ( h_inerc < 0 )
                                    h_inerc = 0;
                            }
                            if ( 0 > h_inerc )
                            {
                                h_inerc += 0.5;
                                if ( h_inerc > 0 )
                                    h_inerc = 0;
                            }
                        }
                        else if (dX(dir) < 0)
                        {
                            if ( h_inerc > -8.0 )
                                h_inerc -= 0.5;
                        }
                        else if (dX(dir) > 0)
                        {
                            if ( h_inerc < 8.0 )
                                h_inerc += 0.5;
                        }

                        if (dY() == 0)
                        {
                            if (  v_inerc > 0)
                            {
                                v_inerc -= 0.5;
                                if ( v_inerc < 0 )
                                    v_inerc = 0;
                            }
                            if ( v_inerc < 0 )
                            {
                                v_inerc += 0.5;
                                if ( v_inerc > 0 )
                                    v_inerc = 0;
                            }
                        }
                        else if (dY() < 0)
                        {
                            if ( v_inerc > -12 )
                                v_inerc -= 0.5;
                        }
                        else if (dY() > 0)
                        {
                            if ( v_inerc < 12 )
                                v_inerc +=  0.5;
                        }
                    }
                }
            }
        }
    }

    if ( damage_limit >= 100 && damage_limited == 0 )
    {
        scene_add_effect(this,112, getX(), getY() + 100, dir, -1);
        scene_add_effect(this,137, getX(), getY() + 100, dir, -1);
        damage_limited = 1;
    }

    if ( !char_is_shock() && field_4C0 <= 0 && field_4C2 == 0)
        damage_limited = 0;

    if ( field_80D )
    {
        if ( field_814 <= 0 )
            field_80D = 0;
        else
            field_814--;

        if ( field_810 > 0 )
            field_810--;
        else
        {
            field_810 = scene_rand_rng(60) + 60;

            float yy = 25.0-scene_rand_rngf(50);

            float tmp[3];
            tmp[0] = scene_rand_rngf(360);
            tmp[1] = scene_rand_rngf(60) + 90.0;
            tmp[2] = 0.0;

            if (yy >= 0)
                addbullet(this,NULL, 980, scene_rand_rngf(100)+x-50.0, yy+y, dir, -1, tmp, 3);
            else
                addbullet(this,NULL, 980, scene_rand_rngf(100)+x-50.0, yy+y, dir, 1, tmp, 3);
        }
    }

    field_18C = -1;
    if ( weather_id != WEATHER_BLUE_SKY || field_526 > 0 )
    {
        field_800 = 1;
        field_801 = 1;
        field_802 = 1;
        field_803 = 1;
        field_804 = 1;
        field_4C8 = 0;
    }
    if ( weather_id != WEATHER_MOUNTAIN_VAPOR )
        field_4CC = 0;

    if ( weather_id != WEATHER_RIVER_MIST )
    {
        field_808 = 0;
        field_4D4 = 480;
    }
    if ( weather_id != WEATHER_CALM )
    {
        field_4CD = 0;
        field_4CE = 0;
    }
    if ( weather_id != WEATHER_MONSOON )
    {
        field_4D8 = 0;

        /*  // HACK      NOT USED?
        int8_t j = 0;
        for (uint32_t i=0; i< 1280; i+=160)
        {
            lvl_hgt_1[j] = 0;
            lvl_hgt_2[j] = 0;

            setlvl_height_rng(i, i+159.0, 0);
        }*/
    }

    field_54C = 1.0;
    field_530 = 1.0;
    field_534 = 1.0;
    field_56D = 0;
    field_198 = 1.0;
    field_56E = 0;
    field_548 = 1.0;
    field_56F = 0;
    field_544 = 1.0;
    field_570 = 0;
    speed_mult = 1.0;
    field_4AA = 0;
    field_538 = 1.0;
    field_56C = 0;
    limit_multiply = 1.0;
    field_80C = 0;
    field_550 = 0;
    field_554 = 0;
    field_558 = 0;
    field_540 = 0;
    if ( !keyDown(INP_BC) || keyDown(INP_BC) >= 3)
        field_836 = 0;

    /*if ( controlling_type == 2 ) // HACK
    {
        if ( get_game_difficulty() <= 3 )
        {
            switch ( get_game_difficulty() )
            {
            case 0:
                field_530 = 0.95;
                break;
            case 1:
                field_530 = 1.0;
                break;
            case 2:
                field_530 = 1.2;
                break;
            case 3:
                field_530 = 1.5;
                break;
            }
        }
    }*/

    if ( field_7F8 != 0 )
    {
        field_54C = 0;
        field_7F8--;
    }
    if ( field_526 == 0)
    {
        switch ( weather_id )
        {
        case WEATHER_DRIZZLE:
            field_544 = 1.25;
            break;

        case WEATHER_CLOUDY:
            field_54C += field_54C;
            break;

        case WEATHER_BLUE_SKY:
            if ( get_seq() >= 500 && get_seq() < 600 )
            {
                field_800 = 0;
                field_801 = 0;
                field_802 = 0;
                field_803 = 0;
                field_804 = 0;
                field_4C8 = 0;
            }
            break;

        case WEATHER_HAIL:
            field_548 = 1.25;
            break;

        case WEATHER_SPRING_HAZE:
            field_56C = 1;
            break;

        case WEATHER_HEAVY_FOG:
            field_550 = 0.5;
            break;

        case WEATHER_SNOW:
            field_554 = 0.5;
            break;

        case WEATHER_SUNSHOWER:
            field_56D = 1;
            break;

        case WEATHER_SPRINKLE:
            field_56E = 1;
            break;

        case WEATHER_MOUNTAIN_VAPOR:
            field_570 = 1;
            if ( field_4CC == 0 )
            {
                field_4CC = 1;
                mountain_vapor_shuffle();
            }
            break;

        case WEATHER_RIVER_MIST:
            if ( player_index == 1 )
                field_4D4 = enemy->field_4D4;
            else
                field_4D4 = (sin_deg(field_808) * 480.0 + 480.0);

            if ( get_seq() < 100 || (get_seq() > 111 && get_seq() < 500 ))
            {

                field_808++;

                float tmp = (fabs(enemy->x - x) - field_4D4) * 0.01;

                if ( tmp < -3.0 )
                    tmp = -3.0;
                else if (tmp > 3.0)
                    tmp = 3.0;

                if ((x < enemy->x && dir == -1) || (x > enemy->x && dir == 1))
                    enemy->field_74C -= tmp;
                else
                    enemy->field_74C = tmp;
            }
            break;

        case WEATHER_TYPHOON:
            field_538 = 0;
            field_4AA = 1;
            break;

        case WEATHER_CALM:
            if ( char_is_shock() )
                field_4CD = 0;
            else if ( field_4CD == 0  && enemy->char_is_shock() )
            {
                field_4CE += 3;
                field_4CD = 1;
                if ( field_4CE >= 15 )
                    field_4CE = 15;

                enemy->field_4CE = field_4CE;

                weather_time_mul(0.9);

                float tmp[3];
                tmp[0] = 0.0;
                tmp[1] = 0.0;
                tmp[2] = 0.0;

                addbullet(this, NULL, 1110, x, 0.0, dir, -1, tmp, 3);
            }

            if ( field_4CD != 0  &&
                    (time_count_get() % 10 == 0) && health > 0 )
            {
                health += field_4CE + 5;
                if (health > 10000)
                    health = 10000;
            }
            break;

        case WEATHER_DUST_STORM:
            field_56F = 1;
            break;

        case WEATHER_SCORCHING_SUN:
        {
            float tmp = y - 100.0;
            if ( tmp >= 0.0 )
            {
                if ( tmp > 600.0 )
                    tmp = 600.0;

                float tmp2 = (10.0 * tmp / 600.0);

                current_card_energy += (tmp * 5.0 / 600.0);

                if ( char_is_shock() )
                    tmp2 *= 0.25;

                if ( health > 0 )
                {
                    if ( health <= tmp2 )
                        health = 1;
                    else
                        health -= tmp2;
                }
                field_530 = tmp * 0.35 / 600.0 + 1.0;
            }
        }
        break;

        case WEATHER_MONSOON:
            field_80C = 1;
            break;

        default:
            break;
        }
    }
    if ( field_84C > 0 )
    {
        field_84C --;
        time_stop = 2;

        if ( enemy->shader_type != 1 )
            enemy->shader_type = 1;
        if ( field_84C <= 0 )
        {
            field_84C = 0;
            enemy->shader_type = 0;
        }
    }
    if ( field_848 > 0 )
    {
        if ( (int32_t)field_848 % 15 == 0 )
            scene_add_effect(this, 155, x, y, dir, 1);

        if ( (int32_t)field_848 % 10 == 0 )
            scene_add_effect(this, 154, x, getlvl_height(), dir, -1);

        spell_energy += 10;
        field_848--;

        if ( spell_energy > max_spell_energy )
            spell_energy = max_spell_energy;
    }

    if ( tengu_fan == 1 )
        speed_mult = 1.0;

    if ( tengu_fan == 2 )
        speed_mult = 1.0;

    if ( tengu_fan == 3 )
        speed_mult = 1.0;

    if ( tengu_fan >= 4 )
        speed_mult = 1.0;

    if ( field_526 == 0 )
        if ( weather_id == WEATHER_TEMPEST )
            speed_mult = 1.4;


    field_530 *= (field_844 * 0.1   + 1.0);
    field_534 *= (field_844 * 0.075 + 1.0);

    if ( field_840 == 1.0 )
        field_534 *= 0.97;

    if ( field_840 == 2.0 )
        field_534 *= 0.93;

    if ( field_840 == 3.0 )
        field_534 *= 0.88;

    if ( field_840 >= 4.0 )
        field_534 *= 0.8;

    if ( field_84E > 0 )
    {
        field_538 *= 0.5;

        if ( shader_type == 0 )
            shader_type = 3;

        field_84E--;
        shader_cB = 0;
        shader_cR = shader_cG = (64.0 - cos(field_84E * 8.0) * 64.0);

        if ( field_84E <= 0 )
        {
            shader_type = 0;
            field_84E = 0;
        }
    }
    field_74C -= field_838;

    field_838 --;
    if (field_838 < 0)
        field_838 = 0;

    if ( field_852 > 0 )
    {
        if ( field_51C < 2 )
            field_51C = 1;

        if ( field_520 < 2 )
            field_520 = 1;

        speed_mult *= 1.2;

        if ( speed_mult >= 2.0 )
            speed_mult = 2.0;

        field_848++;

        if ( get_seq() != 691 )
            field_852--;

        if ( shader_type )
            shader_type = 3;

        uint32_t tm_c = 6 * time_count_get() % 360;

        if ( tm_c < 60 )
        {
            shader_cB = 0;
            shader_cG = (tm_c / 60.0 * 255.0);
            shader_cR = 255;
        }
        else if ( tm_c <= 119 ) //60..120
        {
            shader_cG = 255;
            shader_cB = 0;
            shader_cR = (255.0 - (tm_c - 60.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 179 ) //120..180
        {
            shader_cG = 255;
            shader_cR = 0;
            shader_cB = ((tm_c - 120.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 239 )
        {
            shader_cB = 255;
            shader_cR = 0;
            shader_cG = (255.0 - (tm_c - 180.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 299 )
        {
            shader_cB = 255;
            shader_cG = 0;
            shader_cR = ((tm_c - 240.0) / 60.0 * 255.0);
        }
        else if ( tm_c <= 359 )
        {
            shader_cG = 0;
            shader_cB = (255.0 - (tm_c - 300.0) / 60.0 * 255.0);
            shader_cR = 255;
        }

        if ( field_852 <= 0 )
        {
            shader_type = 0;
            field_850 = 0;
        }

    }

}

void char_c::func20()
{

}

bool char_c::flip_to_enemy()
{
    int8_t d = dir;

    if (enemy->x < x)
    {
        dir = -1;
        return d != -1;
    }
    else if (enemy->x > x)
    {
        dir = 1;
        return d != 1;
    }
    return false;
}

void char_c::flip_with_force()
{
    if ( dir == 1 )
    {
        if ( enemy->x < x )
        {
            dir = -1;
            h_inerc = -h_inerc;
        }
    }
    if ( dir == -1 )
    {
        if ( enemy->x > x )
        {
            dir = 1;
            h_inerc = -h_inerc;
        }
    }
}

void char_c::reset_forces()
{
    h_inerc = 0;
    v_inerc = 0;
    v_force = 0;
    //h_force = 0;
}

void char_c::func18()
{


    bool grn = char_on_ground();
    if ( grn && field_4C4 == 0 )
    {
        air_dash_cnt = 0;
        field_49C = 0;
    }
    if ( get_prior() == 0)
        if ( grn && field_4C4 == 0)
        {
            int32_t sq = get_seq();
            if ( sq != 6 && sq != 7 && sq != 8 )
            {
                int32_t in_y = dY();
                int32_t in_x = dX(dir);

                if (in_y == 0)
                {
                    if (in_x == 0)
                    {
                        if ( sq == 1 || sq == 2 )
                            set_seq(3);
                        else if ( sq != 0 && sq != 3 && sq != 10 )
                            set_seq(0);
                    }
                    else
                    {
                        flip_to_enemy();
                        if (in_x < 0)
                        {
                            if ( sq != 5 )
                                set_seq(5);
                        }
                        else /*if (in_x > 0)*/
                        {
                            if ( sq != 4 )
                                set_seq(4);
                        }

                    }
                    flip_to_enemy();
                }
                else if (in_y > 0)
                {
                    flip_to_enemy();
                    in_x = dX(dir);

                    if ( in_x < 0 )
                    {
                        if ( sq != 8 )
                            set_seq(8);
                    }
                    else if (in_x > 0)
                    {
                        if ( sq != 7 )
                            set_seq(7);
                    }
                    else /*if (in_x == 0)*/
                    {
                        if ( sq != 6 )
                            set_seq(6);
                    }
                }
                else if (in_y < 0)
                {
                    if ( sq != 2 && sq != 1 )
                    {
                        set_seq(1);
                        flip_to_enemy();
                    }
                }
            }
        }
}


bool char_c::sub10func()
{
    int32_t sq = get_seq();

    if ( field_4C4 || (char_on_ground() != 1 && field_4C4 != 1))
        return false;
    if ( y - getlvl_height() <= 5.0|| sq == 98 || sq == 99 )
    {
        y = getlvl_height();
        return false;
    }
    if ( !char_is_shock())
    {
        if ( sq < 700 || sq > 799 )
        {
            scaleX = 1.0;
            scaleY = 1.0;

            set_seq(9);
        }
        else
            set_seq(704);

        v_inerc = 0.0;
        v_force = 0.5;

        if ( h_inerc > 10.0 )
            h_inerc = 10.0;
        if ( h_inerc < -10.0 )
            h_inerc = -10.0;
    }
    else
    {
        set_seq(71);
        field_1A8 = 0.0;
        field_1A4 = -h_inerc;
        scaleX = 1.0;
        scaleY = 1.0;
        angZ    = 0.0;
        v_force = 0.5;
    }
    return true;
}



void char_c::play_sfx(uint32_t idx)
{
    if (sfx[idx % MAX_CHR_SFX] != NULL)
        sfx_play(sfx[idx % MAX_CHR_SFX]);
}

void char_c::clear_key(inp_keys key)
{
    input->zero_input(key);
}

int32_t char_c::keyDown(inp_keys key)
{
    return input->keyDown(key);
}
int32_t char_c::keyHit(inp_keys key)
{
    return input->keyHit(key, true);
}
int32_t char_c::keyUp(inp_keys key)
{
    return input->keyUp(key);
}

int32_t char_c::dX(int8_t _dir)
{
    return input->dX(_dir);
}
int32_t char_c::dY()
{
    return input->dY();
}

int32_t char_c::hX(int8_t _dir)
{
    return input->hX(_dir);
}
int32_t char_c::hY()
{
    return input->hY();
}

void char_c::set_dX(int8_t dir)
{
    input->set_dX(dir);
}
void char_c::set_dY(int8_t dir)
{
    input->set_dY(dir);
}

void char_c::set_keyDown(inp_keys key, int32_t val)
{
    input->set_keyDown(key, val);
}

void char_c::sub_486FD0(float p1, float p2)
{
    field_7F0 = -atan2_deg(enemy->getY() - y, (enemy->getX() - x) * dir);

    if ( field_7F0 < p2)
        field_7F0 = p2;
    else if ( field_7F0 > p1 )
        field_7F0 = p1;
}

void char_c::set_seq_params()
{
    int32_t sq = get_seq();
    switch(sq)
    {
    case 0:
    case 1:
    case 2:
    case 3:
        if ( !field_49A )
            reset_forces();
        break;
    case 6:
        if ( (pres_move & PMOVE_N08) == 0  && (keyDown(INP_D) == 0 || dY() <= 0 || dX(dir) != 0 ))
        {
            if ( field_49A == 0 )
                reset_forces();
            v_force = 0.0;
        }
        else
            set_seq(208);

        break;
    case 7:
        if ( (pres_move & PMOVE_N09) == 0  && (keyDown(INP_D) == 0 || dY() <= 0 || dX(dir) <= 0 ))
        {
            if ( field_49A == 0 )
                reset_forces();
            v_force = 0.0;
        }
        else
            set_seq(209);

        break;
    case 8:
        if ( (pres_move & PMOVE_N07) == 0  && (keyDown(INP_D) == 0 || dY() <= 0 || dX(dir) >= 0 ))
        {
            if ( field_49A == 0 )
                reset_forces();
            v_force = 0.0;
        }
        else
            set_seq(210);

        break;
    case 10:
        scene_play_sfx(30);
        reset_forces();
        break;
    case 50:
    case 57:
    case 63:
        h_inerc = -15;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 53:
    case 59:
    case 65:
        field_7D0 = 0;
        field_7D2 = 0;
        h_inerc = -25;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 52:
        h_inerc = -25;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 56:
    case 62:
        h_inerc = -10;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 54:
    case 60:
    case 66:
        h_inerc = 0.0;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 51:
    case 55:
    case 58:
    case 61:
    case 64:
    case 67:
        h_inerc = -20;
        v_inerc = 0;
        field_1A4 = 0;
        field_1A8 = 0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 70:
        field_571 = 1;
        field_572 = 1;
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 0.8;
        if ( h_inerc > 0.0 )
            field_7D0 = 1;
        else if (h_inerc < 0)
            field_7D0 = -1;
        else
            field_7D0 = 0;
        angZ = 0.0;
        break;
    case 71:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 0.5;
        field_7D0 = 7;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 72:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 1.3;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 73:
    case 88:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;

        v_force = 0.8;
        field_7D0 = 7;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 74:
    case 75:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 0.8;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 76:
        field_571 = 1;
        field_572 = 1;
        weather_forecast_next();
        for (int8_t i = 0; i < 5; i++)
            scene_add_effect(this,201,x,y+100,dir,1);

        field_7D0++;
        x_off = x_delta;
        y_off = y_delta;

        hit_stop = 5;

        scene_add_effect(this,38, x - dir*50, y+100, dir, 1);
        scene_add_effect(this,59, x - dir*50, y+100, dir, 1);

        h_inerc = 0.0;
        v_inerc = 0.0;
        v_force = 0.0;
        //shake_camera(2.0); //HACK
        scene_play_sfx(22);
        angZ = 0;
        break;

    case 77:
        h_inerc = -field_1A4;
        v_inerc = field_1A8;
        v_force = 0.8;
        x_off = x_delta;
        y_off = y_delta;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;

    case 78:
        field_571 = 1;
        field_572 = 1;
        field_7D0++;
        weather_forecast_next();

        for (int8_t i=0; i < 5; i++)
            scene_add_effect(this,201, x, y, dir, 1);

        h_inerc = 0.0;
        v_inerc = 0.0;
        v_force = 0.0;
        //shake_camera(4.0); //HACK
        scene_play_sfx(22);

        scene_add_effect(this, 38, x - 50*dir, y+100, dir, 1);
        scene_add_effect(this, 59, x - 50*dir, y+100, dir, 1);

        angZ = 0;
        break;
    case 89:
        field_571 = 1;
        field_572 = 1;
        weather_forecast_next();
        scene_add_effect(this, 58, x, y, dir, -1);
        for (int8_t i=0; i < 5; i++)
            scene_add_effect(this,201, x, y+100, dir, 1);
        angZ = 0;
        break;
    case 97:
        weather_forecast_next();
        scene_add_effect(this, 58, x, y, dir, -1);

        for (int8_t i=0; i < 5; i++)
            scene_add_effect(this, 201, x, y, dir, 1);
        angZ = 0;
        if ( field_882 > 0 )
            set_seq(96);
        break;
    case 98:
        reset_forces();
        air_dash_cnt = 0;
        field_7D0 = 0;
        break;
    case 99:
        reset_forces();
        field_7DC = 0.0;
        dash_angle = 0.0;
        air_dash_cnt = 0;
        field_7E4 = 0.0;
        field_7D6 = 0;
        field_7E8 = 0.0;
        field_7D8 = 0;
        field_7EC = 0.0;
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 112:
    case 113:
    case 197:
    case 198:
    case 199:
        reset_forces();
        break;
    case 115:
        x_off = x_delta;
        y_off = y_delta;
        angZ = 0;
        break;
    case 140:
        h_inerc = -11;
        field_7D0 = 0;
        v_inerc = 0.0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 143:
    case 144:
        h_inerc = -12;
        field_7D0 = 0;
        v_inerc = 0.0;
        field_571 = 1;
        field_572 = 1;
        angZ = 0;
        break;
    case 145:
        h_inerc = -10.0;
        field_571 = 1;
        v_inerc = 14.0;
        field_572 = 1;
        v_force = 0.5;
        angZ = 0.0;
        break;
    case 149:
        field_571 = 1;
        field_572 = 1;
        x_off = x_delta;
        y_off = y_delta;
        h_inerc = -3.0;
        v_inerc = 17.5;
        v_force = 0.5;
        break;
    case 150:
    case 154:
        h_inerc = -6.0;
        field_190 = 0;
        v_inerc = 0.0;
        field_83C = 0;
        field_7D0 = 0;
        break;
    case 151:
    case 155:
        h_inerc = -10.0;
        field_190 = 0;
        v_inerc = 0.0;
        field_83C = 0;
        field_7D0 = 0;
        break;
    case 152:
    case 156:
        h_inerc = -13.0;
        field_190 = 0;
        v_inerc = 0.0;
        field_83C = 0;
        field_7D0 = 0;
        break;
    case 153:
    case 157:
        h_inerc = -14.5;
        field_190 = 0;
        v_inerc = 0.0;
        field_83C = 0;
        field_7D0 = 0;
        break;
    case 158:
        h_inerc = -6.0;
        field_7D0 = 7;
        v_inerc = 12.0;
        field_7D2 = 0;
        field_83C = 0;
        v_force = 0.75;
        break;
    case 159:
    case 163:
        h_inerc = -6.0;
        field_190 = 0;
        v_inerc = 0.0;
        field_7D0 = 0;
        break;
    case 160:
    case 164:
        h_inerc = -10.0;
        field_190 = 0;
        v_inerc = 0.0;
        field_7D0 = 0;
        break;
    case 161:
    case 165:
        h_inerc = -13.0;
        field_190 = 0;
        v_inerc = 0.0;
        field_7D0 = 0;
        break;
    case 162:
    case 166:
        h_inerc = -14.5;
        field_190 = 0;
        v_inerc = 0.0;
        field_7D0 = 0;
        break;
    case 167:
        h_inerc = -6.0;
        field_7D0 = 7;
        v_inerc = 8.0;
        v_force = 0.75;
        break;
    case 180:
        reset_forces();
        h_inerc = 8.0;
        v_inerc = 12.5;
        v_force = 0.75;
        scene_add_effect(this, 61, x, y + 100, dir, 1);
        angZ = 0;
        break;
    case 181:
        reset_forces();
        h_inerc = -8.0;
        v_inerc = 12.5;
        v_force = 0.75;
        scene_add_effect(this, 61, x, y + 100, dir, 1);
        angZ = 0;
        break;
    case 200:
        field_49A = 1;
        reset_forces();
        field_7DC = 0.0;
        dash_angle = 0.0;
        field_7E4 = 0.0;
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 201:
    case 202:
    case 203:
        reset_forces();
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 208:
    case 209:
    case 210:
    case 211:
    case 212:
        if ( field_49A == 0 )
            reset_forces();
        v_force = 0.0;
        break;
    case 220:
    case 221:
    case 222:
        reset_forces();
        scene_add_effect(this, 69, x, y+100, dir, 1);
        break;
    case 223:
        field_49A = 1;
        reset_forces();
        scene_add_effect(this, 69, x, y+100, dir, 1);
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 224:
    case 225:
    case 226:
        reset_forces();
        scene_add_effect(this, 69, x, y+100, dir, 1);
        field_7D4 = 0;
        field_7D2 = 0;
        field_7D0 = 0;
        break;
    case 690:
        reset_forces();
        if ( cards_added > 0 )
        {
            field_190 = 0;
            sub_488E70();
        }
        break;
    case 691:
        field_190 = 0;
        reset_forces();
        switch ( field_7D0 )
        {
        case 4:
            field_840 ++;
            if ( field_840 > 4.0 )
                field_840 = 4.0;
            scene_add_effect(this, field_840 + 130, x, y, 1, 1);
            break;
        case 5:
            field_560++;
            if ( field_560 > 4 )
                field_560 = 4;
            scene_add_effect(this, field_560 + 130, x, y, 1, 1);
            break;
        case 10:
            tengu_fan++;
            if ( tengu_fan > 4 )
                tengu_fan = 4;
            {
                float params[3];
                params[0] = 0;
                params[1] = 0;
                params[2] = 1;
                addbullet(this,NULL,1010, x, y, dir, 1, params,3);
            }
            scene_add_effect(this, tengu_fan + 130, x, y, 1, 1);
            break;
        case 17:
            field_84E = 240;
            break;
        case 18:
            field_844++;
            if ( field_844 > 4.0 )
                field_844 = 4.0;
            scene_add_effect(this, field_844 +130, x, y, 1, 1);
            break;
        case 19:
            if ( field_850 < 3 )
            {
                scene_add_effect(this, field_850 + 130, x, y, 1, 1);
            }
            else
            {
                field_852 += 420;
                field_850 = 3;
                scene_add_effect(this, 139, x, y, 1, 1);
            }
            break;
        default:
            break;
        }
        break;
    case 692:
    case 693:
    case 694:
        scene_add_effect(this, 71, x, y + 100, dir, 1);
        field_7D0 = 0;
        field_7D2 = 0;
        field_190 = 0;
        reset_forces();
        break;
    case 695:
        field_194 = 1;
        field_190 = 0;
        reset_forces();
        break;
    case 696:
        field_194 = 1;
        field_190 = 0;
        field_49A = 0;
        reset_forces();
        scene_add_effect(this, 69, x, y + 100, dir, 1);
        field_4A6 = 10;
        break;
    case 697:
        field_194 = 1;
        field_190 = 0;
        field_49A = 0;
        reset_forces();
        scene_add_effect(this, 69, x, y + 100, dir, 1);
        break;
    case 698:
        field_7D0 = 0;
        field_194 = 1;
        field_190 = 0;
        field_49A = 0;
        reset_forces();
        break;
    case 700:
        reset_forces();
        v_force = 0.0;
        field_190 = 1;
        break;
    case 701:
    case 702:
    case 703:
        reset_forces();
        v_force = 0.0;
        break;
    case 704:
        if ( v_force == 0 )
            v_force = 0.5;
        break;
    case 705:
        reset_forces();
        h_inerc = field_854;
        break;
    case 706:
        reset_forces();
        h_inerc = field_858;
        break;
    case 709:
        scene_play_sfx(30);
        reset_forces();
        break;
    case 789:
        field_7D8 = 0;
        reset_forces();
        break;
    case 790:
        field_7D0 = 0;
        reset_forces();
        break;
    case 795:
        field_7D0 = 0;
        break;
    case 796:
    case 799:
        field_7DC = 0.0;
        reset_forces();
        break;
    default:
        printf("set_seq_params() unknown id: %d\n",get_seq());
        break;
    }
}

c_bullet *char_c::new_bullet()
{
    return NULL;
}

bool char_c::char_idle_or_move()
{
    return get_seq() < 50;
}

bool char_c::char_is_shock()
{
    uint32_t s = get_seq();
    return s >= 50 && s < 150;
}

bool char_c::char_is_block_knock()
{
    uint32_t s = get_seq();
    return s >= 150 && s < 168;
}

bool char_c::spell200_seq299_300_field190_0_3()
{
    return ((get_seq() > 299 && field_190 != 0 && field_190 != 3) || get_seq() < 300 ) && spell_energy >= 200;
}

bool char_c::seq299_300_field190_0_3()
{
    return ((get_seq() > 299 && field_190 != 0 && field_190 != 3) || get_seq() < 300 );
}

void char_c::sub_488E70()
{
    int32_t id = cards_active[0]->id;
    switch ( id )
    {
    case 100:
        if ( skills_2[0]++ == -1 )
            skills_2[0] = 1;
        if ( skills_2[0] >= 5 )
            skills_2[0] = 4;
        skills_2[4] = -1;
        skills_2[8] = -1;
        skills_2[12] = -1;
        break;
    case 101:
        if ( skills_2[1]++ == -1 )
            skills_2[1] = 1;
        if ( skills_2[1] >= 5 )
            skills_2[1] = 4;
        skills_2[5] = -1;
        skills_2[9] = -1;
        skills_2[13] = -1;
        break;
    case 102:
        if ( skills_2[2]++ == -1 )
            skills_2[2] = 1;
        if ( skills_2[2] >= 5 )
            skills_2[2] = 4;
        skills_2[6] = -1;
        skills_2[10] = -1;
        skills_2[14] = -1;
        break;
    case 103:
        if ( skills_2[3]++ == -1 )
            skills_2[3] = 1;
        if ( skills_2[3] >= 5 )
            skills_2[3] = 4;
        skills_2[7] = -1;
        skills_2[11] = -1;
        skills_2[15] = -1;
        break;
    case 104:
        if ( skills_2[4]++ == -1 )
            skills_2[4] = 1;
        if ( skills_2[4] >= 5 )
            skills_2[4] = 4;
        skills_2[0] = -1;
        skills_2[8] = -1;
        skills_2[12] = -1;
        break;
    case 105:
        if ( skills_2[5]++ == -1 )
            skills_2[5] = 1;
        if ( skills_2[5] >= 5 )
            skills_2[5] = 4;
        skills_2[1] = -1;
        skills_2[9] = -1;
        skills_2[13] = -1;
        break;
    case 106:
        if ( skills_2[6]++ == -1 )
            skills_2[6] = 1;
        if ( skills_2[6] >= 5 )
            skills_2[6] = 4;
        skills_2[2] = -1;
        skills_2[10] = -1;
        skills_2[14] = -1;
        break;
    case 107:
        if ( skills_2[7]++ == -1 )
            skills_2[7] = 1;
        if ( skills_2[7] >= 5 )
            skills_2[7] = 4;
        skills_2[3] = -1;
        skills_2[11] = -1;
        skills_2[15] = -1;
        break;
    case 108:
        if ( skills_2[8]++ == -1 )
            skills_2[8] = 1;
        if ( skills_2[8] >= 5 )
            skills_2[8] = 4;
        skills_2[0] = -1;
        skills_2[4] = -1;
        skills_2[12] = -1;
        break;
    case 109:
        if ( skills_2[9]++ == -1 )
            skills_2[9] = 1;
        if ( skills_2[9] >= 5 )
            skills_2[9] = 4;
        skills_2[1] = -1;
        skills_2[5] = -1;
        skills_2[13] = -1;
        break;
    case 110:
        if ( skills_2[10]++ == -1 )
            skills_2[10] = 1;
        if ( skills_2[10] >= 5 )
            skills_2[10] = 4;
        skills_2[2] = -1;
        skills_2[6] = -1;
        skills_2[14] = -1;
        break;
    case 111:
        if ( skills_2[11]++ == -1 )
            skills_2[11] = 1;
        if ( skills_2[11] >= 5 )
            skills_2[11] = 4;
        skills_2[3] = -1;
        skills_2[7] = -1;
        skills_2[15] = -1;
        break;
    case 112:
        if ( skills_2[12]++ == -1 )
            skills_2[12] = 1;
        if ( skills_2[12] >= 5 )
            skills_2[12] = 4;
        skills_2[0] = -1;
        skills_2[4] = -1;
        skills_2[8] = -1;
        break;
    case 113:
        if ( skills_2[13]++ == -1 )
            skills_2[13] = 1;
        if ( skills_2[13] >= 5 )
            skills_2[13] = 4;
        skills_2[1] = -1;
        skills_2[5] = -1;
        skills_2[9] = -1;
        break;
    case 114:
        if ( skills_2[14]++ == -1 )
            skills_2[14] = 1;
        if ( skills_2[14] >= 5 )
            skills_2[14] = 4;
        skills_2[2] = -1;
        skills_2[6] = -1;
        skills_2[10] = -1;
        break;
    case 115:
        if ( skills_2[15]++ == -1 )
            skills_2[15] = 1;
        if ( skills_2[15] >= 5 )
            skills_2[15] = 4;
        skills_2[3] = -1;
        skills_2[7] = -1;
        skills_2[11] = -1;
        break;
    default:
        break;
    }
    scene_add_effect(this, 71, x, y + 100.0, dir, 1);
    scene_add_effect(this, skills_2[id-100] + 130, x, y, 1, 1);
    sub_469450(0, 0, 60);
    sub_483570();
    sub_468330();
}

void char_c::sub_469450(int32_t id, int8_t _cost, int8_t efx)
{
    if ( cards_added != 0 )
    {
        int32_t cost = 0;

        if (_cost > 0)
            cost = _cost - (weather_id == WEATHER_CLOUDY);
        else
            cost = cards_active[id]->cost - (weather_id == WEATHER_CLOUDY);

        if (cost < 1)
            cost = 1;

        if (cards_active[id]->id >= 200)
            if (efx > 0)
                stand_gfx->show();

        //sub_435B70(&battle_manager->unks2[player_index], cards_active[id]->id, efx); //HACK

        cards_used.push_back(cards_active[id]);

        cards_active.erase(cards_active.begin() + id, cards_active.begin() + id + cost);

        cards_added = cards_active.size();
    }
}

void char_c::sub_483570()
{
    if ( weather_id == WEATHER_MOUNTAIN_VAPOR )
        weather_time_set(1);
    if ( weather_id == WEATHER_CLOUDY )
        weather_time_set(1);
    if ( weather_id == WEATHER_DRIZZLE )
        weather_time_mul(0.75);
}

void char_c::sub_468330()
{
    if ( field_56E != 0 )
    {
        for (int8_t i=0; i< 32; i++)
            if (skills_2[i] < 0)
                skills_1[i] = 0;
            else
                skills_1[i] = 4;
    }
    else
    {
        for (int8_t i=0; i< 32; i++)
            if (skills_2[i] < 0)
                skills_1[i] = 0;
            else
                skills_1[i] = skills_2[i];
    }
}

void char_c::sub_487370(uint32_t seq_id, uint16_t cprior)
{
    if ( cprior >= 10 )
        correction |= 0x10u;
    set_seq(seq_id);
    //input_push_pressed_to_buf(v3); //HACK
    angZ = 0.0;
}

void char_c::char_h_move(float move)
{
    float movel;

    movel = speed_mult * move;
    h_inerc = movel;
    if ( move > 0.0 )
        h_inerc += tengu_fan * 0.5;
    else if ( move < 0.0 )
        h_inerc -= tengu_fan * 0.5;
}


void char_c::char_loadsfx(const char *name)
{
    char buf[CHRBUF];
    for (uint32_t i=0; i<MAX_CHR_SFX; i++)
    {
        sprintf(buf,"data/se/%s/%3.3d.cv3",name,i);

        sfx[i] = sfx_load_cv3(buf);
    }
}





bool char_c::hi_jump_after_move()
{
    if ( dY() > 0)
    {
        if ( dX(dir) > 0 )
        {
            angZ = 0.0;
            set_seq(209);
            return true;
        }
        else if ( dX(dir) < 0 )
        {
            angZ = 0.0;
            set_seq(210);
            return true;
        }
        else
        {
            angZ = 0.0;
            set_seq(208);
            return true;
        }
    }

    return false;
}

bool char_c::border_escape_ground()
{
    if ( pres_move & PMOVE_DD  && field_80E == 0)
        if (  char_is_block_knock() && (max_spell_energy >= 200 || weather_id == WEATHER_SUNNY) )
        {
            if ( dY() <= 0 )
            {
                angZ = 0.0;
                if ( dX(dir) <= 0 )
                    set_seq(224);
                else
                    set_seq(223);
                if ( weather_id != WEATHER_SUNNY )
                    crash_spell_borders(1);
                return true;
            }
            else
            {
                angZ = 0.0;
                if ( dX(dir) >= 0 )
                    set_seq(220);
                else
                    set_seq(222);
                if ( weather_id != WEATHER_SUNNY )
                    crash_spell_borders(1);
                return true;
            }
        }
    return false;
}

bool char_c::hi_jump(uint16_t cprior, uint32_t hjc)
{
    if ( (pres_move & PMOVE_N08) || (dY() > 0 && dX(dir)==0 && (keyDown(INP_D) || cprior >= 40)) )
        if ( cprior <= get_prior(208) || hjc )
            if ( field_sq_check() )
            {
                angZ = 0.0;
                set_seq(208);
                return true;
            }
    if ( pres_move & PMOVE_N09 || (dY() > 0 && dX(dir) > 0 && (keyDown(INP_D) || cprior >= 40)))
        if ( cprior <= get_prior(209) || hjc )

            if ( field_sq_check())
            {
                angZ = 0.0;
                set_seq(209);
                return true;
            }


    if ( pres_move & PMOVE_N07 || (dY() > 0 && dX(dir) < 0 && (keyDown(INP_D) || cprior >= 40)))
        if ( cprior <= get_prior(210) || hjc)
            if ( field_sq_check())
            {
                angZ = 0.0;
                set_seq(210);
                return true;
            }
    return false;
}

bool char_c::fw_bk_dash_ground(uint16_t cprior, uint32_t hjc)
{
    if ( ((pres_move & PMOVE_NRNR && dir == 1)
            || (pres_move & PMOVE_NLNL && dir == -1)
            || (keyDown(INP_D) && dY() == 0 && dX(dir) > 0))
            && get_seq() != 204
            && cprior <= get_prior(200)
            && field_sq_check())
    {
        angZ = 0.0;
        set_seq(200);
        return true;
    }
    else if (((pres_move & PMOVE_NLNL && dir == 1)
              || (pres_move & PMOVE_NRNR && dir == -1)
              || (keyDown(INP_D) && dY() == 0 && dX(dir) < 0))
             && (cprior <= get_prior(201) || hjc)
             && field_sq_check())
    {
        angZ = 0.0;
        set_seq(201);
        return true;
    }
    return false;
}


bool char_c::border_escape_air()
{
    if ( (pres_move & PMOVE_DD) != 0  && field_80E == 0 && get_seq() == 158 &&
            (max_spell_energy >= 200 || weather_get()==WEATHER_SUNNY ))
    {
        angZ = 0.0;
        if ( dX(dir) > 0 )
        {
            set_seq(226);
            if ( weather_id != WEATHER_SUNNY )
                crash_spell_borders(1);
            return true;
        }
        else
        {
            set_seq(225);
            if ( weather_id != WEATHER_SUNNY )
                crash_spell_borders(1);
            return true;
        }
    }
    return false;
}

bool char_c::fwd_dash_air(uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse)
{
    if ( air_dash_cnt < max_dash
            && (get_seq() != 202 || get_subseq() >= subse)
            && (((pres_move & PMOVE_NRNR) != 0 && dir == 1) || ((pres_move & PMOVE_NLNL) != 0 && dir == -1))
            && (cprior <= get_prior(202) || hjc)
            && (v_inerc <= 0.0 || y > 100.0)
            && field_sq_check())
    {
        angZ = 0.0;
        set_seq(202);
        air_dash_cnt++;
        return true;
    }
    return false;
}

bool char_c::bkg_dash_air(uint16_t cprior, uint32_t hjc, int8_t max_dash, uint16_t subse)
{
    if ( air_dash_cnt < max_dash
            && (get_seq() != 203 || get_subseq() >= subse)
            && (((pres_move & PMOVE_NLNL) != 0 && dir == 1) || ((pres_move & PMOVE_NRNR) != 0 && dir == -1))
            && (cprior <= get_prior(203) || hjc)
            && (v_inerc <= 0.0 || y > 100.0)
            && field_sq_check())
    {
        angZ = 0.0;
        set_seq(203);
        air_dash_cnt++;
        return true;
    }
    return false;
}

bool char_c::flying_air(uint16_t cprior, uint32_t hjc, int8_t max_dash)
{
    if ( air_dash_cnt < max_dash
            && keyDown(INP_D) // >= 1   //OPTIMIZATION
            && (dX(dir) != 0 || dY() != 0)
            && (v_inerc <= 0.0 || y > 100.0)
            && (cprior <= get_prior(214) || hjc)
            && field_sq_check() )
    {
        if ( dY() < 0 )
        {
            if (dX(dir) > 0)
                dash_angle = -45.0;
            else if( dX(dir) < 0 )
                dash_angle = -135.0;
            else
                dash_angle = -90.0;
        }
        else if ( dY() > 0 )
        {
            if (dX(dir) > 0)
                dash_angle = 45.0;
            else if( dX(dir) < 0 )
                dash_angle = 135.0;
            else
                dash_angle = 90.0;
        }
        else
        {
            if (dX(dir) > 0)
                dash_angle = 0.0;
            else if( dX(dir) < 0 )
                dash_angle = 180.0;
            else
                dash_angle = 0.0;
        }
        angZ = 0;
        air_dash_cnt++;
        set_seq(214);
        return true;
    }

    return false;
}



void char_c::stopping(float p)
{
    if (field_49A)
    {
        if (h_inerc > 0)
        {
            h_inerc -= p;
            if (h_inerc < 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
        if ( h_inerc < 0)
        {
            h_inerc += p;
            if (h_inerc > 0)
            {
                reset_forces();
                field_49A = 0;
            }
        }
    }
    else
        reset_forces();
}

void char_c::stopping_posit(float p)
{
    if (field_49A)
    {
        h_inerc -= p;
        if (h_inerc < 0)
        {
            reset_forces();
            field_49A = 0;
        }
    }
    else
        reset_forces();
}

bullist *char_c::get_bullets()
{
    return &bullets;
}

void char_c::health_to_max()
{
    health = max_health;
}

void char_c::set_input_profile(s_profile *prof)
{
    input->load_profile(prof);
}

void char_c::load_face(const char *name)
{
    char buf[256];
    sprintf(buf,"data/character/%s/face/face000.cv2",name);
    player_face_tex = gr_load_cv2(buf,NULL);
    player_face = gr_create_sprite();
    gr_set_spr_tex(player_face, player_face_tex);
}


void shuffle_cards(card_deq *crd)
{
    uint32_t sz = crd->size();
    if (sz > 0)
        for (int32_t i=0; i < 100; i++)
        {
            uint32_t id = scene_rand_rng(sz);
            s_card *tmp = (*crd)[id];
            crd->erase(crd->begin() + id);
            crd->push_front(tmp);
        }
}

void char_c::set_cards_deck(s_profile *prof, uint32_t deck_id)
{
    cards_deck.clear();
    cards_shuffle.clear();
    cards_active.clear();
    cards_used.clear();

    for (uint32_t i=0; i < 20; i++)
    {
        uint32_t id = prof->decks[char_id][deck_id % 4][i];
        s_card *crd = cards_get_card(&chr_cards,id);

        if (!crd)
            printf("UNKNOWN CARD ID %d \n",id);
        else
            cards_deck.push_back(crd);
    }

    cards_shuffle = cards_deck;
    shuffle_cards(&cards_shuffle);
}


bool char_c::sub_4699E0()
{
    return y > 0.0 && field_4BA == 0 && char_is_shock();
}


void char_c::char_xy_pos_calculation()
{
    char_c *enm = enemy;

    if ( !hit_stop )
    {
        if ( !enm->time_stop )
        {
            if ( field_571 )
            {
                float v4 = (field_744 + h_inerc + enm->field_74C) * dir * field_564;
                if ( get_border_near() * v4 >= 0.0 )
                    if ( getlvl_height(v4) == 0 )
                        x += v4;

                if ( x < CHAR_PADDING )
                    x = CHAR_PADDING;
                if ( x > (BKG_WIDTH - CHAR_PADDING) )
                    x = (BKG_WIDTH - CHAR_PADDING);
            }
            else
                x += (enm->field_74C + h_inerc) * dir * field_564;

            y = field_568 * v_inerc + y;

            if ( field_572 )
                if ( char_on_ground() && field_4C4 == 0 )
                    y = getlvl_height();
        }
    }
}

float c_meta::sub_4634F0()
{
    float dmg = chrt->field_530 * enemy->field_534 * chrt_changeable->combo_rate;
    if ( field_18C >= 0 && field_18C < 32 )
        dmg *= (chrt->skills_1[field_18C] / 10.0 + 1.0);

    char_frame *frm = get_pframe();
    if ( frm->aflags & AF_UNK1000 )
        dmg *= chrt->field_544;
    if ( frm->aflags & AF_UNK800 )
        dmg *= chrt->field_548;
    if ( chrt_changeable->correction & 0x1 )
        dmg *= 0.8;
    if ( chrt_changeable->correction & 0x2 )
        dmg *= 0.8;
    if ( chrt_changeable->correction & 0x4 )
        dmg *= 0.8;
    if ( chrt_changeable->correction & 0x8 )
        dmg *= 0.85;
    if ( chrt_changeable->correction & 0x10 )
        dmg *= 0.925;

    if ( enemy->health < 0 )
        dmg *= 0.7;
    else if ( enemy->max_health > enemy->health )
        dmg *= enemy->health / enemy->max_health * 0.3 + 0.7;
    return dmg;
}


int8_t char_c::sub_469750(uint32_t enemu_aflags)
{
    if ( enemu_aflags & AF_U_HIT )
        return 0;
    if ( field_4AA )
        return 0;

    char_frame *frm = get_pframe();

    if ( frm->fflags & FF_GUARD2 )
        return 6;
    if ( !(frm->fflags & FF_GUARDCANC) )
        return 0;

    if ( !char_is_block_knock() )
    {
        if ( input_function )
        {
            if ( field_578 == 0  && ((enemy->x - x) * dX(1) > 0  || dX(1) == 0))
                return 0;
        }
        else if ( controlling_type == 3 ) //CHAR_CTRL_TRAIN_DUMMY
        {
            set_dY(0);
            set_dX(0);
            /*if ( practice_params->field_C <= 0 ) //HACK
            {
                if ( field_578 == 0  && ((enemy->x - x) * gX(1) > 0  || gX(1) == 0))
                    return 0;
            }*/
        }
        else if ( settings_get()->get_difficulty() == GAME_DIFF_NORMAL && scene_rand_rng(100) >= 95 )
        {
            if ( field_578 == 0  && ((enemy->x - x) * dX(1) > 0  || dX(1) == 0))
                return 0;
        }
        else if ( settings_get()->get_difficulty() == GAME_DIFF_EASY && scene_rand_rng(100) >= 70 )
        {
            if ( field_578 == 0  && ((enemy->x - x) * dX(1) > 0  || dX(1) == 0))
                return 0;
        }
        else
        {
            if ( enemy->x - x <= 0.0 )
                set_dX(1);
            else
                set_dX(-1);

            if ( controlling_type == 3 )
            {
                if ( /*practice_params->dummy_block_type*/ dummy_block_type == 2 ) // HACK
                    set_dY(0);
                else if ( dummy_block_type == 3 )
                    set_dY(1);
                else
                    set_dY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);
            }
            else
                set_dY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);

            if ( field_578 == 0  && ((enemy->x - x) * dX(1) > 0  || dX(1) == 0))
                return 0;
        }
    }
    else
    {
        if ( input_function )
        {
            if ( dX(1) == 0 && (enemu_aflags & AF_GUARDCRUSH) )
                return 0;
        }
        else if ( controlling_type == 3 )
        {
            if ( dummy_block_type == 2 )
                set_dY(0);
            else if ( dummy_block_type == 3 )
                set_dY(1);
            else
                set_dY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);
        }
        else
            set_dY((enemu_aflags & AF_MID_HIT) == 0 ? 1 : 0);
    }

    if ( !char_on_ground_flag() || frm->fflags & FF_AIRBORNE )
    {
        return (enemu_aflags & AF_AIR_HIT) == 0 ? 0 : 5;
    }
    else
    {
        if ( dY() <= 0 )
        {
            if ( enemu_aflags & AF_MID_HIT )
                return 1;
            else
                return  (enemu_aflags & AF_UNK40) == 0 ? 2 : 0;
        }
        else
        {
            if ( enemu_aflags & AF_LOW_HIT )
                return 3;
            else
                return (enemu_aflags & AF_UNK40) == 0 ? 4 : 0;
        }
    }
    return 0;
}

void char_c::char_stats_check()
{
    char_c *enm = enemy;

    if ( !enm->time_stop )
    {
        if ( hit_stop )
        {
            hit_stop--;
        }
        else
        {
            if ( field_740 > 0 )
                field_740--;

            if ( field_4BC )
                field_4BC--;

            if (damage_limit)
            {
                if ( (get_seq() >= 197 && get_seq() <= 199) || (field_4C0 && !char_is_shock()) )
                {
                    damage_limit = 0;
                    field_4C0 = 0;
                }
            }

            if (field_4C0)
            {
                if (char_is_shock())
                    field_4C0 = 0;
                else
                    field_4C0--;
            }


            if ( field_51C )
                field_51C--;

            if ( field_51E )
                field_51E--;

            char_frame *frm = get_pframe();

            if ( frm->fflags & FF_UNK800)
                field_51E = 10;

            if ( field_520 )
                field_520--;

            if ( field_4AA )
                field_4AA--;

            if ( field_522 )
                field_522--;

            if ( field_6EC > 0 )
                field_6EC--;

            if ( field_524 > 0)
                field_524--;

            if ( field_526 > 0 )
                field_526--;


            if (cards_added >= 5)
            {
                current_card_energy = 0;
            }
            else if (current_card_energy >= 500 && controlling_type != 2 ) //HACK
            {
                add_card();
                scene_play_sfx(36);
                current_card_energy = 0;
            }

            sub_463200();
        }
    }
}

void char_c::spell_energy_spend(int32_t energy, int32_t stop_time)
{
    if ( get_seq() >= 500  && get_seq() < 600)
        if ( field_4C8 > 0 )
            energy >>= (field_4C8 - 1);

    spell_energy -= energy;

    if ( spell_energy < 0 )
        spell_energy = 0;

    if ( spell_energy_stop < stop_time )
        spell_energy_stop = stop_time;
}

void char_c::crash_spell_borders(int8_t num)
{
    for (int8_t i=0; i<num; i++)
        if (max_spell_energy > 0)
        {
            max_spell_energy -= 200;
            if (max_spell_energy < 0)
                max_spell_energy = 0;

            spell_energy = max_spell_energy;
            spell_energy_stop = 0;
            battle_ui_orbeffect(1, player_index, spell_energy / 200);
        }
}

void char_c::add_card_energy(int32_t energy)
{
    current_card_energy += field_54C * (float)energy;
}

void char_c::add_card_energy2(int32_t energy)
{
    if (controlling_type != 2)
        if (cards_added < card_slots)
        {
            current_card_energy += energy;
            if (current_card_energy > 500)
                current_card_energy = 500;
        }
}

void char_c::add_card()
{
    if ( (int32_t)cards_active.size() < card_slots )
        if (cards_shuffle.size())
        {
            current_card_energy = 0;

            s_card *card = cards_shuffle.front();
            cards_shuffle.pop_front();
            if (card)
                cards_active.push_back(card);
            cards_added = cards_active.size();
        }
}

void char_c::add_card(int32_t id)
{
    if ( (int32_t)cards_active.size() < card_slots )
    {
        s_card *crd = cards_get_card(&chr_cards, id);

        if (crd)
        {
            current_card_energy = 0;

            if (crd)
                cards_active.push_back(crd);
            cards_added = cards_active.size();
        }
    }
}

bool char_c::check_AB_pressed()
{
    if ( keyDown(INP_AB) == 1 && get_seq() < 600 )
    {
        set_keyDown(INP_AB, 4);
        //a1->pressed_AB = 4;
        //loop_active_cards(chr); //HACK?

        //code from loop_active_cards
        if (cards_active.size())
        {
            s_card *crd = cards_active.front();
            cards_active.pop_front();
            cards_active.push_back(crd);
        }

        return true;
    }
    return false;
}

void char_c::sub_4689D0(int32_t a2)
{
    if ( controlling_type != CONTROL_PC_STORY )
    {
        if ( current_card_energy >= a2 )
            current_card_energy -= a2;
        else
        {
            if ( cards_added <= 0 )
                current_card_energy = 0;
            else
            {
                current_card_energy += 500 - a2;

                if ( weather_id == WEATHER_SNOW )
                    weather_time_mul(3.0/4.0);

                scene_add_effect(this, 160, x, y + 100, dir, 1);
                sub_4684F0();
            }
        }
    }
}

void char_c::sub_4684F0()
{
    if ( !cards_active.empty() )
    {
        cards_active.pop_back();

        cards_added = cards_active.size();

        if (cards_added != 0)
            if (cards_active[0]->type == 255)
                max_health = cards_active[0]->cost;
    }
}

bool char_c::sub_468660(int8_t card)
{
    if ( cards_added > card )
    {
        int8_t num = 1;
        if ( cards_active[card]->cost - (weather_id == WEATHER_CLOUDY) >= 1)
            num = cards_active[card]->cost - (weather_id == WEATHER_CLOUDY);

        return cards_added >= num || (cards_added > 0 && weather_id == WEATHER_MOUNTAIN_VAPOR);
    }
    return false;
}

void char_c::sub_462FF0()
{
    char_frame *frm = get_pframe();
    if ( !(frm->fflags & FF_UNK100000) )
    {
        if ( damage_limit < 100 )
        {
            if ( health > 0 )
            {
                if ( !(char_on_ground() && field_4C4 == 0) )
                {
                    if ( field_4BA )
                    {
                        field_4BA--;
                    }
                    else
                    {
                        if ( input_function || controlling_type != 3 ) //HACK
                        {
                            if ( keyDown(INP_X_AXIS) )
                            {
                                if ( keyDown(INP_A) || keyDown(INP_B) || keyDown(INP_C) || keyDown(INP_D) )
                                {
                                    damage_limit = 0;
                                    flip_to_enemy();
                                    if (dX(dir) <= 0)
                                        set_seq(181);
                                    else
                                        set_seq(180);
                                }
                            }
                        }
                        else
                        {
                            //HACK
                            /*v3 = practice_params->dummy_tek;
                            if ( v3 )
                            {
                              v4 = v3 - 1;
                              if ( v4 )
                              {
                                if ( v4 == 1 )
                                {
                                  damage_limit = 0;
                                  flip_to_enemy(v1);
                                  v5 = meta.vtbl;
                                  v6 = get_MT_range(2u);
                                  v5->func2_set_seq(v1, v6 + 180);// random air tek
                                }
                              }
                              else
                              {
                                damage_limit = 0;
                                flip_to_enemy(v1);
                                meta.vtbl->func2_set_seq(v1, 181);
                              }
                            }
                            else
                            {
                              damage_limit = 0;
                              flip_to_enemy(v1);
                              meta.vtbl->func2_set_seq(v1, 180);
                            }
                            */
                        }
                    }
                }
            }
        }
    }
}

void char_c::sub_4834F0()
{
    if ( weather_id == WEATHER_BLUE_SKY || weather_id == WEATHER_HAIL || weather_id == WEATHER_SPRINKLE )
        weather_time_mul(0.9);
}

bool char_c::sub_469710()
{
    return get_seq() >= 197 && get_seq() < 200;
}

bool char_c::sub_469730()
{
    return get_seq() >= 95 && get_seq() < 100;
}

void char_c::sub_4873B0(int32_t seq, int32_t smt)
{
    if ( smt >= 10 )
        correction |= 8;

    set_seq(seq);
    //input_push_pressed_to_buf(chr); //HACK
    angZ = 0.0;
}

void char_c::sub_4834E0(int16_t next_stop_time)
{
    field_4A6 = next_stop_time;
}

void char_c::sub_469A20()
{
    if ( time_stop )
        time_stop--;

    if ( field_4A6 )
    {
        time_stop = field_4A6;
        field_4A6 = 0;
    }

    field_74C = 0.0;
    field_564 = 1.0;
    field_568 = 1.0;

    if ( health < 0 )
        health = 0;

    if ( health_prev < 0 )
        health_prev = 0;

    if ( health > max_health )
        health = max_health;

    if ( !char_is_shock() )
        health_prev = health;

    stand_gfx->update();

    if ( field_710 > 0 )
        field_710--;

    if ( field_526 )
        weather_id = WEATHER_CLEAR;
    else
        weather_id = weather_get();
    sub_468330();
}

void char_c::sub_46AB50(int8_t img, int16_t time)
{
    field_742 = img;
    field_740 = time;
    if ( enemy->field_740 != 0 || field_740 != 0 )
        scene_set_spell_img(player_index, spell_images[img]);
    else
    {
        scene_set_spell_img(0, spell_images[img]);
        scene_set_spell_img(1, spell_images[img]);
    }
}


void char_c::sub_463200()
{
    if ( !time_stop )
    {
        if ( max_spell_energy < 1000 )
        {
            if ( crshd_sp_brdrs_timer < 4800 )
            {
                if ( weather_id == WEATHER_SUNSHOWER )
                {
                    crshd_sp_brdrs_timer += 50;
                }
                else
                {
                    if ( max_spell_energy <= 800 )
                        crshd_sp_brdrs_timer +=  5;
                    if ( max_spell_energy <= 600 )
                        crshd_sp_brdrs_timer +=  2;
                    if ( max_spell_energy <= 400 )
                        crshd_sp_brdrs_timer +=  3;
                    if ( max_spell_energy <= 200 )
                        crshd_sp_brdrs_timer +=  8;
                    if ( max_spell_energy <= 0 )
                        crshd_sp_brdrs_timer +=  10;
                }
                if ( crshd_sp_brdrs_timer >= 4800 )
                {
                    battle_ui_orbeffect(2, player_index, spell_energy / 200);//HACK
                    max_spell_energy += 200;
                    crshd_sp_brdrs_timer = 0;
                }
            }
        }

        if ( spell_energy_stop )
        {
            spell_energy_stop--;
        }
        else
        {
            if ( weather_id == WEATHER_HAIL )
                spell_energy += 12;
            else
                spell_energy += 6;

            if ( field_560 >= 1 )
                if ( !(time_count_get() & 1) )
                    spell_energy++;

            if ( field_560 >= 2 )
            {
                if ( !(time_count_get() & 1) )
                    spell_energy++;

                if ( !(time_count_get() & 3) )
                    spell_energy++;
            }

            if ( field_560 >= 3 )
            {
                if ( !(time_count_get() & 1) )
                    spell_energy++;

                if ( !(time_count_get() & 3) )
                    spell_energy++;

                if ( !(time_count_get() % 6u) )
                    spell_energy++;
            }

            if ( field_560 >= 4 )
            {
                if ( !(time_count_get() & 1) )
                    spell_energy++;

                if ( !(time_count_get() & 3) )
                    spell_energy++;

                if ( !(time_count_get() % 6u) )
                    spell_energy++;

                if ( time_count_get() % 6u == 3 )
                    spell_energy++;
            }

            if (max_spell_energy < spell_energy)
                spell_energy = max_spell_energy;
        }
    }
}

void char_c::sub_4685C0(int /*a2*/)
{
    //HACK

//  char_c *v2; // esi@1
//  int v3; // eax@3
//  int v4; // ST08_4@5
//  int v5; // ST04_4@5
//  int v6; // ST00_4@5
//  int v7; // eax@5
//  added_card_stru *v8; // eax@6
//
//  v2 = a1;
//  if ( a1->cards_added )
//  {
//    if ( a2 )
//    {
//      v3 = a1->field_6F0;
//      if ( v3 >= 0 )
//        a1->field_6EC = v3;
//      v4 = get_added_card_by_id((def_deque *)&a1->cards_active, 0)->id;
//      v5 = v2->char_id;
//      v6 = v2->meta.enemy->char_id;
//      v7 = sub_43D120();
//      sub_42F060((void *)v7, v6, v5, v4);
//      stand_graph::show(&v2->stand_gfx);
//    }
//    v8 = get_added_card_by_id((def_deque *)&v2->cards_active, 0);
//    sub_435B70(&battle_manager->unks[v2->player_index], v8->id, a2);
//  }
}

void char_c::sub_46AC00()
{
    max_spell_energy = 1000;
    spell_energy = 1000;
    spell_energy_stop = 0;
    crshd_sp_brdrs_timer = 0;
    field_740 = 0;
}

void char_c::mountain_vapor_shuffle()
{
    int32_t sz = cards_active.size();
    if (sz)
    {
        for(int32_t i=0; i<sz; i++)
            cards_shuffle.push_front(cards_active[i]);

        cards_active.clear();

        shuffle_cards(&cards_shuffle);
        for(int32_t i=0; i<sz; i++)
            add_card();
    }
}

bool char_c::sub_489F10(uint16_t cprior)
{
    if ( keyDown(INP_X_AXIS) || keyDown(INP_Y_AXIS) )
    {
        if (cprior <= get_prior(690))
        {
            if (cards_active[0]->id >= 100 && cards_active[0]->id <= 199)
                if (seq299_300_field190_0_3())
                {
                    angZ = 0.0;
                    //input_push_pressed_to_buf(v3);
                    set_seq(690);
                    return true;
                }
        }
    }
    if ( cards_active[0]->id == 2 || cards_active[0]->id == 4 || cards_active[0]->id == 5 ||
            cards_active[0]->id == 6 || cards_active[0]->id == 10 || cards_active[0]->id == 14 ||
            cards_active[0]->id == 17 || cards_active[0]->id == 18 || cards_active[0]->id == 19 )
    {
        if ( cprior<= 0 && seq299_300_field190_0_3())
        {
            angZ = 0.0;
            field_7D0 = cards_active[0]->id;
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(691);
            sub_469450(0, 0, 60);
            sub_483570();
            scene_add_effect(this, 71, x, y + 100.0, dir, 1);
            return true;
        }
    }
    if ( cards_active[0]->id == 7 || cards_active[0]->id == 16 || cards_active[0]->id == 17 || cards_active[0]->id == 20 )
    {
        if ( cprior<= 50 && seq299_300_field190_0_3())
        {
            angZ = 0.0;
            field_7D0 = cards_active[0]->id;
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(691);
            sub_469450(0, 0, 60);
            sub_483570();
            scene_add_effect(this, 71, x, y + 100.0, dir, 1);
            return true;
        }
    }
    if ( cards_active[0]->id == 8 )
    {
        if ( cprior<= 50 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            field_7D0 = cards_active[0]->id;
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(697);
            sub_469450(0, 0, 60);
            sub_483570();
            return true;
        }
    }
    if ( cards_active[0]->id == 11 )
    {
        if ( cprior<= 50 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            field_7D0 = cards_active[0]->id;
            //input_push_pressed_to_buf(v3); //HACK?
            set_seq(698);
            sub_469450(0, 0, 60);
            sub_483570();
            scene_add_effect(this, 71, x, y + 100.0, dir, 1);
            return true;
        }
    }
    if ( cards_active[0]->id == 3 )
    {
        if ( cprior<= 50 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            field_7D0 = cards_active[0]->id;
            //input_push_pressed_to_buf(v3); //HACK?
            set_seq(200);
            spell_energy_spend(400, 300);
            sub_469450(0, 0, 60);
            sub_483570();
            scene_add_effect(this, 71, x, y + 100.0, dir, 1);
            field_836 = 1;
            return true;
        }
    }
    if ( cprior<= get_prior(696) && cards_active[0]->id == 13 )
        if (get_seq() >= 150 && get_seq() <= 157 && seq299_300_field190_0_3())
        {
            angZ = 0.0;
            sub_469450(0, 0, 60);
            sub_483570();
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(696);
            return true;
        }

    if ( field_83C == 0 && cards_active[0]->id == 12 && get_seq() < 150 && get_seq() > 158 && seq299_300_field190_0_3() )
    {
        //input_push_pressed_to_buf(v3); //HACK

        int32_t stp_tm = 160;
        if (cards_added > 0)
            for(int32_t i=0; i<cards_added; i++)
                if (cards_active[i]->id == 12)
                    stp_tm -= 20;

        if (stp_tm < 80)
            stp_tm = 80;
        spell_energy_spend(200, stp_tm);
        field_838 = 15.0;
        field_83C = 1;
        if ( get_seq() >= 154 && get_seq() <= 157 )
            scene_add_effect(this, 71, x, y + 50.0, dir, 1);
        else
            scene_add_effect(this, 71, x, y + 100.0, dir, 1);

        return true;
    }
    else
    {
        if ( cprior <= get_prior(695) && cards_active[0]->id == 0 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            //input_push_pressed_to_buf(v3); //HACK
            sub_469450(0, 0, 60);
            sub_483570();
            set_seq(695);
            return true;
        }
        if ( cprior > 50 )
            return false;

        if ( cards_active[0]->id == 1 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            sub_469450(0, 0, 60);
            sub_483570();
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(694);
            return true;
        }
        if ( cards_active[0]->id == 15 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            sub_469450(0, 0, 60);
            sub_483570();
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(693);
            return true;
        }

        if ( cards_active[0]->id == 9 && seq299_300_field190_0_3() )
        {
            angZ = 0.0;
            sub_469450(0, 0, 60);
            sub_483570();
            //input_push_pressed_to_buf(v3); //HACK
            set_seq(692);
            return true;
        }
        else
            return false;
    }
    return false;
}








stand_graph::stand_graph()
{
    tex = NULL;
    alpha = 0;
    disp_stage = -1;
    player = NULL;
    xpos = 0;
}

stand_graph::~stand_graph()
{
    if (tex)
        gr_delete_tex(tex);
}

void stand_graph::init(char_c *parent, const char *name)
{
    char buf[CHRBUF];
    sprintf(buf,"data/stand/cutin/%s.cv2",name);
    tex = gr_load_cv2(buf, NULL);
    gr_set_repeate(tex,true);
    player = parent;
}

void stand_graph::show()
{
    disp_stage = 0;
    xpos = -640.0;
    frames = 0;
    alpha = 128;
}

void stand_graph::update()
{
    int8_t last_stage = disp_stage;

    if ( last_stage >= 0 )
    {
        if ( last_stage == 1 )
        {
            if ( frames == 0)
                disp_stage = 2;
        }
        else if ( last_stage == 2 )
        {
            if ( alpha )
                alpha -= 2;
            else
                disp_stage = -1;
        }
        else if (last_stage == 0)
        {
            xpos = (sin_deg(frames * 3) - 1.0) * 480.0 - 64.0;

            if (player->player_index == 1)
                xpos = 640.0 - xpos;

            if ( frames == 30 )
                disp_stage = 1;
        }
        if ( last_stage == disp_stage )
            frames++;
        else
            frames = 0;
    }
}

void stand_graph::draw(int8_t plane)
{
    if (disp_stage >= 0)
    {
        gr_tex_box box;
        box.tex = tex;
        box.autosize = true;
        box.overlay_tex = false;
        box.x = xpos;
        box.y = 32.0;
        box.a = alpha;
        box.r = 255;
        box.g = 255;
        box.b = 255;
        box.skew_in_pix = false;
        box.skew_x = 0;
        box.skew_y = 0;
        box.tex_scl_x = 1.0 - 2.0 * (player->player_index == 1);
        box.tex_scl_y = 1.0;

        gr_draw_tex_box(&box, gr_alpha, plane);

    }
}
