//stops SDL main hijacking
#define SDL_MAIN_HANDLED

//standard headers
#include<stdio.h>
#include<stdint.h>

//includes
#include"SDL.h"
#include"external/glad/glad.h"

//local source
#include"lefty_defs.h"
#include"lefty_structs.h"
#include"lefty_window.h"
#include"lefty_draw.h"
#include"lefty_shader_utils.h"

int main(int argc, char* argv[])
{
    //init window and opengl context
    SDL_Window* window = lefty_initSDL();
    SDL_GLContext* context = lefty_initOpenGL(window);

    //load shader code from source
    char* basic_vert_src = loadShaderSource("shaders/basic_vert.glsl");
    free((void*)basic_vert_src);

    char* basic_frag_src = loadShaderSource("shaders/basic_frag.glsl");
    free((void*)basic_frag_src);

    lefty_shader basic_vert = compileVertexShader(basic_vert_src, "basic_vert");

    //main game loop
    lefty_gameLoop(window);

    //cleanup
    lefty_glContextCleanup(context);
    lefty_windowCleanup(window);

    return 0;
}