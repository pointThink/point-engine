#include "Sprite.h"

#include <SDL2/SDL_image.h>
#include "Logging.h"

PE::Rendering::SpriteManager::SpriteManager(Window * game_window, std::string game_content_path)
{
	this->game_content_path = game_content_path;
	this->game_window = game_window;
}

PE::Rendering::SpriteManager::~SpriteManager()
{
	ClearBank();
}


void PE::Rendering::SpriteManager::LoadSprite(std::string file_path, std::string sprite_name)
{
	SDL_Surface * image_unoptimized = IMG_Load((game_content_path + "/" + file_path).c_str());

	if (image_unoptimized == NULL)
    {
        PE::LogError("Error loading sprite: " + std::string(IMG_GetError()));
        return;
    }

	SDL_Surface * image = SDL_ConvertSurface(image_unoptimized, SDL_GetWindowSurface(game_window->GetSDLWindow())->format, 0);
	SDL_FreeSurface(image_unoptimized);

	SDL_Texture * texture = SDL_CreateTextureFromSurface(game_window->GetSDLRenderer(), image);
	SDL_FreeSurface(image);

	sprite_bank.insert({sprite_name, texture});
}

void PE::Rendering::SpriteManager::RemoveSprite(std::string sprite_name)
{
	SDL_DestroyTexture(sprite_bank.find(sprite_name)->second);
	sprite_bank.erase(sprite_bank.find(sprite_name));
}


void PE::Rendering::SpriteManager::ClearBank()
{
	for (auto const& [key, val] : sprite_bank)
	{
		SDL_DestroyTexture(val);
	}
	sprite_bank.clear();
}

void PE::Rendering::SpriteManager::DrawSprite(std::string sprite_name, int x, int y)
{
    if (!sprite_bank.count(sprite_name))
    {
        PE::LogWarning("Could not draw sprite " + sprite_name + " because it does not exist");
        return; // exit the function because attempting to draw a missing sprite crashes the engine - PT
    }
    SDL_Texture * texture = sprite_bank.find(sprite_name)->second;

	// this is stupid - PT
	int w;
	int h;

	SDL_QueryTexture(texture, NULL, NULL, &w, &h);

	// Temporary rect to define position of drawn sprite - PT
	SDL_Rect * temp_rect = new SDL_Rect();

	temp_rect->x = x;
	temp_rect->y = y;
	temp_rect->w = w;
	temp_rect->h = h;

	SDL_RenderCopy(game_window->GetSDLRenderer(), texture, NULL, temp_rect);

	delete temp_rect;
}

void PE::Rendering::SpriteManager::DrawTileSprite(std::string sprite_name, int orgin_x, int orgin_y, int tile_w, int tile_h, int tile_count_x, int tile_count_y)
{
	for (int i = 0; i < tile_count_x; i++)
	{
		for (int i2 = 0; i2 < tile_count_y; i2++)
		{
			DrawSprite(sprite_name, orgin_x + tile_w * i, orgin_y + tile_h * i2);
		}
	}
}

void PE::Rendering::SpriteManager::DrawSpritePlus(std::string sprite_name, int x, int y, int w, int h, int rotation)
{
    // todo: implement
}
