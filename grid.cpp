#include <iostream>
#include <iomanip>
#include <locale>
#include <string>
#include <sstream>
#include <math.h>
#include <vector>
#include "grid.h"

using namespace std;

Grid::Grid (int grids)
{
	actGridSize = (grids * 2 + 1);
	rowCount = 'a';
	colCount = 1;
	rowCoordA = 0;
	colCoordA = 0;
	rowCoordB = 0;
	colCoordB = 0;
	rowMove = 0;
	colMove = 0;
	boxCount = 0;

	grid = new char*[actGridSize];

	for (int row = 0; row < actGridSize; row++)
		grid[row] = new char [actGridSize];

	for (int row = 0; row < actGridSize; row++)
		for (int col = 0; col < actGridSize; col++)
		{
			int rowMath = 0;
			int colMath = 0;
			rowMath = (row % 2);
			colMath = (col % 2);

			if (rowMath == 0 && colMath == 0)
				grid[row][col] = '+';
			else
				grid[row][col] = ' ';
		}
}

void Grid::compSetup()
{
	compPicks compPick;
	for (int row = 0; row < actGridSize; row += 2)
		for (int col = 1; col < actGridSize; col += 2)
		{
			compPick.compRow = row;
			compPick.compCol = col;
			compPick.free = 0;
			cPick.push_back (compPick);
		}
	for (int row = 1; row < actGridSize; row +=2)
		for (int col = 0; col < actGridSize; col += 2)
		{
			compPick.compRow = row;
			compPick.compCol = col;
			compPick.free = 0;
			cPick.push_back (compPick);
		}

}

void Grid::removeCompCoords()
{
	for (unsigned int i = 0; i < cPick.size(); i++)
		if (cPick[i].compRow == rowMove && cPick[i].compCol == colMove)
			cPick.erase(cPick.begin() + i);
}

void Grid::printGrid()
{

	colCount = 1;
	rowCount = 'a';
		for (int row = 0; row < actGridSize; row++)
		{
			int rowMath = 0;
			rowMath = (row % 2);
			if (rowMath == 0)
			{
				cout << rowCount << " ";
				rowCount++;
			}
			else
				cout << "  ";

			for (int col = 0; col < actGridSize; col++)
				cout << grid[row][col];

				cout << endl;
		}

		cout << "  ";
		for (int col = 0; col < actGridSize; col++)
		{
			int colMath = 0;
			colMath = (col % 2);
			if (colMath == 0)
			{
				cout << colCount;
				colCount++;
			}
			else
				cout << " ";
		}
		cout << endl;
}

