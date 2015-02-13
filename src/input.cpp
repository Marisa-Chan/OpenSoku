#include "global_types.h"
#include "input.h"

#define KF_LEFT   0x01
#define KF_RIGHT  0x02
#define KF_UP     0x04
#define KF_DOWN   0x08
#define KF_A      0x10
#define KF_B      0x20
#define KF_C      0x40
#define KF_D      0x80
#define KF_AB     0x100
#define KF_BC     0x200


static bool key_matrix[sf::Keyboard::KeyCount];

void key_matrix_init()
{
	memset(key_matrix, 0, sizeof(key_matrix));
}

void key_matrix_set(int32_t idx, bool down)
{
	key_matrix[idx] = down;
}

bool key_matrix_get(int32_t idx)
{
	return key_matrix[idx];
}





inp_ab::inp_ab()
{
	memset(&raw, 0, sizeof(keys_struct));
	memset(&up, 0, sizeof(keys_struct));
	memset(&down, 0, sizeof(keys_struct));
	memset(&hit, 0, sizeof(keys_struct));

	raw_keys_bitset = 0;

	keyhit_timer = 0;

	flush_kframes();
}

//void inp_ab::zero_input()
//{
//    for (uint32_t i=0; i<INP_KEYS; i++)
//    {
//        key_dn[i] = false;
//        pr_key_dn[i] = false;
//    }
//}

void inp_ab::zero_input(inp_keys key)
{
	switch(key)
	{
	case INP_A:
		up.A = 0;
		hit.A = 0;
		down.A = 0;
		break;
	case INP_B:
		up.B = 0;
		hit.B = 0;
		down.B = 0;
		break;
	case INP_C:
		up.C = 0;
		hit.C = 0;
		down.C = 0;
		break;
	case INP_D:
		up.D = 0;
		hit.D = 0;
		down.D = 0;
		break;
	case INP_AB:
		up.AB = 0;
		hit.AB = 0;
		down.AB = 0;
		break;
	case INP_BC:
		up.BC = 0;
		hit.BC = 0;
		down.BC = 0;
		break;
	case INP_ST:
		up.START = 0;
		hit.START = 0;
		down.START = 0;
		break;
	case INP_X_AXIS:
		up.X = 0;
		hit.X = 0;
		down.X = 0;
		break;
	case INP_Y_AXIS:
		up.Y = 0;
		hit.Y = 0;
		down.Y = 0;
		break;
	default:
		break;
	}
}

//void inp_ab::flush_cur()
//{
//    for (uint32_t i=0; i<INP_KEYS; i++)
//    {
//        pr_key_dn[i] = key_dn[i];
//        key_dn[i] = false;
//    }
//}

//void inp_ab::fill_kframes()
//{
//    for(uint32_t i=INPKEYBUF-1; i>0; i--)
//        k_frames[i] = k_frames[i-1];
//
//    uint8_t vkf = 0;
//
//    if (key_dn[INP_UP])
//        vkf |= KF_UP;
//
//    if (key_dn[INP_DOWN])
//        vkf |= KF_DOWN;
//
//    if (key_dn[INP_LEFT])
//        vkf |= KF_LEFT;
//
//    if (key_dn[INP_RIGHT])
//        vkf |= KF_RIGHT;
//
//    if (key_dn[INP_A])
//        vkf |= KF_A;
//
//    if (key_dn[INP_B])
//        vkf |= KF_B;
//
//    if (key_dn[INP_C])
//        vkf |= KF_C;
//
//    if (key_dn[INP_D])
//        vkf |= KF_D;
//
//    k_frames[0] = vkf;
//
//    for (uint32_t i=0; i<INP_KEYS; i++)
//    {
//        if (key_dn[i] && key_frm[i] < 255)
//            key_frm[i]++;
//        else if (!pr_key_dn[i] && !key_dn[i])
//            key_frm[i] = 0;
//    }
//}

