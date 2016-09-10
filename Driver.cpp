#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "Implementation.h"
//#include "MapClass.h"
#include "GenerateMap.h"
#include "GenerateItemClass.h"
#include "GenerateAttributeClass.h"

using namespace std;

bool showGames(ifstream &gamefiles, GameFileType &gfs, int &numGames);	// lists the available games
int  getGameNumber(int &numGames);					// asks the user for the number of the game they want to play
void getGameFileName(GameFileType &gfsLL, int &gameNum, char gf[]);	// gets the name of the file to open.
char * toLowerMulti(char upperMulti[], int arraySize);	// Just like "tolower," but for character arrays
void CreateMap(char mfBufferIn[], MapType &BuildMap);

void CharShunter(char CharBuffer[], char direction, int NumSpaces, int startLoc, int endLoc);
void CharEraser(char CharBuffer[], int NumSpacesFromEnd);


void RemoveAfterFirst(char CharBuffer[], char afterChar);
void RemoveAfterLast(char CharBuffer[], char afterChar);

void MoveCharBufferIndexToNewData(char charBuffer[], int &charBufferIndex);

int main()
{	//===============================//
	// Find the Game, and fire it up //
	//===============================//
	int numGames = 0;	// number of games available.
	int gameNum = 0;	// The game number to be played.
	int option = 0;		// Used so the User can decide which action to take.
	GameFileType gfsLL;	// Linked List that holds the names of the available games.
	char gf[115] = {0};	// Example: <gamefile>.txt
	MapType	MapList; MapList.next = MapList.previous = NULL;	// Initialize "MapList" pointers
	MapType * currentMap = MapList.next; // MapClass * currentMap = NULL

	char completeFilePath[301] = {0};	// used for the maps files
	char itemCompleteFilePath[301] = {0};	// used for the items files
	char attributeCompleteFilePath[301] = {0};	// used for the attributes files
	char characterCompleteFilePath[301] = {0};	// used for the characters files
	char propertiesCompleteFilePath[301] = {0};	// used for the properites files

	// Linked Lists.
	ItemType ItemLL;
	AttributeType AttributeLL;
	CharacterType CharacterLL;

	cout << "What would you like to do?"
		 << endl;

OPTIONS:
	cout << "1) Play a game \n"
		 << "2) run a simulation (wip) \n"
		 << "3) compress/encrypt a game (wip) \n"
		 << "4) Turing Test (wip) \n"
		 << "5) Quit \n"
		 << "6) Show Options \n"
		 << endl;

	char optionChar[] = {0};
	cin >> optionChar;	// Gets the option from the user. Note: Should check if input is a number or not
					// and return an error message if it is not a number.

	if(!(isdigit(optionChar[0])))	// checks if the inputed data is a digit or not
	{
		cout << "Please Pick only a NUMBER (1, 2, 3, 4, 5, or 6)"
			 << endl;
		goto OPTIONS;
	}

	if(atoi(optionChar) < 1 || atoi(optionChar) > 6)	// checks if the inputed data is a valid number or not
	{
		cout << "Please Pick only a NUMBER (1, 2, 3, 4, 5, or 6)"
			 << endl;
		goto OPTIONS;
	}

	option = atoi(optionChar);	// converts the inputed data to a useable integer value from a character "value".

	while(option != 5)
	{
		if(option == 1)
		{
			cout << "Welcome. Which game do you want to open?"
				 << endl;

			ifstream gamefiles("gamefiles.txt");	// file containing the list of available games to play
			if(!showGames(gamefiles, gfsLL, numGames))	// checks if there are in fact any available games. if there are, it prints the available games to the screen.
			{
				cout << "There are apparently no games available. Oops! \n"
					 << "Please Quit this and add some games to your games list please."
					 << endl;
				cin.ignore();
				return 0;
			}


			cout << "\n Choose a game number."
				 << endl;

			gameNum = getGameNumber(numGames);
			getGameFileName(gfsLL, gameNum, gf);
			
			char gfPath[150] = {0};
			strcat_s(gfPath, "games/");
			strcat(gfPath, gf);

			strcpy(completeFilePath, gfPath);	// saves the complete file path that is being used. Used to open the map files later on.

			ifstream masterFile(gfPath);

			char mfBufferIn[201] = {0};	// Temporarily holds data from the game's masterfile.

			do	// checks the MasterFile for the sub-MasterFiles(maps, items, characters, attributes, properties)
			{
				
			//cin.ignore();
			cout << mfBufferIn << endl;
				masterFile.get(mfBufferIn, 25,':');	// gets the keywords("maps:", "items:", "characters", etc.)

				// MAPS
				if(strcmp(toLowerMulti(mfBufferIn, 200), "Maps") == 0)	// Maps
				{
					masterFile.getline(mfBufferIn, 200);	// gets the Sub-MasterFile for the Maps Folder.
					CharShunter(mfBufferIn, 'L', 2, 2, strlen(mfBufferIn));	// removes the colon and following space from the beginning of mfBufferIn. strseek might fix the 2nd "2."
					CharShunter(completeFilePath, 'L', 14, 20, 34);	// removes the file name and extension from the end of completeFilePath. *Note* this will not work with different file names. Must be Updated!
					strcat(completeFilePath, mfBufferIn);
					
					strcpy(MapList.MapName, "r");			// shows that the first link in the list holds no useful data.
					strcpy(itemCompleteFilePath, completeFilePath);
					strcpy(attributeCompleteFilePath, completeFilePath);
					strcpy(characterCompleteFilePath, completeFilePath);
					strcpy(propertiesCompleteFilePath, completeFilePath);

					ifstream mapFolder(completeFilePath);		// Opens the file containing the map names with their extensions. mapFolder opens a FILE that may as well be a folder

					if(sizeof(mapFolder) == 0)	// If the map folder is empty
					{
						cout << "There are no maps in the \"Maps.txt\" file"
							 << endl;

						goto OPTIONS;
					}
						char MapFilePath[301] = {0};
						strcpy(MapFilePath, completeFilePath);	// The ".txt" at the end will need to be removed.
//						mapFolder.getline(MapFilePath, 300);

						

						MapType Box;
						strcpy(Box.MapName, "Start");
						Box.previous = Box.next = NULL;
						Box.Xdis = Box.Ydis = 0;

						MapType *Current = &Box;
						Box.previous = NULL;

						ifstream MapsFile(MapFilePath);	// file that contains all map names
						CharEraser(MapFilePath, 8);	// Removes the "Maps.txt ".

						while(!MapsFile.eof())	// This is where we set up the mapType structures.
												// We build the maps later on. We still have to open the files.
						{
							// start -> hook up pointers.
							MapType *newMap = new(MapType);
							newMap->previous = Current;
							newMap->next = NULL;
							Current->next = newMap;
							// end -> hook up pointers.

							Current = Current->next;
							
							char temp[115] = {0};
							MapsFile.getline(temp, 114);
							strcat(MapFilePath, temp);
							strcpy(Current->MapFilePath, MapFilePath);
							CharEraser(MapFilePath, strlen(temp));

							strcpy(Current->MapName, temp);
							CharEraser(Current->MapName, 4);

							ifstream ActualMapFile(Current->MapFilePath);
							ActualMapFile >> Current->Xdis >> Current->Ydis;


							GenerateMapClass MapGenerator;

							MapGenerator.BuildMapSkeleton(Current);	// Create the map's skeleton
						//	MapGenerator.SetupMapTiles(Current, ActualMapFile);
						}

						MapsFile.close();

						Current = Box.next;

						while(Current != NULL)
						{
							ifstream ActualMapFile(Current->MapFilePath);

							GenerateMapClass MapGenerator;
							MapGenerator.SetupMapTiles(Box, Current, ActualMapFile);

							Current = Current->next;
						}


					/*
					MapClass *newMap = new(MapClass);

					currentMap->next = newMap;
					*/

					
					continue;
				}

				if(strcmp(toLowerMulti(mfBufferIn, 200), "Items") == 0)	// Items
				{
					masterFile.getline(mfBufferIn, 200);	// gets the Sub-MasterFile for the Items Folder
					CharShunter(mfBufferIn, 'L', 2, 2, strlen(mfBufferIn));	// removes the colon and following space from the beginning of mfBufferIn. strseek might fix the 2nd "2."
					RemoveAfterFirst(itemCompleteFilePath, '//');
					strcat(itemCompleteFilePath, mfBufferIn);
					
					ifstream ItemsFile(itemCompleteFilePath);
					char itemCompleteFilePathBackup[251] = {0};	// cuz I'm lazy. You can tell by my spelling =/
					strcpy(itemCompleteFilePathBackup, itemCompleteFilePath);

					ItemType *CurrentItem = &ItemLL;

					RemoveAfterLast(itemCompleteFilePath, '//');	// remove the "items.txt"

					while(!ItemsFile.eof())	// get first half of item data (build the item's attributes).
					{
						ItemType *newItem = new(ItemType);
						CurrentItem->next = newItem;
						newItem->previous = CurrentItem;

						CurrentItem = CurrentItem->next;

						ItemsFile.getline(CurrentItem->ItemName, 114);	// get the item name from the file.
						strcat(itemCompleteFilePath, CurrentItem->ItemName);	// create a file path to open the item's file.
						strcat(itemCompleteFilePath, ".txt");	// add the .txt extension onto the end.

						char ItemID[11] = {0};

						ItemsFile.getline(ItemID, 10);	// get the item's ID from the file.
						CurrentItem->ItemID = atoi(ItemID);

						ifstream ActualItemFile(itemCompleteFilePath);
						RemoveAfterLast(itemCompleteFilePath, '//');	// remove the file and extension.

						GenerateItemClass generateItem;
						generateItem.SetupItemsFromFile_AttributesHalf(CurrentItem, &ItemLL, &AttributeLL, ActualItemFile);


					}

					ItemsFile.close();

					ItemsFile.open(itemCompleteFilePathBackup);

					CurrentItem = &ItemLL;

					while(!ItemsFile.eof())	// get the second half of item data (build the item's items).
					{
						CurrentItem = CurrentItem->next;	// the first "element" in 'ItemLL' contains no useful data (aside from pointers the actual useful data).

						ItemsFile.getline(CurrentItem->ItemName, 114);	// get the item name from the file.
					//	strcat(itemCompleteFilePath, CurrentItem->ItemName);	// create a file path to open the item's file.
					//	strcat(itemCompleteFilePath, ".txt");	// add the .txt extension onto the end.

						char ItemID[11] = {0};

						ItemsFile.getline(ItemID, 10);

					//	ifstream ActualItemFile(itemCompleteFilePath);
					//	RemoveAfterLast(itemCompleteFilePath, '//');	// remove the file and extension.

						GenerateItemClass generateItem;
						generateItem.SetupItemsFromFile_ItemsHalf(CurrentItem, &ItemLL, &AttributeLL, itemCompleteFilePath, CurrentItem->ItemName);


					}

					continue;
				}
				
				if(strcmp(toLowerMulti(mfBufferIn, 200), "Attributes") == 0)	// Attributes
				{
					masterFile.getline(mfBufferIn, 200);	// gets the Sub-MasterFile for the Items Folder
					CharShunter(mfBufferIn, 'L', 2, 2, strlen(mfBufferIn));	// removes the colon and following space from the beginning of mfBufferIn. strseek might fix the 2nd "2."
					RemoveAfterFirst(attributeCompleteFilePath, '//');
					strcat(attributeCompleteFilePath, mfBufferIn);
					
					ifstream AttributesFile(attributeCompleteFilePath);	// opens the file containing all the attributes.

					AttributeType *CurrentAttribute = &AttributeLL;

					// this loop reads in the names and number IDs of all the attributes. Reads the data From the "Attributes.txt" file in the 'AttributesFolder'.
					// It also creates the original AttributeLL.
					// Important to Note: The first "element" of the 'AttributeLL' holds no useful data and is basically just a tag.
					while(!AttributesFile.eof())               
					{
						char charBuffer[2501] = {0};
						int  charBufferIndex = 0;

						AttributeType *newAttribute = new(AttributeType);
						CurrentAttribute->next = newAttribute;
						newAttribute->previous = CurrentAttribute;

						CurrentAttribute = CurrentAttribute->next;

						// Initialize the attribute's variables, just in case.
						CurrentAttribute->next = NULL;
						CurrentAttribute->ToAttribute = NULL;
						CurrentAttribute->ToCharacter = NULL;
						CurrentAttribute->ToItem = NULL;
						CurrentAttribute->ToMap = NULL;
						CurrentAttribute->AttributeAmount = 0;

						AttributesFile.getline(charBuffer, 114);

						// helps to open an individual attribute's file.
						char IndividualAttributeFilePath[251] = {0};
						strcpy(IndividualAttributeFilePath, attributeCompleteFilePath);
						RemoveAfterLast(IndividualAttributeFilePath, '//');

						
						// set the attribute's name
						while(charBuffer[charBufferIndex] != ' ')
						{
							CurrentAttribute->AttributeName[charBufferIndex] = charBuffer[charBufferIndex];
							charBufferIndex++;
						}
						
						// finishes helping to open an individual attribute's file.
						strcat(IndividualAttributeFilePath, CurrentAttribute->AttributeName);
						strcat(IndividualAttributeFilePath, ".txt");
						ifstream IndividualAttributeFile(IndividualAttributeFilePath);	// I just realized that this doesn't do anything in this loop.

						MoveCharBufferIndexToNewData(charBuffer, charBufferIndex);

						// set the attribute's ID
						char attID[16] = {0};
						int  attIDindex = 0;
						while(charBuffer[charBufferIndex] != '\n')
						{
							attID[attIDindex] = charBuffer[charBufferIndex];
							attIDindex++;
							charBufferIndex++;
						}

						CurrentAttribute->AttributeAmount = atoi(attID);
					}

					CurrentAttribute = AttributeLL.next;	// again, the first element in the 'AttributeLL' contains no useful data and is more-or-less just a tag.

					// This loop Builds each element of the 'AttributeLL', one at a time. 
					while(CurrentAttribute != NULL)
					{
						char charBuffer[2501] = {0};
						int  charBufferIndex = 0;
						
						// helps to open an individual attribute's file.
						char IndividualAttributeFilePath[251] = {0};
						strcpy(IndividualAttributeFilePath, attributeCompleteFilePath);
						RemoveAfterLast(IndividualAttributeFilePath, '//');
						
						// finishes helping to open an individual attribute's file.
						strcat(IndividualAttributeFilePath, CurrentAttribute->AttributeName);
						strcat(IndividualAttributeFilePath, ".txt");
						ifstream IndividualAttributeFile(IndividualAttributeFilePath);

						GenerateAttributeClass GenerateAttribute;

						CurrentAttribute->ToAttribute = GenerateAttribute.SetupAttributesFromFile(NULL, NULL, &AttributeLL, IndividualAttributeFile);

						CurrentAttribute = CurrentAttribute->next;
					}

					continue;
				}

				if(strcmp(toLowerMulti(mfBufferIn, 200), "Characters") == 0)	// Characters
				{
					masterFile.getline(mfBufferIn, 200);	// gets the Sub-MasterFile for the Items Folder
					CharShunter(mfBufferIn, 'L', 2, 2, strlen(mfBufferIn));	// removes the colon and following space from the beginning of mfBufferIn. strseek might fix the 2nd "2."
					RemoveAfterFirst(characterCompleteFilePath, '//');
					strcat(characterCompleteFilePath, mfBufferIn);
					
					ifstream CharactersFile(characterCompleteFilePath);

					CharacterType *CurrentCharacter = &CharacterLL;

					while(!CharactersFile.eof())
					{
						CharacterType *newCharacter = new(CharacterType);
						CurrentCharacter->next = newCharacter;
						newCharacter->previous = CurrentCharacter;

						CurrentCharacter = CurrentCharacter->next;

						CharactersFile.getline(CurrentCharacter->CharacterName, 114);
					}

					continue;
				}
				
				//if(strcmp(toLowerMulti(mfBufferIn, 200), "Properties") == 0)	// Properties
				//{
				//	masterFile.getline(mfBufferIn, 200);	// gets the Sub-MasterFile for the Items Folder
				//	CharShunter(mfBufferIn, 'L', 2, 2, strlen(mfBufferIn));	// removes the colon and following space from the beginning of mfBufferIn. strseek might fix the 2nd "2."
				//	RemoveAfterFirst(propertiesCompleteFilePath, '//');
				//	strcat(propertiesCompleteFilePath, mfBufferIn);
				//	int index = 2 + 2;
				//	continue;
				//}

			}
			while(strcmp(toLowerMulti(mfBufferIn, 200), "") != 0);

			cout << "WIP \n"
				 << endl;

			// Now for moving the character around the map.

			goto OPTIONS;	// lets the user see the options again
		}
		if(option == 2)
		{
			// do stuff
			goto OPTIONS;	// lets the user see the option again
		}
		if(option == 3)
		{
			// do stuff///////////////////////////////////////////////////////////////////////////////
			goto OPTIONS;	// lets the user see the option again
		}
		if(option == 4)
		{
			// do stuff
			goto OPTIONS;	// lets the user see the option again
		}
		if(option == 5)
		{
			return 0;
		}
		if(option == 6)
		{
			goto OPTIONS;	// lets the user see the option again
		}
		if(option > 6)
		{
			cout << "Please pick an option between 1 and 6."
				 << endl;
			goto OPTIONS;	// lets the user see the option again
		}

		cin >> option;
	}


	return 0;
}

