#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

struct s_camera
{
    float x;
    float y;
    float scale;
};

class c_scene
{
    private:

    s_camera cam;

    public:

    //c_scene();


    void set_camera(float x1, float y1, float x2, float y2);
    void upd_camera(float x1, float y1, float x2, float y2);
    void apply_camera();
};


#endif // SCENE_H_INCLUDED
