@echo off

mkdir build
mkdir build\bin
mkdir build\lib
mkdir build\include

xcopy include\SDL2 build\include\SDL2

xcopy bin build\bin
xcopy source\*.h build\include\PointEngine
xcopy source\Rendering\*.h build\include\PointEngine

g++ source\*.cpp source\Rendering\*.cpp -m64 -DENGINE_BUILD -DWINDOWS64 -shared -o build\bin\pointengine.dll -Iinclude -Isource -Isource\Rendering -Llib -lSDL2main -lSDL2 -lSDL2_image -Wl,--out-implib,build\lib\libpointengine.a -w