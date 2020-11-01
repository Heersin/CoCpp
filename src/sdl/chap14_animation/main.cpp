#include "media.h"

// >>>>>>>>>>>>>> Main Part <<<<<<<<<<<<<<<<<
int main()
{
    // surface on window
    SDL_Window *base_window;
    SDL_Surface *base_surface;

    // render on window
    SDL_Renderer *base_render;

    base_window = NULL;
    base_surface = NULL;
    base_render = NULL;

    // Texture Wrapper
    TextureWrapper stage;
    TextureWrapper role;
    // static 
    SpriteFactory sprite;

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
                "SDL Example"))
    {
        printf("Failed to create default window\n");
        Close_SDL_lib();
        return -1;
    }

    // create renderer on window
    if(!Create_default_renderer_on_window(&base_render, &base_window))
    {
        printf("Failed to create renderer on window\n");
        SDL_DestroyWindow( base_window );
        Close_SDL_lib();
        return -1;
    }


// >>>>>>>>>>>>>>>> Main Event Loop <<<<<<<<<<<<<<<<<<<<<<,
    bool quit = false;
    SDL_Event e;

    // load spirite
    sprite.procSprite(
        &base_render,
        "rsrc/ani.png",
        1,
        9
    );

    // Clear Screen
    SDL_SetRenderDrawColor(base_render, 0xFF, 0xFF, 0xFF, 0xFF);
    SDL_RenderClear(base_render);
    
    // load stage
    // render background
    stage.loadFromFile(&base_render, "rsrc/night.png");

    // load role
    // render role
    role.loadFromFile(&base_render, "rsrc/kizuna.png");


    int frame = 0;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
            if (e.type == SDL_QUIT)
                quit = true;

        // render stage
        stage.render(&base_render, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // render role
        role.setAlpha(200);
        role.render(
            &base_render, 
            SCREEN_WIDTH / 10,
            0
        );

        // render animation
        // animation angle is 270
        sprite.renderClip(&base_render, SCREEN_WIDTH / 2, 0, 0, frame % 8, 270);

        // render clip
        SDL_RenderPresent(base_render);
        ++frame;
    }

    // close and clean
    // clean
    stage.freeTexture();
    role.freeTexture();
    sprite.freeSprite();
    SDL_DestroyRenderer( base_render );
    SDL_DestroyWindow( base_window );

    // close
    Close_SDL_lib();
    return 0;
}