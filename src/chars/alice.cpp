#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../character_def.h"
#include "../scene.h"
#include "../bullets.h"
#include "alice.h"

char_alice::char_alice(inp_ab *func, uint8_t pal):
	char_c::char_c(func)
{
	char_id = CHAR_ID_ALICE;
	pgp->load_dat("alice",pal);
	char_loadsfx("alice");
	cards_load_cards(&chr_cards,"alice");
	load_face("alice");
}

c_bullet *char_alice::new_bullet()
{
	c_bullet *tmp = new alice_bullets();
	return tmp;
}


void char_alice::func10()
{
	int32_t sq = get_seq();

	x_delta = 0;
	y_delta = 100;

	if ( controlling_type == CONTROL_PC_STORY )
	{
		if ( cards_added > 0 )
		{
			switch ( cards_active[0]->id )
			{
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
			case 5:
			case 6:
			case 7:
			case 8:
			case 9:
			case 10:
			case 11:
				field_4AA = 2;
				field_534 = 0.25;
				field_55C = 2.0;
				field_538 = 0.0;
				field_86A = 1;
				if ( get_pframe()->extra1[4] == 1 )
				{
					field_86A = 3;
					field_55C = 3.0;
				}
				if ( get_pframe()->extra1[4] == 2 )
				{
					field_86A = 3;
					field_55C = 6.0;
				}
				break;
			case 12:
			case 13:
			case 14:
			case 15:
				field_4AA = 2;
				field_534 = 0.5;
				field_55C = 2.0;
				field_538 = 0.0;
				field_86A = 1;
				if ( get_pframe()->extra1[4] == 1 )
				{
					field_86A = 3;
					field_55C = 3.0;
				}
				if ( get_pframe()->extra1[4] == 2 )
				{
					field_86A = 3;
					field_55C = 6.0;
				}
				break;
			default:
				break;
			}
		}
		if ( field_882 == 1 )
		{
			if ( field_188 >= max_health && !field_574 )
			{
				field_86A = 2;
				field_882 = 2;
				flip_with_force();
				set_seq( 149);
				scene_add_effect(this, 53, x, y + 100.0, dir, 1);
				if ( cards_added >= 1 && cards_active[0]->id <= 11 )
				{
					field_884 = 300;
					field_886 = 300;
				}
			}
			if ( health <= 0 )
				field_882 = 2;
		}
		if ( field_884 > 0 )
		{
			if ( damage_limit > 0 && damage_limit < 100 )
				damage_limit = 0;

			if ( field_884 == 1 || health <= 0 )
			{
				field_4AA = 0;
				field_884 = 0;
				field_4BA = 0;
				field_188 = 0;
				field_820 = 0;
				field_81E = 1;
				field_81A = 0;
				field_81C = 0;
				field_818 = 0;
				field_882 = 1;
				if (health > 0 )
				{
					float tmp[3];
					tmp[0] = 0.0;
					tmp[1] = 0.0;
					tmp[2] = 0.0;
					addbullet(this, NULL, 1201, 180.0, 130.0, 1, 2, tmp, 3);
				}
			}
			else
			{
				field_86A = 2;
				field_4AA = 2;
				field_538 = 1.0;
				field_534 = 1.0;
				field_884--;
				field_4BA = 6000;
			}
		}
		if ( health <= 0 )
			field_86A = 0;
	}

	if ( char_is_shock() )
		field_8BC[0] = 0;
	field_898++;
	if ( field_898 >= 360 )
		field_898 = 0;
	if ( health <= 0 )
	{
		field_890[0] = 0;
		field_890[1] = 0;
	}
	if ( sq > 149 && sq < 159 )
	{
		if ( !bbarrier_show )
		{
			bbarrier_show = 1;
			if ( sq > 149 && sq < 154 )
				addbullet(this, NULL, 998, (60 * dir) + x, y + 110.0, dir, 1, 0, 0);
			if ( sq > 153 && sq < 158 )
				addbullet(this, NULL, 998, (60 * dir) + x, y + 60.0, dir, 1, 0, 0);
			if ( sq == 158 )
				addbullet(this, NULL, 998, (60 * dir) + x, y + 100.0, dir, 1, 0, 0);
		}
	}

	if ( hit_stop != 0 /*|| enemy->time_stop != 0 */)
		return;

	switch(sq)
	{
	case 0:
		sub10func();
		if (h_inerc == 0)
			field_49A = 0;
		stopping(0.5);
		process();
		break;
	case 1:
		sub10func();
		stopping(0.5);
		if (process() && get_frame() == 0)
			set_seq(2);
		break;
	case 2:
		sub10func();
		stopping(0.5);
		process();
		break;
	case 3:
		sub10func();
		stopping(0.5);
		if (process() && get_frame() == 0)
			set_seq(0);
		break;
	case 4:
		sub10func();
		char_h_move( 6.0);
		process();
		break;
	case 5:
		sub10func();
		char_h_move( -6.0);
		process();
		break;
	case 6:
		if (get_subseq() == 0)
		{
			sub10func();
			if (field_49A == 0)
				reset_forces();
		}
		if (get_subseq()>0)
		{
			v_inerc -=v_force;

			if (char_on_ground_down())
			{
				set_seq(10);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}
		process();

		if (get_subseq() == 1 && get_frame_time() == 0 &&
				get_frame() == 0 && get_elaps_frames() == 0)
		{
			v_inerc = 15.0;
			v_force = 0.65;
			field_49A = 0;
		}
		break;
	case 7:
		if (get_subseq() == 0)
		{
			sub10func();
			if (field_49A == 0)
				reset_forces();
		}

		if (get_subseq()>0)
		{
			v_inerc -=v_force;

			if (char_on_ground_down())
			{
				set_seq(10);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}

		process();

		if (get_subseq() == 1 && get_frame_time() == 0 &&
				get_frame() == 0 && get_elaps_frames() == 0)
		{
			char_h_move( 5.0);
			v_inerc = 15.0;
			v_force = 0.65;
			field_49A = 0;
		}
		break;
	case 8:
		if (get_subseq() == 0)
		{
			sub10func();
			if (field_49A == 0)
				reset_forces();
		}

		if (get_subseq()>0)
		{
			v_inerc -=v_force;

			if (char_on_ground_down())
			{
				set_seq(10);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}

		process();

		if (get_subseq()       == 1 &&
				get_frame_time()   == 0 &&
				get_frame()        == 0 &&
				get_elaps_frames() == 0)
		{
			v_inerc = 15.0;
			v_force = 0.65;
			char_h_move( -5.0);
			field_49A = 0;
		}
		break;
	case 9:
		if (v_force == 0)
			v_force = 0.6;

		v_inerc -=v_force;

		if (char_on_ground_down())
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
			break;
		}

		process();
		break;
	case 10:
		sub10func();
		reset_forces();
		if (process())
		{
			if (input->gY() < 0)
				set_seq(2);
			else
				set_seq(0);
		}
		break;
	case 197:
		sub10func();
		if ( process() )
		{
			if ( controlling_type == CONTROL_PC_STORY )
			{
				set_seq(700);
				field_51C = 3;
				field_520 = 3;
				break;
			}
			else
			{
				set_seq(0);
				if ( gY() < 0 )
					set_seq( 1);
			}
		}
		if ( get_frame_time() == 0 )
		{
			if (get_frame() == 8)
				reset_forces();
			else if (get_frame() == 13)
			{
				if (enemy->x < x)
					dir = -1;
				else
					dir = 1;
			}
		}
		break;

	case 198:
		sub10func();
		if ( process() )
		{
			if ( controlling_type == CONTROL_PC_STORY )
			{
				set_seq(700);
				field_51C = 3;
				field_520 = 3;
				break;
			}
			else
			{
				set_seq(0);
				if ( gY() < 0 )
					set_seq( 1);
			}
		}
		if ( get_frame_time() == 0 )
		{
			if (get_frame() == 8)
				reset_forces();
			else if (get_frame() == 13)
			{
				if (enemy->x < x)
					dir = -1;
				else
					dir = 1;
			}
		}
		break;

	case 199:
		sub10func();
		if ( process() )
		{

			if ( controlling_type == CONTROL_PC_STORY )
			{
				set_seq(700);
				field_51C = 3;
				field_520 = 3;
				break;
			}
			else
			{
				set_seq(0);
				if ( gY() < 0)
					set_seq(1);
			}
		}
		if ( get_frame_time() == 0  && get_frame() == 5)
		{
			if (enemy->x < x)
				dir = -1;
			else
				dir = 1;
		}
		break;

	case 200:
		sub10func();
		field_49A = 1;
		if ( h_inerc > 9.0 )
		{
			h_inerc -= 0.5;
			if ( h_inerc < 9.0 )
				h_inerc = 9.0;
		}
		process();
		if ( get_subseq() == 0 && get_frame() == 2 && get_frame_time() == 0 )
		{
			char_h_move( 10.0);
			scene_add_effect(this, 125, (80 * dir) + x, y + 80.0, dir, 1);
			scene_add_effect(this, 126, x, y + 80.0, dir, 1);
			scene_play_sfx(31);
		}
		else if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 5 == 0 )
			{
				float yy = (scene_rand() % 200) + y;
				float xx = x + 50.0 - (scene_rand() % 100);
				scene_add_effect(this, 124, xx, yy, dir, 1);
			}
			if ( gY() <= 0 )
			{
				field_7D0++;

				if ( (gX(dir) <= 0 && field_7D0 > 5) || field_7D0 > 45 )
					set_seq( 204);
			}
			else
			{
				if ( gX(dir) <= 0 )
					set_seq(211);
				else
					set_seq(212);
			}
		}
		break;

	case 201:
		if ( get_subseq() == 0 && get_frame() <= 1 )
			sub10func();

		if ( get_subseq() == 3 )
		{
			sub10func();
			h_inerc += 2.0;
			if ( h_inerc > 0.0 )
				h_inerc = 0.0;
		}
		if ( char_on_ground_flag() == 0 && get_elaps_frames() % 5 == 0 )
		{
			float yy = (scene_rand() % 200) + y;
			float xx = x + 50.0 - (scene_rand() % 100);
			scene_add_effect(this, 124, xx, yy, -dir, 1);
		}
		if ( get_subseq() < 3 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				v_inerc = 0.0;
				y = getlvl_height();
				set_subseq( 3);
				break;
			}
		}
		if ( process() )
		{
			set_seq( 0);
			h_inerc = 0.0;
		}
		else
		{
			if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
			{
				char_h_move( -10.0);
				v_inerc = 4.5;
				v_force = 0.6;
				scene_add_effect(this, 125, x, y + 80.0, -dir, 1);
				scene_add_effect(this, 126, x, y + 80.0, -dir, 1);
				scene_play_sfx(31);
			}
		}
		break;

	case 202:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			reset_forces();
			y = getlvl_height();
			set_seq( 10);
			break;
		}
		if ( get_subseq() == 1 || get_subseq() == 2 )
			if ( get_elaps_frames() % 5 == 0 )
			{
				float yy = (scene_rand() % 200) + y;
				float xx = x + 50.0 - (scene_rand() % 100);
				scene_add_effect(this, 124, xx, yy, dir, 1);
			}
		process();
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
		{
			field_7D0 = 0;
			char_h_move( 8.5);
			v_inerc = 5.0;
			v_force = 0.6;
			scene_add_effect(this, 125, (80 * dir) + x, y + 110.0, dir, 1);
			scene_add_effect(this, 126, x, y + 110.0, dir, 1);
			scene_play_sfx(31);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
			flip_with_force();
		break;

	case 203:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			reset_forces();
			y = getlvl_height();
			//get_frame_time() = 0; //CHECKME
			set_seq( 10);
		}
		else
		{
			if ( get_subseq() < 3 && get_elaps_frames() % 5 == 0 )
			{
				float yy = (scene_rand() % 200) + y;
				float xx = x + 50.0 - (scene_rand() % 100);
				scene_add_effect(this, 124, xx, yy, -dir, 1);
			}
			process();
			if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 1 )
			{
				char_h_move( -8.5);
				v_inerc = 5.0;
				v_force = 0.6;
				scene_add_effect(this, 125, x, y + 120.0, -dir, 1);
				scene_add_effect(this, 126, x, y + 120.0, -dir, 1);
				scene_play_sfx(31);
			}
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
				flip_with_force();
		}
		break;

	case 204:
		sub10func();
		h_inerc -= 0.5;
		if ( h_inerc < 0.0 )
		{
			h_inerc = 0.0;
			field_49A = 0;
		}
		if ( process() )
		{
			set_seq( 0);
			field_49A = 0;
		}
		break;

	case 208:
		if ( get_subseq() == 0 )
			sub10func();
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
		}
		else
		{
			if ( char_on_ground_flag() || v_inerc > 0.0 )
				field_522 = 2;
			if ( get_subseq() > 0 )
			{
				v_inerc -= v_force;
				if ( v_inerc < -20.0 )
					v_inerc = -20.0;
			}
			process();
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			{
				char_h_move( 0.0);
				v_inerc = 19.0;
				v_force = 0.65;
				field_49A = 0;
				scene_add_effect(this, 63, x, y, dir, 1);
			}
		}
		break;

	case 209:
	case 212:
	case 221:
		if ( get_subseq() == 0 )
			sub10func();
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
		}
		else
		{
			if ( char_on_ground_flag() || v_inerc > 0.0 )
				field_522 = 2;
			if ( get_subseq() > 0 )
			{
				v_inerc -= v_force;
				if ( v_inerc < -20.0 )
					v_inerc = -20.0;
			}
			process();
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			{
				char_h_move(9.0);
				v_inerc = 15.0;
				v_force = 0.65;
				field_49A = 0;
				scene_add_effect(this, 63, x, y, dir, 1);
			}
		}
		break;

	case 210:
	case 222:
		if ( get_subseq() == 0 )
			sub10func();
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
		}
		else
		{
			if ( char_on_ground_flag() || v_inerc > 0.0 )
				field_522 = 2;
			if ( get_subseq() > 0 )
			{
				v_inerc -= v_force;
				if ( v_inerc < -20.0 )
					v_inerc = -20.0;
			}
			process();
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			{
				char_h_move(-9.0);
				v_inerc = 15.0;
				v_force = 0.65;
				field_49A = 0;
				scene_add_effect(this, 63, x, y, dir, 1);
			}
		}
		break;

	case 211:
		if ( get_subseq() == 0 )
			sub10func();
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
		}
		else
		{
			if ( char_on_ground_flag() || v_inerc > 0.0 )
				field_522 = 2;
			if ( get_subseq() > 0 )
			{
				v_inerc -= v_force;
				if ( v_inerc < -20.0 )
					v_inerc = -20.0;
			}
			process();
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			{
				char_h_move(2.0);
				v_inerc = 19.0;
				v_force = 0.65;
				field_49A = 0;
				scene_add_effect(this, 63, x, y, dir, 1);
			}
		}
		break;

	case 214:
		if ( process() )
		{
			set_seq( 9);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if ( get_subseq() == 1 )
				scene_play_sfx(31);
			if (get_subseq() == 6 )
			{
				set_seq( 9);
				break;
			}
		}
		if ( input->gY() > 0)
		{
			field_7D2 = 90 - input->gX(dir) * 45;
		}
		else if (input->gY() == 0)
		{
			if (input->gX(dir) > 0 )
				field_7D2 = 0;
			else if (input->gX(dir) < 0 )
				field_7D2 = 180;
		}
		else if (input->gY() < 0)
		{
			field_7D2 = -90 - input->gX(dir) * 45;
		}

		if ( get_subseq() == 5 || get_subseq() == 6 )
			v_inerc -= v_force;

		if ( get_subseq() <= 0 || get_subseq() >= 5 )
		{
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				v_force = 0.0;
				v_inerc = 0.0;
				if ( get_subseq() >= 5 )
				{
					set_seq( 10);
					reset_forces();
				}
				else
				{
					reset_ofs();
					set_seq( 215);
				}
			}
			break;
		}
		field_7D6++;
		field_7D4 = field_7D2 - dash_angle;
		if ( field_7D4 >180 )
			field_7D4 -= 360;
		else if (field_7D4 < -180)
			field_7D4 += 360;

		if ( field_7D4 > 0 )
		{
			if ( weather_id != WEATHER_SUNNY )
				dash_angle += 0.5;
			else
				dash_angle += 1.5;
		}
		else if ( field_7D4 < 0 )
		{
			if ( weather_id != WEATHER_SUNNY )
				dash_angle -= 0.5;
			else
				dash_angle -= 1.5;
		}
		h_inerc = cos_deg(dash_angle) * field_7DC;
		v_inerc = sin_deg(dash_angle) * field_7DC;

		if ( y > 680.0 )
			if ( v_inerc > 0.0 )
				v_inerc = 0.0;

		field_7DC += 0.3;
		if ( field_7DC > 12.0 )
			field_7DC = 12.0;

		spell_energy_spend( weather_id != WEATHER_SUNNY ? 10 : 5, 1);
		angZ = -dash_angle;


		if ( h_inerc < 0.0 )
			angZ = 180.0 - dash_angle;


		if ( h_inerc < 0.0 )
		{
			if ( get_subseq() == 1 )
				set_subseq(3);
			else if ( get_subseq() == 2 )
				set_subseq(4);
		}
		else
		{
			if ( get_subseq() == 3 )
				set_subseq(1);
			else if ( get_subseq() == 4 )
				set_subseq(2);
		}

		if ( get_elaps_frames() % 5 == 1 )
		{
			float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
			float xx = cos_deg(dash_angle) * 100.0 * dir + x;
			scene_add_effect(this, 125, xx, yy, dir, 1);
		}

		if ( (keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
		{
			reset_ofs();
			angZ = 0;

			if ( get_subseq() == 1 || get_subseq() == 2 )
			{
				if ( dir == 1 )
				{
					if ( enemy->x >= x )
						set_subseq(5);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(6);
					}
				}
				else
				{
					if ( enemy->x <= x )
						set_subseq(5);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(6);
					}
				}
			}
			else if ( get_subseq() == 3 || get_subseq() == 4 )
			{
				if ( dir == 1 )
				{
					if ( enemy->x >= x )
						set_subseq(6);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(5);
					}
				}
				else
				{
					if ( enemy->x <= x )
						set_subseq(6);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(5);
					}
				}
			}
		}
		break;

	case 215:
		sub10func();
		if ( h_inerc > 0.0 )
		{
			h_inerc -= 0.75;
			if ( h_inerc < 0.0 )
				h_inerc = 0.0;
		}
		if ( h_inerc < 0.0 )
		{
			h_inerc += 0.75;
			if ( h_inerc > 0.0 )
				h_inerc = 0.0;
		}
		if ( process() )
			set_seq( 0);

		break;

	case 217:
		if ( process() )
		{
			set_seq( 9);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if ( get_subseq() == 1 )
				scene_play_sfx(31);
			if (get_subseq() == 6 )
			{
				set_seq( 9);
				break;
			}
		}

		field_7D2 = atan2_deg(enemy->y + 100.0 - y, (enemy->x - x) * dir);

		if ( get_subseq() == 5 || get_subseq() == 6 )
			v_inerc -= v_force;

		if ( get_subseq() <= 0 || get_subseq() >= 5 )
		{
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				v_force = 0.0;
				v_inerc = 0.0;
				if ( get_subseq() >= 5 )
				{
					set_seq( 10);
					reset_forces();
				}
				else
				{
					reset_ofs();
					set_seq( 215);
				}
			}
			break;
		}

		field_7D6++;
		field_7D4 = field_7D2 - dash_angle;
		if ( field_7D4 >180 )
			field_7D4 -= 360;
		else if (field_7D4 < -180)
			field_7D4 += 360;

		if ( field_7D4 > 0 )
		{
			if ( weather_id != WEATHER_SUNNY )
				dash_angle += 0.25;
			else
				dash_angle += 0.75;
		}
		else if ( field_7D4 < 0 )
		{
			if ( weather_id != WEATHER_SUNNY )
				dash_angle -= 0.25;
			else
				dash_angle -= 0.75;
		}

		h_inerc = cos_deg(dash_angle) * field_7DC;
		v_inerc = sin_deg(dash_angle) * field_7DC;

		if ( y > 680.0 )
			if ( v_inerc > 0.0 )
				v_inerc = 0.0;

		field_7DC += 0.3;
		if ( field_7DC > 12.0 )
			field_7DC = 12.0;

		if (weather_id == WEATHER_SUNNY)
			spell_energy_spend(10, 1);
		else
			spell_energy_spend(15, 60);

		angZ = -dash_angle;

		if ( h_inerc < 0.0 )
		{
			if ( get_subseq() == 1 )
				set_subseq(3);
			else if ( get_subseq() == 2 )
				set_subseq(4);
		}

		if ( h_inerc >= 0 )
		{
			if ( get_subseq() == 3 )
				set_subseq(1);
			else if ( get_subseq() == 4 )
				set_subseq(2);
		}

		if ( get_elaps_frames() % 5 == 1 )
		{
			float yy = sin_deg(dash_angle) * 100.0 + y + 100.0;
			float xx = cos_deg(dash_angle) * 100.0 * dir + x;
			scene_add_effect(this, 125, xx, yy, dir, 1);
		}

		if ( (keyDown(INP_D) == 0 && field_7D6 > 10) || spell_energy <= 0 )
		{
			reset_ofs();

			if ( get_subseq() == 1 || get_subseq() == 2 )
			{
				if ( dir == 1 )
				{
					if ( enemy->x >= x )
						set_subseq(5);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(6);
					}
				}
				else
				{
					if ( enemy->x <= x )
						set_subseq(5);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(6);
					}
				}
			}
			else if ( get_subseq() == 3 || get_subseq() == 4 )
			{
				if ( dir == 1 )
				{
					if ( enemy->x >= x )
						set_subseq(6);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(5);
					}
				}
				else
				{
					if ( enemy->x <= x )
						set_subseq(6);
					else
					{
						dir = -dir;
						h_inerc = -h_inerc;
						set_subseq(5);
					}
				}
			}
		}
		break;

	case 220:
		if ( get_subseq() == 0 )
			sub10func();
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
			break;
		}
		if ( char_on_ground_flag() || v_inerc > 0.0 )
			field_522 = 2;
		if ( get_subseq() > 0 )
		{
			v_inerc -= v_force;
			if ( v_inerc < -20.0 )
				v_inerc = -20.0;
		}
		process();
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			char_h_move( 0.0);
			v_inerc = 19.0;
			v_force = 0.65;
			field_49A = 0;
			scene_add_effect(this, 63, x, y, dir, 1);
		}
		break;

	case 223:
		sub10func();
		field_49A = 1;
		process();
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 5 == 0 )
			{
				float yy = (scene_rand() % 200) + y;
				float xx = x + 50.0 - (scene_rand() % 100);
				scene_add_effect(this, 124, xx, yy, dir, 1);
			}
			field_7D0++;
			if ( (gX(dir) <= 0 && field_7D0 >= 13) || field_7D0 > 45 )
				set_seq( 204);
		}
		if ( get_subseq() == 0 && get_frame() == 4 && get_frame_time() == 0 )
		{
			char_h_move( 5.0);

			scene_add_effect(this, 125, (80 * dir) + x, y + 80.0, dir, 1);
			scene_add_effect(this, 126, x, y + 80.0, dir, 1);
			scene_play_sfx(31);
		}
		break;

	case 224:
		if ( get_subseq() == 0 && get_frame() <= 0 )
			sub10func();
		if ( get_subseq() == 3 )
		{
			sub10func();
			h_inerc += 2.0;
			if ( h_inerc > 0.0 )
				h_inerc = 0.0;
		}
		if ( !char_on_ground_flag() && get_elaps_frames() % 5 == 0 )
		{
			float yy = (scene_rand() % 200) + y;
			float xx = x + 50.0 - (scene_rand() % 100);
			scene_add_effect(this, 124, xx, yy, -dir, 1);
		}
		if ( get_subseq() < 3 && char_on_ground_down() )
		{
			v_inerc -= v_force;
			if (char_on_ground_down())
			{
				v_inerc = 0.0;
				y = getlvl_height();
				set_subseq( 3);
			}
			break;
		}

		if ( process() )
		{
			set_seq( 0);
			h_inerc = 0.0;
		}
		else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
		{
			char_h_move( -10.0);
			v_inerc = 4.5;
			v_force = 0.6;
			scene_add_effect( this, 125, x, y + 80.0, -dir, 1);
			scene_add_effect( this, 126, x, y + 80.0, -dir, 1);
			scene_play_sfx(31);
		}
		break;

	case 225:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			reset_forces();
			y = getlvl_height();
			set_seq( 10);
			break;
		}
		if ( get_subseq() == 1 || get_subseq() == 2 )
			if ( get_elaps_frames() % 5 == 0 )
			{
				float yy = (scene_rand() % 200) + y;
				float xx = x + 50.0 - (scene_rand() % 100);
				scene_add_effect(this, 124, xx, yy, -dir, 1);
			}
		if ( process() )
			set_seq( 9);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			char_h_move( -8.5);
			v_inerc = 5.0;
			v_force = 0.6;
			scene_add_effect( this, 125, x, y + 120.0, -dir, 1);
			scene_add_effect( this, 126, x, y + 120.0, -dir, 1);
			scene_play_sfx(31);
		}
		break;

	case 226:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			reset_forces();
			y = getlvl_height();
			set_seq( 10);
		}
		else
		{
			if ( get_subseq() == 1 || get_subseq() == 2 )
				if ( get_elaps_frames() % 5 == 0 )
				{
					float yy = (scene_rand() % 200) + y;
					float xx = x + 50.0 - (scene_rand() % 100);
					scene_add_effect(this, 124, xx, yy, dir, 1);
				}
			if ( process() )
				set_seq( 9);
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
			{
				if ( get_subseq() == 1 )
				{
					field_7D0 = 0;
					char_h_move( 8.5);
					v_inerc = 5.0;
					v_force = 0.6;
					scene_add_effect(this, 125, (80 * dir) + x, y + 110.0, dir, 1);
					scene_add_effect(this, 126, x, y + 110.0, dir, 1);
					scene_play_sfx(31);
				}
				if ( get_subseq() == 3 )
					flip_with_force();
			}
		}
		break;

	case 300:
	case 330:
		sub10func();
		//if ( !get_true(0) ) //CHECKME
		{
			if ( field_49A )
			{
				h_inerc -= 0.5;
				if ( h_inerc < 0.0 )
				{
					h_inerc = 0.0;
					field_49A = 0;
				}
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame_time() == 0 && get_frame() == 2 )
			{
				scene_play_sfx(27);
				field_49A = 0;
			}
		}
		break;

	case 301:
		sub10func();
		//if ( !get_true(0) ) //CHECKME
		{
			if ( field_49A )
			{
				h_inerc -= 0.5;
				if ( h_inerc < 0.0 )
				{
					h_inerc = 0.0;
					field_49A = 0;
				}
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame_time() == 0 && get_frame() == 2 )
			{
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 1.0;
				addbullet(this, NULL, 849, (30 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			}
		}
		break;

	case 302:
		sub10func();
		/*if ( get_true(1) )
		  break; */  //CHECKME
		if ( field_49A )
		{
			h_inerc -= 0.5;
			if ( h_inerc < 0.0 )
			{
				h_inerc = 0.0;
				field_49A = 0;
			}
		}
		if ( keyDown(INP_A) == 0)
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			if ( not_charge_attack )
			{
				scene_add_effect(this, 62, x - (20 * dir), y + 120.0, dir, 1);
				next_subseq();
			}
			else
			{
				scene_play_sfx(29);
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 8.0;
				addbullet(this, NULL, 849, (110 * dir) + x, y + 105.0, dir, 1, tmp, 3);
			}
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_subseq() == 1 )
		{
			if (get_frame() == 0 )
				set_seq( 0);
			else if (get_frame() == 1)
			{
				scene_play_sfx(29);
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 26.0;
				addbullet(this, NULL, 849, (110 * dir) + x, y + 105.0, dir, 1, tmp, 3);
			}
		}
		break;

	case 303:
		sub10func();
		//if ( !get_true(0) ) //CHECKME
		{
			if ( field_49A > 0 || h_inerc > 0.0 )
			{
				h_inerc -= 0.6;
				if ( h_inerc < 0.0 )
				{
					h_inerc = 0.0;
					field_49A = 0;
				}
			}
			if ( process() )
				set_seq( 2);
			if ( get_frame_time() == 0 )
			{
				if ( get_frame() == 2 )
					h_inerc = 6.0;
				if ( get_frame() == 3 )
					scene_play_sfx(28);
			}
		}
		break;

	case 304:
		sub10func();
		//if ( !get_true(1) ) //CHECKME
		{
			if ( h_inerc > 0.0 )
			{
				h_inerc -= 1.0;
				if ( h_inerc < 0.0 )
					h_inerc = 0.0;
			}
			if ( get_frame() >= 4 && get_frame() <= 6 )
			{
				if ( field_7D0 % 4 == 0 && field_7D2 <= 4 )
				{
					float tmp[3];
					tmp[0] = -10.0 - field_7D2 * 13.0;
					tmp[1] = 20.0;
					tmp[2] = 11.0;
					addbullet(this, NULL, 849, x + 30.0, y + 100.0, dir, 1, tmp, 3);
					field_7D2++;
				}
				field_7D0++;
			}
			if ( process() )
				set_seq( 2);
		}
		break;

	case 305:
		sub10func();
		//if ( !get_true(1) ) //CHECKME
		{
			if ( get_frame() > 3 )
			{
				h_inerc -= 0.75;
				if ( h_inerc < 0.0 )
					h_inerc = 0.0;
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame_time() == 0 && get_frame() == 2 )
				scene_play_sfx(29);
		}
		break;

	case 306:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
		}
		else
		{
			if ( process() )
				set_seq( 9);
			if ( get_frame_time() == 0 && get_frame() == 4 )
				scene_play_sfx(27);
		}
		break;

	case 307:
		if ( get_subseq() == 1 )
		{
			sub10func();
		}
		else
		{
			if ( get_frame() >= 11 )
				v_inerc -= v_force;
			if ( char_on_ground_down() /*&& get_frame() >= 0 */) //CHECKME
			{
				set_subseq( 1);
				reset_forces();
				y = getlvl_height();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			set_seq( 9);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			scene_play_sfx(29);
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 16.0;
			addbullet(this, NULL, 849, (50 * dir) + x, y + 140.0, dir, 1, tmp, 3);
		}
		break;

	case 308:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			set_seq(10);
			y = getlvl_height();
			reset_forces();
		}
		else
		{
			if ( process() )
				set_seq( 9);
			if ( get_subseq() == 0)
			{
				if ( get_frame_time() == 0 && get_frame() == 4 )
					for (int32_t i = 0; i < 6; i++)
					{
						float tmp[3];
						tmp[0] = -i * 60.0;
						tmp[1] = 13.0;
						tmp[2] = 17.0;

						addbullet(this, NULL, 849, (25 * dir) + x, y + 95.0, dir, 1, tmp, 3);
						field_7D2++;
					}
				if ( get_frame_time() == 0 && get_frame() == 5 )
				{
					h_inerc = -4.0;
					v_inerc = 8.0;
				}
				if ( get_frame_time() == 0 &&  get_frame() == 7 )
					scene_play_sfx(29);
			}
			if ( get_subseq() == 1 && get_frame_time() == 0 )
				field_190 = 0;
		}
		break;

	case 309:
		if ( get_subseq() == 4 )
			sub10func();
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				set_subseq( 4);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
			for (int32_t i = 0; i < 6; i++)
			{
				float tmp[3];
				tmp[0] = -i * 60.0;
				tmp[1] = 13.0;
				tmp[2] = 24.0;

				addbullet(this, NULL, 849, (30 * dir) + x, y + 120.0, dir, 1, tmp, 3);
				field_7D2++;
			}
		if ( get_subseq() == 1 && get_frame_time() == 0 && get_frame() == 1 )
			scene_play_sfx(29);
		if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 4 )
			v_force = 0.5;
		if ( get_frame_time() == 0 && get_subseq() == 1 )
			field_190 = 0;
		break;

	case 310:
		if ( field_190 )
		{
			field_7D0++;
			if ( field_7D0 > 5 )
			{
				field_190 = 0;
				field_7D0 = 0;
			}
		}
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() == 0 )
				h_inerc = 15.0;
			if ( get_elaps_frames() % 8 == 0 )
				scene_play_sfx(27);
			if ( field_190 )
			{
				field_7D0++;
				if ( field_7D0 > 5 )
				{
					field_190 = 0;
					field_7D0 = 0;
				}
			}
			if ( get_elaps_frames() > 30 )
			{
				next_subseq();
				v_inerc = 6.0;
				h_inerc *= 0.5;
			}
		}
		if ( get_subseq() == 2 )
		{
			v_inerc -= v_force;
			if ( getlvl_height() >= v_inerc + y )
			{
				v_inerc = 0.0;
				y = getlvl_height();
				set_seq( 9);
				break;
			}
		}
		if ( process() )
			set_seq( 9);
		break;

	case 320:
		sub10func();
		//if ( !get_true(0) ) //CHECKME
		{
			if ( get_frame() > 1 )
			{
				h_inerc -= 2.0;
				if ( h_inerc < 0.0 )
					h_inerc = 0.0;
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame_time() == 0 && get_frame() == 2 )
			{
				scene_play_sfx(28);
				field_49A = 0;
			}
		}
		break;

	case 321:
		sub10func();
		//if ( !get_true(0) ) //CHECKME
		{
			if ( get_frame() > 3 )
			{
				h_inerc -= 1.0;
				if ( h_inerc < 0.0 )
					h_inerc = 0.0;
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame_time() == 0 && get_frame() == 3 )
			{
				scene_play_sfx(28);
				h_inerc = 10.0;
				field_49A = 0;
			}
		}
		break;

	case 322:
		sub10func();
		//if ( !get_true(1) ) //CHECKME
		{
			h_inerc -= 1.5;
			if ( h_inerc < 0.0 )
				h_inerc = 0.0;
			if ( keyDown(INP_A) == 0 )
				not_charge_attack = 0;
			if ( process() )
				set_seq( 0);
			if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			{
				set_seq( 0);
				break;
			}
			if (get_subseq() == 0 && get_frame_time() == 0)
			{
				if (get_frame() == 7)
				{
					if (not_charge_attack == 1)
					{
						next_subseq();
						scene_add_effect(this, 62, x - (33 * dir), y + 112.0, dir, -1);
						break;
					}
					else
						h_inerc = 15;
				}

				if (get_frame() == 9)
				{
					scene_play_sfx(29);
					field_49A = 0;
				}
			}
			if (get_subseq() == 1 && get_frame_time() == 0)
			{
				if (get_frame() == 11)
					h_inerc = 19.0;
				else if (get_frame() == 12)
					scene_play_sfx(29);
			}
		}
		break;

	case 400:
		sub10func();
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);

		if ( get_elaps_frames() == 0  && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float tmp[3];
			tmp[0] = -74.0;
			tmp[1] = 25.0;
			tmp[2] = 7.0;

			addbullet(this, NULL, 803,x - 74*dir, y + 104, dir, 1,tmp,3 );
			play_sfx(2);
			field_190 = 1;
			spell_energy_spend( 200, 45);
			add_card_energy( 30);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq(0);
		else if ((get_subseq() == 2 && get_elaps_frames() >= 20) ||
				 (get_subseq() == 4 && get_elaps_frames() >= 25) ||
				 (get_subseq() == 6 && get_elaps_frames() >= 40))
			next_subseq();
		break;

	case 401:
		sub10func();
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( process() )
			set_seq(0);
		if ( get_elaps_frames() == 0  && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float tmp[3];
			tmp[0] = -74;
			tmp[1] = 40;
			tmp[2] = 0;

			addbullet(this, NULL, 803,x - 74*dir, y + 104, dir, 1,tmp,3 );
			play_sfx(2);
			field_190 = 1;
			spell_energy_spend( 200, 45);
			add_card_energy( 30);
		}

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq(0);
		else if ((get_subseq() == 2 && get_elaps_frames() >= 30) ||
				 (get_subseq() == 4 && get_elaps_frames() >= 25) ||
				 (get_subseq() == 6 && get_elaps_frames() >= 45))
			next_subseq();
		break;

	case 402:
		sub10func();
		if ( process() )
			set_seq( 2);
		if ( get_frame_time() == 0 && get_frame() == 4 )
		{
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 7.0;

			addbullet(this, NULL, 801, (20 * dir) + x, y + 90.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 45);
			field_190 = 1;
			add_card_energy( 30);
		}
		break;

	case 404:
		if ( get_subseq() == 8 )
			sub10func();
		if ( get_subseq() == 3 || get_subseq() == 7 )
			v_inerc -= v_force;
		if ( char_on_ground_down() && get_subseq() <= 7 )
		{
			set_subseq( 8);
			y = getlvl_height();
			reset_forces();
			break;
		}
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
		{
			float tmp[3];
			tmp[0] = -74.0;
			tmp[1] = 25.0;
			tmp[2] = 7.0;
			addbullet(this, NULL, 803, x - (74 * dir), y + 104.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 45);
			field_190 = 1;
			add_card_energy( 30);
		}
		if ( get_elaps_frames() == 0 )
		{
			if ( get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			{
				set_seq( 9);
				break;
			}
			if ( get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 8 )
				set_seq( 9);
		}

		if ((get_subseq() == 2 && get_elaps_frames() >= 20) ||
				(get_subseq() == 4 && get_elaps_frames() >= 25) ||
				(get_subseq() == 6 && get_elaps_frames() >= 40))
			next_subseq();
		break;

	case 405:
		if ( get_subseq() == 8 )
			sub10func();
		if ( get_subseq() == 3 || get_subseq() == 7 )
			v_inerc -= v_force;
		if ( char_on_ground_down() && get_subseq() <= 7 )
		{
			set_subseq( 8);
			y = getlvl_height();
			reset_forces();
			break;
		}
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
		{
			float tmp[3];
			tmp[0] = -74.0;
			tmp[1] = 40.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 803, x - (74 * dir), y + 104.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 45);
			field_190 = 1;
			add_card_energy( 30);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if (get_subseq() == 4)
			{
				set_seq( 9);
				break;
			}
			else if ( get_subseq() == 8 )
				set_seq( 9);
		}
		if ((get_subseq() == 2 && get_elaps_frames() >= 30) ||
				(get_subseq() == 4 && get_elaps_frames() >= 25) ||
				(get_subseq() == 6 && get_elaps_frames() >= 40))
			next_subseq();
		break;

	case 406:
		if ( get_subseq() == 8 )
			sub10func();
		if ( get_subseq() == 3 || get_subseq() == 7 )
			v_inerc -= v_force;
		if ( char_on_ground_down() && get_subseq() <= 7 )
		{
			set_subseq( 8);
			y = getlvl_height();
			reset_forces();
			break;
		}
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1)
		{
			float tmp[3];
			tmp[0] = -74.0;
			tmp[1] = 25.0;
			tmp[2] = 7.0;
			addbullet(this, NULL, 803, x - (74 * dir), y + 104.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 45);
			field_190 = 1;
			add_card_energy( 30);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if (get_subseq() == 4)
			{
				set_seq( 9);
				break;
			}
			else if ( get_subseq() == 8 )
				set_seq( 9);
		}
		if ((get_subseq() == 2 && get_elaps_frames() >= 20) ||
				(get_subseq() == 4 && get_elaps_frames() >= 25) ||
				(get_subseq() == 6 && get_elaps_frames() >= 40))
			next_subseq();
		break;

	case 408:
		sub10func();
		//if ( !get_true(1) ) //CHECKME
		{
			if ( get_frame() >= 6 )
				h_inerc -= 0.5;
			if ( h_inerc < 0.0 )
			{
				h_inerc = 0.0;
				field_49A = 0;
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame_time() == 0 && get_frame() == 4 )
			{
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 19.0;
				addbullet(this, NULL, 849, (30 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			}
		}
		break;

	case 409:
		v_inerc -= v_force;
		if ( char_on_ground_down() )
		{
			set_seq( 10);
			reset_forces();
			y = getlvl_height();
		}
		else if ( process() )
			set_seq( 9);
		break;

	case 410:
		sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			float tmp[3];
			tmp[0] = -45.0;
			tmp[1] = 40.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 805, (5 * dir) + x, y + 108.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 60);
			add_card_energy( 30);
			field_190 = 1;
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			if ( !not_charge_attack )
				set_seq( 0);
			else
				scene_add_effect(this, 62, x - (66 * dir), y + 148.0, dir, 1);
		}
		break;

	case 411:
		sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 40.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 805, (5 * dir) + x, y + 108.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 60);
			add_card_energy( 30);
			field_190 = 1;
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			if ( !not_charge_attack )
				set_seq( 0);
			else
				scene_add_effect(this, 62, x - (66 * dir), y + 148.0, dir, 1);
		}
		break;

	case 412:
		sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 10 )
			h_inerc = 0.0;

		if ( process() )
			set_seq( 0);

		if (get_subseq() == 0 && get_frame_time() == 0)
		{
			if (get_frame() == 9)
			{
				float tmp[3];
				tmp[0] = -80.0;
				tmp[1] = 40.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 805, (5 * dir) + x, y + 108.0, dir, 1, tmp, 3);
				play_sfx( 2);
				field_190 = 1;
				spell_energy_spend(200, 60);
				add_card_energy( 30);
				break;
			}
			else if (get_frame() == 10)
				h_inerc = 34.0;
		}

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			if ( not_charge_attack )
				scene_add_effect(this, 62, x - (66 * dir), y + 148.0, dir, 1);
			else
				set_seq( 0);
		}
		break;

	case 414:
		if ( get_subseq() == 2 )
			sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 && get_frame() >= 12 )
			v_inerc -= v_force;

		if ( ( (get_subseq() == 0 || get_subseq() == 1) && get_frame() >= 12) && char_on_ground_down() )
		{
			set_subseq(2);
			y = getlvl_height();
			reset_forces();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			float tmp[3];
			tmp[0] = 45.0;
			tmp[1] = 40.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 805, (20 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 60);
			field_190 = 1;
			add_card_energy( 30);
		}
		else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 11 && not_charge_attack == 1 )
		{
			scene_add_effect(this, 62, x - (47 * dir), y + 185.0, dir, 1);
			next_subseq();
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 &&
				  (get_subseq() == 1 || get_subseq() == 2 ))
			set_seq( 9);
		break;

	case 415:
		if ( get_subseq() == 2 )
			sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 && get_frame() >= 12 )
			v_inerc -= v_force;
		if ( ( (get_subseq() == 0 || get_subseq() == 1) && get_frame() >= 12) && char_on_ground_down() )
		{
			set_subseq(2);
			y = getlvl_height();
			reset_forces();
			break;
		}

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 40.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 805, (20 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 60);
			field_190 = 1;
			add_card_energy( 30);
		}
		else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 11 && not_charge_attack == 1 )
		{
			scene_add_effect(this, 62, x - (47 * dir), y + 185.0, dir, 1);
			next_subseq();
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 &&
				  (get_subseq() == 1 || get_subseq() == 2 ))
			set_seq( 9);
		break;

	case 416:
		if ( get_subseq() == 2 )
			sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 && get_frame() >= 12 )
			v_inerc -= v_force;

		if ( ( (get_subseq() == 0 || get_subseq() == 1) && get_frame() >= 12) && char_on_ground_down() )
		{
			set_subseq(2);
			y = getlvl_height();
			reset_forces();
			break;
		}

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 5 )
		{
			float tmp[3];
			tmp[0] = 80.0;
			tmp[1] = 40.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 805, (20 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 60);
			field_190 = 1;
			add_card_energy( 30);
		}
		else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 8 && not_charge_attack == 1 )
		{
			scene_add_effect(this, 62, x - (47 * dir), y + 185.0, dir, 1);
			next_subseq();
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 &&
				  (get_subseq() == 1 || get_subseq() == 2 ))
			set_seq( 9);
		break;

	case 418:
		sub10func();
		//if ( !get_true(1) ) //CHECKME
		{
			h_inerc -= 0.35;
			if ( h_inerc < 0.0 )
			{
				h_inerc = 0.0;
				field_49A = 0;
			}
			if ( process() )
				set_seq( 0);
			if ( get_frame() == 2 || get_frame() == 4)
			{
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 21.0;
				addbullet(this, NULL, 849, x, y + 50.0, dir, -1, tmp, 3);
				scene_play_sfx(29);
			}
			if ( get_frame() == 3 || get_frame() == 5)
			{
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 23.0;
				addbullet(this, NULL, 849, x, y + 50.0, dir, 1, tmp, 3);
				scene_play_sfx(29);
			}
		}
		break;

	case 419:
		sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			float tmp[3];
			tmp[0] = -180.0;
			tmp[1] = 35.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 805, (45 * dir) + x, y + 108.0, dir, 1, tmp, 3);
			play_sfx( 2);
			spell_energy_spend(200, 60);
			add_card_energy( 30);
			field_190 = 1;
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			set_seq( 0);
		break;

	case 500:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			field_190 = 1;
			float tmp[3];
			tmp[0] = 20.0;
			tmp[1] = 30.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 810, (8 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 3);
			spell_energy_spend(200, 120);
			add_card_energy( 30);
		}
		break;

	case 501:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			field_190 = 1;
			float tmp[3];
			tmp[0] = -5.0;
			tmp[1] = 30.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 810, (8 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 3);
			spell_energy_spend(200, 120);
			add_card_energy( 30);
		}
		break;

	case 505:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 7 )
		{
			field_190 = 1;
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 25.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 811, (8 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 10);
			spell_energy_spend(200, 120);
			add_card_energy( 30);
		}
		break;

	case 506:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 7 )
		{
			field_190 = 1;
			float tmp[3];
			tmp[0] = -45.0;
			tmp[1] = 25.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 811, (8 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 10);
			spell_energy_spend(200, 120);
			add_card_energy( 30);
		}
		break;

	case 507:
		if ( get_subseq() == 3 )
			sub10func();

		if ( get_subseq() <= 3 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				reset_forces();
				y = getlvl_height();
				set_subseq( 3);
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 5 )
		{
			h_inerc = -5.0;
			v_inerc = 5.0;
			v_force = 0.5;
		}
		else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 25.0;
			tmp[2] = 0.0;
			field_190 = 1;
			addbullet(this, NULL, 811, (17 * dir) + x, y + 104.0, dir, 1, tmp, 3);
			play_sfx( 10);
			spell_energy_spend(200, 120);
			add_card_energy( 30);
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
			set_seq( 9);
		break;

	case 508:
		if ( get_subseq() == 3 )
			sub10func();

		if ( get_subseq() <= 3 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				reset_forces();
				y = getlvl_height();
				set_subseq( 3);
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 5 )
		{
			h_inerc = -5.0;
			v_inerc = 5.0;
			v_force = 0.5;
		}
		else if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			float tmp[3];
			tmp[0] = 45.0;
			tmp[1] = 25.0;
			tmp[2] = 0.0;
			field_190 = 1;
			addbullet(this, NULL, 811, (17 * dir) + x, y + 104.0, dir, 1, tmp, 3);
			play_sfx( 10);
			spell_energy_spend(200, 120);
			add_card_energy( 30);
		}
		else if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
			set_seq( 9);
		break;

	case 510:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float t = 4.0;
			if ( skills_1[8] >= 2 )
				t = 5.0;
			if ( skills_1[8] >= 4 )
				t = 6.0;

			for (int32_t i=0; i < t; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / t;
				tmp[1] = 0;
				tmp[2] = 0;
				tmp[3] = 0;

				int ord = sin_deg(-tmp[0]) <= 0.0 ? 0 : 1;

				addbullet(this, NULL, 812, x, y + 120.0, dir, (1 - 2 * ord), tmp, 4);
			}
			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 511:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float t = 4.0;
			if ( skills_1[8] >= 2 )
				t = 5.0;
			if ( skills_1[8] >= 4 )
				t = 6.0;

			for (int32_t i=0; i < t; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / t;
				tmp[1] = 0;
				tmp[2] = 0;
				tmp[3] = 1;

				int ord = sin_deg(-tmp[0]) <= 0.0 ? 0 : 1;

				addbullet(this, NULL, 812, x, y + 120.0, dir, (1 - 2 * ord), tmp, 4);
			}
			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 512:
		if ( get_subseq() == 4 )
			sub10func();
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() && get_subseq() == 3 )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 4);
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float t = 4.0;
			if ( skills_1[8] >= 2 )
				t = 5.0;
			if ( skills_1[8] >= 4 )
				t = 6.0;

			for (int32_t i=0; i < t; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / t;
				tmp[1] = 0;
				tmp[2] = 0;
				tmp[3] = 0;

				int ord = sin_deg(-tmp[0]) <= 0.0 ? 0 : 1;

				addbullet(this, NULL, 812, x, y + 120.0, dir, (1 - 2 * ord), tmp, 4);
			}
			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
			v_force = 0.5;
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		break;

	case 513:
		if ( get_subseq() == 4 )
			sub10func();
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() && get_subseq() == 3 )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 4);
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float t = 4.0;
			if ( skills_1[8] >= 2 )
				t = 5.0;
			if ( skills_1[8] >= 4 )
				t = 6.0;

			for (int32_t i=0; i < t; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / t;
				tmp[1] = 0;
				tmp[2] = 0;
				tmp[3] = 1;

				int ord = sin_deg(-tmp[0]) <= 0.0 ? 0 : 1;

				addbullet(this, NULL, 812, x, y + 120.0, dir, (1 - 2 * ord), tmp, 4);
			}
			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 520:
		if ( get_subseq() == 0 || get_subseq() == 4 || get_subseq() == 8 )
			sub10func();
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 || get_subseq() == 2 || get_subseq() == 3 || get_subseq() == 5 || get_subseq() == 6 || get_subseq() == 7 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 8);
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 && not_charge_attack == 1 )
		{
			set_subseq( 4);
			scene_add_effect(this, 62, x - (4 * dir), y + 116.0, dir, -1);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			h_inerc = -7.5;
			v_inerc = 12.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
		{
			h_inerc = -6.0;
			v_inerc = 17.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
		{
			switch ( skills_1[1] )
			{
			case 0:
				field_7D2 = 3;
				break;
			case 1:
			case 2:
				field_7D2 = 4;
				break;
			case 3:
			case 4:
				field_7D2 = 5;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) + 20.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6 )
		{
			switch ( skills_1[1]  )
			{
			case 0:
				field_7D2 = 4;
				break;
			case 1:
			case 2:
				field_7D2 = 5;
				break;
			case 3:
			case 4:
				field_7D2 = 6;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) + 30.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}
		break;

	case 521:
		if ( get_subseq() == 0 || get_subseq() == 4 || get_subseq() == 8 )
			sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 || get_subseq() == 2 || get_subseq() == 3 || get_subseq() == 5 || get_subseq() == 6 || get_subseq() == 7 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 8);
				break;
			}
		}

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 && not_charge_attack == 1 )
		{
			set_subseq( 4);
			scene_add_effect(this, 62, x - (4 * dir), y + 116.0, dir, -1);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			h_inerc = -7.5;
			v_inerc = 12.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
		{
			h_inerc = -6.0;
			v_inerc = 17.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
		{
			switch ( skills_1[1] )
			{
			case 0:
				field_7D2 = 3;
				break;
			case 1:
			case 2:
				field_7D2 = 4;
				break;
			case 3:
			case 4:
				field_7D2 = 5;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) - 30.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6 )
		{
			switch ( skills_1[1]  )
			{
			case 0:
				field_7D2 = 4;
				break;
			case 1:
			case 2:
				field_7D2 = 5;
				break;
			case 3:
			case 4:
				field_7D2 = 6;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) - 10.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}
		break;

	case 522:
		if ( get_subseq() == 8 )
			sub10func();
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 || get_subseq() == 2 || get_subseq() == 3 || get_subseq() == 5 || get_subseq() == 6 || get_subseq() == 7 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 8);
				break;
			}
		}

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 && not_charge_attack == 1 )
		{
			set_subseq( 4);
			scene_add_effect(this, 62, x - (4 * dir), y + 116.0, dir, -1);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			h_inerc = -7.5;
			v_inerc = 12.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
		{
			h_inerc = -6.0;
			v_inerc = 17.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
		{
			switch ( skills_1[1] )
			{
			case 0:
				field_7D2 = 3;
				break;
			case 1:
			case 2:
				field_7D2 = 4;
				break;
			case 3:
			case 4:
				field_7D2 = 5;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) + 20.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6 )
		{
			switch ( skills_1[1]  )
			{
			case 0:
				field_7D2 = 4;
				break;
			case 1:
			case 2:
				field_7D2 = 5;
				break;
			case 3:
			case 4:
				field_7D2 = 6;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) + 30.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}
		break;

	case 523:
		if ( get_subseq() == 8 )
			sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 || get_subseq() == 2 || get_subseq() == 3 || get_subseq() == 5 || get_subseq() == 6 || get_subseq() == 7 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 8);
				break;
			}
		}

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 && not_charge_attack == 1 )
		{
			set_subseq( 4);
			scene_add_effect(this, 62, x - (4 * dir), y + 116.0, dir, -1);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			h_inerc = -7.5;
			v_inerc = 12.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
		{
			h_inerc = -6.0;
			v_inerc = 17.5;
			v_force = 0.7;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 2 )
		{
			switch ( skills_1[1] )
			{
			case 0:
				field_7D2 = 3;
				break;
			case 1:
			case 2:
				field_7D2 = 4;
				break;
			case 3:
			case 4:
				field_7D2 = 5;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) - 30.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 6 )
		{
			switch ( skills_1[1]  )
			{
			case 0:
				field_7D2 = 4;
				break;
			case 1:
			case 2:
				field_7D2 = 5;
				break;
			case 3:
			case 4:
				field_7D2 = 6;
				break;
			default:
				break;
			}
			field_190 = 1;
			add_card_energy( 50);
			for ( int32_t i = 0; i < field_7D2; i++ )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(45) - 10.0;
				tmp[1] = 15.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 815, (14 * dir) + x, y + 111.0, dir, 1, tmp, 3);
			}
			play_sfx( 5);
			spell_energy_spend(200, 120);
		}
		break;

	case 525:
		sub10func();
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 && get_elaps_frames() > 15 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0)
		{
			if ( get_frame() == 8 && not_charge_attack == 1 )
			{
				next_subseq();
				scene_add_effect(this, 62, x - (33 * dir), y + 112.0, dir, -1);
				break;
			}
			if ( get_frame() == 10 )
			{
				float t = 4;
				if ( skills_1[5] >= 3 )
					t = 5;
				if ( skills_1[5] >= 4 )
					t = 6;

				for (int32_t i=0; i < t; i++)
				{
					float tmp[3];
					tmp[0] = scene_rand_rng(80) * 0.1 + 2.0;
					tmp[1] = scene_rand_rng(70) * 0.1 + 21.0;
					tmp[2] = 0;

					addbullet(this, NULL, 816, (124 * dir) + x, y + 100.0, dir, 1, tmp, 3);
				}

				play_sfx( 3);
				field_190 = 1;
				spell_energy_spend(200, 120);
				add_card_energy( 50);
			}
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			set_seq( 0);
			break;
		}
		if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
		{
			float t = 5;
			if ( skills_1[5] >= 6 )
				t = 5;
			if ( skills_1[5] >= 7 )
				t = 6;

			for (int32_t i=0; i < t; i++)
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(80) * 0.1 + 2.0;
				tmp[1] = scene_rand_rng(70) * 0.1 + 21.0;
				tmp[2] = 0;

				addbullet(this, NULL, 816, (124 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			}

			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 526:
		sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( get_subseq() == 1 && get_elaps_frames() > 15 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0)
		{
			if ( get_frame() == 8 && not_charge_attack == 1 )
			{
				next_subseq();
				scene_add_effect(this, 62, x - (33 * dir), y + 112.0, dir, -1);
				break;
			}
			if ( get_frame() == 10 )
			{
				float t = 4;
				if ( skills_1[5] >= 3 )
					t = 5;
				if ( skills_1[5] >= 4 )
					t = 6;

				for (int32_t i=0; i < t; i++)
				{
					float tmp[3];
					tmp[0] = scene_rand_rng(60) * 0.1 + 9.0;
					tmp[1] = scene_rand_rng(70) * 0.1 + 21.0;
					tmp[2] = 0;

					addbullet(this, NULL, 816, (124 * dir) + x, y + 100.0, dir, 1, tmp, 3);
				}

				play_sfx( 3);
				field_190 = 1;
				spell_energy_spend(200, 120);
				add_card_energy( 50);
			}
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			set_seq( 0);
			break;
		}
		if ( get_subseq() == 2 && get_frame_time() == 0 && get_frame() == 2 )
		{
			float t = 5;
			if ( skills_1[5] >= 3 )
				t = 6;
			if ( skills_1[5] >= 4 )
				t = 7;

			for (int32_t i=0; i < t; i++)
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(60) * 0.1 + 9.0;
				tmp[1] = scene_rand_rng(70) * 0.1 + 21.0;
				tmp[2] = 0;

				addbullet(this, NULL, 816, (124 * dir) + x, y + 100.0, dir, 1, tmp, 3);
			}

			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 530:
		sub10func();
		if ( !keyDown(INP_B) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			float tmp[3];
			tmp[0] = 3.0;
			tmp[1] = 5.0;
			tmp[2] = 0;
			addbullet(this, NULL, 817, x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 40);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 531:
		sub10func();
		if ( !keyDown(INP_C) )
			not_charge_attack = 0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			float tmp[3];
			tmp[0] = 3.0;
			tmp[1] = 5.0;
			tmp[2] = 9.0;
			addbullet(this, NULL, 817, x, y + 100.0, dir, 1, tmp, 3);
			play_sfx( 40);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 540:
		sub10func();
		if ( get_subseq() == 2 && get_elaps_frames() >= 20 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			field_190 = 1;
			add_card_energy( 50);
			float tmp[4];
			tmp[0] = 4.0;
			tmp[1] = 15.0;
			tmp[2] = 0.0;
			tmp[3] = 10.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = -4.0;
			tmp[1] = 15.0;
			tmp[2] = 0.0;
			tmp[3] = 5.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 8.0;
			tmp[1] = 14.0;
			tmp[2] = 0.0;
			tmp[3] = 15.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = -8.0;
			tmp[1] = 14.0;
			tmp[2] = 0.0;
			tmp[3] = 0.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 0);
		break;

	case 541:
		sub10func();
		if ( get_subseq() == 2 && get_elaps_frames() >= 20 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			field_190 = 1;
			add_card_energy( 50);
			float tmp[4];
			tmp[0] = 5.0;
			tmp[1] = 17.0;
			tmp[2] = 0.0;
			tmp[3] = 0.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 10.0;
			tmp[1] = 17.0;
			tmp[2] = 0.0;
			tmp[3] = 5.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 5.0;
			tmp[1] = 12.0;
			tmp[2] = 0.0;
			tmp[3] = 10.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 10.0;
			tmp[1] = 12.0;
			tmp[2] = 0.0;
			tmp[3] = 15.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 0);
		break;

	case 542:
		if ( get_subseq() == 8 )
			sub10func();
		if ( get_subseq() == 2 && get_elaps_frames() >= 20 )
		{
			v_force = 0.5;
			next_subseq();
			break;
		}
		if ( get_subseq() == 3 || get_subseq() == 7 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				set_subseq( 8);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			field_190 = 1;
			add_card_energy( 50);
			float tmp[4];
			tmp[0] = 4.0;
			tmp[1] = 15.0;
			tmp[2] = 0.0;
			tmp[3] = 10.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = -4.0;
			tmp[1] = 15.0;
			tmp[2] = 0.0;
			tmp[3] = 5.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 8.0;
			tmp[1] = 14.0;
			tmp[2] = 0.0;
			tmp[3] = 15.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = -8.0;
			tmp[1] = 14.0;
			tmp[2] = 0.0;
			tmp[3] = 0.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && (get_subseq() == 4 || get_subseq() == 8))
			set_seq( 9);
		break;

	case 543:
		if ( get_subseq() == 8 )
			sub10func();
		if ( get_subseq() == 2 && get_elaps_frames() >= 20 )
		{
			v_force = 0.5;
			next_subseq();
			break;
		}
		if ( get_subseq() == 3 || get_subseq() == 7 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				set_subseq( 8);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			field_190 = 1;
			add_card_energy( 50);
			float tmp[4];
			tmp[0] = 5.0;
			tmp[1] = 17.0;
			tmp[2] = 0.0;
			tmp[3] = 0.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 10.0;
			tmp[1] = 17.0;
			tmp[2] = 0.0;
			tmp[3] = 5.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 5.0;
			tmp[1] = 12.0;
			tmp[2] = 0.0;
			tmp[3] = 10.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
			tmp[0] = 10.0;
			tmp[1] = 12.0;
			tmp[2] = 0.0;
			tmp[3] = 15.0;
			addbullet(this, NULL, 820, x, y + 120.0, dir, -1, tmp, 4);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && (get_subseq() == 4 || get_subseq() == 8))
			set_seq( 9);
		break;

	case 545:
		sub10func();
		if ( get_subseq() == 1 || get_subseq() == 2 )
			if (get_elaps_frames() % 7 == 0 )
				if ( field_7D0 <= 4 )
				{
					float tmp[3];
					tmp[0] = (scene_rand() % 110) - 60.0;
					tmp[1] = (scene_rand() % 170) + 10.0;
					tmp[2] = 0.0;
					if ( scene_rand_rng(100) > 50 )
						field_7D2 = -1;
					else
						field_7D2 = 1;
					float yy = y + tmp[1];
					float xx = dir * tmp[0] + x;
					addbullet(this, NULL, 821, xx, yy, dir, field_7D2, tmp, 3);
					field_7D0++;
				}
		if ( get_subseq() == 2 && (int32_t)get_elaps_frames() >= 43 - 3 * skills_1[6] )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if (get_subseq() == 1)
			{
				spell_energy_spend(200, 120);
				add_card_energy( 50);
			}
			if (get_subseq() == 4)
			{
				set_seq( 0);
				break;
			}
		}
		break;

	case 546:
		sub10func();
		if ( get_subseq() == 1 )
			if (get_elaps_frames() % 7 == 0 )
				if ( field_7D0 <= skills_1[6] + 4 )
				{
					float tmp[3];
					tmp[0] = (scene_rand() % 110) - 60.0;
					tmp[1] = (scene_rand() % 170) + 10.0;
					tmp[2] = 0.0;
					if ( scene_rand_rng(100) > 50 )
						field_7D2 = -1;
					else
						field_7D2 = 1;
					float yy = y + tmp[1];
					float xx = dir * tmp[0] + x;
					addbullet(this, NULL, 821, xx, yy, dir, field_7D2, tmp, 3);
					field_7D0++;
				}

		if ( get_subseq() == 1 && (int32_t)get_elaps_frames() >= 50 + 4 * skills_1[6] )
		{
			next_subseq();
			h_inerc = 0.0;
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			h_inerc = 5.0;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 547:
		if ( get_subseq() == 4 )
			sub10func();
		if ( get_subseq() == 1 || get_subseq() == 2 )
			if (get_elaps_frames() % 7 == 0 )
				if ( field_7D0 <= 6 )
				{
					float tmp[3];
					tmp[0] = (scene_rand() % 110) - 60.0;
					tmp[1] = (scene_rand() % 170) + 10.0;
					tmp[2] = 0.0;
					if ( scene_rand_rng(100) > 50 )
						field_7D2 = -1;
					else
						field_7D2 = 1;
					float yy = y + tmp[1];
					float xx = dir * tmp[0] + x;
					addbullet(this, NULL, 821, xx, yy, dir, field_7D2, tmp, 3);
					field_7D0++;
				}

		if ( get_subseq() == 2 && get_elaps_frames() >= 20 )
		{
			next_subseq();
			break;
		}
		if ( get_subseq() <= 2 )
			v_inerc -= 0.1;
		if ( get_subseq() == 3 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				reset_forces();
				y = getlvl_height();
				next_subseq();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		break;

	case 548:
		if ( get_subseq() == 4 )
			sub10func();
		if ( get_subseq() == 1 || get_subseq() == 2 )
			if (get_elaps_frames() % 7 == 0 )
				if ( field_7D0 <= 10 )
				{
					float tmp[3];
					tmp[0] = (scene_rand() % 110) - 60.0;
					tmp[1] = (scene_rand() % 170) + 10.0;
					tmp[2] = 0.0;
					if ( scene_rand_rng(100) > 50 )
						field_7D2 = -1;
					else
						field_7D2 = 1;
					float yy = y + tmp[1];
					float xx = dir * tmp[0] + x;
					addbullet(this, NULL, 821, xx, yy, dir, field_7D2, tmp, 3);
					field_7D0++;
				}

		if ( get_subseq() == 2 && get_elaps_frames() >= 50 )
		{
			next_subseq();
			break;
		}
		if ( get_subseq() <= 2 )
			v_inerc -= 0.1;
		if ( get_subseq() == 3 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				reset_forces();
				y = getlvl_height();
				next_subseq();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		break;

	case 550:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			field_190 = 1;
			add_card_energy( 50);
			float t1, t2;
			t1 = 6.0;
			t2 = 15.0;
			if ( skills_1[10] >= 2 )
			{
				t1 = 8.0;
				t2 = 10.0;
			}
			if ( skills_1[10] >= 3 )
			{
				t1 = 10.0;
				t2 = 9.0;
			}
			if ( skills_1[10] >= 4 )
			{
				t1 = 12.0;
				t2 = 8.0;
			}
			for (int32_t i = 0; i < t1 ; i++)
			{
				float tmp[5];
				tmp[0] = i * t2 - 175.0;
				tmp[1] = scene_rand_rng(12) + 12.0;
				tmp[2] = 0.0;
				tmp[3] = scene_rand_rng(8);
				tmp[4] = 0.0;
				addbullet(this, NULL, 822, x, y + 120.0, dir, -1, tmp, 5);
			}
		}
		break;

	case 551:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame() == 3 && get_frame_time() == 0 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			field_190 = 1;
			add_card_energy( 50);
			float t1, t2;
			t1 = 6.0;
			t2 = 15.0;
			if ( skills_1[10] >= 2 )
			{
				t1 = 8.0;
				t2 = 10.0;
			}
			if ( skills_1[10] >= 3 )
			{
				t1 = 10.0;
				t2 = 9.0;
			}
			if ( skills_1[10] >= 4 )
			{
				t1 = 12.0;
				t2 = 8.0;
			}
			for (int32_t i = 0; i < t1 ; i++)
			{
				float tmp[5];
				tmp[0] = i * t2 - 175.0;
				tmp[1] = scene_rand_rng(12) + 12.0;
				tmp[2] = 0.0;
				tmp[3] = scene_rand_rng(8);
				tmp[4] = 6.0;
				addbullet(this, NULL, 822, x, y + 120.0, dir, -1, tmp, 5);
			}
		}
		break;

	case 560:
		sub10func();
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			field_190 = 1;

		if ( (get_subseq() == 1 || get_subseq() == 2) && get_elaps_frames() >= 10 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 565:
		sub10func();
		if ( get_subseq() == 1 && get_elaps_frames() > 12 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 18 )
			next_subseq();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 566:
		sub10func();
		if ( get_subseq() == 0 && get_elaps_frames() == 1 )
			field_8BC[0] = 0;
		if ( get_subseq() == 1 && get_elaps_frames() > 12 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 33 )
			next_subseq();

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			play_sfx( 3);
			field_190 = 1;
			spell_energy_spend(200, 120);
			add_card_energy( 50);
		}
		break;

	case 567:
		if ( get_subseq() == 4 )
		{
			sub10func();
		}
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 4);
				break;
			}
		}
		if ( get_subseq() == 1 && get_elaps_frames() > 20 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 10 )
			next_subseq();
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if ( get_frame() == 2 )
				field_8BC[0] = 1;
			if ( get_frame() == 3 )
				field_8BC[0] = 0;
			if ( get_frame() == 6 )
			{
				play_sfx( 3);
				field_190 = 1;
				spell_energy_spend(200, 120);
				add_card_energy( 50);
			}
		}
		if ( get_subseq() == 3 && get_frame_time() == 0 && get_frame() == 2 )
			v_force = 0.5;
		break;

	case 568:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_frame_time() == 0 && get_frame() == 8 )
		{
			play_sfx( 3);
			spell_energy_spend(200, 45);
			field_190 = 1;
			add_card_energy( 50);
			field_890[0]++;
			if ( field_890[0] >= 3 )
				field_890[0] = 3;
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = field_890[0];
			addbullet(this, NULL, 830, x, y + 120.0, dir, -1, tmp, 3);
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 0);
		break;

	case 569:
		if ( get_subseq() == 4 )
		{
			sub10func();
		}
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 4);
				break;
			}
		}
		if ( get_subseq() == 0 && get_elaps_frames() == 1 )
			field_8BC[0] = 0;
		if ( get_subseq() == 1 && get_elaps_frames() > 24 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 21 )
			next_subseq();
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if ( get_frame() == 2 )
				field_8BC[0] = 1;
			if ( get_frame() == 3 )
				field_8BC[0] = 0;
			if ( get_frame() == 6 )
			{
				play_sfx( 3);
				field_190 = 1;
				spell_energy_spend(200, 120);
				add_card_energy( 50);
			}
		}
		if ( get_subseq() == 3 && get_frame_time() == 0 && get_frame() == 2 )
			v_force = 0.5;
		break;

	case 570:
		sub10func();
		if ( get_subseq() == 2 && get_elaps_frames() >= 18 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);

		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if (get_subseq() == 1)
			{
				play_sfx( 13);
				spell_energy_spend(200, 120);
				field_190 = 1;
				add_card_energy( 50);
				float tmp[4];
				if ( field_890[1] <= 0 )
				{
					tmp[0] = 0.0;
				}
				else
				{
					float xx = (field_89C[field_890[1] - 1] - x - (13 * dir)) * dir;
					float yy = field_8AC[field_890[1] - 1] - y - 115.0;
					tmp[0] = -atan2_deg(yy, xx);
				}
				tmp[1] = 30.0;
				if ( skills_1[11] < 4 )
					tmp[2] = 0.0;
				else
					tmp[2] = 3.0;

				addbullet(this, NULL, 827, (13 * dir) + x, y + 115.0, dir, -1, tmp, 4);

				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 2.0;
				addbullet(this, NULL, 827, (13 * dir) + x, y + 115.0, dir, -1, tmp, 4);
			}
			if ( get_subseq() == 4 )
				set_seq( 0);
		}
		break;

	case 571:
		sub10func();
		if ( get_subseq() == 2 && get_elaps_frames() >= 18 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 )
		{
			if (get_subseq() == 1)
			{
				play_sfx( 13);
				spell_energy_spend(200, 120);
				field_190 = 1;
				add_card_energy( 50);
				float tmp[4];
				if ( field_890[1] <= 0 )
				{
					tmp[0] = 0.0;
				}
				else
				{
					float xx = (field_89C[field_890[1] - 1] - x - (13 * dir)) * dir;
					float yy = field_8AC[field_890[1] - 1] - y - 115.0;
					tmp[0] = -atan2_deg(yy, xx);
				}
				tmp[1] = 30.0;
				if ( skills_1[11] < 4 )
					tmp[2] = 5.0;
				else
					tmp[2] = 6.0;

				addbullet(this, NULL, 827, (13 * dir) + x, y + 115.0, dir, -1, tmp, 4);

				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 2.0;
				addbullet(this, NULL, 827, (13 * dir) + x, y + 115.0, dir, -1, tmp, 4);
			}
			if ( get_subseq() == 4 )
				set_seq( 0);
		}
		break;

	case 600:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() >= 39 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (34 * dir), y + 114.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
		{
			play_sfx( 20);
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 850, (125 * dir) + x, y + 120.0, dir, 1, tmp, 3);
		}
		break;

	case 601:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() >= 39 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_frame_time() == 0 && get_frame() == 2 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (44 * dir), y + 100.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_frame_time() == 0 && get_frame() == 6 )
		{
			play_sfx( 22);
			for(int32_t i = 0; i < 360; i += 60)
			{
				float tmp[4];
				tmp[0] = 0;
				tmp[1] = 0;
				tmp[2] = 0;
				tmp[3] = i;

				addbullet(this, NULL, 851, (32 * dir) + x, y + 104.0, dir, -1, tmp, 4);
			}
		}
		break;

	case 602:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() > 60 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 18 )
			next_subseq();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if ( get_frame() == 3 )
			{
				field_4A6 = 40;
				scene_play_sfx(23);
				scene_add_effect(this, 115, x - (60 * dir), y + 147.0, dir, 1);
				sub_469450( 0, 0, 60);
				sub_483570();
				weather_forecast_next();
			}
			if ( get_frame() == 4 )
			{
				float tmp[3];
				tmp[0] = 0;
				tmp[1] = 0;
				tmp[2] = 0;

				addbullet(this, NULL, 852, x - (50 * dir), y + 184.0, dir, -1, tmp, 3);
			}
		}
		break;

	case 603:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() >= 39 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (34 * dir), y + 114.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_subseq() == 2 && get_frame() == 2 && get_frame_time() == 0 )
		{
			play_sfx( 24);
			float tmp[3];
			tmp[0] = 0;
			tmp[1] = 0;
			tmp[2] = 0;

			addbullet(this, NULL, 853, (125 * dir) + x, y + 120.0, dir, 1, tmp, 3);
		}
		break;

	case 604:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() >= 39 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_frame_time() == 0 && get_frame() == 2 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (44 * dir), y + 100.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_frame_time() == 0 && get_frame() == 6 )
		{
			play_sfx( 26);
			for(int32_t i = 0; i < 720; i += 60)
			{
				float tmp[4];
				tmp[0] = 0;
				tmp[1] = 0;
				tmp[2] = 0;
				tmp[3] = i;

				addbullet(this, NULL, 854, x, y + 104.0, dir, -1, tmp, 4);
			}
		}
		break;

	case 605:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() > 80 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 18 )
			next_subseq();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if (get_frame() == 3)
			{
				field_4A6 = 40;
				scene_play_sfx(23);
				scene_add_effect(this, 115, x - (60 * dir), y + 147.0, dir, 1);
				sub_469450( 0, 0, 60);
				sub_483570();
				weather_forecast_next();
			}
			if ( get_frame() == 4 )
			{
				for(int32_t i = 0; i < 6; i ++)
				{
					float tmp[4];
					tmp[0] = 0;
					tmp[1] = 0;
					tmp[2] = 0;
					tmp[3] = i;

					addbullet(this, NULL, 855, x - (50 * dir), y + 184.0, dir, -1, tmp, 4);
				}
			}
		}
		break;

	case 606:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 2 == 0 && field_7D0 <= 7 )
			{
				play_sfx( 28);
				float tmp[4];
				tmp[0] = (6 * field_7D0 % 4) - 60.0;
				tmp[1] = field_7D0 * 3.0 + 20.0;
				tmp[2] = 0.0;
				tmp[3] = field_7D0;
				addbullet(this, NULL, 856, x, y + 110.0, dir, -1, tmp, 4);
				field_7D0++;
			}
			if ( get_elaps_frames() % 2 == 0 )
			{
				if ( field_7D2 <= 7 )
				{
					play_sfx( 28);
					float tmp[4];
					tmp[0] = (6 * field_7D2 % 4) - 60.0;
					tmp[1] = field_7D2 * 3.0 + 20.0;
					tmp[2] = 0.0;
					tmp[3] = field_7D2;
					addbullet(this, NULL, 856, x, y + 110.0, -dir, -1, tmp, 4);
					field_7D2++;
				}
			}
			if ( get_elaps_frames() >= 90 )
				next_subseq();
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			play_sfx( 28);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, (20 * dir) + x, y + 131.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		break;

	case 607:
		sub10func();
		sub_46AB50( 3, 2);
		if ( process() )
			set_seq( 0);
		if ( get_frame_time() == 0 && get_frame() == 4 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (63 * dir), y + 150.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_frame_time() == 0 && get_frame() == 9 )
		{
			play_sfx( 5);
			float tmp[4];
			tmp[0] = -30.0;
			tmp[1] = 30.0;
			tmp[2] = 0.0;
			tmp[3] = -45.0;
			addbullet(this, NULL, 857, (20 * dir) + x, y + 110.0, dir, 1, tmp, 4);
		}
		break;

	case 608:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && (get_elaps_frames() > 480 || keyDown(INP_D)) )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (60 * dir), y + 147.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 3.0;
			addbullet(this, NULL, 858, (30 * dir) + x, y + 130.0, dir, 1, tmp, 3);
		}
		break;

	case 609:
		sub10func();
		if ( get_subseq() <= 2 )
			sub_46AB50( 3, 2);
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, (13 * dir) + x, y + 110.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			play_sfx( 35);
		if ( get_subseq() == 2 && get_elaps_frames() >= 24 )
			next_subseq();
		break;

	case 610:
		sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 5 == 0 )
			{
				float tmp[3];
				tmp[0] = (scene_rand() % 110) - 60.0;
				tmp[1] = (scene_rand() % 170) + 10.0;
				tmp[2] = 0.0;
				if ( get_elaps_frames() == 0 )
				{
					tmp[0] = 20.0;
					tmp[1] = 100.0;
				}
				if ( scene_rand_rng(100) > 50 )
					field_7D2 = -1;
				else
					field_7D2 = 1;
				float yy = y + tmp[1];
				float xx = dir * tmp[0] + x;
				addbullet(this, NULL, 860, xx, yy, dir, field_7D2, tmp, 3);
				field_7D0++;
			}
			if ( get_subseq() == 1 && get_elaps_frames() >= 120 )
			{
				next_subseq();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (44 * dir), y + 100.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			h_inerc = 5.0;
		if ( get_subseq() == 2 )
		{
			h_inerc -= 0.3;
			if ( h_inerc < 0.0 )
				h_inerc = 0.0;
			if ( get_frame_time() == 0 && get_frame() == 4 )
			{
				field_190 = 0;
				field_194 = 1;
				scene_play_sfx(29);
			}
		}
		break;

	case 611:
		sub10func();
		sub_46AB50( 3, 2);
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 3 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			char_frame *frm = get_pframe();
			float yy = y - frm->extra1[5];
			float xx = frm->extra1[4] * dir + x;
			scene_add_effect(this, 115, xx, yy, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 3 == 0 )
			{
				if ( field_7D0 <= 30 )
				{
					if ( field_7D0 == 30 )
					{
						float tmp[3];
						tmp[0] = scene_rand_rng(20) * 0.1 + 1.0;
						tmp[1] = scene_rand_rng(20) * 0.1 + 3.0;
						tmp[2] = 0.0;
						addbullet( this, NULL, 861, x, y + 50.0, dir, -1, tmp, 3);
						play_sfx( 3);
					}
					else
					{
						float tmp[3];
						tmp[0] = scene_rand_rng(40) * 0.1 + 3.0;
						tmp[1] = scene_rand_rng(20) * 0.1 + 1.0;
						tmp[2] = 9.0;
						addbullet( this, NULL, 861, x, y + 50.0, dir, -1, tmp, 3);
					}
					field_7D0 ++;
				}
			}
			if ( get_elaps_frames() % 5 )
				play_sfx( 40);
			if ( get_elaps_frames() >= 150 )
				next_subseq();
		}
		break;

	case 652:
		if ( get_subseq() == 5 )
		{
			sub10func();
		}
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				reset_forces();
				set_subseq( 5);
				y = getlvl_height();
				break;
			}
		}
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() > 60 )
			next_subseq();
		if ( get_subseq() == 2 && get_elaps_frames() > 18 )
			next_subseq();
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			v_force = 0.5;
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if ( get_frame() == 5 )
			{
				field_4A6 = 40;
				scene_play_sfx(23);
				scene_add_effect(this, 115, x - (60 * dir), y + 147.0, dir, 1);
				sub_469450( 0, 0, 60);
				sub_483570();
				weather_forecast_next();
			}
			if ( get_frame() == 6 )
			{
				float tmp[3];
				tmp[0] = 0.0;
				tmp[1] = 0.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 852, x - (50 * dir), y + 184.0, dir, -1, tmp, 3);
			}
		}
		break;

	case 657:
		if ( get_subseq() == 4 )
			sub10func();
		if ( get_subseq() <= 1 )
			sub_46AB50( 3, 2);
		if ( get_subseq() == 1 && get_elaps_frames() >= 40 )
		{
			next_subseq();
			v_force = 0.5;
			break;
		}
		if (get_subseq() == 2 || get_subseq() == 3)
		{
			v_inerc -= v_force;
			if (char_on_ground_down())
			{
				reset_forces();
				y = getlvl_height();
				set_subseq( 4);
				break;
			}
		}

		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, x - (63 * dir), y + 150.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			play_sfx( 5);
			float tmp[4];
			tmp[0] = -30.0;
			tmp[1] = 30.0;
			tmp[2] = 0.0;
			tmp[3] = 0.0;
			addbullet(this, NULL, 857, (20 * dir) + x, y + 110.0, dir, 1, tmp, 4);
		}
		break;

	case 659:
		if ( get_subseq() == 5 )
		{
			sub10func();
		}
		else
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				reset_forces();
				set_subseq( 5);
				break;
			}
		}
		if ( get_subseq() <= 2 )
			sub_46AB50( 3, 2);
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 2 )
		{
			field_4A6 = 40;
			scene_play_sfx(23);
			scene_add_effect(this, 115, (8 * dir) + x, y + 136.0, dir, 1);
			sub_469450( 0, 0, 60);
			sub_483570();
			weather_forecast_next();
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			play_sfx( 35);
		if ( get_subseq() == 2 && get_elaps_frames() >= 24 )
		{
			next_subseq();
			v_force = 0.5;
		}
		break;

	case 660:
		if ( get_subseq() == 4 )
			sub10func();
		sub_46AB50( 3, 2);
		if ( get_subseq() == 1 || get_subseq() == 2 )
		{
			if ( get_elaps_frames() % 5 == 0 )
			{
				float tmp[3];
				tmp[0] = (scene_rand() % 110) - 60.0;
				tmp[1] = (scene_rand() % 170) + 10.0;
				tmp[2] = 0.0;
				if ( get_elaps_frames() == 0 )
				{
					tmp[0] = 20.0;
					tmp[1] = 100.0;
				}
				if ( scene_rand_rng(100) > 50 )
					field_7D2 = -1;
				else
					field_7D2 = 1;
				float yy = y + tmp[1];
				float xx = dir * tmp[0] + x;
				addbullet(this, NULL, 860, xx, yy, dir, field_7D2, tmp, 3);
				field_7D0++;
			}
		}
		if (get_subseq() == 2 && get_elaps_frames() >= 100 )
		{
			next_subseq();
			break;
		}
		if ( get_subseq() <= 2 && !time_stop )
			v_inerc -= 0.05;
		if ( get_subseq() == 3 )
		{
			v_inerc -= v_force;
			if (char_on_ground_down())
			{
				reset_forces();
				y = getlvl_height();
				next_subseq();
				break;
			}
		}
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if ( get_frame() == 2 )
			{
				field_7DC = h_inerc;
				dash_angle = v_inerc;
				h_inerc = 0.0;
				v_inerc = 0.0;
				field_4A6 = 40;
				scene_play_sfx(23);
				scene_add_effect(this, 115, (8 * dir) + x, y + 136.0, dir, 1);
				sub_469450( 0, 0, 60);
				sub_483570();
				weather_forecast_next();
			}
			if ( get_frame() == 3 )
			{
				h_inerc = field_7DC;
				v_inerc = dash_angle;
			}
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 4 )
			set_seq( 9);
		break;

	case 695:
		sub10func();
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 7 )
		{
			scene_play_sfx(55);
			scene_add_effect(this, 140, x, y + 100.0, dir, 1);
			scene_add_effect(this, 140, x, y + 100.0, dir, 1);
			scene_add_effect(this, 140, x, y + 100.0, dir, 1);
			scene_add_effect(this, 141, x, y + 100.0, dir, -1);
			scene_add_effect(this, 142, x, y, dir, -1);
		}
		break;
	case 696:
		sub10func();
		h_inerc -= 1.5;
		if ( h_inerc < 0.0 )
			h_inerc = 0.0;
		if ( process() )
			set_seq( 0);
		if ( get_subseq() == 0 && get_frame_time() == 0 )
		{
			if ( get_frame() == 8 )
				h_inerc = 15.0;
			if ( get_frame() == 9 )
			{
				scene_play_sfx(29);
				field_49A = 0;
			}
		}
		break;

	case 710:
		sub10func();
		if ( get_subseq() == 1 && (int32_t)get_elaps_frames() > field_7D0 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			switch ( settings_get()->get_difficulty() )
			{
			case GAME_DIFF_LUNA:
				field_7D0 = 30;
				break;
			case GAME_DIFF_HARD:
				field_7D0 = 45;
				break;
			case GAME_DIFF_NORMAL:
				field_7D0 = 60;
				break;
			case GAME_DIFF_EASY:
				field_7D0 = 120;
				break;
			default:
				break;
			}
			play_sfx( 2);
			float tmp[3];
			tmp[0] = -45.0 - scene_rand_rng(90);
			tmp[1] = scene_rand_rng(60) * 0.1 + 7.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 900, x, y + 100.0, dir, -1, tmp, 3);
		}
		break;

	case 711:
		sub10func();
		if ( get_subseq() == 0 && get_elaps_frames() % 2 == 0 )
		{
			float tmp[3];
			tmp[0] = scene_rand_rng(360);
			tmp[1] = scene_rand_rng(400) + 200.0;
			tmp[2] = scene_rand_rng(7);
			char_frame *frm = get_pframe();
			float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
			float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
			addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
		}
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 2 == 0 && (int32_t)get_elaps_frames() <= field_7D0 - 30 )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(360);
				tmp[1] = scene_rand_rng(400) + 200.0;
				tmp[2] = scene_rand_rng(7);
				char_frame *frm = get_pframe();
				float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
				float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
				addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
			}
			if ( (int32_t)get_elaps_frames() >= field_7D0 )
			{
				next_subseq();
				break;
			}
		}
		if ( get_subseq() == 3 && (int32_t)get_elaps_frames() >= field_7D0 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			switch ( settings_get()->get_difficulty())
			{
			case GAME_DIFF_LUNA:
				field_7D0 = 120;
				field_7DC = 10.0;
				dash_angle = 10.0;
				break;
			case GAME_DIFF_HARD:
				field_7D0 = 120;
				field_7DC = 8.0;
				dash_angle = 8.0;
				break;
			case GAME_DIFF_NORMAL:
				field_7D0 = 150;
				field_7DC = 6.0;
				dash_angle = 8.0;
				break;
			case GAME_DIFF_EASY:
				field_7D0 = 180;
				field_7DC = 4.0;
				dash_angle = 7.0;
				break;
			default:
				break;
			}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
		{
			switch ( settings_get()->get_difficulty() )
			{
			case 0:
			case 1:
			case 2:
			case 3:
				field_7D0 = 180;
				break;
			default:
				break;
			}
			play_sfx( 2);
			for (int32_t i=0; i < field_7DC; i++)
			{
				float tmp[3];
				tmp[0] = -60.0 - scene_rand_rng(120);
				tmp[1] = scene_rand_rng(dash_angle * 10.0) * 0.1 + 7.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 900, x, y + 100.0, dir, -1, tmp, 3);
			}
		}
		break;

	case 720:
		sub10func();
		if ( get_subseq() == 0 && get_elaps_frames() % 2 == 0 )
		{
			float tmp[3];
			tmp[0] = scene_rand_rng(360);
			tmp[1] = scene_rand_rng(400) + 200.0;
			tmp[2] = scene_rand_rng(7);
			char_frame *frm = get_pframe();
			float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
			float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
			addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
		}
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() % 2 == 0 && (int32_t)get_elaps_frames() <= field_7D0 - 30 )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(360);
				tmp[1] = scene_rand_rng(400) + 200.0;
				tmp[2] = scene_rand_rng(7);
				char_frame *frm = get_pframe();
				float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
				float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
				addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
			}
			if ( (int32_t)get_elaps_frames() >= field_7D0 )
			{
				next_subseq();
				break;
			}
		}

		if ( get_subseq() == 3 && (int32_t)get_elaps_frames() >= field_7D0 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			switch ( settings_get()->get_difficulty())
			{
			case GAME_DIFF_LUNA:
				field_7D0 = 60;
				break;
			case GAME_DIFF_HARD:
				field_7D0 = 90;
				break;
			case GAME_DIFF_NORMAL:
				field_7D0 = 120;
				break;
			case GAME_DIFF_EASY:
				field_7D0 = 180;
				break;
			default:
				break;
			}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
		{
			switch ( settings_get()->get_difficulty() )
			{
			case 0:
			case 1:
			case 2:
			case 3:
				field_7D0 = 120;
				break;
			default:
				break;
			}
			play_sfx( 22);
			float tmp[3];
			tmp[0] = -60.0 - scene_rand_rng(120);
			tmp[1] = scene_rand_rng(dash_angle * 10.0) * 0.1 + 7.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 910, x, y + 100.0, dir, -1, tmp, 3);
		}
		break;

	case 730:
		if ( get_subseq() == 0 )
			sub10func();
		if ( get_subseq() == 1 )
			v_inerc -= v_force;
		if ( get_subseq() == 2 && get_elaps_frames() % 2 == 0 )
		{
			float tmp[3];
			tmp[0] = scene_rand_rng(360);
			tmp[1] = scene_rand_rng(400) + 200.0;
			tmp[2] = scene_rand_rng(7);
			char_frame *frm = get_pframe();
			float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
			float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
			addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
		}
		if ( get_subseq() == 3 )
		{
			if ( get_elaps_frames() % 2 == 0 && (int32_t)get_elaps_frames() <= field_7D0 - 30 )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(360);
				tmp[1] = scene_rand_rng(400) + 200.0;
				tmp[2] = scene_rand_rng(7);
				char_frame *frm = get_pframe();
				float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
				float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
				addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
			}
			if ( (int32_t)get_elaps_frames() >= field_7D0 )
			{
				next_subseq();
				break;
			}
		}
		if ( get_subseq() == 2 || get_subseq() == 3 )
		{
			h_inerc *= 0.98;
			v_inerc *= 0.98;
		}
		if ( get_subseq() == 5 && (int32_t)get_elaps_frames() >= field_7D0 )
		{
			next_subseq();
			break;
		}
		if ( process() )
			set_seq( 0);
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			h_inerc = scene_rand_rng(20) * 0.1 - 10.0;
			v_inerc = 10.0;
			v_force = 0.5;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
			switch ( settings_get()->get_difficulty() )
			{
			case GAME_DIFF_LUNA:
			case GAME_DIFF_HARD:
			case GAME_DIFF_NORMAL:
			case GAME_DIFF_EASY:
				field_7D0 = 60;
				break;
			default:
				break;
			}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 5 )
		{
			switch ( settings_get()->get_difficulty() )
			{
			case GAME_DIFF_LUNA:
				field_7D0 = 90;
				dash_angle = 10;
				field_7DC = 12.0;
				field_7E4 = 16.0;
				field_7E8 = 7.0;
				break;
			case GAME_DIFF_HARD:
				field_7D0 = 90;
				dash_angle = 8.0;
				field_7DC = 10;
				field_7E4 = 12.0;
				field_7E8 = 7.0;
				break;
			case GAME_DIFF_NORMAL:
				field_7D0 = 90;
				dash_angle = 8.0;
				field_7DC = 10;
				field_7E4 = 6.0;
				field_7E8 = 7.0;
				break;
			case GAME_DIFF_EASY:
				field_7D0 = 90;
				dash_angle = 6.0;
				field_7DC = 8.0;
				field_7E4 = 0.0;
				field_7E8 = 7.0;
				break;
			default:
				break;
			}
			play_sfx( 22);
			for (int32_t i=0; i < field_7DC; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / field_7DC;
				tmp[1] = 0.0;
				tmp[2] = 0.0;
				tmp[3] = field_7E8 * 2;
				addbullet(this, NULL, 920, x, y + 100.0, dir, -1, tmp, 4);
			}

			for (int32_t i=0; i < dash_angle; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / dash_angle;
				tmp[1] = 0.0;
				tmp[2] = 0.0;
				tmp[3] = field_7E8;
				addbullet(this, NULL, 920, x, y + 100.0, -dir, -1, tmp, 4);
			}
			for (int32_t i=0; i < field_7E4; i++)
			{
				float tmp[4];
				tmp[0] = i * 360.0 / dash_angle;
				tmp[1] = 0.0;
				tmp[2] = 0.0;
				tmp[3] = field_7E8 * 3.0;
				addbullet(this, NULL, 920, x, y + 100.0, -dir, -1, tmp, 4);
			}
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 7 )
		{
			set_seq( 731);
			reset_forces();
		}
		break;

	case 731:
		if ( process() )
		{
			set_seq( 730);
			set_subseq( 2);
			break;
		}
		if ( get_subseq() >= 1 )
		{
			h_inerc = (dash_angle - x) * dir * 0.05;
			v_inerc = 0.05 * (field_7DC - y);
			if ( get_elaps_frames() >= 30 )
			{
				next_subseq();
				break;
			}
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			field_7D0 = 0;
			if ( getlvl_height() >= y )
				field_7DC = scene_rand_rng(100) + 150.0;
			else
				field_7DC = scene_rand_rng(250) + 50.0;

			if ( x > 640.0 )
				dash_angle = scene_rand_rng(480) + 100.0;
			else
				dash_angle = 1180 - scene_rand_rng(480);

			if ( dash_angle >= x )
				dir = 1;
			else
				dir = -1;
		}
		break;

	case 740:
		sub10func();

		if ( get_subseq() == 0 && get_elaps_frames() % 2 == 0 )
		{
			float tmp[3];
			tmp[0] = scene_rand_rng(360);
			tmp[1] = scene_rand_rng(400) + 200.0;
			tmp[2] = scene_rand_rng(7);
			char_frame *frm = get_pframe();
			float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
			float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
			addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
		}
		if ( get_subseq() == 1)
		{
			if ( get_elaps_frames() % 2 == 0 && (int32_t)get_elaps_frames() <= field_7D2 - 30 )
			{
				float tmp[3];
				tmp[0] = scene_rand_rng(360);
				tmp[1] = scene_rand_rng(400) + 200.0;
				tmp[2] = scene_rand_rng(7);
				char_frame *frm = get_pframe();
				float yy = sin_deg(-tmp[0]) * tmp[1] + y - frm->extra1[5];
				float xx = (cos_deg(-tmp[0]) * tmp[1] + frm->extra1[4]) * dir + x;
				addbullet(this, NULL, 970, xx, yy, dir, 1, tmp, 3);
			}
			if ((int32_t)get_elaps_frames() >= field_7D2 )
			{
				next_subseq();
				break;
			}
		}
		if ( get_subseq() == 3 && (int32_t)get_elaps_frames() >= field_7D2 )
		{
			next_subseq();
			break;
		}
		if ( process() )
		{
			set_seq( 0);
			field_7D0 = 0;
			field_7D2 = 0;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
			field_7D2 = 90;
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 3 )
		{
			field_7D2 = 240;
			play_sfx( 2);
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 580.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 930, x, y + 100.0, dir, 1, tmp, 3);
			tmp[0] = 180.0;
			addbullet(this, NULL, 930, x, y + 100.0, -dir, 1, tmp, 3);
		}
		break;

	case 750:
		if ( get_subseq() >= 1 && get_subseq() <= 3 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				y = getlvl_height();
				set_subseq( 4);
				reset_forces();
				x = 640.0;
				break;
			}
		}
		if ( process() )
		{
			set_seq( 751);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			field_888 = 60;
			field_88A = 60;
			v_force = 0.5;
			v_inerc = 15.0;
			h_inerc = (640.0 - x) / 60.0 * dir;
		}
		break;

	case 751:
		if ( field_888 <= 0 )
		{
			set_seq( 752);
			break;
		}
		if ( process() )
		{
			set_seq( 751);
			break;
		}
		if ( get_elaps_frames() == 0 && get_frame_time() == 0 && get_frame() == 0 && get_subseq() == 1 )
		{
			field_6F5 = 1;
			sub_4685C0( -1);
			sub_46AB50( 2, -1);
			field_188 = 0;
			field_868 = 1;
			field_820 = 0;
			field_81E = 1;
			field_81A = 0;
			field_818 = 0;
			scene_play_sfx(23);
			field_882 = 1;
			field_86A = 1;
			field_888 = 60;
			field_88A = 60;
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 1203, 180.0, 130.0, 1, 2, tmp, 3);
			tmp[2] = 1.0;
			addbullet(this, NULL, 1202, x, y + 100.0, dir, -1, tmp, 3);
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 5.0;
			addbullet(this, NULL, 940, x, y, dir, -1, tmp, 3);
			play_sfx( 37);
		}
		break;
	case 752:
		if ( get_subseq() == 1 )
		{
			if ( get_elaps_frames() == 60 )
			{
				float tmp[3];
				tmp[0] = 1.0;
				tmp[1] = 0.0;
				tmp[2] = 0.0;
				addbullet(this, NULL, 1250, 0.0, 0.0, 1, 2, tmp, 3);
			}
			if ( get_elaps_frames() == 240 )
			{
				/*v861 = cards_active[0];
				v862 = field_6EC;
				v863 = v861->id;
				v864 = char_id;
				v865 = enemy->char_id;
				v866 = sub_43D120();
				sub_42F100((void *)v866, v865, v864, v863, v862);*/ //FIXME
				field_6F5 = 0;
				field_574 = 3;
				//sub_43D380(3000, 0); //FIXME
			}
		}
		if ( process() )
			set_seq( 752);
		break;

	case 770:
		if ( process() )
			set_seq( 700);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			field_6F5 = 1;
			sub_4685C0( -1);
			sub_46AB50( 2, -1);
			field_188 = 0;
			health_to_max();
			field_868 = 1;
			field_820 = 0;
			field_81E = 1;
			field_81A = 0;
			field_818 = 0;
			scene_play_sfx(23);
			field_882 = 1;
			field_86A = 1;
			float tmp[3];
			tmp[0] = 0.0;
			tmp[1] = 0.0;
			tmp[2] = 0.0;
			addbullet(this, NULL, 1201, 180.0, 130.0, 1, 2, tmp, 3);
			tmp[2] = 1.0;
			addbullet(this, NULL, 1202, x, y + 100.0, dir, -1, tmp, 3);
		}
		break;

	case 771:
		if ( process() )
			set_seq( 700);
		if ( get_subseq() == 0 && get_frame_time() == 0 && get_frame() == 6 )
		{
			field_6F5 = 1;
			sub_4685C0( -1);
			sub_46AB50( 2, -1);
			field_188 = 0;
			health_to_max();
			field_868 = 1;
			field_820 = 0;
			field_81E = 1;
			field_81A = 0;
			field_818 = 0;
			scene_play_sfx(23);
		}
		break;

	case 788:
		if ( process() )
			set_seq( 700);
		break;

	case 795:
		if (get_subseq() == 0)
		{
			v_inerc -= 0.3;
			if (char_on_ground_down())
			{
				scene_play_sfx(30);
				set_subseq(1);
				y = getlvl_height();
				reset_forces();
				break;
			}
		}
		if ( process() )
			set_seq( 700);
		break;
	case 797:
		if ( get_subseq() <= 2 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				scene_play_sfx(30);
				set_subseq( 3);
				y = getlvl_height();
				v_inerc = 0.0;
				break;
			}
		}
		if ( get_subseq() == 3 )
		{
			h_inerc -= 0.75;
			if ( h_inerc < 0.0 )
			{
				h_inerc = 0.0;
				x = 480.0;
			}
			if ( x > 480.0 )
				x = 480.0;
		}
		if ( process() )
			set_seq( 0);
		break;
	case 798:

		if ( get_subseq() <= 2 )
		{
			v_inerc -= v_force;
			if ( char_on_ground_down() )
			{
				scene_play_sfx(30);
				set_subseq( 3);
				y = getlvl_height();
				v_inerc = 0.0;
				break;
			}
		}
		if ( get_subseq() == 3 )
		{
			h_inerc -= 0.75;
			if ( h_inerc < 0.0 )
			{
				h_inerc = 0.0;
				x = 800.0;
			}
			if ( x < 800.0 )
				x = 800.0;
		}
		if ( process() )
			set_seq( 700);
		break;

	default:
		char_c::func10();
	}
}

