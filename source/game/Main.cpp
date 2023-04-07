#include "PointEngine.h"

#include "SDL.h"

using namespace PE;

Rendering::Animation a;

class Player : public Entity::EntityBase
{
	public:
	void Init()
	{
		layer = 0;

		entity_name = "player";
		colidable = true;

		position = { 0, 0 };
		motion = { 0, 0 };

		Collision::CollisionBox* cb = new Collision::CollisionBox;
		cb->pos = { 0, 0 };
		cb->size = { 20, 20 };

		collision_group.AddObject("square", cb);
	}

	void Update()
	{
		motion = { 0, 0 };

		if (game->input_manager->GetKeyState(PE_KEY_W)->IsDown())
		{
			motion.y = -100;
		}


		if (game->input_manager->GetKeyState(PE_KEY_S)->IsDown())
		{
			motion.y = 100;
		}


		if (game->input_manager->GetKeyState(PE_KEY_A)->IsDown())
		{
			motion.x = -100;
		}


		if (game->input_manager->GetKeyState(PE_KEY_D)->IsDown())
		{
			motion.x = 100;
		}

		for (Collision::CollisionObject* co : collision_group.objects)
		{
			if (co->tag == "square")
			{
				co->pos = position;
			}
		}
	}

	void Draw()
	{
		game->window->camera_offset.x = -position.x + game->window->GetWidth() / 2;
		game->window->camera_offset.y = -position.y + game->window->GetHeight() / 2;
		game->window->DrawSquare({ position.x, position.y }, { 20, 20 }, { 255, 0, 255, 255 });

		game->font_manager->DrawString({ position.x + 20, position.y + 20 }, "default", "This is the player", Utils::Color(255, 0, 255, 255));
	}
};

class TestEntity : public Entity::EntityBase
{
	void Init()
	{
		layer = 1;

		colidable = true;

		Collision::CollisionBox* box = new Collision::CollisionBox;
		box->pos = { 40, 40 };
		box->size = { 20, 20 };

		collision_group.AddObject("box", box);
	}

	void Update(){}

	void Draw()
	{
		Game::GetInstance()->window->DrawSquare({ 40, 40 }, { 20, 20 }, { 255, 0, 0, 255 });
	}


	void OnCollision(Entity::EntityBase* entity)
	{
		PE::LogInfo("Collision");
		game->entity_manager->RemoveEntity(entity);
	}
};

void HandleEvent(EventType et, EventParameters ep)
{

	if (et == GAME_DRAW)
	{
		// a.UpdateCurrentFrame();

		
	}
	else if (et == GAME_UPDATE)
	{
		Game::GetInstance()->SetGameName(std::to_string(1 / Game::GetInstance()->GetFrameTime()));
	}
}

int main()
{
	Game* game = Game::GetInstance();

	// a.AddSprite("test");
	// a.AddSprite("test2");
	
	// a.SetFramerate(10);

	game->Init();

	// game->sprite_manager->LoadSprite("test2.bmp", "test2");
	// game->sprite_manager->LoadSprite("test.bmp", "test");
	
	game->entity_manager->AddEntity(new TestEntity());
	game->entity_manager->AddEntity(new Player);
	

	game->SetGameName("Test");
	game->SetEventHandler(&HandleEvent);

	game->Run();

	return 0;
}