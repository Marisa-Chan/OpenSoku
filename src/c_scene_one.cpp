#include "global_types.h"
#include "c_scene_one.h"
#include "input.h"
#include "character_def.h"
#include "chars.h"
#include "background.h"
#include "bullets.h"
#include "weather.h"

void c_scene_one::init(background *bg, char_c *p1, char_c *p2)
{
        bkg = bg;
    chrs[0] = p1;
    chrs[1] = p2;

    chrs[0]->x = 480;
    chrs[0]->y = 0;
    chrs[1]->x = 800;
    chrs[1]->y = 0;

    chrs[0]->dir = 1.0;
    chrs[1]->dir = -1.0;

    chrs[0]->enemy = chrs[1];
    chrs[1]->enemy = chrs[0];

    chrs[0]->player_index = 0;
    chrs[1]->player_index = 1;

    scn_p1[0] = 0;
    scn_p1[1] = 0;
    scn_p2[0] = 0;
    scn_p2[1] = 0;

    chrs[0]->init_vars();
    chrs[1]->init_vars();

    // chrs[1]->controlling_type = 3;

    set_camera(chrs[0],chrs[1]);
    func13(0);
}


int8_t c_scene_one::update()
{
    frames++;
    int32_t ret = 0;
    switch(cur_game_state)
    {
    case 0:
        ret = state0_update();
        break;
    case 1:
        ret = state1_update();
        break;
    case 2:
        ret = state2_update();
        break;
    case 3:
        ret = state3_update();
        break;
    case 5:
        ret = state5_update();
        break;
    case 6:
        ret = state6_update();
        break;
    case 7:
        ret = state7_update();
        break;
    default:
        ret = 0;
        break;
    }
    return ret;
}

int8_t c_scene_one::state0_update()
{
    scene_subfunc1();
  scene_check_collisions();
  scene_subfunc4();
  scene_subfunc5();
  if ( frames > 60 )
  {
    //play_music_(0); //HACK
    func13(1);
  }
  return 0;
}

int8_t c_scene_one::state1_update()
{
    func16();
  //sub_478D00(v2); //Zero input HACK
  scene_subfunc1();
  scene_check_collisions();
  scene_subfunc4();
  scene_subfunc5();
  //if ( field_8 )
    func13(2);
  return 0;
}

int8_t c_scene_one::state2_update()
{
    func16();
    scene_subfunc1();
    scene_subfunc2();
    scene_check_collisions();
    scene_subfunc4();
    scene_subfunc5();
    func12();
    return 0;
}

int8_t c_scene_one::state3_update()
{
  if ( frames > 120 || (frames & 3) == 0)
  {
    func16();
    //if ( frames > 120 )
      //sub_478D00(v2); //HACK ZERO ABCD INPUT
    scene_subfunc1();
    if ( chrs[0]->field_577 == 0|| chrs[1]->field_577 == 0)
      scene_subfunc2();
    scene_check_collisions();
    scene_subfunc4();
  }
  scene_subfunc5();
  if ( chrs[0]->field_577 && chrs[1]->field_577 )
    func13(1);

  return 0;
}

int8_t c_scene_one::state5_update()
{
  if ( frames > 180 || (frames & 3) == 0 )
  {
      func16();
    //if ( frames > 180 )
      //sub_478D00(v2); //HACK ZERO ABCD INPUT
    scene_subfunc1();
    scene_subfunc2();
    scene_check_collisions();
    scene_subfunc4();
  }
  scene_subfunc5();
  if ( frames > 360 )
  {
    /*if ( gameplay_type_get() == GAMEPLAY_REPLAY )
      return result;*/

      func13(6);
  }
  return 0;
}

