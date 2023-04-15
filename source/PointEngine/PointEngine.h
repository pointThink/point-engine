#pragma once

// this is required otherwise the linker throws an error
// no touchy - PT
#define SDL_MAIN_HANDLED

#include "Game.h"
#include "Logging.h"
#include "Rendering/Window.h"
#include "Rendering/Sprite.h"
#include "Vector.h"
#include "Entity/Entity.h"
#include "Input.h"
#include "Collision.h"
#include "Console/Console.h"
