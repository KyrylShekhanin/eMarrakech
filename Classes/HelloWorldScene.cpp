#include "HelloWorldScene.h"

USING_NS_CC;


auto AssamOrientListener = EventListenerKeyboard::create();
auto PutCarpetListener = EventListenerKeyboard::create();

Scene* HelloWorld::createScene()
{
 
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
    return scene;
}

bool HelloWorld::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 4);


	Vec2 Help_Pos = Vec2(origin.x+visibleSize.width-LABEL_FONTSIZE, origin.y  + visibleSize.height-LABEL_FONTSIZE);
	Label* Help = CreateTextLabel("Help", LABEL_FONTNAME1, LABEL_FONTSIZE, Help_Pos);
	Help->setAnchorPoint(Vec2(1, 1));
	Help->setString
		("ASSAM\n"
		"KEY_LEFT - turn left\n"
		"KEY_RIGHT - turn right\n"
		"ENTER - start movement\n\n"

		"CARPET\n"
		"KEY_W - create new carpet\n"
		"KEY_Q - turn left\n"
		"KEY_R - turn right\n"
		"KEY_LEFT - move left\n"
		"KEY_RIGHT - move right\n"
		"KEY_UP - move up\n"
		"KEY_DOWN - move down\n");

	Vec2 Label_Pos[NUM_PLAYER];
	for (int i = 0; i < NUM_PLAYER; i++)
	{
		Label_Pos[i] = Vec2(origin.x, origin.y + (-i)*100+visibleSize.height);
		player[i].init(i);
		Label_player[i] = CreateTextLabel("Player", LABEL_FONTNAME1, LABEL_FONTSIZE, Label_Pos[i]);
		Label_player[i]->setString("Player: " + std::to_string(player[i].getIdPlayer() + 1) +
			"\n    Carpet: " + std::to_string(player[i].getNumCarpet()) +
			"\n    Coins: " + std::to_string(player[i].getCoins()));
		Label_player[i]->setAnchorPoint(Vec2(0, 1));
		Label_player[i]->setColor(player[i].getColor());
	}

	Vec2 StateGamePos = Vec2(origin.x + visibleSize.width/2 , origin.y + visibleSize.height - 2*LABEL_FONTSIZE);
	StateGame = CreateTextLabel("State", LABEL_FONTNAME1, LABEL_FONTSIZE, StateGamePos);
	StateGame->setColor(player[ActivePlayer].getColor());
	StateGame->setString("ASSAM");

	for (int i = 0; i < 81; i++)
	{
		tile[i].init(Vec2(i%9, i/9));
		this->addChild(tile[i].texture, 0);
	}
	this->Zorder = 0;
	this->ActivePlayer = 0;
	assam.init(Vec2(4,4));
	this->addChild(assam.texture, NUM_CARPET*NUM_PLAYER + 1);


	AssamOrientListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::AssamOrient, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(AssamOrientListener, this);

	PutCarpetListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::CarpetPosition, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(PutCarpetListener, this);
	PutCarpetListener->setEnabled(false);


	//assam.Rotation();
	//assam.Rotation();
	//assam.Rotation();
	//auto fire = Sprite::create("Character Boy.png");
	//fire->setPosition(origin.x + visibleSize.width / 2, origin.y + visibleSize.height / 2);
	//fire->setScale(0.5);
	//fire->setAnchorPoint(Vec2(0.5, 0.2));
	//fire->setRotation(90);
	//this->addChild(fire, 100);
    /////////////////////////////
    // 3. add your codes below...
	//this->unscheduleUpdate
	this->scheduleUpdate();
    return true;
}

void HelloWorld::AssamRotationPositive(float dt)
{
	auto rotate = RotateBy::create(0.3, Vec3(0, 0, 90));
	assam.texture->runAction(rotate);
	assam.setOrient(((assam.getOrient() << 1)&0x0f)? assam.getOrient() << 1 : assam.getOrient() >> 3);
	return;
}
void HelloWorld::AssamRotationNegative(float dt)
{
	auto rotate = RotateBy::create(0.3, Vec3(0, 0, -90));
	assam.texture->runAction(rotate);
	assam.setOrient(((assam.getOrient() >> 1) & 0x0f) ? assam.getOrient() >> 1 : assam.getOrient() << 3); 
	return;
}

