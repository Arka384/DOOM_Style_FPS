//#include <SFML/Graphics.hpp>
#include "Global.h"
#include <iostream>
#include "Monster.hpp"
#include "Man.hpp"
#include "Gun.hpp"

bool hit_target(Gun g, Man m);
bool hit_target(Gun g, Monster m);
void check_mouse_pos(float &x, float &y, sf::Window &window);
bool colliding(Man g, Monster m);


int main()
{
	srand(time(NULL));
	sf::RenderWindow window(sf::VideoMode(window_size.x, window_size.y), "Test", sf::Style::Close);
	sf::View view;
	sf::Time t;
	sf::Clock clk;
	float mx = 0, my = 0, dt = 0, fire_timer = 0, m_timer = 0, g_timer = 0;
	bool game_over = false, start_state = true, play_state = false;

	sf::Sprite start_sc, ded_sc;
	sf::Texture start_tex, ded_tex;
	start_tex.loadFromFile("Resources/Sprite_sheets/DOOM.png");
	start_sc.setTexture(start_tex);
	start_sc.setPosition(window_size.x/2 - start_sc.getGlobalBounds().width/2, window_size.y / 2 - start_sc.getGlobalBounds().height / 2);
	ded_tex.loadFromFile("Resources/Sprite_sheets/ded.png");
	ded_sc.setTexture(ded_tex);
	
	/*
	sf::Sprite forest;
	sf::Texture forest_tex;
	forest_tex.loadFromFile("Resources/Sprite_sheets/dark_alley.jpg");
	forest.setTexture(forest_tex);
	forest.setScale(1.5, 1.5);
	forest.setPosition(-250, -100);
	//forest.setPosition(-650, -400);
	*/

	bool mousePressed = false, fired = false, m_dead = false, g_dead = false;
	Man doom_guy;
	doom_guy.Load_texture();
	Monster red_guy;
	red_guy.Load_texture();
	Gun gun;
	gun.Load_Resources();
	window.setMouseCursorVisible(false);

	while (window.isOpen())
	{
		t = clk.restart();
		dt = t.asSeconds();
		fire_timer += dt;
		m_timer += dt;
		g_timer += dt;

		sf::Event evnt;
		while (window.pollEvent(evnt))
		{
			switch (evnt.type)
			{
			case sf::Event::Closed:
				window.close();
			case sf::Event::MouseButtonPressed:
				mousePressed = true;
				fired = true;
				break;
			case sf::Event::MouseButtonReleased:
				mousePressed = false;
				break;
			case sf::Event::KeyPressed:
				if (evnt.key.code == sf::Keyboard::Escape)
					window.close();
				if (evnt.key.code == sf::Keyboard::Enter) {
					if (start_state || game_over) {
						start_state = false;
						game_over = false;
						gun.reset();
						doom_guy.reset();
						red_guy.reset();
						play_state = true;
						gun.theme_sound.play();
					}
				}
				break;
			default:
				break;
			}
		}
		/////////////////////////

		if (play_state)
		{
			mx = sf::Mouse::getPosition(window).x;
			my = sf::Mouse::getPosition(window).y;
			check_mouse_pos(mx, my, window);
			view.setCenter(mx, my);
			window.setView(view);
			gun.crossair.setPosition(mx - 100, my - 300);
			gun.update(mx, my);
			if (gun.health <= 0) {
				gun.theme_sound.stop();
				gun.died.play();
				play_state = false;
				ded_sc.setPosition(mx - window_size.x / 2, my - window_size.y / 2);
				game_over = true;
			}

			if (m_timer >= 0.2) {	//monster
				if ((fired && mousePressed && hit_target(gun, red_guy)) || m_dead) {
					m_dead = red_guy.kill_animation();
					if (!m_dead) {
						red_guy.respawn();
						if (colliding(doom_guy, red_guy))
							red_guy.respawn();
						m_dead = false;
					}
				}
				else
					red_guy.walking(gun);
				m_timer = 0;
			}

			if (g_timer >= 0.2) {	//doom guy
				if ((fired && mousePressed && hit_target(gun, doom_guy)) || g_dead) {
					g_dead = doom_guy.kill_animation();
					if (!g_dead) {
						doom_guy.respawn();
						g_dead = false;
					}
				}
				else
					doom_guy.walking(gun);
				g_timer = 0;
			}

			if (fired) {
				if (fire_timer >= 0.2) {
					gun.fire(fired);
					fire_timer = 0;
				}
			}
			else
				gun.shotgun.setTextureRect(sf::IntRect(0, 0, 220, 145));
		}
		

		///////////////////
		window.clear();
		//window.draw(forest);
		if (start_state)
			window.draw(start_sc);
		if (play_state) {
			window.draw(doom_guy.man);
			window.draw(red_guy.monster);
			window.draw(gun.shotgun);
			window.draw(gun.health_bar);
			window.draw(gun.curr_health);
			window.draw(gun.crossair);
			window.draw(gun.bloodSplash);
		}
		if (game_over)
			window.draw(ded_sc);
		window.display();
	}
}


bool hit_target(Gun g, Man m)
{
	int x = g.crossair.getPosition().x;
	int y = g.crossair.getPosition().y;
	return x > m.man.getPosition().x && x < m.man.getPosition().x + m.man.getGlobalBounds().width
		&& y > m.man.getPosition().y && y < m.man.getPosition().y + m.man.getGlobalBounds().height;
}

bool hit_target(Gun g, Monster m)
{
	int x = g.crossair.getPosition().x;
	int y = g.crossair.getPosition().y;
	return x > m.monster.getPosition().x && x < m.monster.getPosition().x + m.monster.getGlobalBounds().width
		&& y > m.monster.getPosition().y && y < m.monster.getPosition().y + m.monster.getGlobalBounds().height;
}

void check_mouse_pos(float &x, float &y, sf::Window &window)
{
	if (x >= window_size.x)
		x = window_size.x;
	else if (x <= 0)
		x = 0;

	if (y >= window_size.y)
		y = window_size.y;
	else if (y <= 20)
		y = 20;

	sf::Mouse::setPosition(sf::Vector2i(x, y), window);
}

bool colliding(Man g, Monster m)
{
	if (m.monster.getPosition().x > g.man.getPosition().x && m.monster.getPosition().x + m.monster.getGlobalBounds().width
		< g.man.getPosition().x + g.man.getGlobalBounds().width)
		return true;

	return false;
}