int Grid::legal(std::string check)
{
	const char maxInt = ('0' + (colCount - 1));
	const char maxChar = (rowCount - 1);
	const char upperMaxChar (toupper(maxChar));
	std::string passedString;
	std::string pString1;
	std::string pString2;

	for (unsigned int i = 0; i < check.size(); ++i)
	{
		char c = check[i];
		if (c >= 'a' && c <= maxChar)
			passedString += c;
		else if (c == '1' && check[i+1] == '0' && colCount == 11)
		{
			passedString += "*";
			i = i+1;
		}
		else if (c >= '1' && c <= maxInt)
			passedString += c;
		else if (c >= 'A' && c <= upperMaxChar)
			passedString += (c - 'A' + 'a');
		else if (c == 'Q')
			passedString += c;
	}


	//String contains only "Q" or has "Q" in it.
	if (passedString == "Q" && passedString.length() == 1)
		return 3;
	if (passedString.find('Q') != std::string::npos)
		return 1;

	//If what remains is more or less then 4 characters
	if (passedString.length() != 4)
		return 1;

	//split the two strings
	pString1 = passedString.substr(0,2);
	pString2 = passedString.substr(2,2);

	//Arrange the two strings so that they are in the
	//form of a1 a2 (letter, number)
	if (isdigit(pString1[0]) || pString1[0] == '*')
	{
		pString1 += pString1[0];
		pString1.erase(pString1.begin());
	}
	if (isdigit(pString2[0]) || pString2[0] == '*')
	{
		pString2 += pString2[0];
		pString2.erase(pString2.begin());
	}

	//Check that there is a letter in the first spot
	if (isdigit(pString1[0]) || isdigit(pString2[0]) || pString1[0] == '*' || pString2[0] == '*')
		return 1;
	//Check that there is a number in the second spot
	if (isalpha(pString1[1]) || isalpha(pString2[1]))
		return 1;

	//Check that coordinates are adjacent
	int c10 = pString1[0] - 97;
	int c20 = pString2[0] - 97;
	int c11 = 0;
	int c21 = 0;
	int rangeCheck = 0;

	if (pString1[1] == '*')
		c11 = 9;
	else if (pString1[1] != '*')
		c11 = (pString1[1] - '0' - 1);
	if (pString2[1] == '*')
		c21 = 9;
	else if (pString2[1] != '*')
		c21 = (pString2[1] - '0' - 1);

	if (c10 > c20)
		rangeCheck += (c10 - c20);
	else if(c10 < c20)
		rangeCheck += (c20 - c10);

	if (c11 > c21)
		rangeCheck += (c11 - c21);
	else if (c11 < c21)
		rangeCheck += (c21 - c11);

	if (rangeCheck != 1)
		return 1;

	//Convert to grid coordinates
	rowCoordA = (c10 * 2);
	rowCoordB = (c20 * 2);
	colCoordA = (c11 * 2);
	colCoordB = (c21 * 2);

	//Check if option is available
	if (rowCoordA == rowCoordB)
		rowMove = rowCoordA;
	else if (rowCoordA > rowCoordB)
		rowMove = rowCoordA - 1;
	else if (rowCoordA < rowCoordB)
		rowMove = rowCoordB - 1;

	if (colCoordA == colCoordB)
		colMove = colCoordA;
	else if (colCoordA > colCoordB)
		colMove = colCoordA - 1;
	else if (colCoordA < colCoordB)
		colMove = colCoordB - 1;

	//Check Grid to see if coordinates are taken
	if ((rowMove % 2 == 0 && grid[rowMove][colMove] == '-') || (colMove % 2 == 0 && grid[rowMove][colMove] == '|'))
			return 1;

	return 0;
}

void Grid::applyMove()
{
	if (rowMove % 2 == 0)
	{
		grid[rowMove][colMove] = '-';
	}
	else
		grid[rowMove][colMove] = '|';

}

int Grid::checkForBox(int xTurn)
{

	char boxClaimedBy;
	if (xTurn == 1)
		boxClaimedBy = 'H';
	else
		boxClaimedBy = 'C';

	int score = 0;
	int sides = 1;

	if (rowMove % 2 == 0)
	{
		if (rowMove - 1 >= 0 && grid[rowMove - 1][colMove - 1] == '|')		//NW
			sides++;
		if (rowMove - 1 >= 0 && grid[rowMove - 1][colMove + 1] == '|')		//NE
			sides++;
		if (rowMove - 1 >= 0 && grid[rowMove - 2][colMove] == '-')			//N
			sides++;
		if (sides == 4)
		{
			score++;
			grid[rowMove - 1][colMove] = boxClaimedBy;
			boxCount++;
		}

		sides = 1;

		if (rowMove + 1 < actGridSize && grid[rowMove + 1][colMove - 1] == '|')		//SW
			sides++;
		if (rowMove + 1 < actGridSize && grid[rowMove + 1][colMove + 1] == '|')		//SE
			sides++;
		if (rowMove + 1 < actGridSize && grid[rowMove + 2][colMove] == '-')			//S
			sides++;
		if (sides == 4)
		{
			score++;
			grid[rowMove + 1][colMove] = boxClaimedBy;
			boxCount++;
		}
	}

	else if (colMove % 2 == 0)
	{
		if (colMove - 1 >= 0 && grid[rowMove - 1][colMove - 1] == '-')		//NW
			sides++;
		if (colMove - 1 >= 0 && grid[rowMove + 1][colMove - 1] == '-')		//SW
			sides++;
		if (colMove - 1 >= 0 && grid[rowMove][colMove - 2] == '|')			//W
			sides++;
		if (sides == 4)
		{
			score++;
			grid[rowMove][colMove - 1] = boxClaimedBy;
			boxCount++;
		}

		sides = 1;

		if (colMove + 1 < actGridSize && grid[rowMove + 1][colMove + 1] == '-')		//NE
			sides++;
		if (colMove + 1 < actGridSize && grid[rowMove - 1][colMove + 1] == '-')		//SE
			sides++;
		if (colMove + 1 < actGridSize && grid[rowMove][colMove + 2] == '|')			//E
			sides++;
		if (sides == 4)
		{
			score++;
			grid[rowMove][colMove + 1] = boxClaimedBy;
			boxCount++;
		}
	}

	return score;

}

