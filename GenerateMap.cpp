#include "GenerateMap.h"

bool IfAttributeIDExists(AttributeType *AttributeLL, int TileAttributeID, char *AttributeName);

//GenerateMapClass::GenerateMapClass()
//{
////	MapPath.open(MapFilePath);	// Opens the map file for reading
//	Current = NULL;
//
//}

void GenerateMapClass::BuildMapSkeleton(MapType *Map)	// Done
{
	TileType MapTilesStart = *Map->Map.GetMapStart();	// "MapTilesStart" takes on the values of "MapStart"
	// IMPORTANT!!! -> Map.GetMapStart() returns a pointer, not an object!.... HOORAY!
	TileType *Current = &MapTilesStart, *Runner = &MapTilesStart;	// "MapTilesStart" does not hold tile data.
	// ^ that block is fine because there are no pointers to "it."
register	
	int MapArea = Map->Xdis * Map->Ydis;
	
	int Yloc = -1;

	for(int jndex = 1; jndex <= (MapArea); jndex++)
	{
		TileType *newTile = new TileType;
		// create a doubly linked list.
		Current->Next = newTile;
		newTile->Previous = Current;
		newTile->Next = NULL;

		Current = Current->Next;
		// itoa(index, &Current->tilePiece, MapArea);
		Current->x = (jndex - 1) % Map->Xdis;

		if(Current->x == 0)
			Yloc += 1;

		Current->y = Yloc;

		Current->n = Current->s = Current->e = Current->w = NULL; // Initialize all Cardinal Directional pointers
		Current->ToPlayer = Current->ToMap = NULL;
		Current->nextAtt = Current->previousAtt = NULL;
		Current->nextItem = Current->previousItem = NULL;
		Current->nextCharacter = Current->previousCharacter = NULL;
	}

	TileType *VerticalRunner = MapTilesStart.Next, *HorizontalRunner = &MapTilesStart;

	Current = MapTilesStart.Next;	// set current to the start of the map, instead of the "tag" of the map.
	Current->w = Current->n = NULL;

	for(int VRindex = 0; VRindex < Map->Xdis; VRindex++)
		VerticalRunner = VerticalRunner->Next;

	for(int index = 0; index < MapArea; index++)	// "index = 1" helps keep track of where along the map -> the tile "being placed" should be.
	{

		if( (Current->x + 1) % Map->Xdis != 0)	// if not at the map's right edge.
		{
			Current->e = Current->Next;

		}	// East (e) -> Done.

		if( (Current->x + 1) % Map->Xdis != 1) // if not at the map's left edge.
		{	
			Current->w = Current->Previous;

		}	// West (w) -> Done.

		if(Current->y + 1 < Map->Ydis)	// if not "placing tiles" on the bottom (s) edge of the map.
		{
			Current->s = VerticalRunner;

			if(VerticalRunner != NULL)
				VerticalRunner->n = Current;
		}

		if( (Current->y + 1) < Map->Ydis)	// if not "placing tiles" on the bottom (s) edge of the map.
			VerticalRunner = VerticalRunner->Next;	// move VR along

		Current = Current->Next;	// move Current along.
	}

	Map->Map.ReturnMapStart(MapTilesStart);
}

