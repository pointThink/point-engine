mkdir release

mkdir release\include\

mkdir release\include\PointEngine\
mkdir release\include\PointEngine\Console
mkdir release\include\PointEngine\Entity
mkdir release\include\PointEngine\Rendering
mkdir release\include\PointEngine\Utils


mkdir release\include\SDL\
mkdir release\include\imgui\
mkdir release\bin
mkdir release\lib

copy build\Release\pointengine-core.lib release\lib\

copy source\PointEngine\*.h release\include\PointEngine\
copy source\PointEngine\Rendering\*.h release\include\PointEngine\Rendering
copy source\PointEngine\Console\*.h release\include\PointEngine\Console
copy source\PointEngine\Entity\*.h release\include\PointEngine\Entity
copy source\PointEngine\Utils\*.h release\include\PointEngine\Utils


copy vendor\SDL\include\*.h release\include\SDL\
copy vendor\SDL_image\*.h release\include\SDL\
copy vendor\SDL_ttf\*.h release\include\SDL\
copy vendor\imgui\*.h release\include\imgui\

copy build\bin\Release\*.dll release\bin\
