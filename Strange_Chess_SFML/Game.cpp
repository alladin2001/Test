#include "Game.h"




Game::Game()
{
		font.loadFromFile("Font/8277.ttf");		
		image.loadFromFile("Image/piece1.png");
		Init();
}


void Game::Init()
{
	for (int i = 0; i < ARRAY_SIZE; i++)
		array_state[i] = 0;										//filling empty cells
	
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			array_state[j + i*8] = -1;							//initialization of black pieces from the end of the array
			array_state[ARRAY_SIZE - (j + i * 8) - 1] = 1;		//initialization of white pieces from the beginning of the array
		}	
	}
}

void Game::MovePoss()
{
	move_direction = new Direction[4];
	if (cell > 0 && array_state[cell - 1] == 0 && (cell - 1) % SIZE != SIZE - 1)
		move_direction[0] = Direction::Left;

	if (cell < ARRAY_SIZE - 1 && array_state[cell + 1] == 0 && (cell + 1) % SIZE != 0)
		move_direction[1] = Direction::Right;

	if (cell - SIZE >= 0 && array_state[cell - SIZE] == 0)
		move_direction[2] = Direction::Up;

	if (cell + SIZE <= ARRAY_SIZE && array_state[cell + SIZE] == 0)
		move_direction[3] = Direction::Down;
}

int Game::CheckWin() const
{
	int win_white = 0;
	int win_black = 0;

	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (array_state[j + i * SIZE] == 1)					//counting the number of pieces in enemy positions
				win_white++;
			if (array_state[ARRAY_SIZE - 1 - (j + i * SIZE)] == -1)
				win_black++;
		}
	}
	if (win_black != 9 && win_white != 9)
		return 0;												//no winner
	else if (win_white == 9)
		return -1;												//white WIN!!!!
	else
		return 1;												//black WIN!!!!
}

void Game::CheckCell()									
{
	if (array_state[cell] == 1)
	{
		if (check_cell)											//work ENTER
		{
			check_cell = false;
			MovePoss();
		}
		else
		{
			check_cell = true;
			move_direction = NULL;
		}
	}
}




void Game::Move(Direction direction)
{
	if (check_cell)																			//movement of the green cell
	{
		if (direction == Direction::Left && cell > 0)					cell--;
		if (direction == Direction::Right && cell < ARRAY_SIZE - 1)	    cell++;
		if (direction == Direction::Up && cell - SIZE >= 0)				cell -= SIZE;
		if (direction == Direction::Down && cell + SIZE <= ARRAY_SIZE)	cell += SIZE;
	}
	else
	{
		int temp;
		if (direction == Direction::Left && move_direction[0] == Direction::Left)			//moving figures
		{
			temp = array_state[cell];
			array_state[cell] = 0;
			cell--;                                                                                                            
			array_state[cell] = temp;
			CheckCell();
			AI_play->Move(array_state);											//megamind move
		}
		if (direction == Direction::Right && move_direction[1] == Direction::Right)
		{
			temp = array_state[cell];
			array_state[cell] = 0;
			cell++;
			array_state[cell] = temp;
			CheckCell();
			AI_play->Move(array_state);
		}
		if (direction == Direction::Up && move_direction[2] == Direction::Up)
		{
			temp = array_state[cell];
			array_state[cell] = 0;
			cell -= SIZE;
			array_state[cell] = temp;
			CheckCell();
			AI_play->Move(array_state);
		}
		if (direction == Direction::Down && move_direction[3] == Direction::Down)
		{
			temp = array_state[cell];
			array_state[cell] = 0;
			cell += SIZE;
			array_state[cell] = temp;
			CheckCell();
			AI_play->Move(array_state);
		}
	}
}

