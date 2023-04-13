#include "Player.h"

#include <iostream>

#include <PointEngine.h>

#include "Bullet.h"

void Player::Init()
{
	position = {};

	entity_name = "player";
	unique_id = "player";
}

void Player::Draw()
{
	PE_GAME->window->camera_offset.x = -position.x + PE_GAME->window->GetWidth() / 2;
	PE_GAME->window->camera_offset.y = -position.y + PE_GAME->window->GetHeight() / 2;

	PE_GAME->window->DrawSquare(position, {20, 20}, PE::Utils::Color(255, 0, 0, 255));

	PE_GAME->font_manager->DrawString({ 5, 5 }, "default", std::to_string(PE_GAME->entity_manager->GetEntityCount()), Utils::Color(255, 0, 0, 255));

}

void Player::Update()
{
	motion = { 0, 0 };

	if (PE_GAME->input_manager->GetBindState("move_sprint")->IsDown())
	{
		speed = 500;
	}
	else
	{
		speed = 200;
	}

	if (PE_GAME->input_manager->GetBindState("move_up")->IsDown())
	{
		motion.y = -speed; 
	}
	if (PE_GAME->input_manager->GetBindState("move_down")->IsDown())
	{
		motion.y = speed;
	}
	if (PE_GAME->input_manager->GetBindState("move_left")->IsDown())
	{
		motion.x = -speed;
	}
	if (PE_GAME->input_manager->GetBindState("move_right")->IsDown())
	{
		motion.x = speed;
	}
	

}

void Player::Tick()
{
	if (PE_GAME->input_manager->GetBindState("shoot")->IsDown())
	{
		Vector mouse_pos = PE_GAME->input_manager->GetMousePos();
		mouse_pos.x = mouse_pos.x - PE_GAME->window->camera_offset.x;
		mouse_pos.y = mouse_pos.y - PE_GAME->window->camera_offset.y;

		float direction = mouse_pos.GetRotationTo({ position.x + 10, position.y + 10 });

		CreateBullet({ position.x + 5, position.y + 5 }, 500, direction - 90);
	}
}