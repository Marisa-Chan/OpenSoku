#ifndef EFFECTS_H_INCLUDED
#define EFFECTS_H_INCLUDED

void init_effects();
void add_infoeffect(int32_t idx, int8_t order);
void update_infoeffect();
void draw_infoeffect(int8_t order);


void draw_weather_bkg(int8_t sky_id);

#endif // EFFECTS_H_INCLUDED
