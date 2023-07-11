#ifndef LEFTY_STRUCTS_H
#define LEFTY_STRUCTS_H

#include"SDL.h"

/// @brief holds sdl app information on renderer and window
typedef struct
{
    SDL_Renderer *renderer; //only needed for sdl rendering not opengl
    SDL_Window *window;
} sdl_app;

#endif