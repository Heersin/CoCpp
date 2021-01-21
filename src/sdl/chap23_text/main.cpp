#include "media.h"

Timer global_timer;
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
    TextureWrapper text_line;
    TextureWrapper time_panel;

    // static 
    //SpriteFactory sprite;
    SpriteFactory button_sprite;

    // button
    ButtonWrapper return_button(160, 60);

    // string
    std::stringstream time_text;

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
    MusicPlayer unique_player(1,3);

    // test music
    unique_player.loadMusic("rsrc/music.wav");
    unique_player.loadMusicChunk("rsrc/0.wav");
    unique_player.loadMusicChunk("rsrc/1.wav");
    unique_player.loadMusicChunk("rsrc/2.wav");

    // play music 0
    unique_player.playMusic(0);

    // load spirite
    /*
    sprite.procSprite(
        &base_render,
        "rsrc/ani.png",
        1,
        9
    );
    */

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
    //stage.loadFromFile(&base_render, "rsrc/night.png");
    FocusBg stage(&base_render, "rsrc/night.png");

    // load role
    // render role
    Role role(&base_render, "rsrc/kizuna.png");

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
        // unique_key_handler.handleKey();

        // render stage
        stage.focus_render(role);

        // render role
        role.render();
        role.handleEvent(e);

        // render text
        text_line.render(
            &base_render,
            0,
            SCREEN_HEIGHT / 5
        );

        // render time panel
        time_text.str("");
        time_text << "Stop Watcher Walk Time : " << (global_timer.getTicks() / 1000.f );
        time_panel.loadFromText(&base_render, &base_font, time_text.str().c_str(), TTF_COLOR_BLACK);
        time_panel.render(&base_render, SCREEN_WIDTH / 5 * 2, 0);

        // render animation
        // animation angle is 270
        //sprite.renderClip(&base_render, SCREEN_WIDTH / 2, 0, 0, frame % 8, 270);

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
            // Clear Screen
        SDL_SetRenderDrawColor(base_render, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(base_render);
        ++frame;
    }

    // close and clean
    // clean
    text_line.freeTexture();
    time_panel.freeTexture();
    //sprite.freeSprite();
    button_sprite.freeSprite();
    SDL_DestroyRenderer( base_render );
    SDL_DestroyWindow( base_window );

    // close
    Close_SDL_lib();
    return 0;
}