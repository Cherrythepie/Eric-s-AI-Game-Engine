#ifndef MAPCLASS_H
#define MAPCLASS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "AttributeClass.h"
#include "ItemClass.h"
#include "CharacterClass.h"

#include "MapClass.h"

//#include "Implementation.h"

using namespace std;

struct CharacterType;
struct AttributeType;
struct TileType;
struct ItemType;
struct MapType;


struct CharacterType
{
	CharacterClass Character;
	char CharacterName[115];
	int  CharacterID;
	int  CharacterAmount;
	TileType *ToMap;
	ItemType *ToItems;
	AttributeType *ToAttribute;

	CharacterType *next, *previous;
};

struct AttributeType
{
	AttributeClass Attribute;
	char AttributeName[115];
	int  AttributeID;
	int  AttributeAmount;
	CharacterType *ToCharacter;
	ItemType *ToItem;
//	MapType *ToActual;
	AttributeType *ToAttribute;
	TileType *ToMap;

	AttributeType *next, *previous;
};

struct TileType		// map Tiles and Players
{
	char tilePiece;
	TileType *n, *s, *e, *w, *Next, *Previous, *ToPlayer, *ToMap;
	int x, y;
	
	AttributeType *nextAtt, *previousAtt;
	ItemType *nextItem, *previousItem;
	CharacterType *nextCharacter, *previousCharacter;

};


struct ItemType	// To hold Item info.
{
	ItemClass Item;
	char ItemName[115];
	int  ItemID;
	int  ItemAmount;
	TileType *ToMap;
	CharacterType *ToCharacter;
	AttributeType *ToAttribute;
	ItemType *ToItem;

	ItemType *next, *previous;
};

class MapClass
{
private:
	 TileType MapStart;	// Tag showing where the 2d LL -> that is the map -> starts

public:
				MapClass();
	TileType*	GetMapStart() { return &MapStart;};
	void		ReturnMapStart(TileType MapStartReturned) {this->MapStart = MapStartReturned;};

};



																																																																			
#endif;