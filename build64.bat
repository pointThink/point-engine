@echo off

mkdir build
mkdir build\bin
mkdir build\lib
mkdir build\include

copy bin build
copy source\*.h build\include

g++ source\*.cpp -m64 -DENGINE_BUILD -DWINDOWS64 -shared -o build\bin\pointengine.dll -Iinclude -Llib -lSDL2main -lSDL2 -Wl,--out-implib,build\lib\libpointengine.a