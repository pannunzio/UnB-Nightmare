#include "MapActionList.h"

std::vector<MapActions> MapActionList::mapActions;

MapActionList::MapActionList() {
}

MapActionList::~MapActionList(){
//    mapActions.clear();
}

void MapActionList::AddMapAction(MapActions mapAction){
    mapActions.push_back(mapAction);
}
