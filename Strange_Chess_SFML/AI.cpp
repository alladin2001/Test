#include "AI.h"
#include <list>
#include <random>
#include <time.h>


AI::AI(int size)
{
	SIZE = size;
	board = SIZE * SIZE - 1;
}

void AI::Move(int *state)
{
	int *select = Possibility(state);


	if (select[1] == 0)													//Left
	{
		state[AI_state[select[0]] - 1] = state[AI_state[select[0]]];
		state[AI_state[select[0]]] = 0;
		AI_state[select[0]]--;
	}

	if (select[1] == 1)													//Right
	{
	
		state[AI_state[select[0]] + 1] = state[AI_state[select[0]]];
		state[AI_state[select[0]]] = 0;
		AI_state[select[0]]++;
	}

	if (select[1] == 2)													//Up	
	{
	
		state[AI_state[select[0]] - SIZE] = state[AI_state[select[0]]];
		state[AI_state[select[0]]] = 0;
		AI_state[select[0]] -= SIZE;
	}
							
	if (select[1] == 3)													//Down
	{
	
		state[AI_state[select[0]] + SIZE] = state[AI_state[select[0]]];
		state[AI_state[select[0]]] = 0;
		AI_state[select[0]] += SIZE;
	}

	delete[] AI_state;
}


int *AI::Possibility(int *state)
{
	AI_state = new int[9];
	int* free = new int[9];
	int j = 0;						
	for (int i = 0; i < board + 1; i++)						//situation for AI
	{
		if (state[i] == -1)
		{
			AI_state[j] = i;
			j++;
		}
		if(j == 9)
			break;
	}
	

	for (int i = 0; i < 9; i++)								//search candidates for the move
	{
		int temp = 0;
		if (AI_state[i] > 0 && state[AI_state[i] - 1] == 0 && (AI_state[i] - 1) % SIZE != SIZE - 1)
			temp++;

		if (AI_state[i] < board  && state[AI_state[i] + 1] == 0 && (AI_state[i] + 1) % SIZE != 0)
			temp++;

		if (AI_state[i] - SIZE >= 0 && state[AI_state[i] - SIZE] == 0)
			temp++;

		if (AI_state[i] + SIZE <= board + 1 && state[AI_state[i] + SIZE] == 0)
			temp++;
		free[i] = temp;
	}
	
	int piece;
	srand(time(NULL));										//random candidate
	while (true) 
	{
		piece = rand() % 9;
		if (free[piece] != 0)
			break;
	}

	direction = new bool[4];
	for (int i = 0; i < 4; i++)
		direction[i] = false;

	//search for all possible moves

	if (AI_state[piece] > 0 && state[AI_state[piece] - 1] == 0 && (AI_state[piece] - 1) % SIZE != SIZE - 1)
		direction[0] = true;

	if (AI_state[piece] < board  && state[AI_state[piece] + 1] == 0 && (AI_state[piece] + 1) % SIZE != 0)
		direction[1] = true;

	if (AI_state[piece] - SIZE >= 0 && state[AI_state[piece] - SIZE] == 0)
		direction[2] = true;

	if (AI_state[piece] + SIZE <= board + 1 && state[AI_state[piece] + SIZE] == 0)
		direction[3] = true;
	

	int select_direction;								//random move

	while (true)
	{
		select_direction = rand() % 4;
		if (direction[select_direction] == true)
			break;
	}
	
	int *select_item = new int[2];
	select_item[0] = piece;
	select_item[1] = select_direction;

	
	delete[] free;
	delete[] direction;

	return select_item;
}