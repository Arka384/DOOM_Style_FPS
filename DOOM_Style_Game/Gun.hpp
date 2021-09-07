#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

class Gun
{
private:
	int rect_x = 0;
	bool flashed = true;
public:
	int health = 100, bloodSplash_intensity = 0;
	sf::Sprite shotgun, crossair, bloodSplash;
	sf::Texture shotgun_texture, crossair_tex, bloodSplash_tex;
	sf::IntRect rect;
	sf::SoundBuffer shotgun_buffer;
	sf::Sound shotgun_sound;
	sf::RectangleShape health_bar, curr_health;
	
	void Load_Resources(void);
	void update(int, int, sf::Vector2i);
	void fire(bool &);
};

