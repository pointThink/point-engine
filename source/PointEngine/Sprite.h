#pragma once

#include <SDL.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <array>

#include "Core.h"
#include "Window.h"
#include "Vector.h"
#include "Utils.h"

namespace PE
{
	namespace Rendering
	{
		/* package all information relevant to drawing sprites
		so that you dont have to specify everything as parameters
		in one gigant function call
		
		Is far easier and cleaner to specify only what you need*/
		class ENGINE_API SpriteDrawInfo
		{
			public:
			Utils::Color tint = { 255, 255, 255, 255 };

			float transparency = 255;
			float rotation = 0;

			Vector rotation_orgin = { 0, 0 };

			bool flip_horizontally = false;
			bool flip_vertically = false;
		};
		
		class ENGINE_API Sprite
		{
			private:
			/* These should be set at sprite creation because conversion from surface to texture
			or viceversa takes too much time */
			SDL_Texture* texture;
			SDL_Surface* surface;
			
			Vector size = { 0, 0 };

			public:
			Sprite(SDL_Surface* surface);
			~Sprite();

			Vector GetSize();

			SDL_Texture* GetTexture();
			SDL_Surface* GetSurface();
		};

		class ENGINE_API SpriteManager
		{
			private:
			std::unordered_map<std::string, Sprite*> sprite_bank;

			Window* game_window;

			public:
			SpriteManager(Window* game_window);
			~SpriteManager();

			void LoadSprite(std::string& sprite_path, std::string sprite_name);
			void LoadSpritePack(std::string& pack_file);
			void RemoveSprite(std::string& sprite_name);
			void ClearBank();

			void DrawSprite(std::string& sprite_name, Vector position);
			void DrawSprite(std::string& sprite_name, Vector position, Vector size, SpriteDrawInfo info);
			void DrawTileSprite(std::string& sprite_name, Vector orgin, Vector size, Vector tile_count);
			void DrawTileSprite(std::string& sprite_name, Vector orgin, Vector size, Vector tile_count, SpriteDrawInfo info);
		};

		class ENGINE_API Animation
		{
			private:
			// contains the sprite ids of every single frame in the animation
			std::string* sprites = nullptr;

			int framerate = 0;
			int current_frame = 0;

			float time_between_frames;
			Utils::Timer frame_timer;

			std::vector<std::string> frames;

			public:
			void AddSprite(std::string sprite_id);
			std::string GetCurrentSprite();

			void SetFramerate(int framerate);
			int GetFramerate();

			// should be called before every draw
			// sets the right frame based on how much time has passed
			void UpdateCurrentFrame();
			void Reset();
		};
	};
};
