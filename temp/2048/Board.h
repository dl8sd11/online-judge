#ifndef BOARD
#define BOARD

#include <stdio.h>
#include "Direction.h"
#include <cstdlib>
#include <ctime>

class Board{
private:
    char tiles[4][4];
    
public:
    
    Board();
    
	
	void displayBoard();
	void newTile(bool aOnly);
	int moveSingleLine(char[], char[]);
	int moveBoard(Direction);
	bool checkGameOver();
	
};
#endif
