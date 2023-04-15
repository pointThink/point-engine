#pragma once

#include "Rendering/Sprite.h"
#include "Entity.h"
#include "Core.h"

namespace PE
{
	namespace Entity
	{
		class EntityGenericSprite : public EntityBase
		{
			private:
			std::string spriteName;
			Vector scale;

			Rendering::SpriteDrawInfo drawInfo;

			public:
			void Draw();
		};
	}
}