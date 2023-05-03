#include "Lighting.h"

#include <cmath>

#include "Game.h"
#include "Logging.h"

namespace PE
{
	namespace Lighting
	{
		// --- FILE SPECIFIC UTILS ---
		void SetSurfacePixel(SDL_Surface* surface, int x, int y, Uint32 pixel)
		{
			Uint8* target_pixel = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
			*(Uint32*)target_pixel = pixel;
		}

		// stolen from stack overflow
		uint32_t AlphaBlendPixels(uint32_t p1, uint32_t p2)
		{
			static const int AMASK = 0xFF000000;
			static const int RBMASK = 0x00FF00FF;
			static const int GMASK = 0x0000FF00;
			static const int AGMASK = AMASK | GMASK;

			static const int ONEALPHA = 0x01000000;

			unsigned int a = (p2 & AMASK) >> 24;
			unsigned int na = 255 - a;
			unsigned int rb = ((na * (p1 & RBMASK)) + (a * (p2 & RBMASK))) >> 8;
			unsigned int ag = (na * ((p1 & AGMASK) >> 8)) + (a * (ONEALPHA | ((p2 & GMASK) >> 8)));
			return ((rb & RBMASK) | (ag & AGMASK));
		}


		Uint32 GetPixel(SDL_Surface* surface, int x, int y)
		{
			Uint8* target_pixel = (Uint8*)surface->pixels + y * surface->pitch + x * 4;
			return *(Uint32*)target_pixel;
		}

		void BlendMaps(SDL_Surface* s1, SDL_Surface* s2)
		{
			for (unsigned int i = 0; i <= s1->h; i++)
			{
				for (unsigned int j = 0; j <= s1->w; j++)
				{
					SetSurfacePixel(s1, j, i, AlphaBlendPixels(GetPixel(s1, j, i), GetPixel(s2, j, i)));
				}
			}
		}

		Utils::Color Uint32ToColor(uint32_t u32_color)
		{
			Utils::Color color;

			uint8_t bytes[4];
			std::memcpy(&bytes, &u32_color, 4);

			for (int i = 0; i < 4; i++)
			{
				PE::LogInfo(std::to_string(bytes[i]));
			}

			color.a = bytes[3];
			color.r = bytes[2];
			color.g = bytes[1];
			color.b = bytes[0];

			return color;
		}

		uint32_t ColorToUint32(Utils::Color color)
		{
			//Convert color components to value between 0 and 255.
			uint32_t a = (((uint32_t)color.a) << 24);
			uint32_t r = color.r;
			uint32_t g = color.g;
			uint32_t b = color.b;

			//Combine the color components in a single value of the form 0xAaRrGgBB
			return  a | b | (g << 8) | (r << 16);
		}


		// --- LIGHT MANAGER ---
		LightingManager::LightingManager(int cell_size, Vector screen_size)
		{
			CreateCellArray(screen_size, cell_size);
		}

		LightingManager::~LightingManager()
		{
			SDL_FreeSurface(wip_lightmap);
			SDL_FreeSurface(lightmap_surface);
			SDL_DestroyTexture(light_map);
		}

		void LightingManager::CreateCellArray(Vector screen_size, int cell_size)
		{
			// divide the screen into cells
			Vector cell_count;

			cell_count.x = screen_size.x / cell_size;
			cell_count.y = screen_size.y / cell_size;

			cell_array_size = cell_count;

			wip_lightmap = SDL_CreateRGBSurface(0, cell_array_size.x, cell_array_size.y, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);
			lightmap_surface = SDL_CreateRGBSurface(0, cell_array_size.x, cell_array_size.y, 32, 0x00FF0000, 0x0000FF00, 0x000000FF, 0xFF000000);

			ResetLightMap();

			this->cell_size = cell_size;
		}

		void LightingManager::ResetLightMap()
		{
			// fill the surface with black pixels
			for (int i = 0; i < cell_array_size.y; i++)
			{
				for (int j = 0; j < cell_array_size.x; j++)
				{
					SetSurfacePixel(wip_lightmap, j, i, ColorToUint32(Utils::Color(0, 0, 0, 255)));
				}
			}
		}

		Vector LightingManager::ScreenPosToCellPos(Vector screen_pos)
		{
			Vector cell_pos;

			cell_pos.x = screen_pos.x / cell_size;
			cell_pos.y = screen_pos.y / cell_size;

			return cell_pos;
		}

