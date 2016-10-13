#include <cstdio>

#include "TileMap.h"
#include "MapActionList.h"
#include "Defines.h"

TileMap::TileMap() {
}

TileMap::TileMap(std::string file, TileSet* ttileSet) {
	this->tileSet = ttileSet;
	Load(file);
}

TileMap::~TileMap() {

}

void TileMap::PrintMap(){
//	for(int k = 0; k < this->mapDepth; k++){
//		for(int j = 0; j < this->mapHeight; j++){
//			for(int i =0 ; i < this->mapWidth; i++){
//				if(At(i, j, k) < 10)
//					std::cout << "0";
//				std::cout << At(i,j,k) << ",";
//			}
//			std::cout << std::endl;
//		}
//	}
}

void TileMap::Render(int cameraX, int cameraY){
	for(int i = 0; i < this->mapDepth; i++){
		RenderLayer(i, cameraX, cameraY);
	}
}

void TileMap::RenderLayer(int layer, int cameraX, int cameraY){
	for(int j = 0; j < this->mapHeight; j++){
		for(int i = 0; i < this->mapWidth; i++){
			this->tileSet->Render(At(i, j, layer),this->tileSet->GetTileWidth() * i - cameraX * (layer + 1), this->tileSet->GetTileHeight() * j - cameraY * (layer + 1));
		}
    }
}

void TileMap::Load(std::string file){
	std::cout << "TileMap::Load" << endl;
	FILE* arq = fopen(file.c_str(), "r");

	if(!arq)
        std::cout << "falha ao abrir arquivo: "  << file << std::endl;

	fscanf(arq, "%i, %i, %i,", &this->mapWidth, &this->mapHeight, &this->mapDepth);

	this->tileMatrix.resize(this->mapWidth * this->mapHeight * this->mapDepth);

	for(int k = 0 ; k < this->mapDepth; k++)
		for(int j = 0 ; j < this->mapHeight; j++){
			for(int i = 0; i < this->mapWidth; i++){
				fscanf(arq, "%d,", &At(i, j, k));

				if(At(i, j, k) - 1 >= 3 && At(i, j, k) <= 6)
					MapActionList::AddMapAction(MapActions( TILESET_WIDTH * i + 250, TILESET_HEIGHT * j + 40, 3 - j));
			}
		}
	std::cout << "Tile map succesfuly read" << std::endl;
}

void TileMap::SetTileSet(TileSet* ttileSet){
	this->tileSet = ttileSet;
}

int& TileMap::At(int x, int y, int z){
	return this->tileMatrix[x + y * this->mapWidth + z * this->mapHeight * this->mapWidth];
}

int TileMap::GetWidth(){
	return this->mapWidth;
}
int TileMap::GetHeight(){
		return this->mapHeight;
}
int TileMap::GetDepth(){
		return this->mapDepth;
}
