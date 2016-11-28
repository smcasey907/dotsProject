#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "game.h"
#include "grid.h"

using namespace std;

Game::Game ()
{
	pScore = 0;
	cScore = 0;
	gridSize = 0;
}

void Game::initializeGame()
{

	std::string gridSz;
	bool ok = false;

	cout << "What size grid would you like? (2..9) ";
	getline (cin, gridSz);

	while(!ok)
	{
		if (gridSz.empty())
			{exit(0);}

		std::istringstream iss (gridSz);
		iss >> gridSize;

		if (gridSize < 2 || gridSize > 9)
		{
			cout << "Sorry, try again." << endl;
			cout << "What size grid would you like? (2..9) ";
			getline (cin, gridSz);
		}
		else
			break;
	}
}

void Game::printScore()
{
	cout << "You: " << getPlayerScore() << "    Me: " << getCompScore() << endl << endl;
}

void Game::endGamePhase()
{
	cout << "Final Score: " << endl;
	cout << "  You:" << pScore << endl;
	cout << "  Me:" << cScore << endl;

	if(pScore > cScore)
		cout << "Congratulations!";
	if(cScore > pScore)
		cout << "Better luck next time.";
	if(pScore == cScore)
		cout << "I think we need a rematch.";
}







