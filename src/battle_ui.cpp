#include "global_types.h"
#include "battle_ui.h"


battle_ui_std::battle_ui_std()
{
    init();
}

battle_ui_std::~battle_ui_std()
{

}

void battle_ui_std::init()
{
    upper.load_dat("data/battle","battleUpper.dat");
    under.load_dat("data/battle","battleUnder.dat");
    combo.load_dat("data/battle","combo.dat");

    for(int8_t i=0; i < 2; i++)
    {
        btl_std_plr *pl = &player[i];

        pl->lifeBarB = upper.get_gui_t0(10 + i);
        pl->lifeUnderB = upper.get_gui_t0(15 + i);

        pl->lifeBarB->renderable = true;
        pl->lifeUnderB->renderable = true;

        pl->win[0] = upper.get_gui_t0(20 + i * 5);
        pl->win[1] = upper.get_gui_t0(21 + i * 5);

        for (int8_t j=0; j < 5; j++)
        {
            pl->borderBarB[j] = under.get_gui_t0(10 * (2 + i) + j);
            pl->borderBarCrashB[j] = under.get_gui_t0(10 * (10 + i) + j);
            pl->borderBarFullB[j] = under.get_gui_t0(10 * (4 + i) + j);
            pl->borderGaugeB[j] = under.get_gui_t0(10 * (6 + i) + j);
            pl->borderGaugeCrashB[j] = under.get_gui_t0(10 * (8 + i) + j);

            pl->borderBarB[j]->renderable = true;
            pl->borderGaugeB[j]->renderable = true;

            pl->cardBarBigB[j] = under.get_gui_t0(10 * (12 + i) + j);
            pl->cardFaceDown[j] = under.get_gui_t0(10 * (14 + i) + j);
            pl->cardGaugeBigB[j] = under.get_gui_t0(10 * (20 + i) + j);
            pl->cardGaugeBigB2[j] = under.get_gui_t0(205 + 10 * i + j);

            pl->cardGaugeBigB[j]->renderable = true;

            int32_t x_corr = i * pl->cardBarBigB[j]->getTexW();
            pl->addedCards[j].setXY(pl->cardBarBigB[j]->getX() - x_corr,pl->cardBarBigB[j]->getY());

            pl->cardBlink[j] = NULL;
        }

        float scl = (float)pl->cardBarBigB[1]->getTexW() / (float)pl->cardBarBigB[0]->getTexW();

        for (int8_t j=1; j < 5; j++)
            pl->addedCards[j].setScale(scl,scl);
    }
}

void battle_ui_std::link(char_c *p1, char_c *p2)
{
    player[0].chr = p1;
    player[0].health = p1->health;
    player[0].health_prev = p1->health_prev;
    player[1].chr = p2;
    player[1].health = p2->health;
    player[1].health_prev = p2->health_prev;
}

