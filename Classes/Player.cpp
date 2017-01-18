#include "Player.h"


void Player::init(int id)
{
	this->setIdPlayer(id);
	this->setNumCarpet(NUM_CARPET);
	this->setCoins(NUM_COINS);
	this->setBot(true);
	this->setEnable(true);

	switch (id)
	{
	case 0: this->setColor(RED); break;
	case 1: this->setColor(GREEN); break;
	case 2: this->setColor(BLUE); break;
	case 3: this->setColor(WHITE); break;
	default: this->setColor(Color3B(random(0, 255), random(0, 255), random(0, 255))); break;
	}
}

void Player::setIdPlayer(int id)
{
	this->IdPlayer = id;
	return;
}
int Player::getIdPlayer()
{
	return this->IdPlayer;
}

void Player::setNumCarpet(int numCarpet)
{
	this->NumCarpet = numCarpet;
	return;
}
int Player::getNumCarpet()
{
	return this->NumCarpet;
}

void Player::setCoins( int numCoins)
{
	this->Coins = numCoins;
	return;
}
int Player::getCoins()
{
	return this->Coins;
}

void Player::setBot(bool Bot)
{
	this->bot = Bot;
	return;
}
bool Player::getBot()
{
	return this->bot;
}

void Player::setEnable(bool enablr)
{
	this->enable = enable;
	return;
}
bool Player::getEnable()
{
	return this->enable;
}

void Player::setColor(Color3B col)
{
	this->color = col;
	return;
}
Color3B Player::getColor()
{
	return this->color;
}


Player::Player()
{
}


Player::~Player()
{
}
