#pragma once
#include<iostream>

using namespace std;

class NimGame
{
protected:
	bool myTurn = 1;
	const int MAXMOVE = 3;
public:
	virtual bool isEnded() = 0;
	virtual void printGame() = 0;
	virtual void playBestMove() = 0;
	virtual bool minimax(bool isMaximizing) = 0;
	virtual void printWinner() = 0;
	bool isMyTurn();

};


class VariantOne : public NimGame
{
private:
	int nCoins;
	int cScore;
	int hScore;
public:
	VariantOne();
	bool isEnded();
	void printGame();
	bool isValidMove(int move);
	void playBestMove();
	bool minimax(bool isMaximizing);
	void update(int move);
	void printWinner();

};


class VariantTwo : public NimGame
{
private:
	int Piles[3] = { 3,4,5 };
public:
	bool isEnded();
	void printGame();
	bool isValidMove(int pile,int move);
	void playBestMove();
	bool minimax(bool isMaximizing);
	void update(int pile, int move);
	void printWinner();
};


class GM {
private:
	NimGame* Game[2] = {new VariantOne(), new VariantTwo()};
public:
	void run();
	~GM();
};