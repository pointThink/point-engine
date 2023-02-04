#pragma once

#include <string>

#include "Core.h"
#include "Window.h"
#include "Sprite.h"

namespace PE
{
	class ENGINE_API Game
	{
		public:
		virtual void Run() final;

		void SetGameName(std::string name);
		void SetGameVersion(std::string version);
		void SetContentPath(std::string path);

		void QuitApplication();

		private:
		bool should_quit = false;

		std::string game_name;
		std::string game_version;
		std::string game_content_path;

		void Update();
		void Draw();

		PE::Rendering::Window * window = NULL;
		PE::Rendering::SpriteManager * sprite_manager = NULL;
	};
};