void HelloWorld::AssamForawardMovement(float dt)
{
	Vec2 ind = assam.getIndex();
	char orient = assam.getOrient();
	switch (orient)
	{
	case E: ind.x++;
		break;
	case W: ind.x--;
		break;
	case S: ind.y++;
		break;
	case N: ind.y--;
		break;
	}
	assam.setIndex(ind);
	Vec2 prepos = assam.getPosition();
	assam.setPosition(ind);
	auto move = MoveTo::create(0.3, assam.position);
	assam.texture->runAction(move);
	int TileInd = ind.y * 9 + ind.x;
	if (tile[TileInd].getOrient() != NULL)
	{
		char TileOrient = tile[TileInd].getOrient();
		char NegativeAssamOrien = (((assam.getOrient()>>2)&0xf)) ? ((assam.getOrient() >> 2) & 0xf) : ((assam.getOrient() << 2) & 0xf);
		int NumFromTetrada = ((TileOrient & 0x0f)&NegativeAssamOrien) ? 1 : 0;
		bool Positive = (TileOrient >> (4 * NumFromTetrada)&((NegativeAssamOrien >> 1)? NegativeAssamOrien >> 1: NegativeAssamOrien <<3 )) ? true : false;
		if(Positive)
			AssamRotationPositive(0);
		else
			AssamRotationNegative(0);
	}
	scheduleOnce(schedule_selector(HelloWorld::RunAssamRun), 0);
}
void HelloWorld::RunAssamRun(float dt)
{
		int TileInd = assam.getIndex().y * 9 + assam.getIndex().x;
		if (tile[TileInd].getOrient())
		//	AssamForawardMovement(0);
		scheduleOnce(schedule_selector(HelloWorld::AssamForawardMovement), 0.5);
		else
		{
			if (assam.getMoveStep())
			{
				assam.setMoveStep(assam.getMoveStep() - 1);
		//		AssamForawardMovement(0);
				scheduleOnce(schedule_selector(HelloWorld::AssamForawardMovement), 0.5);
			}
		}
}
Carpet *HelloWorld::PutCarpet(float dt)
{
	Carpet *carp = new Carpet;
	carp->init(player[ActivePlayer].getIdPlayer(), assam.getIndex(), assam.getOrient());
	carp->texture->setColor(player[ActivePlayer].getColor());
	this->addChild(carp->texture, Zorder++);
	return carp;
}
void HelloWorld::CarpetRotationPositive(float dt)
{
	auto rotate = RotateBy::create(0.1, Vec3(0, 0, 90));
	carpet->texture->runAction(rotate);
	carpet->setOrient(((carpet->getOrient() << 1) & 0x0f) ? carpet->getOrient() << 1 : carpet->getOrient() >> 3);
	return;
}
void HelloWorld::CarpetRotationNegative(float dt)
{
	auto rotate = RotateBy::create(0.1, Vec3(0, 0, -90));
	carpet->texture->runAction(rotate);
	carpet->setOrient(((carpet->getOrient() >> 1) & 0x0f) ? carpet->getOrient() >> 1 : carpet->getOrient() << 3);
	return;
}
bool HelloWorld::CarpetIsOkey()
{
	Vec2 CarpetIndex = carpet->getIndex();
	Vec2 AssamIndex = assam.getIndex();
	char CarpetOrient = carpet->getOrient();

	if (CarpetIndex.x == 1 && CarpetOrient == W)
		return false;
	if (CarpetIndex.x == 7 && CarpetOrient == E)
		return false;
	if (CarpetIndex.y == 1 && CarpetOrient == N)
		return false;
	if (CarpetIndex.y == 7 && CarpetOrient == S)
		return false;
	if (CarpetIndex.x + 1 == AssamIndex.x && CarpetIndex.y == AssamIndex.y)
		if (CarpetOrient!=E)
		{
			return true;
		}
	if (CarpetIndex.x - 1 == AssamIndex.x && CarpetIndex.y == AssamIndex.y)
		if (CarpetOrient != W)
		{
			return true;
		}
	if(CarpetIndex.y + 1 == AssamIndex.y && CarpetIndex.x == AssamIndex.x)
		if (CarpetOrient != S)
		{
			return true;
		}
	if (CarpetIndex.y - 1 == AssamIndex.y && CarpetIndex.x == AssamIndex.x)
		if (CarpetOrient != N)
		{
			return true;
		}
	return false;
}
void HelloWorld::SetNeighbor()
{
	int TileInd = carpet->getIndex().y * 9 + carpet->getIndex().x;
	switch (carpet->getOrient())
	{
	case E:
		tile[TileInd + 1].setTopCarpet(ActivePlayer);

		tile[TileInd].setNeighbor_carpet(tile[TileInd].getNeighbor_carpet() | E);
		tile[TileInd + 1].setNeighbor_carpet(tile[TileInd + 1].getNeighbor_carpet() | W);

		/*E_E*/
		isTilesOnePlayer(TileInd + 1, TileInd + 1 + 1, E, W);
		
		/*E_S*/
		isTilesOnePlayer(TileInd + 1, TileInd + 1 + 9, S, N);

		/*E_N*/
		isTilesOnePlayer(TileInd + 1, TileInd + 1 - 9, N, S);
		
		break;
	case S:
		tile[TileInd + 9].setTopCarpet(ActivePlayer);
		tile[TileInd].setNeighbor_carpet(tile[TileInd].getNeighbor_carpet() | S);
		tile[TileInd + 9].setNeighbor_carpet(tile[TileInd + 9].getNeighbor_carpet() | N);

		/*S_E*/
		isTilesOnePlayer(TileInd + 9, TileInd + 9 + 1, E, W);
		/*S_S*/
		isTilesOnePlayer(TileInd + 9, TileInd + 9 + 9, S, N);
		/*S_W*/
		isTilesOnePlayer(TileInd + 9, TileInd + 9 - 1, W, E);
		
		break;
	case W:
		tile[TileInd - 1].setTopCarpet(ActivePlayer);
		tile[TileInd].setNeighbor_carpet(tile[TileInd].getNeighbor_carpet() | W);
		tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() | E);


		/*W_S*/
		if (tile[TileInd - 1].getTopCarpet() == tile[TileInd - 1 + 9].getTopCarpet())
		{
			tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() | S);
			tile[TileInd - 1 + 9].setNeighbor_carpet(tile[TileInd - 1 + 9].getNeighbor_carpet() | N);
		}
		else
		{
			tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() & ~S);
			tile[TileInd - 1 + 9].setNeighbor_carpet(tile[TileInd - 1 + 9].getNeighbor_carpet() & ~N);
		}
		/*W_W*/
		if (tile[TileInd - 1].getTopCarpet() == tile[TileInd - 1 - 1].getTopCarpet())
		{
			tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() | W);
			tile[TileInd - 1 - 1].setNeighbor_carpet(tile[TileInd - 1 - 1].getNeighbor_carpet() | E);
		}
		else
		{
			tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() & ~W);
			tile[TileInd - 1 - 1].setNeighbor_carpet(tile[TileInd - 1 - 1].getNeighbor_carpet() & ~E);
		}
		/*W_N*/
		if (tile[TileInd - 1].getTopCarpet() == tile[TileInd - 1 - 9].getTopCarpet())
		{
			tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() | N);
			tile[TileInd - 1 - 9].setNeighbor_carpet(tile[TileInd - 1 - 9].getNeighbor_carpet() | S);
		}
		else
		{
			tile[TileInd - 1].setNeighbor_carpet(tile[TileInd - 1].getNeighbor_carpet() & ~N);
			tile[TileInd - 1 - 9].setNeighbor_carpet(tile[TileInd - 1 - 9].getNeighbor_carpet() & ~S);
		}


		break;
	case N:
		tile[TileInd - 9].setTopCarpet(ActivePlayer);
		tile[TileInd].setNeighbor_carpet(tile[TileInd].getNeighbor_carpet() | N);
		tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() | S);

		/*N_E*/
		if (tile[TileInd - 9].getTopCarpet() == tile[TileInd - 9 + 1].getTopCarpet())
		{
			tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() | E);
			tile[TileInd - 9 + 1].setNeighbor_carpet(tile[TileInd - 9 + 1].getNeighbor_carpet() | W);
		}
		else
		{
			tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() & ~E);
			tile[TileInd - 9 + 1].setNeighbor_carpet(tile[TileInd - 9 + 1].getNeighbor_carpet() & ~W);
		}
		/*N_W*/
		if (tile[TileInd - 9].getTopCarpet() == tile[TileInd - 9 - 1].getTopCarpet())
		{
			tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() | W);
			tile[TileInd - 9 - 1].setNeighbor_carpet(tile[TileInd - 9 - 1].getNeighbor_carpet() | E);
		}
		else
		{
			tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() & ~W);
			tile[TileInd - 9 - 1].setNeighbor_carpet(tile[TileInd - 9 - 1].getNeighbor_carpet() & ~E);
		}
		/*N_N*/
		if (tile[TileInd - 9].getTopCarpet() == tile[TileInd - 9 - 9].getTopCarpet())
		{
			tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() | N);
			tile[TileInd - 9 - 9].setNeighbor_carpet(tile[TileInd - 9 - 9].getNeighbor_carpet() | S);
		}
		else
		{
			tile[TileInd - 9].setNeighbor_carpet(tile[TileInd - 9].getNeighbor_carpet() & ~N);
			tile[TileInd - 9 - 9].setNeighbor_carpet(tile[TileInd - 9 - 9].getNeighbor_carpet() & ~S);
		}

		

		break;
	default: break;
	}
}
inline void HelloWorld::isTilesOnePlayer(int numtile, int numneighbtile, char orient, char unorient)
{
	if (tile[numtile].getTopCarpet() == tile[numneighbtile].getTopCarpet())
	{
		tile[numtile].setNeighbor_carpet(tile[numtile].getNeighbor_carpet() | orient); 
		tile[numneighbtile].setNeighbor_carpet(tile[numneighbtile].getNeighbor_carpet() | unorient); 
	}
	else
	{
		tile[numtile].setNeighbor_carpet(tile[numtile].getNeighbor_carpet() & ~orient); 
		tile[numneighbtile].setNeighbor_carpet(tile[numneighbtile].getNeighbor_carpet() & ~unorient); }
}