void GenerateMapClass::SetupMapTiles(MapType &Box, MapType *Map, ifstream &ActualMapFile)
{
	TileType *Current = Map->Map.GetMapStart();	// Current Now points to the TileType object inside the Map Object.
	// = &MapTilesStart;	// "MapTilesStart" does not hold tile data.
	
	int Xdis, Ydis;
	ActualMapFile >> Xdis >> Ydis;	// get the map size
	int MapArea = Xdis * Ydis;

	for(int i = 0; i < MapArea; i++)	// Works on each tile one at a time.
	{
		Current = Current->Next;	// go to the next tile.

		char CharBuffer[2500] = {0};	// holds data from the file
		if(i % Xdis == 0 && i != 0)	// if at the end of a line (only the ';' is left at the end of the line).
			ActualMapFile.getline(CharBuffer, 2499);	// get (remove) the last ';' at the end of the line in the file.
		ActualMapFile.getline(CharBuffer, 2499, ';');	// Only gets data for one(1) tile at a time.

		int CharPosition = 1;

START:
//		int charAtPositionInt = CharBuffer[CharPosition];
//		char *charAtPositionChar = &CharBuffer[CharPosition];

		if(CharBuffer[CharPosition] == '[')   //(itoa(charAtPositionInt, &charAtPositionChar, 10) == '[')
		{
			CharPosition += 1;
			goto START;
		}

		if(CharBuffer[CharPosition] == '(')
		{
			CharPosition += 1;
NUMTEST:
			if(isdigit /*(atoi */(CharBuffer[CharPosition] ) ) 	// if the character after the '(' is a number.
			{
				// Get the number
				char ItemNumber[11] = {0};
				int index = 0;

				for(; isdigit(CharBuffer[CharPosition]); index)	// Get the number
				{
					ItemNumber[index] = CharBuffer[CharPosition];	//
					index++;
					CharPosition++;
				}
				// Finish Getting the number.

				//CharPosition += index;	// move up CharPosition.

				if(CharBuffer[CharPosition] == ',')	// if the first number
				{
					CharPosition += 1;	// move CharPosition up to the second number.
					ItemType *newItem = new(ItemType);
					newItem->ToCharacter = NULL;
					newItem->ToMap = NULL;
					newItem->next = newItem->previous = NULL;

					newItem->ItemID = atoi(ItemNumber);

					if(Current->nextItem == NULL)
						Current->nextItem = newItem;
					else
					{
						ItemType *CurrentItem = Current->nextItem;

						if(Current->nextItem != NULL)	// if there is at least one item in the tile.
							while(CurrentItem->next != NULL)
								CurrentItem = CurrentItem->next;
						else	// if there are no items in the tile
						{
							newItem->previous = NULL;
							Current->nextItem = newItem;
							goto NUMTEST;
						}

						newItem->previous = CurrentItem;
						CurrentItem->next = newItem;
					}

					

					goto NUMTEST;
				}
				else
				if(CharBuffer[CharPosition] == ')')	// if the second number
				{
					int index = 0;

					//for(; isdigit(CharBuffer[CharPosition]); index)	// Get the number
					//{
					//	ItemNumber[index++] = CharBuffer[CharPosition++];
					//}
					// Finish Getting the number.
						
					//CharPosition += index;	// move up CharPosition.

					ItemType *CurrentItem = Current->nextItem;
					
					while(CurrentItem->next != NULL)	// look for the last item that was added;
						CurrentItem = CurrentItem->next;

					CurrentItem->ItemAmount = atoi(ItemNumber);

					CharPosition += 1;

				//	goto START;
				}
				


			}
			else
			if(CharBuffer[CharPosition] == '*')	// if the new data is an attribute.
			{
				CharPosition += 1;

				char AttributeNumber[10] = {0};
				int index = 0;

				for(; isdigit(CharBuffer[CharPosition]); index)	// Get the number
				{
					AttributeNumber[index++] = CharBuffer[CharPosition++];
				}	// when at the end of the number, CharPosition will be moved to the ')'

				AttributeType *newAttribute = new(AttributeType);
				newAttribute->ToCharacter = NULL;
				newAttribute->ToMap = NULL;
				newAttribute->next = newAttribute->previous = NULL;

				newAttribute->AttributeID = atoi(AttributeNumber);

				if(Current->nextAtt == NULL)
					Current->nextAtt = newAttribute;
				else
				{
					AttributeType *CurrentAttribute = Current->nextAtt;

					if(Current->nextAtt != NULL)	// if there is at least one item in the tile.
						while(CurrentAttribute->next != NULL)
							CurrentAttribute = CurrentAttribute->next;
					else	// if there are no items in the tile
					{
						newAttribute->previous = NULL;
						Current->nextAtt = newAttribute;
					}

					newAttribute->previous = CurrentAttribute;
					CurrentAttribute->next = newAttribute;
				}

				CharPosition += 1;	// look at the next ',' or ']'

			//	goto START;
			}
			else
			if(CharBuffer[CharPosition] == 'c')	// if the new data is a character.
			{
				CharPosition += 1;	// Move CharPosition from the c to the start of the number

				char CharacterNumber[10] = {0};
				int index = 0;

				for(; isdigit(CharBuffer[CharPosition]); index) // Get the number until CharPosition is at the ')'.
				{
					CharacterNumber[index++] = CharBuffer[CharPosition++];
				}	// when at the end of the number, CharPosition will be moved to the ')'

				CharacterType *newCharacter = new(CharacterType);
				newCharacter->ToAttribute = NULL;
				newCharacter->ToMap = NULL;
				newCharacter->next = newCharacter->previous = NULL;

				newCharacter->CharacterID = atoi(CharacterNumber);

				if(Current->nextCharacter == NULL)
					Current->nextCharacter = newCharacter;
				else
				{
					CharacterType *CurrentCharacter = Current->nextCharacter;

					if(Current->nextCharacter != NULL)	// if there is at least one item in the tile.
						while(CurrentCharacter->next != NULL)
							CurrentCharacter = CurrentCharacter->next;
					else	// if there are no items in the tile
					{
						newCharacter->previous = NULL;
						Current->nextCharacter = newCharacter;
					}

					newCharacter->previous = CurrentCharacter;
					CurrentCharacter->next = newCharacter;
				}

				CharPosition += 1;	// look at the next ',' or ']'

			//	goto START;
			}
			else
			if(CharBuffer[CharPosition] == 'L')	// if the new data is a Link.
			{
				CharPosition += 1;	// look at the first arrow.

				char Directions[8] = {0};	// 6 directions, comma, and eol character.
				int  index = 0;

				while(CharBuffer[CharPosition] != ',')
				if(CharBuffer[CharPosition] == '>'	// east
				   ||
				   CharBuffer[CharPosition] == '^'	// north
				   ||
		   tolower(CharBuffer[CharPosition]) == 'v'	// south
				   ||
				   CharBuffer[CharPosition] == '<'	// west
				   ||
		   tolower(CharBuffer[CharPosition]) == 'u'	// up
				   ||
		   tolower(CharBuffer[CharPosition]) == 'd')// down
				{
					Directions[index++] = CharBuffer[CharPosition++];
				}
				else
					CharPosition++;	// something that is not a direction... and needs to be skipped.

				Directions[index] = ',';

				// CharPosition is currently located on the ',' and it needs to be moved to the name of the map to link to.

				CharPosition += 2;	// Move CharPosition to the name of the map.
				index = 0;

				char MapNameToLinkTo[115] = {0};

				while(isalpha(CharBuffer[CharPosition]))
				{
					MapNameToLinkTo[index++] = CharBuffer[CharPosition++];
				}

				// Now CharPosition is located on the '('.
				// Start Getting the Map Coordinates.
				int LinkX = 0, LinkY = 0;
				index = 0;

				CharPosition += 1; // Move CharPosition to the first number (X).

				char LinkXNum[11] = {0}, LinkYNum[11] = {0};

				while(isdigit(CharBuffer[CharPosition]))	// Get the number until you hit the ','
					LinkXNum[index++] = CharBuffer[CharPosition++];

				LinkX = atoi(LinkXNum);

				// CharPosition is currently located on the ','
				// We need to move CharPosition to the next number (Y).
				CharPosition += 1;	// Move CharPosition to the second number (Y).
				index = 0;

				while(isdigit(CharBuffer[CharPosition]))	// Get the number until you hit the ')'
					LinkYNum[index++] = CharBuffer[CharPosition++];

				CharPosition += 1;	// Move CharPosition from the ')' to the '1' or the '2'.

				LinkY = atoi(LinkYNum);
				index = 0;
				// Finish Getting the Map Coordinates.

				char one_way_or_two_way = CharBuffer[CharPosition];	// set as either one-way or two-way for the link.

				CharPosition += 1;	// Move CharPosition from the '1' or '2' to the ')';
				CharPosition += 1;	// Move CharPosition from the ')' to the ']' or the ',';

				// We also need to find the map now too.

				// Start looking for the map.
				MapType *CurrentMapName = Box.next;	// Box.next holds the first map.

				while(CurrentMapName != NULL)
				{
					if(strcmp(CurrentMapName->MapName, MapNameToLinkTo) == 0)	// found the map(name)
					{
						// Now we need to search for the correct Coordinates.

						TileType *CurrentCoord = CurrentMapName->Map.GetMapStart();	// Point to the map tile data.
						CurrentCoord = CurrentCoord->Next;	// Move to the first (actual data bearing) tile of the map.

						while(LinkX < CurrentCoord->x)	// Search for the X-Coordinate
							CurrentCoord = CurrentCoord->e;	// move right by one-x.

						while(LinkY < CurrentCoord->y)	// Search for the Y-Coordinate
							CurrentCoord = CurrentCoord->s;	// move down by one-x.

						// Done searching for the correct Coordinates.

						// Now we need to set up the pointers from the departure tile to the destination tile.
						
						index = 0;

						while(Directions[index] != ',')
						{
							// The links are made to be doubly so. This allows travel from one to the other and vice versa.
							if(Directions[index] == '>')
							{
								Current->e = CurrentCoord;
								
								if(one_way_or_two_way == '2')
									CurrentCoord->w = Current;
							}
							else
							if(Directions[index] == '^')
							{
								Current->n = CurrentCoord;
								
								if(one_way_or_two_way == '2')
									CurrentCoord->s = Current;
							}
							else
							if(tolower(Directions[index]) == tolower('V'))
							{
								Current->s = CurrentCoord;
								
								if(one_way_or_two_way == '2')
									CurrentCoord->n = Current;
							}
							else
							if(Directions[index] == '<')
							{
								Current->w = CurrentCoord;
								
								if(one_way_or_two_way == '2')
									CurrentCoord->e = Current;
							}

							index++;
						}
						goto FINISH_SET_DEPARTURE_TO_DESTINATION;
					}
					else
						CurrentMapName = CurrentMapName->next;	// Look at the next map.

				}
FINISH_SET_DEPARTURE_TO_DESTINATION:;


			}

		}

		if(CharBuffer[CharPosition] == ',')	// if need to read in new item/attribute/link.
		{
			CharPosition += 1;
			goto START;
		}

		if(CharBuffer[CharPosition] == ']')	// if at the end of a tile, so to speak.
		{
			CharPosition += 1;	// Move CharPosition from the ']' to the ';'.
		}

		/*else
		{
			cout << "Error -> "
				<< Map->MapName
				<< " located at "
				<< Map->MapFilePath
				<< " does not contain a correct tile marker. FIX IT!"
				<< endl;
		}*/
	}

	
}

