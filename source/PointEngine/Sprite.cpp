#include "Sprite.h"

#include <SDL_image.h>

#include "Logging.h"
#include "Utils.h"
#include "Vector.h"

#include <fstream>
#include <iostream>
#include <cstdint>
#include <string>

using namespace PE::Rendering;

Sprite::Sprite(SDL_Surface * surface)
{
	this->surface = surface;

	this->size.x = surface->w;
	this->size.y = surface->h;

	// convert the surface into a tetxture
	this->texture = SDL_CreateTextureFromSurface(Game::GetInstance()->window->GetSDLRenderer(), surface);
}

Sprite::~Sprite()
{
	SDL_FreeSurface(surface);
	SDL_DestroyTexture(texture);
}

PE::Vector Sprite::GetSize() { return size; }

SDL_Surface * Sprite::GetSurface() { return surface; }
SDL_Texture * Sprite::GetTexture() { return texture; }

// SpriteManager
SpriteManager::SpriteManager(Window * game_window, std::string game_content_path)
{
	this->game_content_path = game_content_path;
	this->game_window = game_window;
}

SpriteManager::~SpriteManager()
{
	ClearBank();
}


void SpriteManager::LoadSprite(std::string file_path, std::string sprite_name)
{
	SDL_Surface * image_unoptimized = IMG_Load((game_content_path + "/sprites/images/" + file_path).c_str());

	if (image_unoptimized == NULL)
    {
        PE::LogError("Error loading sprite: " + std::string(IMG_GetError()));
        return;
    }

	SDL_Surface * image = SDL_ConvertSurface(image_unoptimized, SDL_GetWindowSurface(game_window->GetSDLWindow())->format, 0);
	SDL_FreeSurface(image_unoptimized);

	Sprite * sprite = new Sprite(image);

	sprite_bank.insert({sprite_name, sprite});
}

void SpriteManager::LoadSpritePack(std::string pack_file)
{
	std::fstream stream(game_content_path + "/sprites/packs/" + pack_file, std::ios::in | std::ios::binary | std::ios::ate);

	if (!stream.is_open())
	{
		PE::LogWarning("Could not open " + pack_file);
		return;
	}


	int file_size = stream.tellg();

	bool end_loop = false;
	int loop_count = 0;
	int current_position = 0;

	while (!end_loop)
	{
		// read the 1000 bytes
		stream.seekg(current_position, std::ios::beg);
		char bytes[1000];

		stream.read(bytes, 1000);

		// get the length of the name
		uint16_t name_length = bytes[0];
		// get length of format
		uint8_t format_length = bytes[1 + name_length];
		// get length of image data
		uint32_t data_length = (uint32_t(bytes[2 + name_length + format_length]) << 24) |
								(uint32_t(bytes[3 + name_length + format_length]) << 16) |
								(uint32_t(bytes[4 + name_length + format_length]) << 8) |
								(uint32_t(bytes[5 + name_length + format_length]) & 0xFF); // what the fuck -PT


		int segment_length = 6 + name_length + format_length + data_length;

		// after getting the segment length load the entire segment
		stream.clear();
		stream.seekg(current_position, std::ios::beg);
		char * segment = new char[segment_length];
		stream.read(segment, segment_length);

		std::string name = "";
		std::string format = "";

		char * data = new char[data_length];

		// read all the data
		// name
		for (int i = 1; i <= name_length; i++)
		{
			name.push_back(segment[i]);
		}

		// format
		for (int i = 1; i <= format_length; i++)
		{
			format.push_back(segment[1 + name_length + i]);
		}

		// data
		for (int i = 0; i < data_length; i++)
		{
			data[i] = segment[6 + name_length + format_length + i];
		}

		// load the actual texture - PT
		PE::LogInfo("Loading sprite " + name);

		//std::ofstream ws("temp.bin", std::ios::binary);
		//ws.write(data, data_length);
		//ws.close();

		//SDL_RWops * io = SDL_RWFromFile("temp.bin", "r");
		SDL_RWops * io = SDL_RWFromMem(data, data_length);

		if (io == NULL)
		{
			PE::LogWarning("Failed to load sprite from memory: " + std::string(SDL_GetError()));
		}

		SDL_Surface * surface = IMG_LoadTyped_RW(io, 1, format.c_str());

		if (surface == NULL)
		{
			PE::LogWarning("Could not load sprite " + name + ": " + std::string(IMG_GetError()));
		}
		else
		{
			Sprite * sprite = new Sprite(surface);

			sprite_bank.insert({ name, sprite });
			PE::LogInfo("Loaded sprite " + name);
		}

		SDL_FreeRW(io);

		delete[] segment;
		delete[] data;

		current_position = current_position + segment_length;

		if (current_position >= file_size)
			end_loop = true;
	}

	stream.close();
}