void HelloWorld::ParkingFees(float dt)
{
	int AssamInd = assam.getIndex().y*9+assam.getIndex().x;
	int Fees = 0;
	if (tile[AssamInd].getTopCarpet() == -1)
		return;

	int *NeighbTile = new int[81];
	for (int i = 0; i < 81; i++)
		NeighbTile[i] = tile[i].getNeighbor_carpet();
	TreeTraversal(Fees, NeighbTile, AssamInd);
	player[tile[AssamInd].getTopCarpet()].setCoins(player[tile[AssamInd].getTopCarpet()].getCoins()+Fees);

}
void HelloWorld::TreeTraversal(int &Fees, int  * &Neigb, int index)
{
	Fees++;
	if (Neigb[index] & NEIGHTBOR_E)
	{
		Neigb[index]   &= ~NEIGHTBOR_E;
		Neigb[index+1] &= ~NEIGHTBOR_W;
		TreeTraversal(Fees, Neigb, index + 1);
	}
	if (Neigb[index] & NEIGHTBOR_S)
	{
		Neigb[index] &= ~NEIGHTBOR_S;
		Neigb[index + 9] &= ~NEIGHTBOR_N;
		TreeTraversal(Fees, Neigb, index + 9);
	}
	if (Neigb[index] & NEIGHTBOR_W)
	{
		Neigb[index] &= ~NEIGHTBOR_W;
		Neigb[index - 1] &= ~NEIGHTBOR_E;
		TreeTraversal(Fees, Neigb, index - 1);
	}
	if (Neigb[index] & NEIGHTBOR_N)
	{
		Neigb[index] &= ~NEIGHTBOR_N;
		Neigb[index - 9] &= ~NEIGHTBOR_E;
		TreeTraversal(Fees, Neigb, index - 9);
	}
}

