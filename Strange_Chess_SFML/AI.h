#pragma once
#include <list>

class AI
{
protected:
	bool *direction;					//possible moves
	int SIZE;						
	int board;
	int *AI_state;						//board situation for AI
	int *Possibility(int *state);		//search algorithm for AI
public:
	AI(int size);
	void Move(int *state);
};

