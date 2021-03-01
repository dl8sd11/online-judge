#include "Game.h"
#include <iostream>
using namespace std;

Game::Game(){
    
    score=0;
}

Direction Game::read_input(){
	
	char input;
	cin>>input;
	
	if(input=='e')
	{
		return UP;
	}
	
	else if(input=='d')
	{
		return DOWN;
	}
	
	else if(input=='s')
	{
		return LEFT;
	}
	
	else if(input=='f')
	{
		return RIGHT;
	}
	
	else return INVALID;
}

void Game::printScore()
{
	cout<<"Score: "<<score<<endl; 
}

void Game::start() {
	board.displayBoard();
	
	
	while (!board.checkGameOver()) {
		Direction dir=read_input();
		int new_score=board.moveBoard(dir);
		score += new_score;
		
		printScore();

        cout << "Hello" << endl;
		board.newTile(false);
        cout << "Hello" << endl;
		board.displayBoard();
        cout << "Hello" << endl;

	}
	
	cout<<"Game Over"<<endl;
	printScore();
	
}


