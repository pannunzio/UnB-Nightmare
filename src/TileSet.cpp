/*
 * TileSet.cpp
 *
 *  Created on: 21 de mar de 2016
 *      Author: Caio
 */

#include "TileSet.h"
#include "TileMap.h"
#include <math.h>

//*****************************************************************//
//Função: CONSTRUTOR**********************************************//
//Retorno: N/A***************************************************//
//Parametros: N/A***********************************************//
//Descrição: constroi o tileSet********************************//
//************************************************************//

TileSet::TileSet(int ttileWidth, int ttileHeight, string file) : tileSet(file){
	tileWidth = ttileWidth;
	tileHeight = ttileHeight;
	if(tileSet.IsOpen()){
		std::cout << "Abertura bem sucedida" << std::endl;
		rows = tileSet.GetHeight()/tileHeight;
		columns = tileSet.GetWidth()/tileWidth;
		std::cout << "Rows x Columns" << std::endl << rows << " " << columns << std::endl;
	}
}

//**********************************************************************//
//Função: TileSet::Render(unsigned index, float x , float y)***********//
//Retorno: void*******************************************************//
//Parametros: unsigned index, float x , float y**********************//
//Descrição: checa de o indice eh valido, e seta o clip*************//
//*****************************************************************//
void TileSet::Render(unsigned index, float x, float y ) {

	if(index > (unsigned)rows*columns || index == 0){
		//std::cout << "Index invalido" << std::endl;
		return;
	}

	else {
		//index =8;
		index--;

		//std::cout << "Index : " << index ;
		//std::cout << "Index_X: " << (int)IndexReverse(index).x;
		//std::cout << "Index_Y: " << (int)IndexReverse(index).y << endl;

		tileSet.SetClip((int)IndexReverse(index).x*tileWidth,(int)IndexReverse(index).y*tileHeight,tileWidth,tileHeight);
		tileSet.Render((int)x,(int)y);
	}

}

Vec2 TileSet::IndexReverse(unsigned index){

	return Vec2((index%columns) ,(int)(index/columns) );
}
//*****************************************************************//
//Função: GetTileWidth(), GetTileHeight()*************************//
//Retorno: int dos gets******************************************//
//Parametros: void**********************************************//
//Descrição: getters*******************************************//
//************************************************************//
int TileSet::GetTileWidth(){
	return tileWidth;
}
int TileSet::GetTileHeight(){
		return tileHeight;
}
TileSet::~TileSet() {

}

