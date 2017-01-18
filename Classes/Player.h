#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define NUM_CARPET 12
#define NUM_COINS 0
#define NUM_PLAYER 3

#define RED Color3B(255, 0, 0)
#define GREEN Color3B(0, 255, 0)
#define BLUE Color3B(0, 0, 255)
#define WHITE Color3B(255, 255, 255)

class Player
{
public:

	int IdPlayer;
	int NumCarpet;
	int Coins;
	bool bot;
	bool enable;
	Color3B color;

	void init(int);

	void setIdPlayer(int);
	int getIdPlayer();

	void setNumCarpet(int);
	int getNumCarpet();

	void setCoins(int);
	int getCoins();

	void setBot(bool);
	bool getBot();

	void setEnable(bool);
	bool getEnable();

	void setColor(Color3B);
	Color3B getColor();


	Player();
	~Player();
};

