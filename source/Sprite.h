#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>

#include "Core.h"
#include "Window.h"

namespace PE
{
	namespace Rendering
	{
		class SpriteManager
		{
			private:
			std::unordered_map<std::string, SDL_Surface*> * sprite_bank;

			Window * game_window;
			std::string game_content_path;

			public:
			SpriteManager(Window * game_window, std::string game_content_path);
			~SpriteManager();

			void LoadSprite(std::string sprite_path, std::string sprite_name);
			void RemoveSprite(std::string sprite_name);
			void ClearBank();

			void DrawSprite(std::string sprite_name, int x, int y);
			void DrawSpritePlus(std::string sprite_name, int x, int y, int w, int h, int rotation);
		};

		class Animation
		{
			// todo: implement	
		};
	};
};