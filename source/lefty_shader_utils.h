#ifndef LEFTY_SHADER_UTILS_H
#define LEFTY_SHADER_UTILS_H

typedef struct
{
    unsigned int shader;
    int type;
    char* name;
} lefty_shader;

char* loadShaderSource(const char* filepath);
lefty_shader compileVertexShader(char* shaderSource, char* name);

#endif