#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#define LABEL_FONTNAME "fonts/Marker Felt.ttf"
#define LABEL_FONTNAME1 "fonts/arial.ttf"
#define LABEL_FONTSIZE 24

#define SCORE_CHANGE 10

/*
if (tile[TileInd + 1].getTopCarpet() == tile[TileInd + 1 + 1].getTopCarpet())
{
	tile[TileInd + 1].setNeighbor_carpet(tile[TileInd + 1].getNeighbor_carpet() | E);
	tile[TileInd + 1 + 1].setNeighbor_carpet(tile[TileInd + 1 + 1].getNeighbor_carpet() | W);
}
else
{
	tile[TileInd + 1].setNeighbor_carpet(tile[TileInd + 1].getNeighbor_carpet() & ~E);
	tile[TileInd + 1 + 1].setNeighbor_carpet(tile[TileInd + 1 + 1].getNeighbor_carpet() & ~W);
}
*/



#include "cocos2d.h"
#include "Tile.h"
#include "Assam.h"
#include "Carpet.h"
#include "Player.h"


USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:

	Tile_m tile[81];
	Assam assam;
	Player player[NUM_PLAYER];
	Carpet *carpet = new Carpet;
	Label *StateGame;
	Label *Label_player[NUM_PLAYER];

	int lastKeyCodeAssam;
	int lastKeyCodeCarpet;
	int Zorder;
	int ActivePlayer;

	

static cocos2d::Scene* createScene();

    virtual bool init();
	void AssamRotationPositive(float dt);
	void AssamRotationNegative(float dt);
	void AssamForawardMovement(float dt);
	void RunAssamRun(float dt);

	Carpet *PutCarpet(float dt);
	void CarpetRotationPositive(float dt);
	void CarpetRotationNegative(float dt);
	bool CarpetIsOkey();
	void SetNeighbor();
	void ParkingFees(float dt);
	void TreeTraversal(int &Fees, int* &Neigb, int index);

	void update(float dt);

	void AssamOrient(EventKeyboard::KeyCode keyCode, Event *event);
	void CarpetPosition(EventKeyboard::KeyCode keyCode, Event *event);
	inline void isTilesOnePlayer( int numtile, int numneighbtile, char orient,  char unorient)
    // a selector callback
    

	void menuCloseCallback(cocos2d::Ref* pSender);
	Label *CreateTextLabel(char *text, char *ff, int fsize, Vec2 pos);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
