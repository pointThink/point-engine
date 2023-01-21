#pragma once

#include <string>

#include "Core.h"
#include "Window.h"

namespace PE
{
	class ENGINE_API Game
	{
		public:
		virtual void Run() final;

		virtual void SetGameName(std::string name) final;
		virtual void SetGameVersion(std::string version) final;

		virtual void QuitApplication() final;

		private:
		bool should_quit = false;

		std::string game_name;
		std::string game_version;

		void Update();
		void Draw();

		PE::Rendering::Window * window = NULL;
	};
};