#pragma once
//#include <SFML/Graphics.hpp>
#include "Global.h"
#include <SFML/Audio.hpp>

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
	sf::SoundBuffer shotgun_buffer, theme_buffer, hurt_buf, died_buf, over_buf;
	sf::Sound shotgun_sound, theme_sound, hurt, died, over;
	sf::RectangleShape health_bar, curr_health;
	
	void Load_Resources(void);
	void update(int, int);
	void fire(bool &);
	void reset(void);
};