void inp_ab::fill_down_up_states()
{
	read_raw_key_data();

	keys_struct last = down;

	down = raw;

//    if (doubles_AB_BC)
//    {
//      v7 = v1->down_A;
//      v8 = v1->down_B;
//      if ( abs(v1->down_A - v8) < 2 )
//      {
//        if ( v7 >= (unsigned int)v8 )
//          v7 = v1->down_B;
//        v1->down_AB = v7;
//      }
//      v9 = v1->down_C;
//      if ( abs(v8 - v9) < 2 )
//      {
//        if ( v8 >= (unsigned int)v9 )
//          v8 = v1->down_C;
//        v1->down_BC = v8;
//      }
//      v10 = v1->down_AB;
//      if ( (unsigned int)v10 <= v3->raw_AB )
//        v10 = v3->raw_AB;
//      v1->down_AB = v10;
//      v11 = v1->down_BC;
//      v12 = v3->raw_BC;
//      if ( v11 <= v12 )
//        v11 = v12;
//      v5 = v13;
//      v1->down_BC = v11;
//      result = v14;
//    }

	up.X = 0;
	up.Y = 0;
	up.START = 0;

	if ( down.A || last.A == 0 )
		up.A = 0;
	else
		up.A = last.A;

	if ( down.B || last.B == 0 )
		up.B = 0;
	else
		up.B = last.B;

	if ( down.C || last.C == 0 )
		up.C = 0;
	else
		up.C = last.C;

	if ( down.D || last.D == 0 )
		up.D = 0;
	else
		up.D = last.D;

	if ( down.AB || last.AB == 0 )
		up.AB = 0;
	else
		up.AB = last.AB;

	if ( down.BC || last.BC == 0 )
		up.BC = 0;
	else
		up.BC = last.BC;
}

void inp_ab::zero_keyhit()
{
	hit.START = 0;

	hit.A = 0;
	hit.B = 0;
	hit.C = 0;
	hit.D = 0;
	hit.AB = 0;
	hit.BC = 0;
	hit.X = 0;
	hit.Y = 0;
	keyhit_timer = 0;
}

int32_t inp_ab::get_hitTimer()
{
	return keyhit_timer;
}

void inp_ab::update(bool clean)
{
	fill_down_up_states();

	uint16_t vkf = 0;
	if (down.X < 0)
		vkf |= KF_LEFT;
	if (down.X > 0)
		vkf |= KF_RIGHT;
	if (down.Y < 0)
		vkf |= KF_UP;
	if (down.Y > 0)
		vkf |= KF_DOWN;
	if (down.A == 1)
		vkf |= KF_A;
	if (down.B == 1)
		vkf |= KF_B;
	if (down.C == 1)
		vkf |= KF_C;
	if (down.D == 1)
		vkf |= KF_D;
	if (down.AB == 1)
		vkf |= KF_AB;
	if (down.BC == 1)
		vkf |= KF_BC;

	if (vkf & (KF_A | KF_B | KF_C | KF_D | KF_AB | KF_BC))
	{
		hit.X = down.X;
		hit.Y = down.Y;
		hit.A = down.A == 1;
		hit.B = down.B == 1;
		hit.C = down.C == 1;
		hit.D = down.D == 1;
		hit.AB = down.AB == 1;
		hit.BC = down.BC == 1;
		keyhit_timer = 10;
	}
	else if (clean || keyhit_timer <= 0)
	{
		zero_keyhit();
	}

	if (keyhit_timer)
		keyhit_timer--;

	for(uint32_t i=INPKEYBUF-1; i>0; i--)
		k_frames[i] = k_frames[i-1];

	k_frames[0] = vkf;

}

void inp_ab::read_raw_key_data()
{
	fill_raw();

	raw_keys_bitset = 0;

	if ( raw.X > 0 )
		raw_keys_bitset = 8;
	else if (raw.X < 0)
		raw_keys_bitset = 4;

	if ( raw.Y > 0 )
		raw_keys_bitset |= 1;
	else if (raw.Y < 0)
		raw_keys_bitset |= 2;

	if ( raw.A )
		raw_keys_bitset |= 0x10u;
	if ( raw.B )
		raw_keys_bitset |= 0x20u;
	if ( raw.C )
		raw_keys_bitset |= 0x40u;
	if ( raw.C )
		raw_keys_bitset |= 0x80u;
	if ( raw.AB )
		raw_keys_bitset |= 0x100u;
	if ( raw.BC )
		raw_keys_bitset |= 0x200u;
	if ( raw.START )
		raw_keys_bitset |= 0x400u;
}

//void inp_ab::set_key(inp_keys key)
//{
//    key_dn[key] = true;
//}

