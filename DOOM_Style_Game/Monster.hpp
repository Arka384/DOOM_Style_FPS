#pragma once
//#include <SFML/Graphics.hpp>
#include "Global.h"
#include "Gun.hpp"

class Monster
{
private:
	int rect_x = 0, rect_y = 0, pos_y = 10;
	float scale_inr = 0.5;
	bool executed = false;
public:
	sf::Sprite monster;
	sf::Texture monster_tex;

	void Load_texture(void);
	void walking(Gun &g);
	bool kill_animation(void);
	void respawn(void);
	void reset(void);
};

