#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define N 0x08
#define W 0x04
#define S 0x02
#define E 0x01

#define ASSAM_FILE "assam.png"

class Assam
{
public:
	Sprite *texture = new Sprite;
	Vec2 position;
	Vec2 index;
	char orient;
	unsigned int move_step;

	Assam();
	~Assam();

	void init(Vec2 ind);

	void setPosition(Vec2);
	Vec2 getPosition();

	void setIndex(Vec2);
	Vec2 getIndex();

	void setOrient(char);
	char getOrient();

	void setMoveStep(unsigned int);
	unsigned int getMoveStep();

	

};

