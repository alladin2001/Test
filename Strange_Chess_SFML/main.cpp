#include <iostream>
#include "Game.h"

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>

int main()
{
	sf::RenderWindow window(sf::VideoMode(620, 700), "SrtrangeChess");
	window.setFramerateLimit(60);

	sf::Font font;
	font.loadFromFile("Font/8277.ttf");

	sf::Text text("F2 - New Game / Esc - Exit / Arrow Keys - Move Cell", font, 25);
	text.setFillColor(sf::Color(205, 133, 63));
	text.setPosition(45.f, 15.f);

	Game game;
	game.setPosition(0.f, 80.f);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (event.type == sf::Event::KeyPressed)
			{
				
				if (event.key.code == sf::Keyboard::Escape) window.close();                 //exit


				if (event.key.code == sf::Keyboard::Left)	game.Move(Direction::Left);		//control
				if (event.key.code == sf::Keyboard::Right)  game.Move(Direction::Right);
				if (event.key.code == sf::Keyboard::Up)     game.Move(Direction::Up);
				if (event.key.code == sf::Keyboard::Down)   game.Move(Direction::Down);

				if (event.key.code == sf::Keyboard::Enter)	game.CheckCell();				//choice
				
				if (event.key.code == sf::Keyboard::F2)  	game.Init();					//new game
			}
		}

		window.clear();
		window.draw(game);
		window.draw(text);
		window.display();
	}

	return 0;
}