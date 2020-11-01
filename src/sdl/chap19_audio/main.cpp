#include "media.h"

// >>>>>>>>>>>>>> Main Part <<<<<<<<<<<<<<<<<
int main()
{
    // surface on window
    SDL_Window *base_window;
    SDL_Surface *base_surface;

    // render on window
    SDL_Renderer *base_render;
    TTF_Font *base_font;

    base_window = NULL;
    base_surface = NULL;
    base_render = NULL;
    base_font = NULL;

    // Texture Wrapper
    TextureWrapper stage;
    TextureWrapper role;
    TextureWrapper text_line;
    // static 
    SpriteFactory sprite;
    SpriteFactory button_sprite;

    // button
    ButtonWrapper return_button(160, 60);

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

    // create font
    if( !Create_ttf_font(&base_font, "rsrc/lazy.ttf", 28) )
    {
        printf("Failed to load ttf font file\n");
        SDL_DestroyWindow(base_window);
        SDL_DestroyRenderer( base_render );
        Close_SDL_lib();
        return -1;
    }

// >>>>>>>>>>>>>>>> Main Event Loop <<<<<<<<<<<<<<<<<<<<<<,
    bool quit = false;
    SDL_Event e;
    KeyWrapper unique_key_handler;

    // load spirite
    sprite.procSprite(
        &base_render,
        "rsrc/ani.png",
        1,
        9
    );

    // load button sprite
    button_sprite.procSprite(
        &base_render,
        "rsrc/button.png",
        1,
        1
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

    // add an text
    text_line.loadFromText(&base_render, &base_font, "Night Class Room", TTF_COLOR_BLACK); 

    int frame = 0;

    while(!quit)
    {
        while(SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;

            return_button.handleEvent(&e);
        }

        // after poll , the key state will be refresh
        // so put key here
        unique_key_handler.handleKey();

        // render stage
        stage.render(&base_render, 0,0, SCREEN_WIDTH, SCREEN_HEIGHT);

        // render role
        role.setAlpha(200);
        role.render(
            &base_render, 
            SCREEN_WIDTH / 10,
            0
        );

        // render text
        text_line.render(
            &base_render,
            0,
            SCREEN_HEIGHT / 5
        );

        // render animation
        // animation angle is 270
        sprite.renderClip(&base_render, SCREEN_WIDTH / 2, 0, 0, frame % 8, 270);

        // Render button
        // set button in left
        return_button.setPosition(
            SCREEN_WIDTH - return_button.getWidth(), 
            SCREEN_HEIGHT - return_button.getHeight());
        // render
        return_button.renderBySprite(
            &base_render,
            &button_sprite, 
            0,
            0,
            0);

        // render clip
        SDL_RenderPresent(base_render);
        ++frame;
    }

    // close and clean
    // clean
    stage.freeTexture();
    role.freeTexture();
    text_line.freeTexture();
    sprite.freeSprite();
    button_sprite.freeSprite();
    SDL_DestroyRenderer( base_render );
    SDL_DestroyWindow( base_window );

    // close
    Close_SDL_lib();
    return 0;
}