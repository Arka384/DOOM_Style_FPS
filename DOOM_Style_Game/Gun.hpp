#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Gun
{
private:
	int rect_x = 0;
	bool flashed = true;
public:
	sf::Sprite shotgun, crossair;
	sf::Texture shotgun_texture, crossair_tex;
	sf::IntRect rect;
	sf::SoundBuffer shotgun_buffer;
	sf::Sound shotgun_sound;
	
	void Load_Resources(void);
	void setPosition(int, int, sf::Vector2i);
	void fire(bool &);
};

