add_requires("libsdl")
add_requires("libsdl_image")
add_requires("libsdl_ttf")

target("pointengine-core")
	set_kind("shared")

	add_packages("libsdl")
	add_packages("libsdl_image")
	add_packages("libsdl_ttf")

	before_build(function (target) 
		target:add("defines", "WINDOWS64")
		target:add("defines", "ENGINE_BUILD")
	end)

	add_headerfiles("source/PointEngine/*.h")
	add_files("source/PointEngine/*.cpp")
	add_includedirs("source/PointEngine/", "vendor/SDL/include", {public=true})

	set_languages("cxx20")


target("test-game")
	set_kind("binary")

	add_deps("pointengine-core")

	before_build(function (target) 
		target:add("defines", "WINDOWS64")
		target:add("defines", "ENGINE_BUILD")
	end)

	set_languages("cxx20")

	add_files("source/Game/*.cpp")
