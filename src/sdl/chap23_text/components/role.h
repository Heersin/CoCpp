#ifndef _H_ROLE
#define _H_ROLE
#include "../base_com/wrapper.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>
class Role
{
    public:
        // As a rectangle
        static const int ROLE_WIDTH = 100;
        static const int ROLE_HEIGHT = 160;

        // the amplitude of every move
        static const int MOVE_DELTA = 10;

        // constructor
        Role(SDL_Renderer **pr, std::string img_path);

        // deconstructor
        ~Role();

        // handle key press
        void handleEvent( SDL_Event &e );

        // functionalities
        void move();

        // show the dot on the screen
        void render();


        // getter
        int getX();
        int getY();
        int getW();
        int getH();

    private:
        int x_pos, y_pos;
        int vel_x, vel_y;

        TextureWrapper texture;
        SDL_Renderer **base_renderer_p;
};

#endif