void Game::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	sf::Color color = sf::Color(101, 67, 33);

	sf::RectangleShape shape(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
	shape.setOutlineThickness(2.f);
	shape.setOutlineColor(color);
	shape.setFillColor(sf::Color(89, 35, 33));
	target.draw(shape, states);

	shape.setSize(sf::Vector2f(CELL_SIZE - 2, CELL_SIZE - 2));						//rendering board
	for (int i = 0; i < SIZE; i++)
	{
		for (int j = 0; j < SIZE; j++)
		{
			sf::Vector2f position(j * CELL_SIZE + 10.f, i * CELL_SIZE + 10.f);
			shape.setPosition(position);
			if (i % 2 == 0) 
			{
				if ((i + j) % 2 != 0) 
				{
					shape.setFillColor(sf::Color(150, 75, 0));
				}
				else
				{
					shape.setFillColor(sf::Color(205, 133, 63));
				}
			}
			else
			{
				if ((i + j) % 2 != 0)
				{
					shape.setFillColor(sf::Color(150, 75, 0));
				}
				else
				{
					shape.setFillColor(sf::Color(205, 133, 63));
				}
			}
			target.draw(shape, states);
		}
	}
	
	
	shape.setFillColor(sf::Color::Transparent);
	shape.setOutlineColor(sf::Color::Yellow);
	if (!check_cell)															//rendering possible moves
	{
		if (move_direction[0] == Direction::Left)
		{
			sf::Vector2f position((cell - 1) % SIZE * CELL_SIZE + 10.f, (cell - 1) / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			target.draw(shape, states);
		}
		if (move_direction[1] == Direction::Right)
		{
			sf::Vector2f position((cell + 1) % SIZE *CELL_SIZE + 10.f, (cell + 1) / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			target.draw(shape, states);
		}
		if (move_direction[2] == Direction::Up)
		{
			sf::Vector2f position((cell - SIZE) % SIZE *CELL_SIZE + 10.f, (cell - SIZE) / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			target.draw(shape, states);
		}
		if (move_direction[3] == Direction::Down)
		{
			sf::Vector2f position((cell + SIZE) % SIZE *CELL_SIZE + 10.f, (cell + SIZE) / SIZE * CELL_SIZE + 10.f);
			shape.setPosition(position);
			target.draw(shape, states);
		}
	}

	sf::Vector2f position(cell % SIZE *CELL_SIZE + 10.f, cell / SIZE * CELL_SIZE + 10.f);   //rendering green/red cell
	shape.setPosition(position);
	if (check_cell)
		shape.setOutlineColor(sf::Color::Green);
	else
		shape.setOutlineColor(sf::Color::Red);
	target.draw(shape, states);


	
	
	
	
	
	sf::Texture texture;
	texture.loadFromImage(image);

	
	sf::Sprite white_piece;
	white_piece.setTexture(texture);
	white_piece.setTextureRect(sf::IntRect(880, 175, 60, 80));
	white_piece.setScale(0.9f, 0.9f);


	sf::Sprite black_piece;
	black_piece.setTexture(texture);
	black_piece.setTextureRect(sf::IntRect(880, 30, 60, 90));
	black_piece.setScale(0.9f, 0.9f);

	
	for (int i = 0; i < SIZE; i++)												//rendering white/black pieces
	{
		for (int j = 0; j < SIZE; j++)
		{
			sf::Vector2f position(j * CELL_SIZE + 18.f, i * CELL_SIZE + 8.f);

			if (array_state[i * SIZE + j] == 1)
			{
				white_piece.setPosition(position);
				target.draw(white_piece, states);
			}

			if (array_state[i * SIZE + j] == -1)
			{
				black_piece.setPosition(position);
				target.draw(black_piece, states);
			}
		}
	}
   

	if (CheckWin() != 0)												//Win?
	{
			sf::Text text("", font, 52);
		if(CheckWin() == 1)
			text.setString("BLACK WIN !!!!!!\n  Please press F2");
		else
			text.setString("WHITE WIN !!!!!!\n  Please press F2");
		shape.setSize(sf::Vector2f(FIELD_SIZE, FIELD_SIZE));
		shape.setFillColor(sf::Color(89, 35, 33));
		text.setPosition(sf::Vector2f(120, 200));
		shape.setPosition(sf::Vector2f(0, 0));
		target.draw(shape, states);
		target.draw(text, states);
	}

}