int Grid::getComputerTurn()
{
	bool choice = false;
	int greaterFreedom = 0;


	while (!choice)
	{
		//1. If there are any boxes that have 3 out of
		//   4 of their edges filled, choose one and
		//   fill in that edge

		//Check for boxes from top down
		for (unsigned int i = 0; i < cPick.size(); i++)
		{
			for (int r = 0; r < actGridSize; r += 2)
				for (int c = 1; c < actGridSize; c += 2)
				{

					if(r+1 < actGridSize && grid[r+1][c+1] == '|' && grid[r+2][c] == '-' && grid[r+1][c-1] == '|' && grid[r][c] != '-')
					{
						std::string pick1 = "  ";
						std::string pick2 = "  ";
						int pR1, pC1;

						pR1 = (r/2 + 97);
						char r1 = pR1;
						pC1 = (c/2 + 49);
						char c1 = pC1;
						pick1[0] = r1;
						pick1[1] = c1;
						pick2[0] = r1;
						pick2[1] = c1 + 1;

						cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;
						rowMove = r;
						colMove = c;

						return 1;
					}
				}

		}

		//Check for boxes bottom up
		for (unsigned int i = 0; i < cPick.size(); i++)
		{
			for (int r = 2; r < actGridSize; r += 2)
				for (int c = 1; c < actGridSize; c += 2)
				{
					if(grid[r-1][c+1] == '|' && grid[r-2][c] == '-' && grid[r-1][c-1] == '|' && grid[r][c] != '-')
					{
						std::string pick1 = "  ";
						std::string pick2 = "  ";
						int pR1, pC1;

						pR1 = (r/2 + 97);
						char r1 = pR1;
						pC1 = (c/2 + 49);
						char c1 = pC1;
						pick1[0] = r1;
						pick1[1] = c1;
						pick2[0] = r1;
						pick2[1] = c1 + 1;

						cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;
						rowMove = r;
						colMove = c;

						return 1;
					}
				}
		}

		//Check for boxes right
		for (unsigned int i = 0; i < cPick.size(); i++)
		{
			for (int r = 1; r < actGridSize; r += 2)
				for (int c = 0; c < actGridSize; c += 2)
				{
					if(c+1 < actGridSize && grid[r-1][c+1] == '-' && grid[r][c+2] == '|' && grid[r+1][c+1] == '-' && grid[r][c] != '|')
					{
						std::string pick1 = "  ";
						std::string pick2 = "  ";
						int pR1, pC1;

						pR1 = (r/2 + 97);
						char r1 = pR1;
						pC1 = (c/2 + 49);
						char c1 = pC1;
						pick1[0] = r1;
						pick1[1] = c1;
						pick2[0] = r1;
						pick2[1] = c1 + 1;

						cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;
						rowMove = r;
						colMove = c;

						return 1;
					}
				}
		}

		//Check for boxes left
		for (unsigned int i = 0; i < cPick.size(); i++)
		{
			for (int r = 1; r < actGridSize; r += 2)
				for (int c = 2; c < actGridSize; c += 2)
				{
					if(grid[r-1][c-1] == '-' && grid[r][c-2] == '|' && grid[r+1][c-1] == '-' && grid[r][c] != '|')
					{

						std::string pick1 = "  ";
						std::string pick2 = "  ";
						int pR1, pC1;

						pR1 = (r/2 + 97);
						char r1 = pR1;
						pC1 = (c/2 + 49);
						char c1 = pC1;
						pick1[0] = r1;
						pick1[1] = c1;
						pick2[0] = r1;
						pick2[1] = c1 + 1;

						cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;
						rowMove = r;
						colMove = c;

						return 1;
					}
				}
		}

		//2. Select an open edge that does not add a third
		//   edge to any box
		for (unsigned int i = 0; i < cPick.size(); i++)
		{
			//Go through the grid and select all spaces that
			//won't add a third edge, adding those points
			//to new vector
			int sides;

			unsigned char r = cPick[i].compRow;
			unsigned char c = cPick[i].compCol;

			//Check North
			sides = 0;
			if (r-1 >= 0 && c-1 >= 0 && grid[r-1][c-1] != ' ')							//NW
				sides++;
			if (r-2 >= 0 && grid[r-2][c] != ' ')										//N
				sides++;
			if (r-1 >= 0 && c+1 < actGridSize && grid[r-1][c+1] != ' ')					//NE
				sides++;
			if (sides >= 2)
				continue;

			//Check East
			sides = 0;
			if (r-1 >= 0 && c+1 < actGridSize && grid[r-1][c+1] != ' ')					//NE
				sides++;
			if (c+2 < actGridSize && grid[r][c+2] != ' ')								//E
				sides++;
			if (r+1 < actGridSize && c+1 < actGridSize && grid[r+1][c+1] != ' ')		//SE
				sides++;
			if (sides >= 2)
				continue;

			//Check South
			sides = 0;
			if (r+1 < actGridSize && c+1 < actGridSize && grid[r+1][c+1] != ' ')		//SE
				sides++;
			if (r+2 < actGridSize && grid[r+2][c] != ' ')								//S
				sides++;
			if (r+1 < actGridSize && c-1 >=0 && grid[r+1][c-1] != ' ')					//SW
				sides++;
			if (sides >= 2)
				continue;

			//Check West
			sides = 0;
			if (r+1 < actGridSize && c-1 >=0 && grid[r+1][c-1] != ' ')					//SW
				sides++;
			if (c-2 >= 0 && grid[r][c-2] != ' ')										//W
				sides++;
			if (r-1 >= 0 && c-1 >= 0 && grid[r-1][c-1] != ' ')							//NW
				sides++;
			if (sides >= 2)
				continue;

			cOpts.push_back(i);
		}

		//Pick the edge that does not make a third
		//edge to a box...if more than one edges are
		//available, pick point with greatest degree
		//of freedom...
		if (cOpts.size() == 1)
		{
			rowMove = cPick[cOpts[0]].compRow;
			colMove = cPick[cOpts[0]].compCol;

			std::string pick1 = "  ";
			std::string pick2 = "  ";
			int pR1, pC1;

			pR1 = (rowMove/2 + 97);
			char r1 = pR1;
			pC1 = (colMove/2 + 49);
			char c1 = pC1;
			pick1[0] = r1;
			pick1[1] = c1;
			pick2[0] = r1;
			pick2[1] = c1 + 1;

			cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;

			cOpts.clear();
			return 0;
		}

		//If vector.size() > 1, pick points with greatest
		//degree of freedom
		if (cOpts.size() > 1)
		{
			//Assign degrees of freedom
			for (unsigned int i = 0; i < cOpts.size(); i++)
			{
				int degOfFree = 0;
				degOfFree = secondLevelRule(i);

				cPick[cOpts[i]].free = degOfFree;
			}

			//Find the greatest degree of freedom from list
			for (unsigned int i = 0; i < cOpts.size(); i++)
			{
			if (greaterFreedom < cPick[cOpts[i]].free)
					greaterFreedom = cPick[cOpts[i]].free;
			}

			//Remove other members that aren't equal to greaterFreedom
			for (int i = cOpts.size() - 1; i >= 0; --i)
			{
				if (cPick[cOpts[i]].free != greaterFreedom)
					cOpts.erase (cOpts.begin()+i);
			}

			//Pick cOpts[0];
			rowMove = cPick[cOpts[0]].compRow;
			colMove = cPick[cOpts[0]].compCol;

			std::string pick1 = "  ";
			std::string pick2 = "  ";
			int pR1, pC1;

			pR1 = (rowMove/2 + 97);
			char r1 = pR1;
			pC1 = (colMove/2 + 49);
			char c1 = pC1;
			pick1[0] = r1;
			pick1[1] = c1;
			pick2[0] = r1;
			pick2[1] = c1 + 1;

			cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;

			cOpts.clear();
			return 0;
		}

		//If there are no available options that
		//won't add a third edge, choose edge that
		//follows third & forth level ruling:
		if (cOpts.size() < 1)
		{
			rowMove = cPick[0].compRow;
			colMove = cPick[0].compCol;

			std::string pick1 = "  ";
			std::string pick2 = "  ";
			int pR1, pC1;

			pR1 = (rowMove/2 + 97);
			char r1 = pR1;
			pC1 = (colMove/2 + 49);
			char c1 = pC1;
			pick1[0] = r1;
			pick1[1] = c1;
			pick2[0] = r1;
			pick2[1] = c1 + 1;

			cout << "I choose to connect dots " << pick1 << " and " << pick2 << "." << endl;

			cOpts.clear();
			return 0;
		}

		choice = true;

	}

	return 0;

}

