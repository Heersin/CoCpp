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

    // init SDL_IMAGE
    int imgFlags = IMG_INIT_PNG;
    if ( !( IMG_Init(imgFlags) & imgFlags ) )
    {
        printf("SDL cannot init error : %s\n", IMG_GetError());
        return false;
    }
    
    // init global to NULL
    g_current_surface = NULL;

    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
        g_keypress_surface_array[i] = NULL;

    SCREEN_WIDTH = 1280;
    SCREEN_HEIGHT = 960;
    return true;
}

// Create Window
bool Create_default_window(
    SDL_Window **pwindow,
    SDL_Surface **psurface,
    int width,
    int height,
    const char* title)
{
    *pwindow = SDL_CreateWindow(
        title, 
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        width,
        height,
        SDL_WINDOW_SHOWN);
    
    if(*pwindow == NULL)
    {
        Log_SDL_error();
        return false;
    }

    *psurface = SDL_GetWindowSurface(*pwindow);
    
    if(*psurface == NULL)
    {
        Log_SDL_error();
        return false;
    }

    return true;
}

// Loads media
bool Load_media()
{
    bool success = true;

    g_current_surface = Load_surface("rsrc/up.png");
    if (g_current_surface == NULL)
    {
        printf("Failed up\n");
        success = false;
    }
    g_keypress_surface_array[KEY_PRESS_SURFACE_UP] = g_current_surface;


    g_current_surface = Load_surface("rsrc/down.png");
    if (g_current_surface == NULL)
    {
        printf("Failed down\n");
        success = false;
    }
    g_keypress_surface_array[KEY_PRESS_SURFACE_DOWN] = g_current_surface;

    g_current_surface = Load_surface("rsrc/left.png");
    if (g_current_surface == NULL)
    {
        printf("Failed left\n");
        success = false;
    }
    g_keypress_surface_array[KEY_PRESS_SURFACE_LEFT] = g_current_surface;

    g_current_surface = Load_surface("rsrc/right.png");
    if (g_current_surface == NULL)
    {
        printf("Failed right\n");
        success = false;
    }
    g_keypress_surface_array[KEY_PRESS_SURFACE_RIGHT] = g_current_surface;

    // default
    g_current_surface = Load_surface("rsrc/default.png");
    if (g_current_surface == NULL)
    {
        printf("Failed default\n");
        success = false;
    }
    g_keypress_surface_array[KEY_PRESS_SURFACE_DEFAULT] = g_current_surface;

    return success;
}

// sub function of Load media
// load bmp by a given name
// add convert feature
SDL_Surface *Load_surface(std::string path)
{
    SDL_Surface *loaded_surface = IMG_Load(path.c_str());
    if (loaded_surface == NULL)
    {
        printf("Unable to load image %s: error : %s\n", path.c_str(), IMG_GetError());
        return NULL;
    }

    SDL_PixelFormat *format = SDL_AllocFormat(SDL_PIXELFORMAT_RGBA32);
    SDL_Surface *optimized_surface = SDL_ConvertSurface( loaded_surface, format, 0);
    SDL_FreeFormat(format);
    if (optimized_surface == NULL)
    {
        Log_SDL_error();
        SDL_FreeSurface(loaded_surface);
        return NULL;
    }

    SDL_FreeSurface(loaded_surface);
    return optimized_surface;
}

// Free media and shut down SDL
void Close_SDL_lib()
{
    for (int i = 0; i < KEY_PRESS_SURFACE_TOTAL; ++i)
    {
        if (g_keypress_surface_array[i] != NULL)
            SDL_FreeSurface(g_keypress_surface_array[i]);
        g_keypress_surface_array[i] = NULL;
    }
    IMG_Quit();
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

    base_window = NULL;
    base_surface = NULL;
    // init 
    if(!Init_SDL_lib())
    {
        printf("Failed to init SDL\n");
        return -1;
    }

    // create our window
    if(!Create_default_window(
                &base_window,
                &base_surface,
                SCREEN_WIDTH,
                SCREEN_HEIGHT,
                "SDL-Example Window "))
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


    // Perform Bad on KDE (x11 based)
    // which showed an empty window
    // SDL_Delay(2000);


    bool quit = false;
    SDL_Event e;

    // set default bmp
    g_current_surface = g_keypress_surface_array[KEY_PRESS_SURFACE_DEFAULT];

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
            
            if (e.type == SDL_KEYDOWN)
            switch(e.key.keysym.sym)
            {
                case SDLK_UP:
                g_current_surface = g_keypress_surface_array[KEY_PRESS_SURFACE_UP];
                break;

                case SDLK_DOWN:
                g_current_surface = g_keypress_surface_array[KEY_PRESS_SURFACE_DOWN];
                break;

                case SDLK_LEFT:
                g_current_surface = g_keypress_surface_array[KEY_PRESS_SURFACE_LEFT];
                break;

                case SDLK_RIGHT:
                g_current_surface = g_keypress_surface_array[KEY_PRESS_SURFACE_RIGHT];
                break;

                default:
                g_current_surface = g_keypress_surface_array[KEY_PRESS_SURFACE_DEFAULT];
                break;
            }
        }

        SDL_BlitSurface(g_current_surface, NULL, base_surface, NULL);
        SDL_UpdateWindowSurface(base_window);
    }

    // close and clean
    SDL_DestroyWindow( base_window );
    Close_SDL_lib();
    return 0;
}
