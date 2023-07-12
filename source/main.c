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

void lefty_glShaderCompileLinkProgram(void)
{
    //create shader program
    lefty_shaderProgram shaderProgram;
    shaderProgram = createShaderProgram("basic program");

    /* 
    * load shader code from source, compiles the shader and links 
    * against shader program.
    * fopen calls are relative to where the binary is executed
    * make sure you are in the root directory before ./build/lefty.exe
    * or fopen will fail to find the shader paths.  
    */
    char basic_vert_path[] = "source\\shaders\\basic_vert.glsl";
    char basic_frag_path[] = "source\\shaders\\basic_frag.glsl"; 

    //compiles the shader and links against shader program
    const char* basic_vert_src = loadShaderSource(basic_vert_path);
    lefty_shader basic_vert = compileVertexShader(basic_vert_src, "basic_vert");
    attachLinkShaderProgram(shaderProgram, basic_vert.shader);
    free((void*)basic_vert_src);
    debugShaderProgramInfo(shaderProgram.program);

    //compiles the shader and links against shader program
    const char* basic_frag_src = loadShaderSource(basic_frag_path);
    lefty_shader basic_frag = compileFragmentShader(basic_frag_src, "basic_frag");
    attachLinkShaderProgram(shaderProgram, basic_frag.shader);
    free((void*)basic_frag_src);
    debugShaderProgramInfo(shaderProgram.program);
}

int main(int argc, char* argv[])
{
    //init window and opengl context
    SDL_Window* window = lefty_initSDL();
    SDL_GLContext* context = lefty_initOpenGL(window);

    lefty_glShaderCompileLinkProgram();

    //main game loop
    lefty_gameLoop(window);

    //cleanup
    lefty_glContextCleanup(context);
    lefty_windowCleanup(window);

    return 0;
}