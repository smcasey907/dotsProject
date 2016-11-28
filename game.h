 #ifndef GAME_H_
#define GAME_H_

//This class monitors the state of the game,
//the score of the participants, and
class Game
{
public:

	Game();

	void initializeGame ();
	int getGridSize(){return gridSize;};
	void printScore();
	void endGamePhase();


	void playerScored(int scored) {pScore += scored;};
	void compScored(int scored) {cScore += scored;};
	int getPlayerScore () {return pScore;};
	int getCompScore () {return cScore;};



private:
	int pScore;
	int cScore;
	int gridSize;
};


#endif /* GAME_H_ */
