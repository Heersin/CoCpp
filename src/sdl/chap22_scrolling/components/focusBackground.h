#ifndef _H_FOCUS_BG
#define _H_FOCUS_BG

#include "../base_com/wrapper.h"
#include "role.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstring>

/* 
    A scrolling background wihch follows single role
*/

class FocusBg
{
    public:
        FocusBg(SDL_Renderer **pr, std::string img_path);
        ~FocusBg();
        void focus_render(Role& singleton_role);

    private:
        TextureWrapper scroll;
        SDL_Renderer **base_renderer_p;

};;

#endif