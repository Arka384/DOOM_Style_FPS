#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class Man
{
private:
	int rect_y = 0, rect_x = 0, pos_y = 10;
	float scale_inr = 0.5;
public:
	sf::Sprite man;
	sf::Texture man_texture;
	
	void Load_texture(void);
	void walking(void);
	bool kill_animation(void);
	void respawn(void);
};

