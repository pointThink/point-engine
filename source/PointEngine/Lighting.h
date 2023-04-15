#pragma once

#include <SDL.h>

#include <vector>
#include <map>

#include "Utils/Utils.h"
#include "Vector.h"

namespace PE
{
	namespace Lighting
	{
		class LightSource
		{
			public:
			LightSource();
			LightSource(Utils::Color color, int brightness);

			Utils::Color color;
			int brightness;
		};

		class LightObstruction
		{
			public:
			LightObstruction();
			LightObstruction(uint8_t alpha, uint8_t reflectiveness);

			uint8_t alpha;
			uint8_t reflectiveness;
		};

		class LightingManager
		{
			private:
			// array of cells
			Utils::Color* cells;

			std::map<std::array<int, 2>, LightSource> sources;
			std::map<std::array<int, 2>, LightObstruction> obstructions;

			Vector cell_array_size;

			int cell_size;

			SDL_Surface* wip_lightmap = NULL;
			SDL_Surface* lightmap_surface;
			SDL_Texture* light_map = NULL;

			public:
			LightingManager(int cell_size, Vector screen_size);
			~LightingManager();

			void CreateCellArray(Vector screen_size, int cell_size);
			void ResetLightMap();

			Vector ScreenPosToCellPos(Vector screen_pos);

			void CreateLightSource(Vector cell_pos, Utils::Color color, int brightness);
			void CreateObstruction(Vector cell_pos, uint8_t alpha, uint8_t reflectiveness);

			void CastLightRay(Vector initial_pos, Utils::Color color, float brightness, int direction);

			SDL_Texture* GenerateLightMap();

			void ShineLight(Vector position, unsigned int num_rays, LightSource source);
		};
	}
}
