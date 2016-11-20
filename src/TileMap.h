#ifndef TILEMAP_H_
#define TILEMAP_H_

#include "TileSet.h"

#define TILE_MAP_FILE   "map/tileMapTeste.txt"
#define TILE_SET_FILE   "img/tilesetSKDAResized.png"
#define TILESET_WIDTH   345
#define TILESET_HEIGHT  733/3


#include <vector>

class TileMap {
public:
	TileMap();
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
