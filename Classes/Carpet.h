#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define N 0x08
#define W 0x04
#define S 0x02
#define E 0x01

#define RED Color3B(255, 0, 0)
#define GREEN Color3B(0, 255, 0)
#define BLUE Color3B(0, 0, 255)
#define WHITE Color3B(255, 255, 255)

#define CARPET_FILE "carpet.png"

class Carpet
{
public:

	Sprite *texture = new Sprite;
	int IdPlayer;
	Vec2 index;
	Vec2 position;
	char orient;
	int Zord;

	void init(int IdPlayer, Vec2 ind, char Orient);

	void setIdPlayer(int);
	int getIdPlayer();

	void setIndex(Vec2);
	Vec2 getIndex();

	void setPosition(Vec2);
	Vec2 getPosition();

	void setOrient(char);
	char getOrient();

	void setZord(int);
	int getZord();

	Carpet();
	~Carpet();
};

