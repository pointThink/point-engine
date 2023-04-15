#include "BuiltInEntities.h"

#include "Game.h"
#include "Rendering/Sprite.h"

using namespace PE::Entity;
using namespace PE::Rendering;

void EntityGenericSprite::Draw()
{
	PE_GAME->spriteManager->DrawSprite(spriteName, position, scale, drawInfo);
}