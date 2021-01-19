#include "audio.h"

MusicPlayer::MusicPlayer(int max_music, int max_chunk)
{
    musics = NULL;
    chunks = NULL;

    max_music_num = max_music;
    max_chunk_num = max_chunk;
    cur_music_id = 0;
    cur_chunk_id = 0;

    // alloc
    musics = (Mix_Music **)malloc(sizeof(Mix_Music *) * max_music);
    chunks = (Mix_Chunk **)malloc(sizeof(Mix_Chunk *) * max_chunk);
}

void MusicPlayer::freePlayer()
{
// free chunks
    if(chunks != NULL)
    {
        for(int i = 0; i < max_chunk_num; ++i)
        {
            if(chunks[i] != NULL)
                Mix_FreeChunk(chunks[i]);
            chunks[i] = NULL;
        }
        free(chunks);
    }
    chunks = NULL;
    max_chunk_num = 0;
    cur_chunk_id = 0;

// free musics
    if(musics != NULL)
    {
        for(int i = 0; i < max_music_num; ++i)
        {
            if(musics[i] != NULL)
                Mix_FreeMusic(musics[i]);
            musics[i] = NULL;
        }
        free(musics);
    }
    musics = NULL;
    max_music_num = 0;
    cur_music_id = 0;
}

void MusicPlayer::loadMusic(std::string path)
{
    musics[cur_music_id] = Mix_LoadMUS(path.c_str());
    if(musics[cur_music_id] == NULL)
    {
        printf("Failed to load %s\n", path.c_str());
        Log_SDL_MIXER_error();
        return;
    }
    cur_music_id++;
}

void MusicPlayer::loadMusicChunk(std::string path)
{
    chunks[cur_chunk_id] = Mix_LoadWAV(path.c_str());
    if(chunks[cur_chunk_id] == NULL)
    {
        printf("Failed to load %s\n", path.c_str());
        Log_SDL_MIXER_error();
        return;
    }
    cur_chunk_id++;
}


void MusicPlayer::playChunk(int id)
{
    if (id >= cur_chunk_id)
    {
        printf("Out of Chunk Index\n");
        return;
    }

    Mix_PlayChannel(-1, chunks[id], 0);
}

void MusicPlayer::playMusic(int id)
{
    if (id >= cur_music_id)
    {
        printf("Out of Music Index\n");
        return;
    }
    Mix_PlayMusic(musics[id], -1);
}

void MusicPlayer::pauseMusic()
{
    Mix_PauseMusic();
}

void MusicPlayer::stopMusic()
{
    Mix_HaltMusic();
}

void MusicPlayer::resumeMusic()
{
    Mix_ResumeMusic();
}

bool MusicPlayer::isPlaying()
{
    if(Mix_PlayingMusic() == 0)
        return false;
    return true;
}

bool MusicPlayer::isPaused()
{
    if(Mix_PausedMusic() == 1)
        return true;
    return false;
}

int MusicPlayer::getCurrentMusicNum()
{
    return cur_music_id;
}
int MusicPlayer::getCurrentChunkNum()
{
    return cur_chunk_id;
}


