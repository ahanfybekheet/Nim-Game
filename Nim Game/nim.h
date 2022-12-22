#pragma once
#define MAX_MOVE 3
#define N_COINS 23
#define HUMAN 1
#define COMPUTER 0

class Nim
{
protected:
	int nCoins;
	bool whoseTurn;
public:
	bool isEnded();
	void print_coins();


};


class Player {

};
