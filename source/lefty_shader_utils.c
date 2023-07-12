#include <stdio.h>
#include <stdlib.h>

#include"external/glad/glad.h"

#include"lefty_shader_utils.h"
#include"lefty_defs.h"

/// TODO: refactor entire function, malloc not working 
/// null termination failing.
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
        perror("fopen");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = malloc(filesize + 1);
    if(buffer == NULL)
    {
        printf("failed to allocate buffer fore file at path: %s\n", filepath);
        perror("fopen");
        return NULL;
    }

    if(fread(buffer, 1, filesize, file) < filesize)
    {
        printf("failed to read file at path: %s\n", filepath);
        perror("fopen");
        fclose(file);
        free(buffer);
        return NULL;
    }

    buffer[filesize] = '\0';

    fclose(file);

    return buffer;
}

/// TODO: not throwing errors when making changes to the source file
/// @brief compiles a shader from incoming source, and creates a lefty_shader
/// stuct with the shaders name for organization purposes and future link 
/// or attachment to the gl shader program
/// @param shaderSource 
/// @param name 
/// @return lefty_shader struct
lefty_shader compileVertexShader(const char* shaderSource, char* name)
{
    u32 shader;
    shader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(shader, 1, &shaderSource, ((void*)0));
    glCompileShader(shader);

    //check if compilation was successful
    i32 status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
    if(status == GL_FALSE)
    {
        i32 log_length = 0;
        char message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        printf("failed to compile %s\n error: %s\n", name, message);
    }

    lefty_shader vertexShader;
    vertexShader.shader = shader;
    vertexShader.type = GL_VERTEX_SHADER;
    vertexShader.name = name;

    return vertexShader;
}

/// TODO: not throwing errors when making changes to the source file
/// @breif compiles a shader from incoming source, and creates a lefty_shader
/// stuct with the shaders name for organization purposes and future link 
/// or attachment to the gl shader program
/// @param shaderSource
/// @param name
/// @return lefty_shader
lefty_shader compileFragmentShader(const char* shaderSource, char* name)
{
    u32 shader;
    shader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(shader, 1, &shaderSource, ((void*)0));
    glCompileShader(shader);

    //check if compilation was successful
    int* status;
    glGetShaderiv(shader, GL_COMPILE_STATUS, status);
    if(status == GL_FALSE)
    {
        printf("error during compilation of shader: %s\n", name);
        exit(1);
    }

    lefty_shader fragmentShader;
    fragmentShader.shader = shader;
    fragmentShader.type = GL_FRAGMENT_SHADER;
    fragmentShader.name = name;

    return fragmentShader;
}

/// @brief creates an opengl shader program
/// note to self; createShaderProgram function binding
/// is OpenGL 4.0 specific, consider using GLuint glCreateProgram(void)
/// @param  
lefty_shaderProgram createShaderProgram(char* name)
{
    lefty_shaderProgram shaderProgram;
    shaderProgram.name = name;
    shaderProgram.shaders = (u32*)malloc(1 * sizeof(u32)); //add space for one shader
    shaderProgram.program = glCreateProgram();

    //program creation failed
    if(shaderProgram.program == 0)
    {
        printf("error during shader program creation");
        exit(1);
    }

    return shaderProgram;
}

/// @brief attaches and links new shaders to the specified shader program
/// @param program 
/// @param shader 
void attachLinkShaderProgram(lefty_shaderProgram shaderProgram, u32 shader)
{
    //number of shaders attached to program + 1, one additional created on program creation
    u32 shaderCount = sizeof(shaderProgram.shaders) / 4;

    //reallocate memory for additional shader to be stored in lefty_shaderProgram struct
    u32* shaders = realloc(shaderProgram.shaders, (shaderCount + 1) * sizeof(u32));
    if (shaders == NULL)
    {
        printf("error during shader array memory reallocation, linking aborted.");
        return;
    }

    //updated shader array
    shaderProgram.shaders = shaders;
    
    //attach and link incoming shader to program
    glAttachShader(shaderProgram.program, shader);
    glLinkProgram(shaderProgram.program);
    validateLinkStatus(shaderProgram.program);
}


/// @brief https://docs.gl/gl3/glGetShaderInfoLog
/// @param shaderProgram 
void debugShaderProgramInfo(u32 shaderProgram)
{
    i32 maxLength;
    glGetProgramiv(shaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

    if(maxLength != 0) //if info log exists
    {
        char* log = (char*)malloc(maxLength * sizeof(char));
        i32* length;
        glGetShaderInfoLog(shaderProgram, maxLength, length, log);
        printf("%d\n", *length);
        printf("shader program error: \n%s\n", log);
        free(log);
    }
}

void validateLinkStatus(u32 shaderProgram)
{
    i32 status;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &status);
    if(status != GL_TRUE)
    {
        printf("linking of shader program %d failed", shaderProgram);
    }
}