void inp_ab::set_keyDown(inp_keys key, int32_t val)
{
	switch(key)
	{
	case INP_A:
		down.A = val;
		break;
	case INP_B:
		down.B = val;
		break;
	case INP_C:
		down.C = val;
		break;
	case INP_D:
		down.D = val;
		break;
	case INP_AB:
		down.AB = val;
		break;
	case INP_BC:
		down.BC = val;
		break;
	case INP_ST:
		down.START = val;
		break;
	case INP_X_AXIS:
		down.X = val;
		break;
	case INP_Y_AXIS:
		down.Y = val;
		break;
	default:
		break;
	}
}

int32_t inp_ab::keyDown(inp_keys key)
{
	switch(key)
	{
	case INP_A:
		return down.A;
	case INP_B:
		return down.B;
	case INP_C:
		return down.C;
	case INP_D:
		return down.D;
	case INP_AB:
		return down.AB;
	case INP_BC:
		return down.BC;
	case INP_ST:
		return down.START;
	case INP_X_AXIS:
		return down.X;
	case INP_LEFT:
		return down.X < 0;
	case INP_RIGHT:
		return down.X > 0;
	case INP_Y_AXIS:
		return down.Y;
	case INP_UP:
		return down.Y < 0;
	case INP_DOWN:
		return down.Y > 0;
	default:
		return 0;
	}
}

int32_t inp_ab::keyHit(inp_keys key, bool delayed)
{
	if (delayed)
	{
		switch(key)
		{
		case INP_A:
			return hit.A;
		case INP_B:
			return hit.B;
		case INP_C:
			return hit.C;
		case INP_D:
			return hit.D;
		case INP_AB:
			return hit.AB;
		case INP_BC:
			return hit.BC;
		case INP_ST:
			return hit.START;
		case INP_X_AXIS:
			return hit.X;
		case INP_LEFT:
			return (hit.X < 0 ? hit.X : 0);
		case INP_RIGHT:
			return (hit.X > 0 ? hit.X : 0);
		case INP_Y_AXIS:
			return hit.X;
		case INP_UP:
			return (hit.Y < 0 ? hit.Y : 0);
		case INP_DOWN:
			return (hit.Y > 0 ? hit.Y : 0);
		default:
			return 0;
		}
	}
	else
	{
		switch(key)
		{
		case INP_A:
			return down.A == 1;
		case INP_B:
			return down.B == 1;
		case INP_C:
			return down.C == 1;
		case INP_D:
			return down.D == 1;
		case INP_AB:
			return down.AB == 1;
		case INP_BC:
			return down.BC == 1;
		case INP_ST:
			return down.START == 1;
		case INP_X_AXIS:
			return (down.X == -1 || down.X == 1  ? down.X : 0 );
		case INP_LEFT:
			return down.X == -1;
		case INP_RIGHT:
			return down.X == 1;
		case INP_Y_AXIS:
			return (down.Y == -1 || down.Y == 1  ? down.Y : 0 );
		case INP_UP:
			return down.Y == -1;
		case INP_DOWN:
			return down.Y == 1;
		default:
			return 0;
		}
	}
}

int32_t inp_ab::keyUp(inp_keys key)
{
	switch(key)
	{
	case INP_A:
		return up.A;
	case INP_B:
		return up.B;
	case INP_C:
		return up.C;
	case INP_D:
		return up.D;
	case INP_AB:
		return up.AB;
	case INP_BC:
		return up.BC;
	case INP_ST:
		return up.START;
	case INP_X_AXIS:
		return up.X;
	case INP_LEFT:
		return up.X < 0;
	case INP_RIGHT:
		return up.X > 0;
	case INP_Y_AXIS:
		return up.Y;
	case INP_UP:
		return up.Y < 0;
	case INP_DOWN:
		return up.Y > 0;
	default:
		return 0;
	}
}

//uint8_t inp_ab::keyFramed(inp_keys key)
//{
//    return key_frm[key];
//}

void inp_ab::flush_kframes()
{
	for(uint32_t i=0; i<INPKEYBUF; i++)
		k_frames[i] = 0;
}


