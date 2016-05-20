/*
 * TileSet.h
 *
 *  Created on: 21 de mar de 2016
 *      Author: Caio
 */

#ifndef TILESET_H_
#define TILESET_H_

#include <iostream>
#include "sprite.h"
#include "Vec2.h"
class TileSet {
public:
	TileSet(int tileWidth, int tileHeight, std::string file);
	virtual ~TileSet();
	void Render(unsigned index, float x, float y);
	int GetTileWidth();
	int GetTileHeight();

private:
	Vec2 IndexReverse(unsigned index);
	Sprite tileSet;
	int rows, columns;
	int tileWidth, tileHeight;


};

#endif /* TILESET_H_ */
