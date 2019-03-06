#include "Game.cpp"
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(int argc, char **argv)
{
	int sCells;
	int yPos;
	int xPos;

	int nearCount;
	int index;
	int generation;

	int userCol;
	int userRow;

	double userPop;

	int colCount;
	int rowCount;

	int preGame;
	int boundary;
	int gameChoice;
	int Equal;

	int lineLength;
	int lineCount;

	char choice;

	string line;
	string inFile;

	char **board;
	char **board2;
	ifstream inputStream;


	cout << "Would you like to provide a map or random assignment? \n Enter (1) Pre-map or (2) Make your own: ";
	cin >> preGame;
	cout << "Pause between outputs? (Y/N): ";
	cin >> choice;



	//map
	if (preGame == 1)
	{
		cout << "Enter file name: ";
		cin >> argv[1];
		cout << "test";
		inputStream.open(argv[1]); //read file
		if (inputStream.good())
		{
			lineCount= 0;

			while(getline(inputStream, line)) //String to line
			{
				if(lineCount == 1)
				{
					colCount = std::stoi(line);

				}
				else if(lineCount == 1)
				{
					rowCount = std::stoi(line);
				}
			}

			board = new char *[rowCount];		//Getting the 2nd board
			for (int i = 0; i < rowCount; ++i)
			{
				board[i] = new char [colCount];
				board2 = new char *[rowCount];
			}
			for (int i = 0; i < rowCount; ++i)
			{
				board2[i] = new char [colCount];
			}

		}
		cout << "error";
		inputStream.close();
		inputStream.open(argv[1]);
		if (inputStream.good()){		//sets board map values
			while(getline(inputStream, line))
			{
				for(int i = -2; i < rowCount; ++i)
				{
					for(int j = 0; j < colCount; ++j)
					{
						if(i >= 0)
							board[i][j] = line[j];
					}
				}
			}
		}
		inputStream.close();
		GameofLife game1(rowCount, colCount);
		cout << "Generation: 0"<< endl;
        	game1.displayBoard(board, rowCount, colCount);

        	cout << "Which game mode would you like to play? \n 0 = Classic \n 1 = Doughnut \n 2 = Mirror \n Mode: ";
        	cin >> gameChoice;
	}

//own
	else if(preGame == 2)
	{
		cout << "Enter number of columns ";
		cin >> userCol;
		cout << "Enter number of rows: ";
		cin >> userRow;

		cout << "Enter the percent of board to be populated (use decimal): ";
		cin >> userPop;

		GameofLife game1(userRow, userCol, userPop);

		colCount = game1.getCol() + 2;
		rowCount = game1.getRow() + 2;


		board = new char *[rowCount];
		for (int i = 0; i < rowCount; ++i)
			board[i] = new char [colCount];


		board2 = new char *[rowCount];
		for (int i = 0; i < rowCount; ++i)
			board2[i] = new char [colCount];

		game1.fillBoard(board, rowCount, colCount);
		game1.fillBoard(board2, rowCount, colCount);

		sCells = g1.getDensity();
		boundary = g1.getBoundary();

		game1.fillRandom(board, rowCount, colCount, sCells);

		cout << "Generation: 0" << endl;
		game1.displayBoard(board, rowCount, colCount);

		cout << "Which game mode would you like to play? \n 0 = Classic \n 1 = Doughnut \n 2 = Mirror \n Mode: ";
		cin >> gameChoice;
	}

	GameofLife game1(userRow, userCol, userPop);

				colCount = game1.getCol() + 2;
        rowCount = game1.getRow() + 2;



//Classic Mode
	if(gameChoice == 0)
	{
		cout << "Starting Game Mode: Classic" << endl << endl;
		do
		{
			game1.ClassicMode(board, board2, rowCount, colCount);
			game1.isEqual(board, board2, rowCount, colCount, choice);

			Equal = game1.getEqual();
		}
		while(Equal == 0);
	}

//Donut mode
	else if(gameChoice == 1)
	{
		cout << "Starting Game Mode: Donut" << endl << endl;
		do
		{
			game1.DonutMode(board, board2, rowCount, colCount);
			game1.ClassicMode(board, board2, rowCount, colCount);
			game1.isEqual(board, board2, rowCount, colCount, choice);

			Equal = game1.getEqual();
		}
		while(Equal == 0);
	}

//Mirror Mode
	else if(gameChoice == 2)
	{
		cout << "Starting Game Mode: Mirror" << endl << endl;
		do
		{
			game1.MirrorMode(board, board2, rowCount, colCount);
			game1.ClassicMode(board, board2, rowCount, colCount);
			game1.isEqual(board, board2, rowCount, colCount, choice);

			Equal = game1.getEqual();
		}
		while (Equal == 0);
	}

	return 0;
}