bool showGames(ifstream &gamefiles, GameFileType &gfs, int &numGames)
{
	GameFileType *current = &gfs;	// start of linked list

	cout << "The games available are: \n"
		 << endl;

	int fileNum = 0;	// number of games (and) a game's number.
	char games[101] = {0};

	
	
	while(strcmp(games, "end") != 0)	// checks for end of file
	{
		// get the game file names
		gamefiles.getline(games, 100);

		if(strcmp(games, "end") == 0)	// if the end of the file has been reached
			break;

		// print the names to the screen
		cout << ++fileNum 
			 << ") " 
			 << games
			 << endl;

		// add game names to a linked list
		current->next = new(GameFileType);
		current->next->previous = current;
		current = current->next;
		current->next = NULL;
		strcpy(current->filename, games);
		strcat(current->filename, ".txt");
		current->gameNum = fileNum;
	}

	if(fileNum == 0 && strcmp(games, "end") == 0)
	{
		return false;
	}

	numGames = fileNum;

	return true;
}

int getGameNumber(int &numGames)
{
	char num[4] = {2, 5, 7};

	int gn = 0;	// game number
	
	cin >> gn;	// gets the number of the game that the user wants to play.

	while(gn > numGames) // while the inputed value is greater than the number of games available
	{
		cout << "That is not desired input. Just type a number."
			 << endl;
		cin >> gn >> ws;	// gets the number of the game that the user wants to play.
	}
		


	/*while(isdigit(num[0]) != true || isdigit(num[1]) != true || isdigit(num[2]) != true)
	{
		cout << "That is not desired input. Just type a number."
			 << endl;
		cin >> num;
	}*/
	return gn;


}

