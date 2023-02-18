if not exist ../../build/include (
	mkdir ../../build/include
)
if not exist ../../build/bin (
	mkdir ../../build/bin
)
if not exist ../../build/lib (
	mkdir ../../build/lib
)

copy /Y ..\..\source\*.h ..\..\build\include\PointEngine\
xcopy /S /Y ..\..\include\ ..\..\build\include\
