@echo off

mkdir build
mkdir build\bin
mkdir build\lib
mkdir build\include

xcopy include\SDL2 build\include\SDL2

xcopy bin build
xcopy source\*.h build\include
xcopy source\Rendering\*.h build\include

g++ source\*.cpp source\Rendering\*.cpp -m64 -DENGINE_BUILD -DWINDOWS64 -shared -o build\bin\pointengine.dll -Iinclude -Isource -Isource\Rendering -Llib -lSDL2main -lSDL2 -Wl,--out-implib,build\lib\libpointengine.a