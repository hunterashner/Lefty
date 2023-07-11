//standard headers
#include<stdio.h>

//includes
#include"SDL.h"
#include"external/glad/glad.h"

//local source
#include"lefty_defs.h"


/// @brief creates an sdl window primed for opengl rendering
/// @param void
SDL_Window* lefty_initSDL(void)
{
    int rendererFlags;
    int windowFlags;
    SDL_Window* window;

    windowFlags = SDL_WINDOW_OPENGL;

    if(SDL_InitSubSystem(SDL_INIT_VIDEO) < 0)
    {
        printf("failed to init sdl: %s\n", SDL_GetError());
        exit(1);
    }

    window = SDL_CreateWindow(
        "Lefty Engine v0.0.02",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        windowFlags);

    if(window == NULL)
    {
        printf("failed to open window: %s\n", SDL_GetError());
        exit(1);
    }

    return window;
}


/// @brief inits an opengl context on the sdl window
/// @param sdl window returned from initSDL function
SDL_GLContext* lefty_initOpenGL(SDL_Window* window)
{
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GLContext* context = SDL_GL_CreateContext(window);
    if(context == NULL)
    {
        printf("failed to create an sdl opengl context: %s\n",
        SDL_GetError());
    }

    gladLoadGL();
    return context;
}

/// @brief prints open gl versions
/// @param void
void lefty_checkGLVersions(void)
{
    printf("GL %d.%d\n", GL_MAJOR_VERSION, GL_MINOR_VERSION);
}

void lefty_gameLoop(SDL_Window* window)
{
    int exit = 0;
    while(!exit)
    {
        SDL_Event event;
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                {
                    exit = 1;
                } break;

                case SDL_KEYUP:
                {
                    if(event.key.keysym.sym == SDLK_ESCAPE)
                    {
                        exit = 1;
                    }
                } break;
                
                default:
                    break;
            }
        }

        glClearColor(0.7f, 0.8f, 0.9f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        SDL_GL_SwapWindow(window);
        SDL_Delay(1);
    }
}

/// @brief handles cleanup of opengl context, must be cleaned before sdl window
/// @param context 
void lefty_glContextCleanup(SDL_GLContext* context)
{
    SDL_GL_DeleteContext(context);
}

/// @brief handles cleanup of sdl window, last to be destroyed
/// @param window 
void lefty_windowCleanup(SDL_Window* window)
{
    SDL_DestroyWindow(window);
    SDL_Quit();
}