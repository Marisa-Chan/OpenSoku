#include "../global_types.h"
#include "../framedata.h"
#include "../input.h"
#include "../bullets.h"
#include "../scene.h"
#include "../character_def.h"
#include "marisa_bullets.h"
#include <math.h>

void marisa_bullets::func10()
{
    switch(viz.get_seq_id())
    {
    case 800:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }
        if ( viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 && viz.get_subseq() == 0 )
        {
            field_194 = 1;
            field_36C = 0;
        }

        field_36C++;
        h_inerc = cos(addition[0] * 3.1415/180.0) * (addition[1] + field_36C * 0.2);
        v_inerc = -sin(addition[0] * 3.1415/180.0) * (addition[1] + field_36C * 0.2);

        if (x > 1380 || x < -100 || y > 1000 || y < -100)
        {
            active = false;
            break;
        }

        if (viz.get_subseq() == 0 || viz.get_subseq() == 1)
        {
            if (sub_48C6A0(0, 0, 4))
            {
                active = false;
                break;
            }

            angZ = addition[0];

            //sub_48C4B0(v1, 0.0, v5[3], 100.0);
            if ( viz.get_frame_time() > 180 || field_190 != 0 || getlvl_height(this) >= y )
            {
                parent->play_sfx(41);
                active = false;

                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 0;

                for(int32_t i=0; i<6; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 7;
                    addbullet(parent,NULL,800,x,y,dir,1,t,3);
                }

                t[2] = 8;
                addbullet(parent,NULL,800,x,y,dir,1,t,3);

            }
        }
        else if (viz.get_subseq() >= 2 && viz.get_subseq() <= 5)
        {
            if ( sub_48C6A0(0, 0, 3) )
            {
                active = false;
                break;
            }
            angZ += 30;

            if ( viz.get_elaps_frames() == 10 )
            {
                float t[3];
                t[0] = 0;
                t[1] = 0;
                t[2] = 8;
                addbullet(parent,NULL,800,x,y,dir,1,t,3);

                for(int32_t i=0; i<4; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 7;
                    addbullet(parent,NULL, 800, x,y,dir,1,t,3);
                }
                active = false;
                break;
            }
        }
        else if (viz.get_subseq() == 6 )
        {
            if ( viz.get_elaps_frames() <= 20 )
            {
                scaleY = scaleX = (viz.get_elaps_frames() % 2) * 0.1 + 2.0;
            }
            else
            {
                scaleY *= 0.85;
                scaleX *= 0.85;

                if ( c_A < 0xAu )
                {
                    active = false;
                    break;
                }
                if ( viz.get_elaps_frames() > 10 )
                    c_A -= 10;
            }
        }
        else if (viz.get_subseq() == 7 )
        {
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

            addition[1] -= 0.4;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;

            x += dir * h_inerc;
            y += v_inerc;
            scaleY = scaleX *= 0.97;

            if (c_A < 5)
            {
                active = false;
                break;
            }
            c_A -= 5;
            c_R -= 5;
            c_G -= 5;
        }
        else if (viz.get_subseq() == 8 )
        {
            scaleX += 0.3;
            scaleY += 0.3;

            if (c_A < 20)
            {
                active = false;
                break;
            }
            c_A -= 20;
            c_R -= 20;
            c_G -= 20;
        }
        x += dir * h_inerc;
            y += v_inerc;
            if ( viz.process() )
                active = false;
            break;

        break;
    case 802:
        if ( field_190 == 5 )
        {
            active = false;
            break;
        }

        if ( viz.get_subseq() == 0 )
        {
            if ( sub_48C6A0(0, 4, 5) || x > 1380 || x < -100)
            {
                active = false;
                break;
            }
            angZ += 12.0;
            v_inerc -= 0.85;

            if ( field_190 != 0 || getlvl_height(this) >= y )
            {
                active = false;

                float t[3];
                t[0] = 0.0;
                t[1] = 0.0;
                t[2] = 1.0;
                parent->play_sfx(3);

                addbullet(parent, NULL, 802, x,y,dir, 1,t,3);

                for(int32_t i =0; i<8; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 2;
                    addbullet(parent,NULL,802,x,y,dir,1,t,3);
                }

                for(int32_t i =0; i<8; i++)
                {
                    t[0] = scene_rand_rng(360);
                    t[2] = 3;
                    addbullet(parent,NULL,802,x,y,dir,1,t,3);
                }
                t[2] = 4;
                addbullet(parent,NULL,802,x,y,dir,1,t,3);
            }
        }
        else if (viz.get_subseq() == 1)
        {
            if ( viz.get_frame() == 0 )
            {
                if ( field_190 == 6 )
                {
                    field_190 = 0;
                    field_194++;
                }
                if ( field_190 != 0)
                {
                    field_370++;
                    if ( field_370 > 5 )
                    {
                        field_370 = 0;
                        field_190 = 0;
                    }
                }

                scaleY = scaleX = (viz.get_elaps_frames() % 2) * 0.1 + 1.0;

                if ( field_194 == 0)
                    viz.set_frame(1);
            }
            else
            {
                scaleX *= 0.85;
                scaleY *= 0.85;

                if (c_A < 10)
                {
                    active = false;
                    break;
                }
                if ( viz.get_elaps_frames() > 10 )
                    c_A -= 10;
            }
        }
        else if (viz.get_subseq() == 2)
        {
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

            addition[1] -= 0.75;
            if ( addition[1] < 0.25 )
                addition[1] = 0.25;

            field_378 *= 0.995;
            angZ += field_378;
            scaleY = scaleX *= 1.005;

            if (c_A < 5)
            {
                active = false;
                break;
            }

            c_A -= 5;

            if (c_R >= 10)
            {
                c_R -= 10;
                c_G -= 10;
            }
        }
        else if (viz.get_subseq() == 3)
        {
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

            addition[1] -= 0.25;
            if ( addition[1] < 0.5 )
                addition[1] = 0.5;

            field_378 *= 0.995;
            angZ += field_378;
            scaleY = scaleX *= 0.97;

            if (c_A < 5)
            {
                active = false;
                break;
            }

            c_A -= 5;

            if (c_R >= 10)
            {
                c_R -= 10;
                c_G -= 10;
            }

        }
        else if (viz.get_subseq() == 4)
        {
            scaleX += 0.5;
            scaleY += 0.5;

            if (c_A < 25)
            {
                active = false;
                break;
            }
            c_A -= 25;
        }

        x += h_inerc*dir;
        y += v_inerc;

        if ( viz.process() )
        {
            active = false;
            break;
        }
        break;
    case 803:

        if (viz.get_subseq() == 1)
        {
            if ( field_36C % 3 == 0 )
                field_190 = 0;

            if ( char_is_shock(parent))
            {
                for (int32_t i = 0; i< 40; i++)
                {
                    scene_add_effect(parent,201,scene_rand_rng(15)+30*i*dir+x, y,dir,1);
                }
                active = false;
                break;
            }

            if (parent->get_subseq() < 5 && parent->get_seq() == 411)
            {

                x = parent->getX() + dir*44;
                y = parent->getY() + 85;
            }
            else if (parent->get_subseq() < 5 && parent->get_seq() == 415)
            {
                x = parent->getX() + dir*48;
                y = parent->getY() + 104;
            }
            else
                viz.set_subseq(2);

            field_36C++;
        }
        if ( viz.get_subseq() == 2 )
        {
            field_194 = 0;
            scaleY *= 0.8;
            scaleX += 0.1;

            if ( viz.get_elaps_frames() == 40 )
            {
                active = false;
                break;
            }
        }
        if (viz.get_subseq() == 5)
        {
            if ( bul_parent == NULL )
            {
                active = false;
                break;
            }
            angZ = scene_rand_rng(360);

            x = cos((-bul_parent->angZ) * 3.1415926/180.0) * bul_parent->field_37C * bul_parent->dir + bul_parent->x;
            y = sin((-bul_parent->angZ) * 3.1415926/180.0) * bul_parent->field_37C * bul_parent->dir + bul_parent->y;

            if ( bul_parent->field_36C != 0 )
            {
                scaleX = scaleY *= 0.8;
                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
        }
        else if (viz.get_subseq() == 4)
        {
            field_378 -= 20;
            field_37C += field_380;
            if ( field_36C != 0 )
            {
                field_380 *= 0.8;
                field_194 = 0;
                scaleY *= 0.85;

                if ( scaleY <= 0.01 )
                {
                    active = false;
                    break;
                }
            }
            else
            {
                // v70 = addition;
                field_380 += 3.0;
                //sub_4B0670(v1, 0, (v1->rend_cls.scale_y * 35.0), v1->field_37C, (v1->rend_cls.scale_y * -35.0), addition[0], 0, 0);
                //sub_48C5F0(v1, 0);
                if ( field_190 != 0)
                {
                    field_36E++;
                    if ( field_36E >= 3 )
                    {
                        field_190 = 0;
                        field_36E = 0;
                    }
                }
                if ( sub_48C640(2) )
                {
                    field_194 = 0;
                    field_36C = 1;
                    break;
                }
                else
                {
                    if ( field_194 > 0 )
                    {
                        if ( parent->get_seq() == 411 && parent->get_subseq() < 5)
                        {
                            x = dir * 44 + parent->getX();
                            y = parent->getY() + 85;
                        }
                        else if ( parent->get_seq() == 415 && parent->get_subseq() < 5)
                        {
                            x = dir * 48 + parent->getX();
                            y = parent->getY() + 104;
                        }
                        else
                        {
                            field_36C = 1;
                            break;
                        }

                        if ( char_is_shock(parent))
                        {
                            for (int32_t i = 0; i< 40; i++)
                            {
                                scene_add_effect(parent,201,scene_rand_rng(15)+30*i*dir+x, y,dir,1);
                            }
                            active = false;
                            break;
                        }
                    }
                }
            }
        }
        else if ( viz.get_subseq() == 3 )
        {
            angZ = scene_rand_rng(360);
            if ( !sub_48C6A0(0, 0, 0) )
            {
                if ( bul_parent != NULL )
                {
                    x = bul_parent->getX();
                    y = bul_parent->getY();
                    if ( bul_parent->field_36C != 0)
                    {
                        scaleY = scaleX *= 0.85;
                        if ( scaleX < 0.01 )
                        {
                            active = false;
                            return;
                        }
                    }
                }
                else
                {
                    scaleY = scaleX *= 0.85;

                    if ( scaleX < 0.01 )
                    {
                        active = false;
                        break;
                    }
                }
            }
        }
        if ( viz.process() )
            active=false;

        if ( viz.get_subseq() == 4 )
            set_real_size(field_37C,256);
        //   sub_438450(v1, v1->field_378, 0.0, v1->field_37C, 256.0);

        break;

    case 804:
        if ( viz.get_subseq() == 0 )
        {
            h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
            v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];
            x += dir * h_inerc;
            y += v_inerc;
            scaleY = scaleX = scene_rand_rng(60) * 0.01 + 0.7;

            if ( field_190 == 6 )
            {
                field_190 = 0;
                field_194 ++;
            }
            if ( field_190 != 0 || getlvl_height(this) >= y + v_inerc )
            {
                viz.next_subseq();
                scaleX = 2.0;
                scaleY = 2.0;
                break;
            }
        }
        else if (viz.get_subseq() == 1)
        {
            field_36C++;
            scaleX *= 0.85;
            scaleY *= 0.85;
            if ( c_A >= 10 )
                c_A -=10;
        }
        if (c_A < 10 || x > 1380 || x < -100 || y > 1000 || y < -100 || viz.process())
            active = false;
        break;
    case 848:
        if ( viz.get_subseq() != 0 )
        {
            if ( viz.get_subseq() == 1 )
            {
                if ( addition[1] == 0 && parent->get_seq() == 307 && parent->get_frame() > 4 )
                {
                    x = parent->getX() + dir * 67;
                    y = parent->getY() +  110;
                }
                else if (addition[1] == 1 && parent->get_seq() == 308 && parent->get_frame() > 4 )
                {
                    x = parent->getX() + dir * 30;
                    y = parent->getY() + 30;
                }
                else if (addition[1] == 2 && parent->get_seq() == 408 && parent->get_subseq() > 0)
                {
                    x = parent->getX() + dir*106;
                    y = parent->getY() + 103;
                }
            }
            else if (viz.get_subseq() == 2)
            {
                h_inerc = cos(addition[0] * 3.1415/180.0) * addition[1];
                v_inerc = -sin(addition[0] * 3.1415/180.0) * addition[1];

                addition[1] -= 0.5;
                if ( addition[1] < 0.5 )
                    addition[1] = 0.5;

                x += dir * h_inerc;
                y += v_inerc * 0.25;

                angZ += field_37C;
                scaleY = scaleX +=0.02;

                if ( viz.get_elaps_frames() >= 0 )
                {
                    if ( c_A <= 5 )
                    {
                        active = false;
                        break;
                    }
                    c_A -= 5;
                }
                x += dir * h_inerc;
                y += v_inerc * 0.25;
            }
        }
        else
        {
            x = parent->getX();
            y = parent->getY();
            if ( parent->get_seq() != 322 && parent->get_seq() != 418 && parent->get_seq() != 696 )
            {
                active = false;
                break;
            }
        }
        if ( parent->hit_stop == 0)
        {
            if ( viz.process() )
                active = false;

            if ( viz.get_elaps_frames() == 0 && viz.get_frame_time() == 0 && viz.get_frame() == 0 &&
                    (viz.get_subseq() == 2 || viz.get_subseq() == 1))
                active = false;

            if ( viz.get_subseq() == 1  && viz.get_frame_time() == 0 && viz.get_frame() == 3) //make smoke
            {
                float t[3];
                t[0] = scene_rand_rng(360);
                t[1] = scene_rand_rng(10) * 0.1;
                t[2] = 2;
                addbullet(parent,NULL,848,x,y,dir,1,t,3);
            }
        }
        break;
    default:
        if (viz.process())
            active = false;
    }
}

