#ifndef GAME
#define GAME 

#include <stdio.h>
#include"Board.h"
#include "Direction.h"


class Game
{
	private:
		
		Board board;
		int score;
		
	public:		
		Game(); 
		Direction read_input();
		void printScore();
		void start();
};
#endif