void GenerateMapClass::SetupTileAttributesAndItems(MapType *Map, AttributeType *AttributeLL, ItemType *ItemLL, CharacterType *CharacterLL)	// This function finishes setting up the Map tiles.
{
	GenerateAttributeClass	GenerateAttributes;
	GenerateItemClass		GenerateItems;
	GenerateCharacterClass	GenerateCharacters;

	TileType *CurrentTile = Map->Map.GetMapStart();

	CurrentTile = CurrentTile->Next;	// move to the first tile.

	

	while(CurrentTile != NULL)	// now the items in the map need to be built.
	{
		AttributeType *CurrentAttribute = CurrentTile->nextAtt;
		ItemType *CurrentItem = CurrentTile->nextItem;
		CharacterType *CurrentCharacter = CurrentTile->nextCharacter;

		while(CurrentAttribute != NULL)	// the attribute class is for the most part finished.
		{
			char *AttributeName;

			if(IfAttributeIDExists(AttributeLL, CurrentAttribute->AttributeID, AttributeName) )
			{
				// wip -> GenerateAttributes.SetupAttributesFromLinkedList(NULL, NULL
			}
			CurrentAttribute = CurrentAttribute->next;
		}

		while(CurrentItem != NULL)	// the item class is only half-way finished.
		{
			// wip -> GenerateItems.SetupItemsFromLinkedList(;
			CurrentAttribute = CurrentAttribute->next;
		}

		while(CurrentCharacter != NULL)	// The character class is not finished at all.
		{
			GenerateCharacters.SetupCharactersFromLinkedList(NULL, NULL, AttributeLL);
			CurrentAttribute = CurrentAttribute->next;
		}
	}
}

bool IfAttributeIDExists(AttributeType *AttributeLL, int TileAttributeID, char *AttributeName)
{
	AttributeType *CurrentAttribute = AttributeLL;

	while(CurrentAttribute != NULL)
	{
		if(CurrentAttribute->AttributeID == TileAttributeID)
		{
			AttributeName = CurrentAttribute->AttributeName;
			return true;
		}
	}
}