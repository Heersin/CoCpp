#include "dot.h"
Dot::Dot()
{
    x_pos = 0;
    y_pos = 0;

    vel_x = 0;
    vel_y = 0;
}

void Dot::handleEvent( SDL_event &e )
{
    if (e.type == SDL_KEYDOWN && e.key.repeat == 0)
    {
        switch(e.key.keysym.sym)
        {
            case SDLK_UP:
                vel_y -= DOT_VEL;
                break;
            
            case SDLK_DOWN:
                vel_y += DOT_VEL;
                break;

            case SDLK_RIGHT:
                vel_x += DOT_VEL;
                break;
            
            case SDLK_LEFT:
                vel_x -= DOT_VEL;
                break;
        }
    }
}

void Dot::move()
{
    // should set up a global var file I think
    int SCREEN_HEIGHT = 720;
    int SCREEN_WIDTH = 1280;
    x_pos += vel_x;

    // bound limit
    if ((x_pos < 0) || (x_pos + DOT_WIDTH > SCREEN_WIDTH))
        x_pos -= vel_x;
    
    // then the up and down
    y_pos += vel_y;
    if ((y_pos < 0) || (y_pos + DOT_HEIGHT > SCREEN_HEIGHT))
        y_pos -= vel_y;
}