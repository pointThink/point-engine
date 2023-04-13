#pragma once

#include "Sprite.h"
#include "Entity.h"
#include "Core.h"

namespace PE
{
	namespace Entity
	{
		class EntityGenericSprite : public EntityBase
		{
			private:
			std::string sprite_name;
			Vector scale;

			Rendering::SpriteDrawInfo draw_info;

			public:
			void Draw();
		};
	}
}