#include "BuiltInEntities.h"

#include "Game.h"
#include "Sprite.h"

using namespace PE::Entity;
using namespace PE::Rendering;

void EntityGenericSprite::Draw()
{
	PE_GAME->spriteManager->DrawSprite(sprite_name, position, scale, draw_info);
}