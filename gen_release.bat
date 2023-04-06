mkdir release

mkdir release\include\
mkdir release\include\PointEngine\
mkdir release\include\SDL\
mkdir release\include\imgui\
mkdir release\bin
mkdir release\lib

copy build\Release\pointengine-core.lib release\lib\

copy source\PointEngine\*.h release\include\PointEngine\
copy vendor\SDL\include\*.h release\include\SDL\
copy vendor\SDL_image\*.h release\include\SDL\
copy vendor\imgui\*.h release\include\imgui\

copy build\bin\Release\pointengine-core.dll release\bin\
copy build\bin\Release\SDL2.dll release\bin\
copy build\bin\Release\SDL2_image.dll release\bin\