void battle_ui_std::update()
{
    for(int8_t i=0; i < 2; i++)
    {
        btl_std_plr *pl = &player[i];
        char_c *chr = pl->chr;

        if ( pl->health >= chr->health )
            pl->health = chr->health;
        else
        {
            pl->health = pl->health + chr->max_health / 120;
            if ( pl->health >= chr->health )
                pl->health = chr->health;
        }

        if ( pl->health_prev <= chr->health_prev )
            pl->health_prev = chr->health_prev;
        else
        {
            pl->health_prev = pl->health_prev - chr->max_health / 120;
            if ( pl->health_prev <= chr->health_prev )
                pl->health_prev = chr->health_prev;
        }

        if ( chr->win_count <= 0 )
            pl->win[0]->renderable = false;
        else
            pl->win[0]->renderable = true;

        if ( chr->win_count <= 1 )
            pl->win[1]->renderable = false;
        else
            pl->win[1]->renderable = true;

        pl->borderBarB[0]->renderable = chr->spell_energy < 200;
        pl->borderBarFullB[0]->renderable = pl->borderBarB[0]->renderable == 0;
        pl->borderGaugeB[0]->renderable = chr->max_spell_energy > 0;
        pl->borderGaugeCrashB[0]->renderable = pl->borderGaugeB[0]->renderable == 0;
        pl->borderBarCrashB[0]->renderable = chr->max_spell_energy == 0;

        pl->borderBarB[1]->renderable = chr->spell_energy < 400;
        pl->borderBarFullB[1]->renderable = pl->borderBarB[1]->renderable == 0;
        pl->borderGaugeB[1]->renderable = chr->max_spell_energy > 200;
        pl->borderGaugeCrashB[1]->renderable = pl->borderGaugeB[1]->renderable == 0;
        pl->borderBarCrashB[1]->renderable = chr->max_spell_energy == 200;

        pl->borderBarB[2]->renderable = chr->spell_energy < 600;
        pl->borderBarFullB[2]->renderable = pl->borderBarB[2]->renderable == 0;
        pl->borderGaugeB[2]->renderable = chr->max_spell_energy > 400;
        pl->borderGaugeCrashB[2]->renderable = pl->borderGaugeB[2]->renderable == 0;
        pl->borderBarCrashB[2]->renderable = chr->max_spell_energy == 400;

        pl->borderBarB[3]->renderable = chr->spell_energy < 800;
        pl->borderBarFullB[3]->renderable = pl->borderBarB[3]->renderable == 0;
        pl->borderGaugeB[3]->renderable = chr->max_spell_energy > 600;
        pl->borderGaugeCrashB[3]->renderable = pl->borderGaugeB[3]->renderable == 0;
        pl->borderBarCrashB[3]->renderable = chr->max_spell_energy == 600;

        pl->borderBarB[4]->renderable = chr->spell_energy < 1000;
        pl->borderBarFullB[4]->renderable = pl->borderBarB[4]->renderable == 0;
        pl->borderGaugeB[4]->renderable = chr->max_spell_energy > 800;
        pl->borderGaugeCrashB[4]->renderable = pl->borderGaugeB[4]->renderable == 0;
        pl->borderBarCrashB[4]->renderable = chr->max_spell_energy == 800;

        for (int8_t j=0; j<5; j++)
                pl->addedCards[j].nullTexture();

        if (chr->field_570)
        {
            for(int8_t j=0; j < 5; j++)
            {
                pl->cardFaceDown[j]->renderable = true;
                pl->cardGaugeBigB[j]->renderable = true;
                pl->cardGaugeBigB2[j]->renderable = false;

                if (pl->cardBlink[j])
                {
                    pl->cardBlink[j]->active = false;
                    pl->cardBlink[j] = NULL;
                }
            }
        }
        else
        {
            int32_t crd_cnt = chr->cards_added + chr->cards_shuffle.size();

            //Trying it in loop
            for(int8_t j=0; j<5; j++)
                pl->cardBarBigB[j]->renderable = (chr->cards_added == j && crd_cnt > j);
//            pl->cardBarBigB[0]->renderable = (chr->cards_added == 0 && crd_cnt > 0);
//            pl->cardBarBigB[1]->renderable = (chr->cards_added == 1 && crd_cnt > 1);
//            pl->cardBarBigB[2]->renderable = (chr->cards_added == 2 && crd_cnt > 2);
//            pl->cardBarBigB[3]->renderable = (chr->cards_added == 3 && crd_cnt > 3);
//            pl->cardBarBigB[4]->renderable = (chr->cards_added == 4 && crd_cnt > 4);

            int32_t cost = 0;

            if ( chr->cards_added )
            {
                cost = chr->cards_active.front()->cost;
                if (weather_get() == 2)
                    if (cost > 1)
                        cost--;
            }

            if (cost > crd_cnt)
                cost = 15;

            //Trying it in loop
            for(int8_t j=0; j<5; j++)
            {
                pl->cardFaceDown[j]->renderable = false;
                pl->cardGaugeBigB[j]->renderable = (cost > j) && (crd_cnt > j);
                pl->cardGaugeBigB2[j]->renderable = (cost <= j) && (crd_cnt > j);

                if (j > cost)
                    if (pl->cardBlink[j])
                    {
                        pl->cardBlink[j]->active = false;
                        pl->cardBlink[j] = NULL;
                    }
            }
//            pl->cardFaceDown[0]->renderable = false;
//            pl->cardGaugeBigB[0]->renderable = (cost > 0) && (crd_cnt > 0);
//            pl->cardGaugeBigB2[0]->renderable = (cost <= 0) && (crd_cnt > 0);
//
//            pl->cardFaceDown[1]->renderable = false;
//            pl->cardGaugeBigB[1]->renderable = (cost > 1) && (crd_cnt > 1);
//            pl->cardGaugeBigB2[1]->renderable = (cost <= 1) && (crd_cnt > 1);
//
//            pl->cardFaceDown[2]->renderable = false;
//            pl->cardGaugeBigB[2]->renderable = (cost > 2) && (crd_cnt > 2);
//            pl->cardGaugeBigB2[2]->renderable = (cost <= 2) && (crd_cnt > 2);
//
//            pl->cardFaceDown[3]->renderable = false;
//            pl->cardGaugeBigB[3]->renderable = (cost > 3) && (crd_cnt > 3);
//            pl->cardGaugeBigB2[3]->renderable = (cost <= 3) && (crd_cnt > 3);
//
//            pl->cardFaceDown[4]->renderable = false;
//            pl->cardGaugeBigB[4]->renderable = (cost > 4) && (crd_cnt > 4);
//            pl->cardGaugeBigB2[4]->renderable = (cost <= 4) && (crd_cnt > 4);

            for (uint8_t j=0; j<chr->cards_active.size(); j++)
                pl->addedCards[j].setTexture(chr->cards_active[j]->tex);

            if ((uint8_t )cost <= chr->cards_active.size())
            {
                for (uint8_t j=0; j<cost; j++)
                    if (!pl->cardBlink[j])
                        pl->cardBlink[j] = inf_eff.addeffect(32 + (j > 0),pl->addedCards[j].getX(), -pl->addedCards[j].getY(), 1, 1);
            }
            else
            {
                for (uint8_t j=0; j<5; j++)
                    if (pl->cardBlink[j])
                    {
                        pl->cardBlink[j]->active = false;
                        pl->cardBlink[j] = NULL;
                    }
            }
        }
    }

    inf_eff.update();
}

