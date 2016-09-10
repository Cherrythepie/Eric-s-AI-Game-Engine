#include "MapClass.h"

MapClass::MapClass()
{
	MapStart.e = MapStart.n = MapStart.n = MapStart.Previous = MapStart.s = NULL;
	MapStart.Next = MapStart.Previous = MapStart.ToMap = MapStart.ToPlayer = MapStart.w = NULL;
}