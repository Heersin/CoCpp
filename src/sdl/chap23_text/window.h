#ifndef _H_WINDOW
#define _H_WINDOW

#include <SDL2/SDL.h>

class WindowWrapper
{
    public:
        WindowWrapper();

        bool init();

        SDL_Renderer *createRenderer();

        // free
        void free();

        // getter
        int getW();
        int getH();

        // handle window events
        void handleEvent(SDL_Event& e);
        
        // window focus event
        bool hasMouseFocus();
        bool hasKeyboardFocus();
        bool isMinimized();

        // in fact, it's equal to createRender return
        SDL_Renderer *global_render;
    
    private:
        SDL_Window *window;

        // width and len
        int width;
        int height;

        // state
        bool mouse_focus;
        bool keyb_focus;
        bool fullscreen;
        bool minimized;

};

#endif