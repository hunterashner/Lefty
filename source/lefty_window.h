#ifndef LEFTY_WINDOW_H
#define LEFTY_WINDOW_H

#include"SDL.h"

SDL_Window* lefty_initSDL(void);
SDL_GLContext* lefty_initOpenGL(SDL_Window* window);
void lefty_checkGLVersions(void);
void lefty_gameLoop(SDL_Window* window);
void lefty_glContextCleanup(SDL_GLContext* context);
void lefty_windowCleanup(SDL_Window* window);

#endif
