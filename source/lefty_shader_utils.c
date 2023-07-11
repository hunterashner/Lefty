#include <stdio.h>
#include <stdlib.h>

#include"external/glad/glad.h"

#include"lefty_shader_utils.h"

/// @brief loads glsl source from filepath and stores in string
/// buffer, fails if path or memory allocation is invalid
/// @param filepath 
/// @return glsl source buffer
char* loadShaderSource(const char* filepath)
{
    FILE* file = fopen(filepath, "r");
    if(file == NULL)
    {
        printf("failed to open file at path: %s\n", filepath);
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(filesize + 1);
    if(buffer == NULL)
    {
        printf("failed to allocate buffer fore file at path: %s\n", filepath);
        return NULL;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';

    fclose(file);

    return buffer;
}

/// @brief compiles a shader from incoming source, and creates a lefty_shader
/// stuct with the shaders name for organization purposes and future link 
/// or attachment to the gl shader program
/// @param shaderSource 
/// @param name 
/// @return lefty_shader struct
lefty_shader compileVertexShader(char* shaderSource, char* name)
{
    unsigned int shader;
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shaderSource, ((void*)0));
    glCompileShader(shader);

    //check if compilation was successful
    //glad does not have function pointers for glGetShader....
    //int status;
    // glGetShader(shader, GL_COMPILE_STATUS, status);
    // if(status == GL_FALSE)
    // {
    //     printf("error during compilation of shader: %s\n", *name);
    //     exit(1);
    // }

    lefty_shader vertexShader;
    vertexShader.shader = shader;
    vertexShader.type = GL_VERTEX_SHADER;
    vertexShader.name = name;

    //TODO: find a good organized method for storing lefty_shaders
    return vertexShader;
}