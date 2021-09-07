#include "Gun.hpp"

void Gun::Load_Resources(void)
{
	shotgun_texture.loadFromFile("Resources/Sprite_sheets/shotgun.png");
	crossair_tex.loadFromFile("Resources/Sprite_sheets/crossair.png");
	bloodSplash_tex.loadFromFile("Resources/Sprite_sheets/blood_screen.png");

	shotgun.setTexture(shotgun_texture);
	shotgun.setTextureRect(sf::IntRect(0, 0, 220, 145));
	crossair.setTexture(crossair_tex);

	bloodSplash.setTexture(bloodSplash_tex);
	bloodSplash.setColor(sf::Color(255, 0, 0, bloodSplash_intensity));
	bloodSplash.setScale(3, 3.5);

	shotgun_buffer.loadFromFile("Resources/Sounds/Shotgun.wav");
	shotgun_sound.setBuffer(shotgun_buffer);
	shotgun.setScale(2, 2);

	health_bar.setSize(sf::Vector2f(200, 20));
	health_bar.setOutlineThickness(4.f);
	health_bar.setFillColor(sf::Color::Black);
	health_bar.setOutlineColor(sf::Color::White);
	curr_health.setSize(sf::Vector2f(200, 20));
	curr_health.setFillColor(sf::Color::Red);
}

void Gun::update(int x, int y, sf::Vector2i size)
{
	if (x <= size.x/2) {
		shotgun.setScale(2, 2);
	}
	else {
		shotgun.setScale(-2, 2);
	}
	shotgun.setPosition(size.x / 2,
		(y + size.y / 1.5) - shotgun.getGlobalBounds().height);

	health_bar.setPosition((x - size.x / 2) + health_bar.getSize().x, (y - size.y/1.6) + health_bar.getSize().y);
	curr_health.setSize(sf::Vector2f(health * 2, 20));
	curr_health.setPosition((x - size.x / 2) + health_bar.getSize().x, (y - size.y / 1.6) + health_bar.getSize().y);

	bloodSplash.setPosition(x - bloodSplash.getGlobalBounds().width/2, y - bloodSplash.getGlobalBounds().height/2);
	if(bloodSplash_intensity > 0)
		bloodSplash_intensity--;
	bloodSplash.setColor(sf::Color(255, 0, 0, bloodSplash_intensity));
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

void Gun::reset(void)
{
	rect_x = 0;
	health = 100;
	bloodSplash_intensity = 0;
}