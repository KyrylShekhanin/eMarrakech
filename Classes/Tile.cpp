#include "Tile.h"

/*Sprite texture;
	Vec2 position;
	Vec2 index;
	bool Assam;
	char orient;
	int TopCarpet;
	char Neigbor_carpet;*/
void Tile_m::init(Vec2 ind)
{
	this->index = ind;


	this->setOrient(ind);
	this->setAssam(false);
	this->setTopCarpet(-1);
	this->setNeighbor_carpet(NULL);

	if (ind.y == 0)
	{
		this->texture = Sprite::create(TURN_FILE);
		this->setPosition(ind);
		this->texture->setPosition(this->position);
		if (ind.x == 0)
			this->texture->setRotation(180);
		else if (int(ind.x) % 2 == 0)
			this->texture->setRotation(90);
		
		return;
	}
	else if (ind.y == 8)
	{
		this->texture = Sprite::create(TURN_FILE);
		this->setPosition(ind);
		this->texture->setPosition(this->position);
		this->texture->setRotation(180);
		if (ind.x == 8)
			this->texture->setRotation(0);
		else if (int(ind.x) % 2 == 0)
			this->texture->setRotation(-90);
		return;
	}
	else if (ind.x == 0)
	{
		this->texture = Sprite::create(TURN_FILE);
		this->setPosition(ind);
		this->texture->setPosition(this->position);
		if (ind.y == 0)
			this->texture->setRotation(180);
		else if (int(ind.y) % 2 == 0)
			this->texture->setRotation(-90);
		return;
	}
	else if(ind.x == 8)
	{
		this->texture = Sprite::create(TURN_FILE);
		this->setPosition(ind);
		this->texture->setPosition(this->position);
		this->texture->setRotation(180);
		if (ind.y == 8)
			this->texture->setRotation(0);
		else if (int(ind.y) % 2 == 0)
			this->texture->setRotation(90);
		return;
	}
	else
	{
		this->texture = Sprite::create(TILE_FILE);
		this->setPosition(ind);
		this->texture->setPosition(this->position);
		if (int(ind.y) == 4 && int(ind.x) == 4)
		{
			this->setAssam(true);
		}
		return;
	}
}

void  Tile_m::setPosition(Vec2 ind)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	unsigned int height_texture = texture->getContentSize().height;

	FILE *f = fopen("tail_size", "wt");
	fwrite(&height_texture, 1, 1, f);
	fclose(f);
	
	this->position.y = origin.y + visibleSize.height / 2 - (ind.y - 4) * height_texture;
	this->position.x = origin.x + visibleSize.width / 2 + (ind.x - 4) * height_texture;
}
Vec2 Tile_m::getPosition()
{
	return this->position;
}

void Tile_m::setIndex(Vec2 ind)
{
	this->index = ind;
	return;
}
Vec2 Tile_m::getIndex()
{
	return this->index;
}

void Tile_m::setAssam(bool Yes_No)
{
	this->Assam = Yes_No;
}

bool Tile_m::getAssam()
{
	return this->Assam;
}

void Tile_m::setOrient(Vec2 ind)
{
	if (ind.y == 0)
	{
		if (int(ind.x) % 2 == 0)
		{
			this->orient = S_to_W;
			return;
		}
		else
		{
			this->orient = S_to_E;
			return;
		}
	}
	else if (ind.y == 8)
	{
		if (int(ind.x) % 2 == 0)
		{
			this->orient = N_to_E;
			return;
		}
		else
		{
			this->orient = N_to_W;
			return;
		}
	}
	else if (ind.x == 0)
	{
		if (int(ind.y) % 2 == 0)
		{
			this->orient = E_to_N;
			return;
		}
		else
		{
			this->orient = E_to_S;
			return;
		}
	}
	else if (ind.x == 8)
	{
		if (int(ind.y) % 2 == 0)
		{
			this->orient = W_to_S;
			return;
		}
		else
		{
			this->orient = W_to_N;
			return;
		}
	}
	else if ((ind.x >= 1 && ind.x <= 7)&&((ind.y >= 1 && ind.y <= 7)))
	{
		this->orient = NULL;
		return;
	}
}
char Tile_m::getOrient()
{
	return this->orient;
}

void Tile_m::setTopCarpet(int PlayerColor)
{
	this->TopCarpet = PlayerColor;
}
int Tile_m::getTopCarpet()
{
	return this->TopCarpet;
}

void Tile_m::setNeighbor_carpet(char neighb_flag)
{
	this->Neighbor_carpet = neighb_flag;
}
char Tile_m::getNeighbor_carpet()
{
	return this->Neighbor_carpet;
}