#include "Game.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>


using namespace std;

GameofLife::GameofLife() //constructor
{
	rowC = 0;
	colC = 0;
	gameChoice = 0;
	pause = ' ';
	prcntDensity = 0;
	boundary = 0;
}

GameofLife::GameofLife(int rowIn, int colIn, double prcntIn) //cal percent
{
	rowC = rowIn;
	colC = colIn;
	percentDensity = round((rowIn * colIn * prcntIn));
	boundary = rowIn * colIn;
	generation = 1;
}

GameofLife::GameofLife(int rowIn, int colIn) //cal
{
	rowC = rowIn;
	colC = colIn;
	boundary = rowIn * colIn;
	generation = 1;
}

//reset board
void GameofLife::fillBoard(char **a, int x, int y)
{
	//blank double array
	for (int i = 0; i < x; ++i)
	{
		for (int j = 0; j < y; ++j)
		{
			a[i][j] = ' ';
		}
	}
	//double array -
	for (int i = 1; i < x-1; ++i)
	{
		for (int j = 1; j < y-1; ++j)
		{
			a[i][j] = '-';
		}
	}
}

//random fill
void GameofLife::fillRandom(char **a, int x, int y, int z)
{
	for (int i = 0; i < z; ++i)
	{
		//Generate 2 numbers bigger than 0
		int o = rand()% (x -2) + 1;
		int p = rand()% (y - 2) + 1;
		if(a[o][p] == '-')
		{
			a[o][p] = 'X';
		}
		else if(a[o][p] == 'X')
		{
			--i;
		}
	}
}

//show indexs of board
void GameofLife::displayBoard(char **a, int rowCount, int colCount)
{
	for(int i = 1; i < rowCount-1; ++i)
	{
		for (int j = 1; j < colCount-1; ++j)
		{
			cout << a[i][j] << " ";
			if (j == colCount-2)
			{
				cout << endl;
			}
		}
	}
	cout << endl;
}

//clone?
void GameofLife::boardSwap(char **a, char **b, int rowCount, int colCount)
{
	for (int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			a[i][j] = b[i][j];
		}
	}
}

void GameofLife::ClassicMode(char **a, char **b, int rowCount, int colCount){
	for(int i = 1; i < rowCount -1; ++i)
	{
		for(int j = 1; j < colCount -1; ++j)
		{
			int nearCount = 0;
			int index = 0;
			for (int k = -1; k < 2; ++k)
			{
				for(int l = -1; l < 2; ++l)
				{
					if(a[i+k][j+l] == 'X' && index != 4){
						++nearCount;
					}
					++index;
				}
			}
			if(nearCount < 2)
				b[i][j] = '-';
			else if(nearCount == 2)
				b[i][j] = a[i][j];
			else if(nearCount == 3)
				b[i][j] = 'X';
			else if(nearCount >=4)
				b[i][j] = '-';
		}
	}
}

void GameofLife::DonutMode(char **a, char **b, int rowCount, int colCount){
	for(int i = 0; i < rowCount; ++i)
	{
		for (int j = 0; j < colCount; ++j)
		{
			if(i == 0 && j == 0)
			{
				a[0][0] = a[rowCount-2][colCount-2];
			}
      else if(i==0 && j == colCount-1)
			{
				a[0][j] = a[rowCount-2][1];
			}
      else if(i== rowCount - 1 && j == 0)
			{
				a[i][0] = a[1][colCount - 2];
			}

      else if(i == rowCount -1 && j == colCount - 1)
			{
				a[i][j] = a[1][1];
			}

			else if(i == 0) //top row
			{
				a[i][j] = a[rowCount-2][j];
			}

      else if(i == rowCount - 1) //bottom row
			{
				a[i][j] = a[1][j];
			}

      else if(j == colCount -1)     //right row
			{
				a[i][j] = a[i][1];
			}

			else if(j == 0)   //left row
			{
				a[i][j] = a[i][colCount - 2];
			}

		}
	}

}

void GameofLife::gameMirror(char **a, char **b, int rowCount, int colCount)
{
 	for (int i = 0; i < rowCount; ++i){
                for(int j = 0; j < colCount; ++j){
                        //solve for corners
                        if(i == 0 && j == 0)
                                a[i][j] = a[1][1];
                        else if(i == 0 && j == colCount-1)
                                a[i][j] = a[1][colCount-2];
                        else if(i == rowCount -1 && j == 0)
                                a[i][j] = a[rowCount -2][1];
                        else if(i == rowCount -1 && j == colCount-1)
                                a[i][j] = a[rowCount-2][colCount-2];
                        //solve for sides
                        else if(i == 0)         //top row
                                a[i][j] = a[1][j];
                        else if(i == rowCount - 1)      //bottom row
                                a[i][j] = a[rowCount-2][j];
                        else if(j == 0)
                                a[i][j] = a[i][1];
                        else if(j == colCount - 1)
                                a[i][j] = a[i][colCount - 2];
                }
        }
}


void GameofLife::isEqual(char **a, char **b, int rowCount, int colCount, char choice){	//Checks if both boards are equal

	bool isEqual == false;

	for (int i = 1; i < rowCount - 1; ++i){
		for (int j = 1; j < colCount -1; ++j){
			if(a[i][j] == b[i][j])
			{
				isEqual == true;
			}
			else if(a[i][j] != b[i][j])
			{
				isEqual == false;
			}
		}
	}

	if(isEqual == true)
	{
		cout << "Generation: " << generation << endl;
		displayBoard(b, rowCount, colCount);
		boardSwap(a, b, rowCount, colCount);
		generation++;
	}

	else if (isEqual == false)
	{
		cout << "Done"<<endl;
	}
	
	if(choice == 'Y' || choice =='y'){		//Asks user to press enter to continue.
		cout << "Press Enter to Continue"<< endl;
		cin.ignore();
	}
}

int GofL::getRow(){
	return rowC;
}

int GofL::getCol(){
	return colC;
}

int GofL::getDensity(){
	return prcntDensity;
}

int GofL::getBoundary(){
	return boundary;
}

int GofL::getEqual(){
	return Equal;
}
