// Builds the Maps

#ifndef GENERATEMAP_H
#define GENERATEMAP_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "Implementation.h"	// already pulls from the 'MapClass'
#include "GenerateAttributeClass.h"	// So, the programmer knows what is being used.
#include "GenerateItemClass.h"		// So, the programmer knows what is being used.
#include "GenerateCharacterClass.h"
//#include "MapClass.h"

using namespace std;

class GenerateMapClass
{
private:
	int			MapX, MapY;	// How big the map is
//	MapType		MapToBuild;
//	ifstream	MapPath;
//	MapType		*Current;

public:
//			GenerateMapClass();
void		BuildMapSkeleton(MapType *Map);
void		SetupMapTiles(MapType &Box, MapType *Map, ifstream &ActualMapFile);
void		GenerateMap(MapType *Map);
void		SetupTileAttributesAndItems(MapType *Map, AttributeType *AttributeLL, ItemType *ItemLL, CharacterType *CharacterLL);
void		BuildItem();
void		AddItems();
void		AddAttributes();


};




#endif;