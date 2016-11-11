#include "TileSet.h"
#include "TileMap.h"
#include <math.h>

//#define DEBUG
#ifdef DEBUG
        //se estiver definido debug, imprime os trecos
        #define DEBUG_PRINT(message) do{std::cout << message << std::endl;}while(0);
        #define DEBUG_ONLY(x) do{x;}while(0);
#else
        //caso contrario, recebe argumentos mas faz nada
        #define DEBUG_PRINT(message)
        #define DEBUG_ONLY(x) //do{;}while(0)
#endif //DEBUG

TileSet::TileSet(int ttileWidth, int ttileHeight, string file) : tileSet(file){
	this->tileWidth = ttileWidth;
	this->tileHeight = ttileHeight;

	if(this->tileSet.IsOpen()){
		DEBUG_PRINT("Abertura bem sucedida")
		this->rows = this->tileSet.GetHeight()/this->tileHeight;
		this->columns = this->tileSet.GetWidth()/this->tileWidth;
		DEBUG_PRINT("Rows x Columns" << std::endl << this->rows << " " << this->columns)
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

#ifdef DEBUG
    #undef DEBUG
#endif // DEBUG
