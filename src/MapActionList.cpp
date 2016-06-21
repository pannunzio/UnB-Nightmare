#include "MapActionList.h"


MapActionList::MapActionList(){
}

MapActionList::~MapActionList(){
//    mapActions.clear();
}

void MapActionList::AddMapAction(MapActions mapAction){
    mapActions.push_back(mapAction);
}