void char_alice::set_seq_params()
{
	uint32_t sq = get_seq();
	switch(sq)
	{
	case 214:
	case 217:
		reset_ofs();
		h_inerc = 0.0;
		field_7D6 = 0;
		v_inerc = 0.0;
		v_force = 0.6;
		x_off = 0.0;
		y_off = 95.0;
		field_7DC = 12.0;
		field_7EC = 0.0;
		break;
	case 400:
	case 401:
	case 410:
	case 411:
	case 412:
	case 419:
	case 520:
	case 521:
	case 522:
	case 523:
	case 525:
	case 526:
		field_190 = 0;
		reset_forces();
		field_7D0 = 0;
		field_7D2 = 0;
		field_7D6 = 0;
		field_7D8 = 0;
		not_charge_attack = 1;
		break;
	default:
		char_c::set_seq_params();
		break;
	}
}


void char_alice::func20()
{


	/*v1 = a1;
	  v2 = a1->current_frame_params;
	  v3 = v2->fflags;
	  v147 = a1->current_seq_frames_vector->cprior;
	  v4 = v2->fflags & FF_CANCELLEABLE;
	  v148 = v2->fflags & FF_CANCELLEABLE;
	  v5 = v3 & FF_UNK200000;*/

	uint16_t cprior = get_cprior();
	uint32_t fflags = get_pframe()->fflags;

	bool cc = (fflags & FF_CANCELLEABLE) != 0;
	bool cu = (fflags & FF_HJC) != 0;
	//int32_t sq = get_seq();

	if ( !check_AB_pressed() ) // !sub_4870A0(a1, v2) - AB input check
	{
		if ( cc || cu )
		{
			/*
			 if ( pres_comb >= 700 && pres_comb < 800 )
			 {
			   //v1->class->func2_set_seq(v1, LOWORD(v1->pressed_combination));
			   return;
			 }
			 else*/
			if ( char_on_ground_flag() )
			{
				if ( (cu && cprior >= 10 && hi_jump_after_move())
						|| border_escape_ground()
						|| hi_jump(cprior, cu)
						|| fw_bk_dash_ground(cprior, cu) )
					return;
			}
			else
			{
				int8_t mx = (weather_id == WEATHER_TEMPEST) + 2;
				if ( border_escape_air()
						|| fwd_dash_air(cprior, cu, mx, 2)
						|| bkg_dash_air(cprior, cu, mx, 2)
						|| flying_air(cprior, cu, mx) )
					return;
			}
		}
		if ( field_84C == 0 && cc )
		{
			if (input->keyHit(INP_B))
			{
				if (char_on_ground_flag()) // On Ground
				{
					if (gX(dir) > 0 && gY() == 0)
					{
						if ( cprior <= get_prior(401) )
						{
							angZ = 0;
							set_seq(401);
							return;
						}
					}
				}
			}
		}
	}
}
