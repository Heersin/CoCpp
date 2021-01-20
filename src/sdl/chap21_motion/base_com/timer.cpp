#include "timer.h"

Timer::Timer()
{
    start_ticks = 0;
    flow_ticks = 0;
    latest_ticks = 0;

    is_paused = false;
    is_started = false;
}

void Timer::start()
{
    // set status of timer
    is_started = true;
    is_paused = false;

    // get the current clock timer
    // reset them
    start_ticks = SDL_GetTicks();
    latest_ticks = 0;
    flow_ticks = 0;
}

void Timer::stop()
{
    // set stauts of timer
    is_started = false;
    is_paused = false;

    start_ticks = 0;
    latest_ticks = SDL_GetTicks();
    flow_ticks += latest_ticks;
}

void Timer::pause()
{
    // set status
    // if not start
    if( !is_started )
    {
        printf("Timer Not Start\n");
        return;
    }

    if( is_paused )
    {
        printf("Already paused\n");
        return;
    }

    is_paused = true;
    
    // calculate the paused ticks
    flow_ticks += SDL_GetTicks() - latest_ticks;

}

void Timer::resume()
{
    if ( !is_started )
    {
        printf("Timer Not Start\n");
        return;
    }

    if( !is_paused )
    {
        printf("Not Paused, still running\n");
        return;
    }

    is_paused = false;

    // unfreeze
    latest_ticks = SDL_GetTicks();
}

Uint32 Timer::getTicks()
{
    if( is_started )
        if ( is_paused )
            // return the freeze time (calculated)
            return flow_ticks;
        else
            // like stop watch
            return SDL_GetTicks() - latest_ticks + flow_ticks;
    else
        return 0;
}

Uint32 Timer::getTrueTicks()
{
    if( is_started )
        return SDL_GetTicks() - start_ticks;
    else
        return 0;
}

bool Timer::isStarted()
{
    return is_started;
}

bool Timer::isPaused()
{
    return is_paused;
}
