#pragma once

#include <unordered_map>
#include <string>

#include <SDL_ttf.h>

#include "Core.h"

#include "Utils/Utils.h"
#include "Vector.h"

namespace PE
{
	namespace Font
	{
		class ENGINE_API FontManager
		{
			std::unordered_map<std::string, TTF_Font*> fonts;

			public:
			FontManager();
			~FontManager();

			void LoadFont(std::string name, std::string file, int size);
			void LoadExternalFont(std::string name, std::string file, int size);
			void UnloadFont(std::string name);

			void DrawString(Vector pos, std::string font_name, std::string string, Utils::Color fg);
			void GetStringLength(std::string font_name, std::string string);

			void Clear();
		};
	}
}
	