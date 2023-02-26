#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "Core.h"
#include "Window.h"
#include "Vector.h"

namespace PE
{
	namespace Rendering
	{
		class ENGINE_API SpriteManager
		{
			private:
			std::unordered_map<std::string, SDL_Texture*> sprite_bank;

			Window * game_window;
			std::string game_content_path;

			public:
			SpriteManager(Window * game_window, std::string game_content_path);
			~SpriteManager();

			void LoadSprite(std::string sprite_path, std::string sprite_name);
			void LoadSpritePack(std::string pack_file);
			void RemoveSprite(std::string sprite_name);
			void ClearBank();

			void DrawSprite(std::string sprite_name, Vector position);
			void DrawTileSprite(std::string sprite_name, int orgin_x, int orgin_y, int tile_w, int tile_y, int tile_count_x, int tile_count_y);
			void DrawSpritePlus(std::string sprite_name, Vector position, Vector size, int rotation, bool flip_horizontal, bool flip_vertical);
		};

		class Animation
		{
			// todo: implement
		};
	};
};
