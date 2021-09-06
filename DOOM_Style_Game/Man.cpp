#include "Man.hpp"

void Man::Load_texture(void)
{
	man_texture.loadFromFile("Resources/Sprite_sheets/doom_man.png");
	man.setTexture(man_texture);
	man.setTextureRect(sf::IntRect(0, rect_y, 60, 100));
	man.setPosition(rand() % 1366 - 400, -400);
	man.setScale(2, 2);
}

void Man::walking(void)
{
	//std::cout << man.getPosition().y << std::endl;
	if (man.getPosition().y > -300) {
		rect_y += 100;
		if (rect_y >= 600)
			rect_y = 400;
		man.setTextureRect(sf::IntRect(0, rect_y, 60, 100));
		return;
	}

	rect_y += 100;
	if (rect_y >= 400)
		rect_y = 0;
	man.setTextureRect(sf::IntRect(0, rect_y, 60, 100));

	if (man.getPosition().y <= -300) {
		man.setPosition(man.getPosition().x, man.getPosition().y + pos_y);
		man.setScale(man.getScale().x + scale_inr, man.getScale().y + scale_inr);
	}
}

bool Man::kill_animation(void)
{
	if (rect_x >= 304)
		return false;
	man.setTextureRect(sf::IntRect(rect_x, 730 - (rect_x/10), 60, 80));
	rect_x += 60 + 16;
	return true;
}

void Man::respawn(void)
{
	man.setTextureRect(sf::IntRect(0, rect_y, 60, 100));
	man.setPosition(rand() % 1366 - 400, -400);
	man.setScale(2, 2);
	rect_x = 0;
}