void HelloWorld::AssamOrient(EventKeyboard::KeyCode keyCode, Event *event)
{
	
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW: 
		scheduleOnce(schedule_selector(HelloWorld::AssamRotationNegative), 0.3);
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
		scheduleOnce(schedule_selector(HelloWorld::AssamRotationPositive), 0.3);
		break;
	case EventKeyboard::KeyCode::KEY_KP_ENTER:
		//this->unscheduleUpdate();
		assam.setMoveStep(random(1, 4));
		scheduleOnce(schedule_selector(HelloWorld::RunAssamRun), 0);
		AssamOrientListener->setEnabled(false);
		PutCarpetListener->setEnabled(true);
		StateGame->setString("CARPET");
		
		break;
	default:
		break;
	}
	lastKeyCodeAssam = (int)keyCode;
}
void HelloWorld::CarpetPosition(EventKeyboard::KeyCode keyCode, Event *event)
{
	
	if (keyCode == EventKeyboard::KeyCode::KEY_W&&carpet->getIdPlayer() != ActivePlayer)
	{
		carpet->texture->setScale(0);
		carpet = PutCarpet(0);
		player[ActivePlayer].setNumCarpet(player[ActivePlayer].getNumCarpet() - 1);

	}
	else if (carpet->getIdPlayer() == ActivePlayer)
	{
		Vec2 CurrentInd = carpet->getIndex();
		int TileInd = carpet->getIndex().y * 9 + carpet->getIndex().x;
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
			CurrentInd.x = ((CurrentInd.x - 1) == 0) ? CurrentInd.x : CurrentInd.x - 1;
			carpet->setIndex(CurrentInd);
			carpet->setPosition(CurrentInd);
			carpet->texture->setPosition(carpet->getPosition());
			break;
		case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
			CurrentInd.x = ((CurrentInd.x + 1) == 8) ? CurrentInd.x : CurrentInd.x + 1;
			carpet->setIndex(CurrentInd);
			carpet->setPosition(CurrentInd);
			carpet->texture->setPosition(carpet->getPosition());
			break;
		case EventKeyboard::KeyCode::KEY_UP_ARROW:
			CurrentInd.y = ((CurrentInd.y - 1) == 0) ? CurrentInd.y : CurrentInd.y - 1;
			carpet->setIndex(CurrentInd);
			carpet->setPosition(CurrentInd);
			carpet->texture->setPosition(carpet->getPosition());
			break;
		case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
			CurrentInd.y = ((CurrentInd.y + 1) == 8) ? CurrentInd.y : CurrentInd.y + 1;
			carpet->setIndex(CurrentInd);
			carpet->setPosition(CurrentInd);
			carpet->texture->setPosition(carpet->getPosition());
			break;
		case EventKeyboard::KeyCode::KEY_Q:
			scheduleOnce(schedule_selector(HelloWorld::CarpetRotationNegative), 0.1);
			break;
		case EventKeyboard::KeyCode::KEY_E:
			scheduleOnce(schedule_selector(HelloWorld::CarpetRotationPositive), 0.1);
			break;
		case EventKeyboard::KeyCode::KEY_KP_ENTER:
			if (CarpetIsOkey())
			{
				tile[TileInd].setTopCarpet(ActivePlayer);
				SetNeighbor();
				carpet = new Carpet;
				ActivePlayer = (ActivePlayer + 1 == NUM_PLAYER) ? 0 : ActivePlayer + 1;
				StateGame->setColor(player[ActivePlayer].getColor());
				PutCarpetListener->setEnabled(false);
				StateGame->setString("ASSAM");
				AssamOrientListener->setEnabled(true);
			}
			else
			{
				carpet->setIndex(assam.getIndex());
				carpet->setPosition(carpet->getIndex());
				carpet->texture->setPosition(carpet->getPosition());
			}
			break;
		default:
			break;
		}
	}
	lastKeyCodeCarpet = (int)keyCode;
}

void HelloWorld::update(float dt)
{
	for (int i = 0; i < NUM_PLAYER;i++)
	Label_player[i]->setString("Player: " + std::to_string(player[i].getIdPlayer() + 1) +
		"\n    Carpet: " + std::to_string(player[i].getNumCarpet()) +
		"\n    Coins: " + std::to_string(player[i].getCoins()));

	if (assam.getMoveStep() == 0)
	{
		if (this->isScheduled(schedule_selector(HelloWorld::RunAssamRun)) )
		{
			this->scheduleOnce(schedule_selector(HelloWorld::ParkingFees), 0);
			lastKeyCodeAssam = 0;
		}	
	}
	
}
Label* HelloWorld::CreateTextLabel(char *text, char *ff, int fsize, Vec2 pos)
{
	Label *label = Label::createWithTTF(text, ff, fsize);
	label->setPosition(pos);
	this->addChild(label, 1, "text_lable");
	return label;
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

