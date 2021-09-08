#include "Man.hpp"

void Man::Load_texture(void)
{
	man_texture.loadFromFile("Resources/Sprite_sheets/doom_man.png");
	man.setTexture(man_texture);
	man.setTextureRect(sf::IntRect(0, rect_y, 60, 100));
	man.setPosition(rand() % window_size.x - 300, -400);
	man.setScale(2, 2);
}

void Man::walking(Gun &g)
{
	if (man.getPosition().y > -300) {
		rect_y += 100;
		if (rect_y >= 600)
			rect_y = 400;
		man.setTextureRect(sf::IntRect(0, rect_y, 60, 100));
		g.health -= 5;
		if(g.hurt.getStatus() != sf::Sound::Status::Playing)
			g.hurt.play();
		g.bloodSplash_intensity = 255;
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
	man.setPosition(rand() % window_size.x - 300, -400);
	man.setScale(2, 2);
	rect_x = 0;
}

void Man::reset(void)
{
	rect_y = rect_x = 0;
	pos_y = 10;
	respawn();
}