int8_t inp_ab::check_input_seq(const char *sq, uint8_t frames, int8_t direction)
{
	uint8_t table_reverse [44] = { 0x0B, 0x0A,    8,    9,    2,    0,    1,    6,    4,    5,   0,
								   0,    0,    0,    0,    0,    0, 0x10, 0x20, 0x40, 0x80,   0,
								   0,    0,    0,    0,    0,    0,    1,    0,    0,    0,   0,
								   0,    2,    0,    0,    0,    0,    0, 0xF0,    0,    0,   0
								 };
	uint8_t table_plain   [44] = { 0x0B,    9,    8,  0xA,    1,    0,    2,    5,    4,    6,   0,
								   0,    0,    0,    0,    0,    0, 0x10, 0x20, 0x40, 0x80,   0,
								   0,    0,    0,    0,    0,    0,    1,    0,    0,    0,   0,
								   0,    2,    0,    0,    0,    0,    0, 0xF0,    0,    0,   0
								 };
	uint8_t buf[0x100];

	uint32_t sl = strlen(sq);

	//uint8_t XX = KF_A | KF_B | KF_C;

	int8_t ret_val = 0;

	for (uint32_t i=0; i < sl; i++)
	{
		uint8_t t = 0;

		int16_t in = (uint8_t)toupper(sq[i]);

		in -= '0';

		if (in >= 0 || in < 44)
		{
			if (direction <= 0)
				t = table_reverse[in];
			else
				t = table_plain[in];
		}

		buf[i] = t;
	}

	uint32_t j = 0;

	for (int32_t i=frames-1; i >= 0; i--)
	{
		if (buf[j] == 0xB)
		{
			if (k_frames[i] & KF_DOWN)
				j++;
		}
		else if ( buf[j] >= 0x10 )
		{
			if (buf[j] != 0xF0)
			{
				if ((k_frames[i] & 0xF0) == buf[j])
					j++;
			}
			else
			{
				if (k_frames[i] & 0xF0)
				{
					j++;
					if (k_frames[i] & 0x10)
						ret_val = 1;
					else if (k_frames[i] & 0x20)
						ret_val = 2;
					else if (k_frames[i] & 0x40)
						ret_val = 3;
					else if (k_frames[i] & 0x80)
						ret_val = 4;
				}
			}
		}
		else if ((k_frames[i] & 0xF) == buf[j])
			j++;

		if (j >= sl)
		{
			if (ret_val == 0)
				ret_val = 1;

			return ret_val;
		}

	}

	return ret_val;
}


int32_t inp_ab::dX(int8_t dir)
{
	return down.X * dir;
}

int32_t inp_ab::dY()
{
	return down.Y;
}

int32_t inp_ab::hX(int8_t dir)
{
	return hit.X * dir;
}

int32_t inp_ab::hY()
{
	return hit.Y;
}

void inp_ab::set_dX(int8_t dir)
{
	down.X = dir;
}

void inp_ab::set_dY(int8_t dir)
{
	down.Y = dir;
}


void inp_kb::fill_raw()
{
	if (key_matrix_get(map[INP_LEFT]))
	{
		if (raw.X > 0)
			raw.X = 0;
		raw.X--;
	}
	else if (key_matrix_get(map[INP_RIGHT]))
	{
		if (raw.X < 0)
			raw.X = 0;
		raw.X++;
	}
	else
		raw.X = 0;

	if (key_matrix_get(map[INP_UP]))
	{
		if (raw.Y > 0)
			raw.Y = 0;
		raw.Y--;
	}
	else if (key_matrix_get(map[INP_DOWN]))
	{
		if (raw.Y < 0)
			raw.Y = 0;
		raw.Y++;
	}
	else
		raw.Y = 0;

	if (key_matrix_get(map[INP_A]))
		raw.A++;
	else
		raw.A = 0;

	if (key_matrix_get(map[INP_B]))
		raw.B++;
	else
		raw.B = 0;

	if (key_matrix_get(map[INP_C]))
		raw.C++;
	else
		raw.C = 0;

	if (key_matrix_get(map[INP_D]))
		raw.D++;
	else
		raw.D = 0;

	if (key_matrix_get(map[INP_ST]))
		raw.START++;
	else
		raw.START = 0;

	if (key_matrix_get(map[INP_AB]))
		raw.AB++;
	else
		raw.AB = 0;

	if (key_matrix_get(map[INP_BC]))
		raw.BC++;
	else
		raw.BC = 0;
}


//void inp_kb::update()
//{
//    flush_cur();
//
//    for (uint32_t i=0; i<INP_KEYS; i++)
//        key_dn[i] = key_matrix_get(map[i]);
//        //key_dn[i] = kbd.isKeyPressed((sf::Keyboard::Key)map[i]);
//
//    x_axis = 0;
//    y_axis = 0;
//
//    if (key_dn[INP_LEFT])
//        x_axis -= 1;
//
//    if (key_dn[INP_RIGHT])
//        x_axis += 1;
//
//    if (key_dn[INP_UP])
//        y_axis += 1;
//
//    if (key_dn[INP_DOWN])
//        y_axis -= 1;
//
//    fill_kframes();
//}

