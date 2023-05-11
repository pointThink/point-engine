#include "Font.h"

#include "Game.h"
#include "Logging.h"

using namespace PE;
using namespace PE::Font;

namespace PE
{
	namespace Font
	{
		FontManager::FontManager()
		{
			/*
			if (TTF_Init() == -1)
			{
				PE::LogError("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
				exit(7);
			}
			*/
		}

		FontManager::~FontManager()
		{
			Clear();
		}

		void FontManager::LoadExternalFont(std::string name, std::string file, int size)
		{
			/*
			TTF_Font* new_font = TTF_OpenFont(file.c_str(), size);

			if (new_font == NULL)
				PE::LogWarning("Could not load font: " + std::string(TTF_GetError()));

			fonts.insert({ name, new_font });
			*/
		}

		void FontManager::LoadFont(std::string name, std::string file, int size)
		{
			LoadExternalFont(name, Game::GetInstance()->gameContentPath + "/fonts/" + file, size);
		}

		void FontManager::UnloadFont(std::string name)
		{
			/*
			TTF_CloseFont(fonts.find(name)->second);
			fonts.erase(fonts.find(name));
			*/
		}

		void FontManager::DrawString(Vector pos, std::string font_name, std::string string, Utils::Color fg)
		{
			/*
			SDL_Color sdlFg;

			sdlFg.r = fg.r;
			sdlFg.g = fg.g;
			sdlFg.b = fg.b;
			sdlFg.a = fg.a;

			auto iterator = fonts.find(font_name);

			if (iterator == fonts.end())
			{
				PE::LogError("Could not find font " + font_name);
				return;
			}

			SDL_Surface* text;
			text = TTF_RenderText_Blended(fonts.find(font_name)->second, string.c_str(), sdlFg);

			if (text == NULL)
			{
				LogError("Error drawing font: " + std::string(TTF_GetError()));
				return;
			}

			SDL_Texture* textTexture = SDL_CreateTextureFromSurface(PE_GAME->window->GetSDLRenderer(), text);

			SDL_Rect* textRect = new SDL_Rect;

			textRect->x = int(pos.x) + PE_GAME->window->camera_offset.x;
			textRect->y = int(pos.y) + PE_GAME->window->camera_offset.y;
			textRect->w = int(text->w);
			textRect->h = int(text->h);

			SDL_RenderCopy(PE_GAME->window->GetSDLRenderer(), textTexture, NULL, textRect);

			delete textRect;

			SDL_FreeSurface(text);
			SDL_DestroyTexture(textTexture);
			*/
		}

		int FontManager::GetStringLength(std::string font_name, std::string string)
		{
			/*
			int returnInt = 0;
			TTF_SizeText(fonts.find(font_name)->second, string.c_str(), &returnInt, NULL);

			return returnInt;
			*/

			return 0;
		}

		int FontManager::GetStringHeight(std::string font_name, std::string string)
		{
			/*
			int returnInt = 0;
			TTF_SizeText(fonts.find(font_name)->second, string.c_str(), NULL, &returnInt);

			return returnInt;
			*/

			return 0;
		}
		void FontManager::Clear()
		{

		}
	}
}