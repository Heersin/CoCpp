#include "window.h"

WindowWrapper::WindowWrapper()
{
    // initialize
    window = NULL;

    mouse_focus = false;
    keyb_focus = false;
    fullscreen = false;
    minimized = false;

    width = 0;
    height = 0;
}

bool WindowWrapper::init()
{
    int SCREEN_HEIGHT = 720;
    int SCREEN_WIDTH = 1280;

    window = SDL_CreateWindow(
        "TextBoard", 
        SDL_WINDOWPOS_UNDEFINED, 
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
        );
    
    return window != NULL;
}

SDL_Renderer* WindowWrapper::createRenderer()
{
    return SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );
}

void WindowWrapper::handleEvent(SDL_Event& e)
{
    if (e.type == SDL_WINDOWEVENT)
    {
        bool update = false;
        switch(e.window.event)
        {
            case SDL_WINDOWEVENT_SIZE_CHANGED:
                width = e.window.data1;
                height = e.window.data2;
                SDL_RenderPresent(global_render);
                break;

            case SDL_WINDOWEVENT_EXPOSED:
                SDL_RenderPresent(global_render);
                break;
            
            case SDL_WINDOWEVENT_ENTER:
                mouse_focus = true;
                update = true;
                break;
            
            // mouse leave the window
            case SDL_WINDOWEVENT_LEAVE:
                mouse_focus = false;
                update = false;
                break;

            case SDL_WINDOWEVENT_FOCUS_GAINED:
                keyb_focus = true;
                update = true;
                break;

            case SDL_WINDOWEVENT_FOCUS_LOST:
                keyb_focus = false;
                update = true;
                break;

            case SDL_WINDOWEVENT_MINIMIZED:
                minimized = true;
                break;
            
            case SDL_WINDOWEVENT_MAXIMIZED:
                minimized = false;
                break;
            
            case SDL_WINDOWEVENT_RESTORED:
                minimized = false;
                break;
        }

        if(update)
        {
            printf("mouse : %s, keyboard: %s\n",
                mouse_focus ? "On" : "Off",
                keyb_focus ? "on" : "Off");
        }
    }
}

void WindowWrapper::free()
{
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
    }

    if (global_render != NULL)
    {
        SDL_DestroyRenderer(global_render);
    }

    mouse_focus = false;
    keyb_focus = false;
    width = 0;
    height = 0;
}

int WindowWrapper::getW()
{
    return width;
}

int WindowWrapper::getH()
{
    return height;
}

bool WindowWrapper::hasMouseFocus()
{
    return mouse_focus;
}

bool WindowWrapper::hasKeyboardFocus()
{
    return keyb_focus;
}

bool WindowWrapper::isMinimized()
{
    return minimized;
}

