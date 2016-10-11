#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "TileSet.h"


#include <vector>

class TileMap {
public:
	TileMap(std::string file, TileSet* tileSet);
	~TileMap();

	void PrintMap();

    void Render(int cameraX = 0, int cameraY = 0);
	void RenderLayer(int layer, int cameraX = 0 , int cameraY = 0);

	void Load(std::string file);
	void SetTileSet(TileSet* tileSet);
	int& At(int x, int y, int z = 0);
	int GetWidth();
	int GetHeight();
	int GetDepth();
	void SetTileMap(TileSet* tileSet);

private:
	std::vector<int> tileMatrix;
	TileSet* tileSet;
	int mapWidth;
	int mapHeight;
	int mapDepth;

};

#endif
