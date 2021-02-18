#pragma once
#include <SFML/Graphics.hpp>
#include "AI.h"

const int SIZE = 8;									// side size of the playing field
const int ARRAY_SIZE = SIZE * SIZE;					// playing field size

const int FIELD_SIZE = 620;							// playing field size in pixels
const int CELL_SIZE = 75;							// cell size in pixels

enum class Direction { Left = 0, Right = 1, Up = 2, Down = 3 };

class Game : public sf::Drawable, public sf::Transformable
{
	protected:
		AI *AI_play = new AI(SIZE);					//the most unpredictable AI
		Direction *move_direction;					//possible moves
		int *array_state = new int[ARRAY_SIZE];		//array of the state game
		int cell = 36;								//start position
		bool check_cell = true;						//state of choice
		void MovePoss();							//search algorithm for possible moves
		sf::Image image;
		sf::Font font;
	public:
		Game();
		void Init();								//initialization/new game
		int CheckWin() const;						//who has won
		void Move(Direction direction);				//moving around the board
		void CheckCell();					
	public:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;   //rendering
};

