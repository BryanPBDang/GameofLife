
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>


class GameofLife
{
	public:
		GameofLife();
		GameofLife(int rowIn, int colIn, double prcntIn);
		GameofLife(int rowIn, int colIn);

		void fillBoard(char **a, int r, int c);
		void fillRandom(char **a, int r, int c, int d);
		char gameSelection();

		int getCol();
		int getRow();

		int getEqual();
		int getBoundary();
		int getDensity();

		void displayBoard(char **a, int rowCount, int colCount);
		void boardSwap(char **a, char **b, int rowCount, int colCount);
		void isEqual(char **a, char **b, int rowCount, int colCount, char choice);

		void MirrorMode(char **a, char **b, int rowCount, int colCount);
		void DonutMode(char **a, char **b, int rowCount, int colCount);
		void ClassicMode(char **a, char **b, int rowCount, int colCount);

		int colC;
		int rowC;

		int percentDensity;
		int boundary;
		int generation;
		int Equal;

		int gameChoice;
		
		char pause;

};