bool inp_kb::rawPressed(uint32_t key, int32_t timeout)
{
	//bool prs = kbd.isKeyPressed((sf::Keyboard::Key)key);
	bool prs = key_matrix_get(key);
	if (!prs)
	{
		timeouts[key] = 0;
	}
	else
	{
		if (timeout <= 0)
			timeout = 1;
		timeouts[key] %= timeout;
		if (timeouts[key] == 0)
			return true;

		timeouts[key]++;
	}

	return false;
}

bool inp_kb::rawHit(uint32_t key)
{
	//bool prs = kbd.isKeyPressed((sf::Keyboard::Key)key);
	bool prs = key_matrix_get(key);
	if (prs)
	{
		if (!rawhit[key])
		{
			rawhit[key] = true;
			return true;
		}
	}
	else
	{
		rawhit[key] = false;
	}

	return false;
}

inp_kb::inp_kb()
{
	for (int32_t i=0; i<kCode_COUNT; i++)
		timeouts[i] = 0;
	load_def_profile();
}

void inp_kb::set_devid(uint32_t)
{
	return;
}

void inp_kb::load_profile(s_profile * prof)
{
	map[INP_UP]    = prof->kbd.UP;
	map[INP_DOWN]  = prof->kbd.DOWN;
	map[INP_LEFT]  = prof->kbd.LEFT;
	map[INP_RIGHT] = prof->kbd.RIGHT;
	map[INP_A]     = prof->kbd.A;
	map[INP_B]     = prof->kbd.B;
	map[INP_C]     = prof->kbd.C;
	map[INP_D]     = prof->kbd.D;
	map[INP_AB]    = prof->kbd.AB;
	map[INP_BC]    = prof->kbd.BC;
	map[INP_ST]    = prof->kbd.START;
}

void inp_kb::load_def_profile()
{
	map[INP_UP]    = kC_Up;
	map[INP_DOWN]  = kC_Down;
	map[INP_LEFT]  = kC_Left;
	map[INP_RIGHT] = kC_Right;
	map[INP_A]     = kC_Z;
	map[INP_B]     = kC_X;
	map[INP_C]     = kC_C;
	map[INP_D]     = kC_A;
	map[INP_AB]    = kC_S;
	map[INP_BC]    = kC_D;
	map[INP_ST]    = kC_Q;
}



inp_js::inp_js()
{
	joy_id = 1;
	load_def_profile();
}

void inp_js::load_profile(s_profile * prof)
{
	map[INP_UP]    = INP_AXIS(INP_AX_Y,0);
	map[INP_DOWN]  = INP_AXIS(INP_AX_Y,1);
	map[INP_LEFT]  = INP_AXIS(INP_AX_X,0);
	map[INP_RIGHT] = INP_AXIS(INP_AX_X,1);
	map[INP_A]     = prof->joy.A;
	map[INP_B]     = prof->joy.B;
	map[INP_C]     = prof->joy.C;
	map[INP_D]     = prof->joy.D;
	map[INP_AB]    = prof->joy.AB;
	map[INP_BC]    = prof->joy.BC;
	map[INP_ST]    = prof->joy.START;
}


void inp_js::fill_raw()
{

	if (key_chk(map[INP_LEFT]))
	{
		if (raw.X > 0)
			raw.X = 0;
		raw.X--;
	}
	else if (key_chk(map[INP_RIGHT]))
	{
		if (raw.X < 0)
			raw.X = 0;
		raw.X++;
	}
	else
		raw.X = 0;

	if (key_chk(map[INP_UP]))
	{
		if (raw.Y > 0)
			raw.Y = 0;
		raw.Y--;
	}
	else if (key_chk(map[INP_DOWN]))
	{
		if (raw.Y < 0)
			raw.Y = 0;
		raw.Y++;
	}
	else
		raw.Y = 0;

	if (key_chk(map[INP_A]))
		raw.A++;
	else
		raw.A = 0;

	if (key_chk(map[INP_B]))
		raw.B++;
	else
		raw.B = 0;

	if (key_chk(map[INP_C]))
		raw.C++;
	else
		raw.C = 0;

	if (key_chk(map[INP_D]))
		raw.D++;
	else
		raw.D = 0;

	if (key_chk(map[INP_ST]))
		raw.START++;
	else
		raw.START = 0;

	if (key_chk(map[INP_AB]))
		raw.AB++;
	else
		raw.AB = 0;

	if (key_chk(map[INP_BC]))
		raw.BC++;
	else
		raw.BC = 0;
}

