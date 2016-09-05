#include "TileSet.h"
#include "TileMap.h"
#include <math.h>

TileSet::TileSet(int ttileWidth, int ttileHeight, string file) : tileSet(file){
	this->tileWidth = ttileWidth;
	this->tileHeight = ttileHeight;

	if(this->tileSet.IsOpen()){
		std::cout << "Abertura bem sucedida" << std::endl;
		this->rows = this->tileSet.GetHeight()/this->tileHeight;
		this->columns = this->tileSet.GetWidth()/this->tileWidth;
		std::cout << "Rows x Columns" << std::endl << this->rows << " " << this->columns << std::endl;
	}
}

TileSet::~TileSet() {

}

void TileSet::Render(unsigned index, float x, float y ) {
	if(index > (unsigned)rows * columns || index == 0){
		//std::cout << "Index invalido" << std::endl;
		return;
	} else {
		index--;
		this->tileSet.SetClip((int)IndexReverse(index).x * this->tileWidth, (int)IndexReverse(index).y * this->tileHeight, this->tileWidth, this->tileHeight);
		this->tileSet.Render((int)x,(int)y);
	}
}

int TileSet::GetTileWidth(){
	return this->tileWidth;
}

int TileSet::GetTileHeight(){
		return this->tileHeight;
}

Vec2 TileSet::IndexReverse(unsigned index){
	return Vec2((int)(index/this->rows), (index%this->rows) );
}
