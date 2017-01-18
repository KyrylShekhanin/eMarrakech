#include "Assam.h"



Assam::Assam()
{
}


Assam::~Assam()
{
}

void Assam::init(Vec2 ind)
{
	this->index = ind;

	this->texture = Sprite::create(ASSAM_FILE);
	this->setPosition(ind);
	this->texture->setPosition(this->position);
	this->texture->setScale(0.5);
	this->texture->setAnchorPoint(Vec2(0.5, 0.2));
	this->setIndex(ind);
	this->setOrient(S);
	this->setMoveStep(0);



}

void  Assam::setPosition(Vec2 ind)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	unsigned int height_texture = 0;
	
	FILE *f = fopen("tail_size", "rt");
	fread(&height_texture, 1, 1, f);
	fclose(f);
	//texture->getContentSize().height;
	this->position.y = origin.y + visibleSize.height / 2 - (ind.y - 4) * height_texture;
	this->position.x = origin.x + visibleSize.width / 2 + (ind.x - 4) * height_texture;
}
Vec2 Assam::getPosition()
{
	return this->position;
}

void Assam::setIndex(Vec2 ind)
{
	this->index = ind;
	return;
}
Vec2 Assam::getIndex()
{
	return this->index;
}

void Assam::setOrient(char Orient)
{
	this->orient = Orient;
	return;
}
char Assam::getOrient()
{
	return this->orient;
}

void Assam::setMoveStep(unsigned int value)
{
	this->move_step = value;
	return;
}
unsigned int Assam::getMoveStep()
{
	return this->move_step;
}