		void LightingManager::CreateLightSource(Vector cell_pos, Utils::Color color, int brightness)
		{
			sources[std::array<int, 2>({ int(cell_pos.x), int(cell_pos.y) })] = LightSource(color, brightness);
		}

		void LightingManager::CreateObstruction(Vector cell_pos, uint8_t alpha, uint8_t reflectiveness)
		{
			obstructions[std::array<int, 2>({ int(cell_pos.x), int(cell_pos.y) })] = LightObstruction(alpha, reflectiveness);
		}

		void LightingManager::CastLightRay(Vector initial_pos, Utils::Color color, float brightness, int direction)
		{
			Vector current_pos = initial_pos;
			Vector previous_pos;

			float max_brightness = brightness;

			// set the vector motion based on the angle
			Vector motion;

			motion.x = cos(Utils::DegToRads(direction));
			motion.y = sin(Utils::DegToRads(direction));

			while (brightness > 0)
			{
				previous_pos = current_pos;
				current_pos = current_pos + motion;

				if (!(current_pos.x > Game::GetInstance()->window->GetWidth() || current_pos.x < 0
					||
					current_pos.y > Game::GetInstance()->window->GetHeight() || current_pos.y < 0))
				{
					Utils::Color new_color;
					new_color.a = ((brightness / max_brightness) * color.a);
					new_color.r = color.r;
					new_color.g = color.g;
					new_color.b = color.b;

					// blend the two pixels together
					uint32_t finalized_pixel = ColorToUint32(new_color);//AlphaBlendPixels(GetPixel(wip_lightmap, ScreenPosToCellPos({ current_pos.x, current_pos.y }).x, ScreenPosToCellPos({ current_pos.x, current_pos.y }).y), ColorToUint32(new_color));

					SetSurfacePixel(wip_lightmap, ScreenPosToCellPos({ current_pos.x, current_pos.y }).x, ScreenPosToCellPos({ current_pos.x, current_pos.y }).y, finalized_pixel);
				}
				else
				{
					break;
				}

				// PE::LogInfo(std::to_string(current_pos.x) + " " + std::to_string(current_pos.y));

				brightness = brightness - current_pos.GetDistanceTo(previous_pos);
			}

		}

		void LightingManager::ShineLight(Vector position, unsigned int num_rays, LightSource source)
		{
			for (unsigned int i = 1; i <= num_rays; i++)
			{
				unsigned int direction = (360 / num_rays) * i;

				CastLightRay(position, source.color, source.brightness, direction);
			}
		}

		SDL_Texture* LightingManager::GenerateLightMap()
		{
			SDL_SetSurfaceBlendMode(wip_lightmap, SDL_BLENDMODE_MUL);
			ResetLightMap();

			if (light_map != NULL)
				SDL_DestroyTexture(light_map);

			if (lightmap_surface != NULL)
			{
				for (int i = 0; i < cell_array_size.y; i++)
				{
					for (int j = 0; j < cell_array_size.x; j++)
					{
						SetSurfacePixel(lightmap_surface, j, i, ColorToUint32(Utils::Color(0, 0, 0, 0)));
					}
				}
			}

			//std::vector<SDL_Surface*> surfaces;
			for (auto const& source : sources)
			{
				ShineLight({ double(source.first[0]), double(source.first[1]) }, 360, source.second);
				BlendMaps(lightmap_surface, wip_lightmap);
				ResetLightMap();
			}


			light_map = SDL_CreateTextureFromSurface(Game::GetInstance()->window->GetSDLRenderer(), lightmap_surface);

			return light_map;
		}

		// --- LIGHT ELEMENTS ---
		LightSource::LightSource()
		{
			color = Utils::Color(255, 0, 0, 0);
			brightness = 100;
		}

		LightSource::LightSource(Utils::Color color, int brightness)
		{
			this->color = color;
			this->brightness = brightness;
		}



		LightObstruction::LightObstruction(uint8_t alpha, uint8_t reflectiveness)
		{
			this->alpha = alpha;
			this->reflectiveness = reflectiveness;
		}

		LightObstruction::LightObstruction()
		{
			this->alpha = 255;
			this->reflectiveness = 0;
		}

	}
}
