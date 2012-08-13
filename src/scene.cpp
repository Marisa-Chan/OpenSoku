#include "global_types.h"
#include <math.h>
#include "scene.h"


#define CHAR_PADDING  40
#define VERT_SCALE    2.0
#define SCR_WIDTH     640.0
#define BKG_WIDTH     1280.0
#define VERT_ZERO_PNT 140.0
#define CHAR_VERT_POS 420.0
#define BKG_VERT_POS  946.0
#define BKG_HOR_PAD   60.0

#define CAM_SPEED     0.3

void c_scene::set_camera(float x1, float y1, float x2, float y2)
{
        float xdist = fabs(x1-x2)+CHAR_PADDING * 2;
        float ydist = fabs(y1-y2);

        float sq = sqrt(ydist*VERT_SCALE*
                        ydist*VERT_SCALE+
                        xdist*xdist);

        float new_scale = 1.0;

        if (sq > 0)
            new_scale = SCR_WIDTH/sq;

        if (new_scale > 1.0)
            new_scale = 1.0;
        if (new_scale < 0.5)
            new_scale = 0.5;

        float xpos = (x1+x2+CHAR_PADDING * 2)/2.0 - (SCR_WIDTH/2.0)/new_scale - CHAR_PADDING;

        if (xpos < 0)
            xpos = 0;

        if (xpos >= (BKG_WIDTH - SCR_WIDTH/new_scale))
            xpos  = (BKG_WIDTH - SCR_WIDTH/new_scale);

        float ypos = (y1+y2)/2.0 - VERT_ZERO_PNT/new_scale;

        if (ypos < 0)
            ypos = 0;

        if (ypos >= CHAR_VERT_POS * (new_scale -0.5)*2.0)
            ypos  = CHAR_VERT_POS * (new_scale -0.5)*2.0;

        cam.x = xpos;
        cam.y = ypos;
        cam.scale = new_scale;

}

void c_scene::apply_camera()
{
        gr_reset_state(1);
        gr_plane_translate(1,0,CHAR_VERT_POS+cam.y);
        gr_plane_scale(1,cam.scale,cam.scale);
        gr_plane_translate(1,-cam.x,0);

        gr_reset_state(2);
        gr_plane_translate(2,0,CHAR_VERT_POS+cam.y);
        gr_plane_scale(2,cam.scale,cam.scale);
        gr_plane_translate(2,-cam.x-BKG_HOR_PAD,-BKG_VERT_POS);
}

void c_scene::upd_camera(float x1, float y1, float x2, float y2)
{
    s_camera tmp = cam;
    set_camera(x1,y1,x2,y2);

    cam.x = tmp.x + (cam.x - tmp.x) * CAM_SPEED;
    cam.y = tmp.y + (cam.y - tmp.y) * CAM_SPEED;
    cam.scale = tmp.scale + (cam.scale - tmp.scale) * CAM_SPEED;

    apply_camera();
}
