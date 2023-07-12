@echo off

clang -g ^
source/main.c source/lefty_window.c source/external/glad/glad.c source/lefty_draw.c source/lefty_shader_utils.c ^
-o build/lefty.exe ^
-IC:\Repos\SDL2-2.28.1\include ^
-LC:\Repos\SDL2-2.28.1\lib\x64 ^
-lSDL2 ^
-std=gnu99 ^
-Wno-deprecated-declarations 
REM silencing deprecation warning for functions like fopen, coding like its 1999