void SpriteManager::RemoveSprite(std::string sprite_name)
{
	delete (sprite_bank.find(sprite_name)->second);
	sprite_bank.erase(sprite_bank.find(sprite_name));
}


void SpriteManager::ClearBank()
{
	for (auto const& [key, val] : sprite_bank)
	{
		delete val;
	}
	sprite_bank.clear();
}

void SpriteManager::DrawSprite(std::string sprite_name, Vector position, Vector size, SpriteDrawInfo info)
{
	if (!sprite_bank.count(sprite_name))
	{
		PE::LogWarning("Could not draw sprite " + sprite_name + " because it does not exist");
		return; // exit the function because attempting to draw a missing sprite crashes the engine - PT
	}

	Sprite * sprite = sprite_bank.find(sprite_name)->second;
	SDL_Texture * texture = sprite->GetTexture();

	// Temporary rect to define position of drawn sprite - PT
	SDL_Rect * temp_rect = new SDL_Rect();

	temp_rect->x = position.x;
	temp_rect->y = position.y;
	temp_rect->w = size.x;
	temp_rect->h = size.y;

	SDL_RendererFlip rf;

	if (info.flip_horizontally)
		rf = (SDL_RendererFlip)SDL_FLIP_HORIZONTAL;
	else if (info.flip_vertically)
		rf = (SDL_RendererFlip)SDL_FLIP_VERTICAL;
	else if (info.flip_horizontally && info.flip_vertically)
		rf = (SDL_RendererFlip)(SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
	else
		rf = SDL_FLIP_NONE;

	SDL_RenderCopyEx(Game::GetInstance()->window->GetSDLRenderer(), texture, NULL, temp_rect, info.rotation, NULL, rf);

	delete temp_rect;
}


void SpriteManager::DrawSprite(std::string sprite_name, Vector position)
{
	PE::Game * game = PE::Game::GetInstance();

	position.x = position.x + game->window->camera_offset.x;
	position.y = position.y + game->window->camera_offset.y;

    if (!sprite_bank.count(sprite_name))
    {
        PE::LogWarning("Could not draw sprite " + sprite_name + " because it does not exist");
        return; // exit the function because attempting to draw a missing sprite crashes the engine - PT
    }
    Sprite * sprite = sprite_bank.find(sprite_name)->second;
	SDL_Texture * texture = sprite->GetTexture();

	// Temporary rect to define position of drawn sprite - PT
	SDL_Rect * temp_rect = new SDL_Rect();

	temp_rect->x = position.x;
	temp_rect->y = position.y;
	temp_rect->w = sprite->GetSize().x;
	temp_rect->h = sprite->GetSize().y;

	SDL_RenderCopy(game_window->GetSDLRenderer(), texture, NULL, temp_rect);

	delete temp_rect;
}

void SpriteManager::DrawTileSprite(std::string sprite_name, Vector orgin, Vector size, Vector tile_count)
{
	for (int i = 0; i < tile_count.x; i++)
	{
		for (int i2 = 0; i2 < tile_count.y; i2++)
		{
			DrawSprite(sprite_name, {orgin.x + size.x * i, orgin.y + size.y * i2}, size, SpriteDrawInfo());
		}
	}
}

void SpriteManager::DrawTileSprite(std::string sprite_name, Vector orgin, Vector size, Vector tile_count, SpriteDrawInfo info)
{
	for (int i = 0; i < tile_count.x; i++)
	{
		for (int i2 = 0; i2 < tile_count.y; i2++)
		{
			DrawSprite(sprite_name, { orgin.x + size.x * i, orgin.y + size.y * i2 }, size, info);
		}
	}
}


// ANIMATION

void Animation::AddSprite(std::string sprite_id)
{
	frames.push_back(sprite_id);
}

std::string Animation::GetCurrentSprite()
{
	return frames[current_frame];
}

void Animation::UpdateCurrentFrame()
{
	if (frame_timer.HasTimeElapsed(1.0 / framerate))
	{
		frame_timer.Reset();

		current_frame++;

		if (current_frame >= this->frames.size())
		{
			//current_frame = current_frame - this->frames.size();
			current_frame = 0;
		}
	}
}

void Animation::Reset()
{
	current_frame = 0;
}

void Animation::SetFramerate(int framerate) { this->framerate = framerate; }
int Animation::GetFramerate() { return framerate; }