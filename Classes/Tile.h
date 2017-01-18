#pragma once
#include "cocos2d.h"
using namespace cocos2d;

#define N_to_W 0x84
#define N_to_E 0x81
#define W_to_N 0x48
#define W_to_S 0x42
#define S_to_W 0x24 
#define S_to_E 0x21
#define E_to_S 0x12
#define E_to_N 0x18


#define NEIGHTBOR_N 0x08
#define NEIGHTBOR_W 0x04
#define NEIGHTBOR_S 0x02
#define NEIGHTBOR_E 0x01

#define MAX_IND 9

#define TILE_FILE "tile.png"
#define TURN_FILE "turn.png"
#define CARPET_FILE "carpet.png"
#define HALF_CARPET_FILE "half_carpet.png"

class Tile_m
{
public:

	Sprite *texture =new Sprite;
	Vec2 position;
	Vec2 index;
	bool Assam;
	char orient;
	int TopCarpet;
	char Neighbor_carpet;



	void init(Vec2 ind);

	void setPosition(Vec2);
	Vec2 getPosition();

	void setIndex(Vec2);
	Vec2 getIndex();

	void setAssam(bool);
	bool getAssam();

	void setOrient(Vec2);
	char getOrient();

	void setTopCarpet(int);
	int getTopCarpet();

	void setNeighbor_carpet(char);
	char getNeighbor_carpet();
};

