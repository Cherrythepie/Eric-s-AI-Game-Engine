#ifndef IMP_H
#define IMP_H

#include "MapClass.h"

using namespace std;

struct GameFileType	// Used in the very beginning of main to hold file names in an LL. Has no use for building maps
{
	char filename[101];
	int gameNum;

	GameFileType *next, *previous;
};

struct MapType	// Used to build maps.
{
	MapClass Map;	// "MapType" has a map imbedded inside. Allows the "Map" to be shuffled around inside a "box (MapType)."
	char MapName[115];
	char MapFilePath[115];
	int Xdis, Ydis;		// How big the map will be

	MapType *next, *previous;
};

#endif;