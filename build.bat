@echo off

mkdir build
mkdir build\bin
mkdir build\lib
mkdir build\include

copy bin build
copy *.h build\include

g++ source\*.cpp -o -shared build\bin\pointengine.dll -Iinclude -Llib -lSDL2main -lSDL2 -Wl,--out-implib,build\lib\libpointengine