void battle_ui_std::draw()
{
    for(int8_t i=0; i < 2; i++)
    {
        btl_std_plr *pl = &player[i];
        char_c *chr = pl->chr;
        int8_t pl_cr = 1 - i*2;

        int32_t lsz = ceil((float)pl->lifeBarB->getTexW() * (float)pl->health / (float)chr->max_health);

        pl->lifeBarB->setRect(pl->lifeBarB->getTexW() - lsz, 0, lsz, pl->lifeBarB->getTexH());
        pl->lifeBarB->setDXDY(pl_cr*(pl->lifeBarB->getTexW() - lsz),0);

        int32_t lpsz = ceil((float)pl->lifeUnderB->getTexW() * (float)pl->health_prev / (float)chr->max_health);

        pl->lifeUnderB->setRect(pl->lifeUnderB->getTexW() - lpsz, 0, lpsz, pl->lifeUnderB->getTexH());
        pl->lifeUnderB->setDXDY(pl_cr*(pl->lifeUnderB->getTexW() - lpsz),0);

        for(int8_t j=0; j < 5; j++)
        {
            int32_t sp_lvl = chr->spell_energy - j * 200;
            if (sp_lvl >= 0 && sp_lvl < 200)
            {
                int32_t sp_sz = ceil((float)pl->borderBarB[j]->getTexW() * (float)sp_lvl / 200.0);

                pl->borderBarB[j]->setRect(pl->borderBarB[j]->getTexW() - sp_sz,0,sp_sz, pl->borderBarB[j]->getTexH());
                pl->borderBarB[j]->setDXDY(pl_cr*(pl->borderBarB[j]->getTexW() - sp_sz),0);
            }
            else if (sp_lvl < 0)
            {
                pl->borderBarB[j]->setRect(0,0,0,0);
                pl->borderBarB[j]->setDXDY(0,0);
            }
            else if (sp_lvl >= 200)
            {
                pl->borderBarB[j]->setRect(0,0,pl->borderBarB[j]->getTexW(),pl->borderBarB[j]->getTexH());
                pl->borderBarB[j]->setDXDY(0,0);
            }

            int32_t spc_sz = ceil((float)pl->borderBarCrashB[j]->getTexH() * (float)chr->crshd_sp_brdrs_timer / 4800.0);
            pl->borderBarCrashB[j]->setRect(0, pl->borderBarCrashB[j]->getTexH() - spc_sz, pl->borderBarCrashB[j]->getTexW(),spc_sz);
            pl->borderBarCrashB[j]->setDXDY(0,pl->borderBarCrashB[j]->getTexH() - spc_sz);

            int32_t crd_sz = ceil((float)pl->cardBarBigB[j]->getTexH() * (float)chr->current_card_energy / 500.0);
            pl->cardBarBigB[j]->setRect(0, pl->cardBarBigB[j]->getTexH() - crd_sz, pl->cardBarBigB[j]->getTexW(),crd_sz);
            pl->cardBarBigB[j]->setDXDY(0,pl->cardBarBigB[j]->getTexH() - crd_sz);
        }

        gr_setscale_sprite(chr->player_face,1 - 2 * i,1);
        gr_setxy_sprite(chr->player_face,640 * i,1);
    }

    for(int8_t i=0; i < 2; i++)
        gr_draw_sprite(player[i].chr->player_face,gr_alpha,0);

    under.draw_all(0);

    inf_eff.draw(2,0);

    for (int32_t i=0; i<2; i++)
        for (uint8_t j=0; j<5; j++)
            player[i].addedCards[j].draw(0);

    inf_eff.draw(1,0);

    upper.draw_all(0);

    inf_eff.draw(0,0);
}
