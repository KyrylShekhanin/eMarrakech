#include "Carpet.h"

void Carpet::init(int IdPlayer, Vec2 ind, char Orient)
{
	this->setIndex(ind);

	this->texture = Sprite::create(CARPET_FILE);
	this->setPosition(ind);
	this->texture->setPosition(this->position);
	this->texture->setAnchorPoint(Vec2(0.25, 0.5));

	this->setOrient(Orient);
	switch (this->orient)
	{
	case E: break;
	case S: this->texture->setRotation(90); break;
	case W: this->texture->setRotation(180); break;
	case N: this->texture->setRotation(270); break;
	default: break;
	}

	this->setIdPlayer(IdPlayer);
	switch (this->IdPlayer)
	{
	case 1: this->texture->setColor(RED); break;
	case 2: this->texture->setColor(GREEN); break;
	case 3: this->texture->setColor(BLUE); break;
	case 4: this->texture->setColor(WHITE); break;
	default: break;
	}
}

void Carpet::setIdPlayer(int Id)
{
	this->IdPlayer = Id;
	return;
}
int Carpet::getIdPlayer()
{
	return this->IdPlayer;
}

void Carpet::setIndex(Vec2 ind)
{
	this->index = ind;
	return;
}
Vec2 Carpet::getIndex()
{
	return this->index;
}

void Carpet::setPosition(Vec2 ind)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	unsigned int height_texture = 0;

	FILE *f = fopen("tail_size", "rt");
	fread(&height_texture, 1, 1, f);
	fclose(f);
	this->position.y = origin.y + visibleSize.height / 2 - (ind.y - 4) * height_texture;
	this->position.x = origin.x + visibleSize.width / 2 + (ind.x - 4) * height_texture;
}
Vec2 Carpet::getPosition()
{
	return this->position;
}

void Carpet::setOrient(char orient)
{
	this->orient = orient;
	return;
}
char Carpet::getOrient()
{
	return this->orient;
}

void Carpet::setZord(int Z)
{
	this->Zord = Z;
	return;
}
int Carpet::getZord()
{
	return this->Zord;
}


Carpet::Carpet()
{
}


Carpet::~Carpet()
{
}
