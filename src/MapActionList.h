#ifndef MAPACTIONLIST_H
#define MAPACTIONLIST_H

#include "GameObject.h"
#include "MapActions.h"
#include <vector>
#include <memory>

class MapActionList{
public:
    MapActionList();
    ~MapActionList();

	void AddMapAction(MapActions mapAction);
	std::vector<MapActions> mapActions;
};


#endif
