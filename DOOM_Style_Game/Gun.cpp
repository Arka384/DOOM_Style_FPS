#include "Gun.hpp"

void Gun::Load_Resources(void)
{
	shotgun_texture.loadFromFile("Resources/Sprite_sheets/shotgun.png");
	crossair_tex.loadFromFile("Resources/Sprite_sheets/crossair.png");
	shotgun.setTexture(shotgun_texture);
	shotgun.setTextureRect(sf::IntRect(0, 0, 220, 145));
	crossair.setTexture(crossair_tex);
	shotgun_buffer.loadFromFile("Resources/Sounds/Shotgun.wav");
	shotgun_sound.setBuffer(shotgun_buffer);
	shotgun.setScale(2, 2);
}

void Gun::setPosition(int x, int y, sf::Vector2i size)
{
	if (x <= size.x/2) {
		shotgun.setScale(2, 2);
	}
	else {
		shotgun.setScale(-2, 2);
	}
	shotgun.setPosition(size.x / 2,
		(y + size.y / 1.5) - shotgun.getGlobalBounds().height);
}

void Gun::fire(bool &fired)
{
	if (flashed) {
		shotgun.setTextureRect(sf::IntRect(220, 0, 220, 145));
		flashed = false;
		shotgun_sound.play();
		return;
	}

	switch (rect_x)
	{
	case 0:
		rect = sf::IntRect(130, 190, 110, 125);
		rect_x = 130;
		break;
	case 130:
		rect = sf::IntRect(245, 190, 100, 125);
		rect_x = 245;
		break;
	case 245:
		rect = sf::IntRect(350, 190, 95, 125);
		rect_x = 350;
		break;
	case 350:
		rect = sf::IntRect(455, 190, 90, 125);
		rect_x = 455;
		break;
	case 455:
		rect = sf::IntRect(0, 190, 120, 125);
		rect_x = 0;
		flashed = true;
		fired = false;
		break;
	default:
		break;
	}
	shotgun.setTextureRect(rect);
}