//void inp_js::update()
//{
//    js.update();
//    flush_cur();
//
//    for (uint32_t i=0; i<INP_KEYS; i++)
//        key_dn[i] = key_chk(map[i]);
//
//    x_axis = 0;
//    y_axis = 0;
//
//    if (key_dn[INP_LEFT])
//        x_axis -= 1;
//
//    if (key_dn[INP_RIGHT])
//        x_axis += 1;
//
//    if (key_dn[INP_UP])
//        y_axis += 1;
//
//    if (key_dn[INP_DOWN])
//        y_axis -= 1;
//
//    fill_kframes();
//}

void inp_js::load_def_profile()
{
	map[INP_UP]    = INP_AXIS(INP_AX_Y,0);
	map[INP_DOWN]  = INP_AXIS(INP_AX_Y,1);
	map[INP_LEFT]  = INP_AXIS(INP_AX_X,0);
	map[INP_RIGHT] = INP_AXIS(INP_AX_X,1);
	map[INP_A]     = 0;
	map[INP_B]     = 1;
	map[INP_C]     = 2;
	map[INP_D]     = 3;
	map[INP_AB]    = 4;
	map[INP_BC]    = 5;
	map[INP_ST]    = 6;
}

void inp_js::set_devid(uint32_t id)
{
	joy_id = id;
}

bool inp_js::key_chk(uint32_t key)
{
	if (key & 0xFF00)
	{
		key >>= 8;

		sf::Joystick::Axis ax= sf::Joystick::X;

		switch( (key >> 1) & 0xF)
		{
		case INP_AX_Y:
			ax = sf::Joystick::Y;
			break;
		case INP_AX_Z:
			ax = sf::Joystick::Z;
			break;
		case INP_AX_R:
			ax = sf::Joystick::R;
			break;
		case INP_AX_U:
			ax = sf::Joystick::U;
			break;
		case INP_AX_V:
			ax = sf::Joystick::V;
			break;
		case INP_AX_PX:
			ax = sf::Joystick::PovX;
			break;
		case INP_AX_PY:
			ax = sf::Joystick::PovY;
			break;
		case INP_AX_X:
		default:
			ax = sf::Joystick::X;
		}

		if (key & 0x1)
			return js.getAxisPosition(joy_id,ax) >= 50;
		else
			return js.getAxisPosition(joy_id,ax) <= -50;
	}
	else
	{
		return js.isButtonPressed(joy_id, key & 0x1F);
	}
}

bool inp_both::rawPressed(uint32_t key, int32_t timeout)
{
	return kb.rawPressed(key, timeout);
}

bool inp_both::rawHit(uint32_t key)
{
	return kb.rawHit(key);
}


void inp_both::load_def_profile()
{
	kb.load_def_profile();
	js.load_def_profile();
}

void inp_both::load_profile(s_profile * prof)
{
	kb.load_profile(prof);
	js.load_profile(prof);
}

void inp_both::fill_raw()
{
	kb.fill_raw();
	js.fill_raw();

	raw.X = kb.raw.X + js.raw.X;
	raw.Y = kb.raw.Y + js.raw.Y;
	raw.A = kb.raw.A + js.raw.A;
	raw.B = kb.raw.B + js.raw.B;
	raw.C = kb.raw.C + js.raw.C;
	raw.D = kb.raw.D + js.raw.D;
	raw.AB = kb.raw.AB + js.raw.AB;
	raw.BC = kb.raw.BC + js.raw.BC;
	raw.START = kb.raw.START + js.raw.START;
}

void inp_both::set_devid(uint32_t id)
{
	kb.set_devid(id);
	js.set_devid(id);
}




inp_ab *inp_createinput(inp_types type)
{
	switch(type)
	{
	case INP_TYPE_KB:
		return new inp_kb;
	case INP_TYPE_JOY:
		return new inp_js;
	case INP_TYPE_BOTH:
		return new inp_both;
	case INP_TYPE_NONE:
	default:
		return new inp_none;
	}
}
