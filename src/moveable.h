#ifndef MOVEABLE_H_INCLUDED
#define MOVEABLE_H_INCLUDED

#define BKG_WIDTH     1280

enum s_border
{
    BORD_LEFT  = 1,
    BORD_CENT  = 0,
    BORD_RIGHT = -1
};


class moveable
{
    public :

    float x;
    float y;
    int8_t dir;

    float h_inerc;
    float v_inerc;
    float v_force;

    float angX;
    float angY;
    float angZ;

    float x_off;
    float y_off;

    float scaleX;
    float scaleY;

	uint8_t  c_A;
	uint8_t  c_R;
	uint8_t  c_G;
	uint8_t  c_B;

	bool  y_to_down;

	int16_t rs_w;
	int16_t rs_h;
	bool scale_real;

	moveable();

	void setXY(float x, float y);
	void setX(float x);
	void setY(float y);
	float getX();
	float getY();
	void setOrigin(float x, float y);
	void reset_ofs();

	void set_vec_speed(float angle, float speed);
	void set_vec_speed_2(float angle, float speed);

	void set_real_size(int16_t w, int16_t h);

	s_border get_border_near();
    float getlvl_height();
    float getlvl_height(float dx);

    bool char_on_ground();

};

void init_lvl_height();
void setlvl_height_rng(int32_t from, int32_t to, float lvl);


#endif // MOVEABLE_H_INCLUDED
