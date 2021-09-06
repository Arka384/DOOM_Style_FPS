#include "Monster.hpp"

void Monster::Load_texture(void)
{
	monster_tex.loadFromFile("Resources/Sprite_sheets/doom_sprite_sheet.png");
	monster.setTexture(monster_tex);
	monster.setTextureRect(sf::IntRect(rect_x, rect_y, 42, 64));
	monster.setPosition(rand() % 1100 + 100, -400);
	monster.setScale(2, 2);
}

void Monster::walking(void)
{
	//std::cout << monster.getPosition().y << std::endl;
	if (monster.getPosition().y > -270) {
		rect_x += 50;
		if (rect_x >= 150)
			rect_x = 0;
		monster.setTextureRect(sf::IntRect(rect_x, 225, 50, 62));
		return;
	}

	rect_x += 42;
	if (rect_x >= 126)
		rect_x = 0;
	monster.setTextureRect(sf::IntRect(rect_x, 0, 42, 62));

	if (monster.getPosition().y <= -270) {
		monster.setPosition(monster.getPosition().x, monster.getPosition().y + pos_y);
		monster.setScale(monster.getScale().x + scale_inr, monster.getScale().y + scale_inr);
	}
		
}

bool Monster::kill_animation(void)
{
	if (!executed) {
		rect_x = 0;
		monster.setTextureRect(sf::IntRect(rect_x, 348, 45, 62));
		executed = true;
		return true;
	}

	switch (rect_x)
	{
	case 0:
		rect_x = 45;
		monster.setTextureRect(sf::IntRect(rect_x, 348, 45, 62));
		break;
	case 45:
		rect_x = 90;
		monster.setTextureRect(sf::IntRect(rect_x, 348, 42, 62));
		break;
	case 90:
		rect_x = 132;
		monster.setTextureRect(sf::IntRect(rect_x, 348, 50, 62));
		break;
	case 132:
		rect_x = 185;
		monster.setTextureRect(sf::IntRect(rect_x, 348, 60, 62));
		rect_x = 0;
		executed = false;
		return false;
		break;
	default:
		break;
	}
	return true;
}

void Monster::respawn(void)
{
	monster.setTextureRect(sf::IntRect(rect_x, 0, 42, 62));
	monster.setPosition(rand() % 1366 - 400, -400);
	monster.setScale(2, 2);
}