int8_t c_scene_one::state6_update()
{
    func16();
  //sub_478D90(v2); //HACK ZERO ALL INPUT
  /*if ( battle_manager->field_494 < 30 ) //HACK
    ++battle_manager->field_494;
  if ( (char)((int (__thiscall *)(batman **))v2->battle_manager->pat_infoeffect.pat_objects.vtbl)(&v2->battle_manager) <= 0 )
    ((void (__thiscall *)(c_scene *, signed int))v2->base.vtbl->scene_func_13)(v2, 7);*/
    func13(7);//HACK
  scene_subfunc1();
  scene_check_collisions();
  scene_subfunc4();
  scene_subfunc5();
  return 0;
}

int8_t c_scene_one::state7_update()
{
    return 1;
}


void c_scene_one::func11(char_c *pl)
{
    if ( game_type_get() != GAME_TYPE_TRAINING)
        pl->field_574 = 1;
}

void c_scene_one::func12()
{
  if ( chrs[0]->field_574 )
  {
    if ( chrs[1]->field_574 )
    {
      chrs[0]->win_count++;
      chrs[1]->win_count++;
      field_904 = 2;
      if ( chrs[0]->win_count == chrs[1]->win_count )
      {
        chrs[1]->win_count = 1;
        chrs[0]->win_count = 1;
        func13(3);
      }
      else
      {
        if ( chrs[0]->win_count == 2 )
          chrs[1]->field_576 = 1;
        else
            chrs[0]->field_576 = 1;

        func13(5);
      }
    }
    else
    {
      chrs[1]->win_count++;
      if ( chrs[1]->win_count == 2 )
      {
        chrs[0]->field_576 = 1;
        field_904 = 2;
        func13(5);
      }
      else
      {
          field_904++;
          func13(3);
      }
    }
  }
  else
  {
    if ( chrs[1]->field_574 )
    {
      chrs[0]->win_count++;
      if ( chrs[0]->win_count == 2 )
      {
        chrs[1]->field_576 = 1;
        field_904 = 2;
        func13(5);
      }
      else
      {
        field_904++;
        func13(3);
      }
    }
  }
}



void c_scene_one::func13(int32_t val)
{
    cur_game_state = val;
    switch(val)
    {
    case 1:
    chrs[0]->health = chrs[0]->max_health;
    chrs[1]->health = chrs[1]->max_health;
    case 3:
        for(int8_t i=0; i< 2; i++)
            chrs[i]->field_577 = chrs[i]->field_574 == 0;
        printf("DOWN\n");
        break;
    case 5:
        for(int8_t i=0; i< 2; i++)
            if (chrs[i]->win_count >= 2)
                chrs[i]->field_577 = chrs[i]->field_574 == 0;
        printf("Knock Out\n");
        break;
    default:
        break;
    }
    frames = 0;
}

void c_scene_one::func14()
{
    c_scene::func14();
}

void c_scene_one::func15()
{
    if ( cur_game_state == 2 ) //HACK
    {
        if ( weather_get() == WEATHER_CLEAR )
        {
            weather_time_add(1);
            if ( weather_index_for_name_get() == WEATHER_CLEAR && weather_time_get() >= 0 )
                weather_forecast_set((WEATHER_ID)scene_rand_rng(20));

            else if ( weather_time_get() >= 999 )
            {
                weather_time_set(999);
                weather_change(weather_index_for_name_get(), true);

                switch ( weather_get() )
                {
                case WEATHER_SPRING_HAZE:
                case WEATHER_TEMPEST:
                    weather_time_mul(0.5);
                    break;
                case WEATHER_SUNSHOWER:
                case WEATHER_RIVER_MIST:
                case WEATHER_TYPHOON:
                    weather_time_mul(0.75);
                    break;
                default:
                    break;
                }
            }
        }
        else
        {
            if (time_count_get() & 1)
                weather_time_sub(1);

            if ( weather_time_get() <= 0 )
            {
                weather_time_set(0);
                weather_change(WEATHER_CLEAR, true);
            }
        }
    }
    c_scene::func15();
}

void c_scene_one::func16()
{

}
