#ifndef LEFTY_SHADER_UTILS_H
#define LEFTY_SHADER_UTILS_H

#include"lefty_defs.h"

typedef struct
{
    u32 shader;
    i32 type;
    char* name;
} lefty_shader;

typedef struct 
{
   u32 program;
   u32* shaders;
   char* name;
} lefty_shaderProgram;


char* loadShaderSource(const char* filepath);
lefty_shader compileVertexShader(const char* shaderSource, char* name);
lefty_shader compileFragmentShader(const char* shaderSource, char* name);
lefty_shaderProgram createShaderProgram(char* name);
void attachLinkShaderProgram(lefty_shaderProgram shaderProgram, u32 shader);
void debugShaderProgramInfo(u32 shaderProgram);
void validateLinkStatus(u32 shaderProgram);

#endif