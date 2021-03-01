#include "Board.h"
#include "Direction.h"
#include <iostream>
#include <cmath> 
using namespace std;

Board::Board(){
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			tiles[i][j]=' ';
		}
	}
	
	srand( time(NULL) );
	
	newTile(true);
	newTile(true);
	
}

void Board::displayBoard(){
	
	cout<<"+---+---+---+---+"<<endl;
		
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			cout<<"| "<<tiles[i][j]<<" ";
		}
		cout<<"|"<<endl;
		cout<<"+---+---+---+---+"<<endl;
	}

}

void Board::newTile(bool aOnly){
	
	int ri, rj, word;
	
	while(true)
	{
		ri=rand()%4;
		rj=rand()%4;
		
		if(tiles[ri][rj]==' ')
		{
			word=rand()%3;
			if (aOnly) word = 0;
			
			if(word==0)
			{
				tiles[ri][rj]='A';
			}
			
			else if(word==1)
			{
				tiles[ri][rj]='B';
			}
			
			else if(word==2)
			{
				tiles[ri][rj]='C';
			}
			
			break;
		}	
	}
	
}

int Board::moveSingleLine(char line[4], char new_line[4]){
	
	int score=0;
	int temp; 
	
	//MERGE
	
	for(int i=0;i<3;i++)
	{
		for(int j=i+1;j<4;j++)
		{
			if(line[i]==line[j]&&line[i]!=' ')
			{
				if(i+1==j)
				{
					line[i]=line[i]+1;
					line[j]=' ';
					temp=int(line[i])-64;
					temp=pow(2,temp);
					score=score+temp;
				}
				
				else
				{
					int empty=0;
					
					for(int k=i+1;k<j;k++)
					{
						if(line[k]==' ')
						empty++;	
					}
					
					if(empty==j-i-1)
					{
						line[i]=char(line[i]+1);
						line[j]=' ';
						temp=int(line[i])-64;
						temp=pow(2,temp);
						score=score+temp;	
					}	
					
				}
			}
		}
	}
	
	//ALIGN LEFT
	
	int index=0;
	
	for(int i=0;i<4;i++)
	{
		if(line[i]==' ')
		{
			continue;
		}
		
		else
		{
			new_line[index]=line[i];
			index++;
		}
	}
	
	for(int i=index;index<4;index++)
	{
		new_line[index]=' ';
	}
	
	
	return score;
	
}

int Board::moveBoard(Direction dir){

	if(dir==UP){
		
		int totalscore = 0;
		
		for (int i=0;i<4;i++) {
		
			char line[4];
			char new_line[4];
			int score;
			
			for(int j=0;j<4;j++)
			{
				line[j]=tiles[j][i];
			}
			
			score=moveSingleLine(line,new_line);
			totalscore=totalscore+score;
			
			for(int k=0;k<4;k++)
			{
				tiles[k][i]=new_line[k];
			}
			
		}
		
		return totalscore;

	}
	
	if(dir==DOWN){
		
		int totalscore = 0;
		
		for (int i=0;i<4;i++) {
		
			char line[4];
			char new_line[4];
			int score;
			
			for(int j=0;j<4;j++)
			{
				line[j]=tiles[3-j][i];
			}
			
			score=moveSingleLine(line,new_line);
			totalscore=totalscore+score;
			
			for(int k=0;k<4;k++)
			{
				tiles[3-k][i]=new_line[k];
			}
			
		}
		
		return totalscore;
	
	}
	
	if(dir==LEFT){
		
		int totalscore = 0;
		
		for (int i=0;i<4;i++) {
		
			char line[4];
			char new_line[4];
			int score;
			
			for(int j=0;j<4;j++)
			{
				line[j]=tiles[i][j];
			}
			
			score=moveSingleLine(line,new_line);
			totalscore=totalscore+score;
			
			for(int k=0;k<4;k++)
			{
				tiles[i][k]=new_line[k];
			}
			
		}
		
		return totalscore;
		
	}
	
	if(dir==RIGHT){
		
		int totalscore = 0;
		
		for (int i=0;i<4;i++) {
		
			char line[4];
			char new_line[4];
			int score;
			
			for(int j=0;j<4;j++)
			{
				line[j]=tiles[i][3-j];
			}
			
			score=moveSingleLine(line,new_line);
			totalscore=totalscore+score;
			
			for(int k=0;k<4;k++)
			{
				tiles[i][k]=new_line[3-k];
			}
			
		}
		
		return totalscore;
		
		
	}
    return -1;
	
} 

bool Board::checkGameOver(){
	
	cout << "IN" << endl; 
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<4;j++)
		{
			if(tiles[i][j]==' ')
			return false;
		}
	}
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(tiles[i][j]==tiles[i][j+1])
			return false;
		}
	}
	
	for(int i=0;i<4;i++)
	{
		for(int j=0;j<3;j++)
		{
			if(tiles[j][i]==tiles[j+1][i])
			return false;
		}
	}
	
	cout << "OUT" << endl; 
	return true;
	 
}