//For each edge E in the list, compute the "degrees of freedom"
//of that edge by counting the total number of open edges
//that touch upon either dot at an end of E.  SELECT THE EDGE
//WITH THE MAXIMUM DEGREES OF FREEDOM.
int Grid::secondLevelRule (int index)
{
	int degreesOfFreedom = 0;
	int sRow = cPick[cOpts[index]].compRow;
	int sCol = cPick[cOpts[index]].compCol;
	std::string a;


	if (sRow % 2 == 0)
	{
		if (sRow - 1 > 0)					//NW
			if(grid[sRow-1][sCol-1] == ' ')
				degreesOfFreedom++;
		if (sCol - 2 > 0)					//W
			if (grid[sRow][sCol-2] == ' ')
				degreesOfFreedom++;
		if (sRow + 1 < actGridSize)			//SW
			if (grid[sRow+1][sCol-1] == ' ')
				degreesOfFreedom++;
		if (sRow - 1 > 0)					//NE
			if (grid[sRow-1][sCol+1] == ' ')
				degreesOfFreedom++;
		if (sCol + 2 < actGridSize)			//E
			if (grid[sRow][sCol+2] == ' ')
				degreesOfFreedom++;
		if (sRow + 1 < actGridSize)			//SE
			if (grid[sRow+1][sCol+1] == ' ')
				degreesOfFreedom++;
	}
	else
	{
		if (sCol + 1 < actGridSize)			//NE
			if(grid[sRow-1][sCol+1] == ' ')
				degreesOfFreedom++;
		if (sRow - 2 > 0)					//N
			if (grid[sRow-2][sCol] == ' ')
				degreesOfFreedom++;
		if (sCol - 1 > 0)					//NW
			if (grid[sRow-1][sCol-1] == ' ')
				degreesOfFreedom++;
		if (sCol + 1 < actGridSize)			//SE
			if (grid[sRow+1][sCol+1] == ' ')
				degreesOfFreedom++;
		if (sRow + 2 < actGridSize)			//S
			if (grid[sRow+2][sCol] == ' ')
				degreesOfFreedom++;
		if (sCol - 1 > 0)					//SW
			if (grid[sRow+1][sCol-1] == ' ')
				degreesOfFreedom++;
	}




	return degreesOfFreedom;
}
