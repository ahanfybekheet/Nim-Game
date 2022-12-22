#include "nimGame.h"
#define gm Game[nimVariant-1]
void GM::run()
{
	int nimVariant;
	cout << "Hello in FCI NIM GAME:\n1-Variant one\n2-Variant Two\n==>";
	cin >> nimVariant;
	if (nimVariant != 1 && nimVariant != 2) {
		cout << "Invalid Input Please Try Again later!..";
		exit(0);
	}
	while (!(gm->isEnded())) {
		gm->printGame();
		if (gm->isMyTrun()) {
			gm->playBestMove();
		}
		else {
			if (nimVariant == 1) {
				int move;
				while (true) {
					cout << "Pls pick 1 to 3 coins and <= remaining coins: ";
					cin >> move;
					if (((VariantOne*)gm)->isValidMove(move)) {
						break;
					}
					else {
						cout << "Invalid Input Please Enter Valid Input\n";
					}
				}
				((VariantOne*)gm)->update(move);
			}
			else {
				int pile, move;
				while (true) {
					cout << "Pls pick Row Number then space then 1 to 3 coins and <= remaining coins: ";
					cin >> pile >> move;
					if (((VariantTwo*)gm)->isValidMove(pile, move)) {
						break;
					}
					else {
						cout << "Invalid Input Please Enter Valid Input\n";
					}
				}
				((VariantTwo*)gm)->update(pile, move);

			}

		}
	}
	
}

GM::~GM()
{
	delete Game[0];
	delete Game[1];
}

bool VariantTwo::isEnded()
{
	for (int i = 0; i < 3; i++) {
		if(Piles[i]!=0)
			return false;
	}
	return true;
}

string operator*(string str, int i)
{
	if (i == 0)
	{
		return "";
	}
	while (--i)
	{
		str += str[0];
	}
	return str;
}


void VariantTwo::printGame()
{
	for (int i = 0; i < 3; i++)
	{
		cout << "Row " << i << "    " << string("*") * Piles[i] << endl;
	}
}

bool VariantTwo::isValidMove(int pile, int move)
{
	if (pile > -1 && pile < 4) {
		if (Piles[pile] >= move) {
			return true;
		}
	}
	return false;
}

void VariantTwo::playBestMove()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j <= 3 && j <= Piles[i]; j++)
		{
			Piles[i] -= j;
			bool score = minimax(false);
			Piles[i] += j;
			if (score == 1) {
				update(i, j);
				return;
			}
		}
	}
	for (int i = 0; i < 3; i++)
	{
		for (int j = 1; j <= 3 && j <= Piles[i]; j++)
		{
			update(i, j);
			return;
		}
	}

}

bool VariantTwo::minimax(bool isMaximizing)
{
	if (isEnded())
	{
		return !isMaximizing;
	}
	if (isMaximizing)
	{
		int bestScore = -1;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 1; j <= 3 && j <= Piles[i]; j++)
			{
				Piles[i] -= j;
				int score = minimax(false);
				bestScore = max(score, bestScore);
				Piles[i] += j;
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 2;
		for (int i = 0; i < 3; i++)
		{
			for (int j = 1; j <= 3 && j <= Piles[i]; j++)
			{
				Piles[i] -= j;
				int score = minimax(true);
				bestScore = min(score, bestScore);
				Piles[i] += j;
			}
		}
		return bestScore;
	}
}

void VariantTwo::update(int pile, int move)
{
	Piles[pile] -= move;
	myTurn = !myTurn;

}

VariantOne::VariantOne()
{
	nCoins = 23;
	cScore = 0;
	hScore = 0;
}

bool VariantOne::isEnded()
{
	return nCoins;
}

void VariantOne::printGame()
{
	for (int i = 0; i < nCoins; i++) {
		cout << '*';
	}
	cout << endl;
}

bool VariantOne::isValidMove(int move)
{
	return nCoins >=move && move < 4  && move>-1;
}

void VariantOne::playBestMove()
{
	for (int i = 1; i <= 3; i++)
	{
		if (nCoins >= i)
		{
			nCoins -= i;
			cScore += i;
			bool score = minimax(false);
			nCoins += i;
			cScore -= i;
			if (score == 1) {
				update(i);
				return;
			}
		}
	}
	update(1);
}

bool VariantOne::minimax(bool isMaximizing)
{
	if (isEnded())
	{
		return cScore % 2 == 0;
	}
	if (isMaximizing)
	{
		int bestScore = -1;
		for (int i = 1; i <= 3; i++)
		{
			if (nCoins >= i)
			{
				nCoins -= i;
				cScore += i;
				int score = minimax(false);
				bestScore = max(score, bestScore);
				nCoins += i;
				cScore -= i;
			}
		}
		return bestScore;
	}
	else
	{
		int bestScore = 2;
		for (int i = 1; i <= 3; i++)
		{
			if (nCoins >= i)
			{
				nCoins -= i;
				hScore += i;
				int score = minimax(true);
				bestScore = min(score, bestScore);
				nCoins += i;
				hScore -= i;
			}
		}
		return bestScore;
	}
}

void VariantOne::update(int move)
{
	nCoins -= move;
	myTurn = !myTurn;
}

void VariantOne::set_hScore(int score)
{
	hScore = score;
}

bool NimGame::isMyTrun()
{
	return myTurn;
}