void getGameFileName(GameFileType &gfsLL, int &gameNum, char gf[])
{
	GameFileType *current = gfsLL.next;	// set current at the start of the Linked List

	while(gameNum != current->gameNum && current->next != NULL)	// search the LL for the right game file name
		current = current->next;
	strcpy(gf, current->filename);	// return the file name
}

char * toLowerMulti(char upperMulti[], int arraySize)
{
	for(int i = 0; i < arraySize; i++)
		tolower(upperMulti[i]);

	return upperMulti;
}

void CreateMap(char mfBufferIn[], MapType &BuildMap)
{
//	GenerateMapClass MapGenerator(mfBufferIn);


}

void CharShunter(char CharBuffer[], char direction, int NumSpacesToMove, int startLoc, int endLoc)
{
	// CharBuffer-contains the char array that needs to be shunted.
	// direction--should be an 'l' (L) or an 'r' (R) to specify which direction to shunt the text.
	// NumSpacesToMove---is the number of spaces to move the text right or left.
	// startLoc---is the beginning location, in the Char array, of the block of text to move.
	// endLoc-----is the end location, in the Char array, of the block of text to move.

	// This function moves a block of text (that is inside a Char array) left or right. It will
	// overwrite the areas in the ORIGINAL Char array with the block of text that is moved there.
	// The array spaces left over, from where the block of text used to be, will be filled in
	// with blank spaces.

	if(toupper(direction) == 'L')
		for(int index = startLoc; index != endLoc; index++)
		{
			CharBuffer[index - NumSpacesToMove] = CharBuffer[index];	// shunts the character to the left
			CharBuffer[index] = '\0';									// Where the character originally was, it is replaced by a space (' ')
		}

	if(toupper(direction) == 'R')
		for(int index = endLoc; index != startLoc; index--)
		{
			CharBuffer[index + NumSpacesToMove] = CharBuffer[index];	// shunts the character to the right
			CharBuffer[index] = '\0';									// Where the character originally was, it is replaced by a space (' ')
		}
}

