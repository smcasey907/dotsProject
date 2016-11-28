#ifndef GRID_H_
#define GRID_H_

#include <iostream>
#include <string>
#include <vector>

class Grid
{
public:
	Grid(int grids);

	//Store a vector of possible options for comp
	void compSetup();
	void removeCompCoords();


	//Print grid at current state
	void printGrid ();

	//Check for legal move
	int legal(std::string check);

	//Apply the legal move
	void applyMove();

	//Check to see if there is a box present and score it if so
	int checkForBox(int xTurn);

	int getComputerTurn();

	//Check if a box is completed
	int getBoxCount () {return boxCount;};

private:

	char** grid;
	int actGridSize;

	char rowCount;
	int colCount;

	int rowCoordA;
	int colCoordA;
	int rowCoordB;
	int colCoordB;

	int rowMove;
	int colMove;

	int boxCount;

	struct compPicks
	{
		int compRow;
		int compCol;
		int free;
	};

	std::vector <compPicks> cPick;
	std::vector <int> cOpts;

	int secondLevelRule(int index);

};


#endif /* GRID_H_ */
