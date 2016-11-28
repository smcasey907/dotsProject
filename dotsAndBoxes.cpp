#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "game.h"
#include "grid.h"

using namespace std;


int main()
{


	Game game;

	//Create a new game and prompt player for grid size
	game.initializeGame();

	//Create the game grid based on grid size
	Grid grid(game.getGridSize());

	grid.compSetup();

	bool gameFinished = false;
	int turn = 1;

	while (!gameFinished)
	{
		//Player's Turn
		if (turn == 1)
		{
			grid.printGrid();
			game.printScore();
			int legalCheck = 1;
			int score = 0;
			while (legalCheck == 1)
			{
				std::string playerChoice;
				cout << "What two dots would you like to connect? (Q to quit) ";
				getline (cin, playerChoice);
				if (playerChoice == "\r" || playerChoice == "\n" || playerChoice == "\0")
				{
					gameFinished = true;
					break;
				}
				legalCheck = grid.legal(playerChoice);
				if (legalCheck == 1)
				{
					cout << "Sorry, try again." << endl;
				}
				else if (legalCheck == 3)
				{
					gameFinished = true;
					break;
				}
				if (legalCheck == 0)
				{
					legalCheck = 0;
					grid.applyMove();
					grid.removeCompCoords();
					score = grid.checkForBox(turn);

					if (score >= 1)
					{
						game.playerScored(score);
						turn = 1;
						score = 0;
					}
					else
					{
						turn = 0;
						score = 0;
					}
				}

			}

			//Before end of turn, check if grid is full
			int gfCheck = game.getGridSize();
			if (grid.getBoxCount() == (gfCheck * gfCheck))
			{
				gameFinished = true;
				break;
			}
		}

		//Computer's Turn
		if (turn == 0)
		{

			int score = 0;
			int scored = 0;

			grid.printGrid();
			game.printScore();

			scored = grid.getComputerTurn();
			grid.applyMove();
			grid.removeCompCoords();
			if (scored == 1)
			{
				score = grid.checkForBox(turn);
				game.compScored(score);
				turn = 0;
				score = 0;
			}
			else
			{
				turn = 1;
				score = 0;
			}

			//Before end of turn, check if grid is full
			int gfCheck = game.getGridSize();
			if (grid.getBoxCount() == (gfCheck * gfCheck))
			{
				gameFinished = true;
				break;
			}

		}
	}


	//End Game phase
	grid.printGrid();
	cout << endl;
	game.endGamePhase();

	return 0;
}