void CharEraser(char CharBuffer[], int NumSpacesFromEnd)
{
	int locToEraseOrig = strlen(CharBuffer) - 1;
	for(int i = 0; i != NumSpacesFromEnd; i++, locToEraseOrig--)
		CharBuffer[locToEraseOrig] = '\0';

	//int locToEraseOrig = strlen(CharBuffer) -2, locToErase = locToEraseOrig;	// the "+ 1" is workaround
	//for(locToErase; locToErase != locToEraseOrig - NumSpacesFromEnd; locToErase--)
	//	CharBuffer[locToErase] = ' ';

	return;
}

void RemoveAfterFirst(char CharBuffer[], char afterChar)
{
	int index = 0;

	for(; index < strlen(CharBuffer); index)	// search through the char array for the "afterChar"
	{
		if(CharBuffer[index++] == afterChar)
			break;

	}

	while(index < strlen(CharBuffer) )	// Remove characters (turn to ' 's) after the "afterChar"
		CharBuffer[index++] = '\0';
}

void RemoveAfterLast(char CharBuffer[], char afterChar)
{
	int index = 0;
	int removeSpot = 0;

	for(; index < strlen(CharBuffer); index++)	// search through the char array for the "afterChar"
	{
		if(CharBuffer[index] == afterChar)
			removeSpot = index + 1;

	}

	while(removeSpot < strlen(CharBuffer) )	// Remove characters (turn to ' 's) after the "afterChar"
		CharBuffer[removeSpot++] = '\0';
}
void MoveCharBufferIndexToNewData(char charBuffer[], int &charBufferIndex)
{
	while(! isalnum(charBuffer[charBufferIndex]) )	// moves charBufferIndex to the next number or character.
		charBufferIndex++;
}




