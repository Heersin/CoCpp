#include "role.h"
Role::Role(SDL_Renderer **global_render, std::string img_path) : texture()
{
    x_pos = 0;
    y_pos = 0;

    vel_x = 0;
    vel_y = 0;
    
    base_renderer_p = global_render;
    texture.loadFromFile(base_renderer_p, img_path);
}

void Role::handleEvent( SDL_event &e )
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                vel_y -= Role_VEL;
                break;
            
            case SDLK_DOWN:
                vel_y += Role_VEL;
                break;

            case SDLK_RIGHT:
                vel_x += Role_VEL;
                break;
            
            case SDLK_LEFT:
                vel_x -= Role_VEL;
                break;
        }
    }
}

void Role::move()
{
    // should set up a global var file I think
    int SCREEN_HEIGHT = 720;
    int SCREEN_WIDTH = 1280;
    x_pos += vel_x;

    // bound limit
    if ((x_pos < 0) || (x_pos + ROLE_WIDTH > SCREEN_WIDTH))
        x_pos -= vel_x;
    
    // then the up and down
    y_pos += vel_y;
    if ((y_pos < 0) || (y_pos + ROLE_HEIGHT > SCREEN_HEIGHT))
        y_pos -= vel_y;
}

void Role::render()
{
    texture.render(base_renderer_p, x_pos, y_pos, ROLE_WIDTH, ROLE_HEIGHT);
}