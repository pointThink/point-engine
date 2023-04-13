#include "Font.h"

#include "Game.h"
#include "Logging.h"

using namespace PE;
using namespace PE::Font;

FontManager::FontManager()
{
	if (TTF_Init() == -1)
	{
		PE::LogError("Failed to initialize SDL_ttf: " + std::string(TTF_GetError()));
		exit(7);
	}
}

FontManager::~FontManager()
{
	Clear();
}

void FontManager::LoadExternalFont(std::string name, std::string file, int size)
{
	TTF_Font* new_font = TTF_OpenFont(file.c_str(), size);

	if (new_font == NULL)
		PE::LogWarning("Could not load font: " + std::string(TTF_GetError()));

	fonts.insert({name, new_font});
}

void FontManager::LoadFont(std::string name, std::string file, int size)
{
	LoadExternalFont(name, Game::GetInstance()->gameContentPath + "/fonts/" + file, size);
}

void FontManager::UnloadFont(std::string name)
{
	TTF_CloseFont(fonts.find(name)->second);
	fonts.erase(fonts.find(name));
}

void FontManager::DrawString(Vector pos, std::string font_name, std::string string, Utils::Color fg)
{
	SDL_Color sdl_fg;

	sdl_fg.r = fg.r;
	sdl_fg.g = fg.g;
	sdl_fg.b = fg.b;
	sdl_fg.a = fg.a;

	auto iterator = fonts.find(font_name);

	if (iterator == fonts.end())
	{
		PE::LogError("Could not find font " + font_name);
		return;
	}

	SDL_Surface* text;
	text = TTF_RenderText_Blended(fonts.find(font_name)->second, string.c_str(), sdl_fg);
	
	SDL_Texture* text_texture = SDL_CreateTextureFromSurface(PE_GAME->window->GetSDLRenderer(), text);

	SDL_Rect* text_rect = new SDL_Rect;

	text_rect->x = int(pos.x) + PE_GAME->window->camera_offset.x;
	text_rect->y = int(pos.y) + PE_GAME->window->camera_offset.y;
	text_rect->w = int(text->w);
	text_rect->h = int(text->h);

	SDL_RenderCopy(PE_GAME->window->GetSDLRenderer(), text_texture, NULL, text_rect);

	delete text_rect;

	SDL_FreeSurface(text);
	SDL_DestroyTexture(text_texture);
}

void FontManager::GetStringLength(std::string font_name, std::string string) {}

void FontManager::Clear()
{

}