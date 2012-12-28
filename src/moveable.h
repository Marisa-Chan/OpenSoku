#ifndef MOVEABLE_H_INCLUDED
#define MOVEABLE_H_INCLUDED

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

};

#endif // MOVEABLE_H_INCLUDED
