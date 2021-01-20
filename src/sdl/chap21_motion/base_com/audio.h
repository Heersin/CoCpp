#ifndef _H_AUDIO
#define _H_AUDIO

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include "utils.h"
#include <iostream>

class MusicPlayer
{
    public:
        // player create and destroy
        MusicPlayer(int max_music, int max_chunk);
        void freePlayer();
        void loadMusic(std::string path);
        void loadMusicChunk(std::string path);

        // player action
        void playChunk(int id);
        void playMusic(int id);
        void pauseMusic();
        void stopMusic();
        void resumeMusic();

        // player status check
        bool isPlaying();
        bool isPaused();

        // playere atrribute
        int getCurrentMusicNum();
        int getCurrentChunkNum();

    private:
        Mix_Music **musics;
        Mix_Chunk **chunks;
        int max_music_num;
        int max_chunk_num;
        // record current hold chunk/music number
        int cur_music_id;
        int cur_chunk_id;
};

#endif