void marisa_bullets::set_seq_params()
{
    switch(viz.get_seq_id())
    {
    case 800:
        scaleY = scaleX = 2.0;
        field_194 = 1;
        angZ = addition[0];

        viz.set_subseq(addition[2]);

        if ( viz.get_subseq() == 0 )
        {
            //if ( addition[3] != 0 )
            //sub_4B0780(v2, 989, COERCE_UNSIGNED_INT(15.0), 5, 1, 2);
        }

        if ( viz.get_subseq() > 1 && viz.get_subseq() < 6)
            scaleY = scaleX = 1.0;

        if ( viz.get_subseq() == 7 )
        {
            scaleY = scaleX = scene_rand_rng(200) * 0.01 + 2.0;
            angZ = scene_rand_rng(360);
            addition[1] = scene_rand_rng(15) * 0.1 + 10.0;
        }
        break;
    case 802:

        field_194 = 1;
        viz.set_subseq(addition[2]);

        if ( viz.get_subseq() == 0 )
        {
            h_inerc = addition[1] * 6.0 + 6.0;
            v_inerc = addition[1] * 6.0 + 12.5;
        }
        else if ( viz.get_subseq() == 2 ||  viz.get_subseq() == 3 )
        {
            field_378 = scene_rand_rng(10) - 5.0;
            scaleY = scaleX = scene_rand_rng(200) * 0.01 + 1.0;
            angZ = scene_rand_rng(360);
            addition[1] = scene_rand_rng(15) * 0.1 + 15.0;
            addition[0] = scene_rand_rng(360);
        }
        break;
    case 803:
        field_194 = 10;
        viz.set_subseq(addition[2]);
        if ( viz.get_subseq() <= 2 )
            x_off = -40.0;
        else if ( viz.get_subseq() == 4 )
        {
            //sub_438450(v2, 0.0, 0.0, 0.0, 256.0);
            field_194 = 10;
            float t[3];
            t[0] = 0;
            t[1] = 0;
            t[2] = 3;
            addbullet(parent,this,803,x,y,dir,1,t,3);
            t[2] = 5;
            addbullet(parent,this,803,x,y,dir,1,t,3);
            set_real_size(0,0);
            //sub_438450(v2, 0.0, 0.0, 0.0, 256.0);
            field_380 = 35.0;
        }
        break;
    case 804:
        field_194 = 1;
        break;
    case 848:
        angZ = addition[0];
        viz.set_subseq(addition[2]);
        if ( viz.get_subseq() == 2 )
        {
            if ( scene_rand_rng(100) >= 50 )
                field_37C = -1.0;
            else
                field_37C = 1.0;
        }
        return;
    }
}



