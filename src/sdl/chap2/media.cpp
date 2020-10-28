#include "media.h"

// Starts Up SDL
bool Init_SDL_lib()
{
    // init SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        Log_SDL_error();
        return false;
    }
    
    // init global to NULL
    gHelloWorld = NULL;
    SCREEN_WIDTH = 640;
    SCREEN_HEIGHT = 480;
    return true;
}

// Create Window
bool Create_default_window(
    SDL_Window *window,
    SDL_Surface *surface,
    int width,
    int height,
    const char* title)
{
    window = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN);
    
    if(window == NULL)
    {
        Log_SDL_error();
        return false;
    }

    surface = SDL_GetWindowSurface(window);
    
    if(surface == NULL)
    {
        Log_SDL_error();
        return false;
    }

    return true;
}

// Loads media
bool Load_media()
{
    gHelloWorld = SDL_LoadBMP("rsrc/02.bmp");
    if(gHelloWorld == NULL){
        Log_SDL_error();
        return false;
    }
    return true;
}

// Free media and shut down SDL
void Close_SDL_lib()
{
    if(gHelloWorld != NULL)
        SDL_FreeSurface(gHelloWorld);
    SDL_Quit();
}

void Log_SDL_error()
{
    printf("SDL Error : %s \n", SDL_GetError());
}


int main()
{
    SDL_Window *base_window;
    SDL_Surface *base_surface;
    // init 
    if(!Init_SDL_lib())
    {
        printf("Failed to init SDL\n");
        return -1;
    }

    // create our window
    if(!Create_default_window(
                base_window,
                base_surface,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                "SDL Chap2"))
    {
        printf("Failed to create default window");
        Close_SDL_lib();
        return -1;
    }

    if(!Load_media())
    {
        printf("Failed to load image\n");
        SDL_DestroyWindow( base_window );
        Close_SDL_lib();
        return -1;
    }

    SDL_BlitSurface(gHelloWorld, NULL, base_surface, NULL);
    SDL_UpdateWindowSurface(base_window);
    // Perform Bad on KDE (x11 based)
    // which showed an empty window
    // SDL_Delay(2000);

    // close and clean
    SDL_DestroyWindow( base_window );
    Close_SDL_lib();
    return 0;
}
