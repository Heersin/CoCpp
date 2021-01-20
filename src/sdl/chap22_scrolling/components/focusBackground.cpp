#include "focusBackground.h"

FocusBg::FocusBg(SDL_Renderer **pr, std::string img_path):scroll()
{
    base_renderer_p = pr;
    scroll.loadFromFile(base_renderer_p, img_path);
}

FocusBg::~FocusBg()
{
    scroll.freeTexture();
}

void FocusBg::focus_render(Role& singleton_role)
{
    int SCREEN_HEIGHT = 720;
    int SCREEN_WIDTH = 1280;
    const int DEFAULT_CAMERA_WIDTH = 50;
    const int DEFAULT_CAMERA_HEIGHT = 30;

    int camera_x, camera_y;

    int role_x, role_y;
    int role_w, role_h;
    role_x = singleton_role.getX();
    role_y = singleton_role.getY();
    role_w = singleton_role.getW();
    role_h = singleton_role.getH();

    camera_x = role_x + role_w / 2 - DEFAULT_CAMERA_WIDTH / 2;
    camera_y = role_y + role_h / 2 - DEFAULT_CAMERA_HEIGHT / 2;

    // bound limit
    if (camera_x < 0)
        camera_x = 0;
    if (camera_y < 0)
        camera_y = 0;
    if (camera_x > SCREEN_WIDTH - DEFAULT_CAMERA_WIDTH)
        camera_x = SCREEN_WIDTH - DEFAULT_CAMERA_WIDTH;
    if (camera_y > SCREEN_HEIGHT - DEFAULT_CAMERA_HEIGHT)
        camera_y = SCREEN_HEIGHT - DEFAULT_CAMERA_HEIGHT;

    // render
    scroll.render(base_renderer_p, camera_x, camera_y, DEFAULT_CAMERA_WIDTH, DEFAULT_CAMERA_HEIGHT);
}