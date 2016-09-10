#include "GenerateItemClass.h"

// THE ATTRIBUTES, NO QUESTION, HAVE TO BE BUILT (OR ALMOST FULLY BUILT) BEFORE THE ITEMS ARE BUILT. IT WILL TAKE SOME GOOD CODING TO REBUILD THE ATTRIBUTES IN THE ITEMS OTHERWISE.

void GetName(char charBuffer[], char name[], int charBufferIndex);
bool IfAttExists(char attributeName[], AttributeType *AttributeLL);	// checks if the attribute exists.
bool IfItemExists(char itemName[], ItemType *ItemLL);	// checks if the item exists.
//bool IfIsEmpty(char charBuffer[]);	// checks if a char array (string) is empty.
AttributeType* CreateNewAttributeType(AttributeType *CurrentAttribute);
AttributeType* CreateNewBlankAttributeType();

void ThatFunctionThatBuildsAnItemsAttributes(ItemType		*Item, 
											 ItemType		*ItemLL,
										     ItemType		*ItemsToBuild,
										     AttributeType  *AttributeLL,
										     AttributeType  *AttributesToBuild,
										     ifstream		&ActualItemFile,
											 char			charBuffer[],
											 int			charBufferIndex,
											 char			itemName[],
											 char			attributeName[],
											 char			attributeValue[]);

void PlaceNewAttribute(AttributeType *CurrentItemAttribute, AttributeType *CurrentAttribute);
bool IfSpecialAttribute(char attributeName[]);
void ItemMoveCharBufferIndexToNewData(char charBuffer[], int &charBufferIndex);
void CreateAndPlaceItemSpecialAttributes(char attributeName[], char charBuffer[], int charBufferIndex, char valueName[], AttributeType *CurrentItemAttribute, ItemType *Item);

void GenerateItemClass::SetupItemsFromFile_AttributesHalf  (ItemType		*Item, 
															ItemType		*ItemLL,
															AttributeType	*AttributeLL,
															ifstream		&ActualItemFile)
{
	char charBuffer[2501] = {0};
	int  charBufferIndex  =  0 ;

	char attributeName[251] = {0};
	char valueName    [251] = {0};

	AttributeType *CurrentAttribute = AttributeLL->next;
	AttributeType *CurrentItemAttribute = Item->ToAttribute;

	GenerateAttributeClass GenerateAttributes;

	ActualItemFile.getline(charBuffer, 2500);

	while(! ActualItemFile.eof() )
	{
		charBufferIndex = 0;
		ActualItemFile.getline(charBuffer, 2500);

		// set up the attribute on the left side of the '=' sign, if there is one.
		GetName(charBuffer, attributeName, charBufferIndex);

		if(IfSpecialAttribute(attributeName) )
		{
			if(strcmp(attributeName, "Contains") == 0 || strcmp(attributeName, "Components") == 0 )
				return;

			CreateAndPlaceItemSpecialAttributes(attributeName, charBuffer, charBufferIndex, valueName, CurrentItemAttribute, Item);
			continue;
		}

		if(Item->ToAttribute == NULL)
		{
			Item->ToAttribute = GenerateAttributes.SetupAttributesFromLinkedList(attributeName, ItemLL, AttributeLL);
			CurrentItemAttribute = Item->ToAttribute;
		}
		else
			CurrentItemAttribute->next = GenerateAttributes.SetupAttributesFromLinkedList(attributeName, ItemLL, AttributeLL);

		// set up the attribute on the right side of the '=' sign, if there is one.
		CurrentItemAttribute = CurrentItemAttribute->next;

		ItemMoveCharBufferIndexToNewData(charBuffer, charBufferIndex);
		GetName(charBuffer, valueName, charBufferIndex);

		AttributeType *valueAttribute = new(AttributeType);

		CurrentItemAttribute->ToAttribute = valueAttribute;

		if(isdigit(valueName[0]) )	// if valueName is an actual value for a unit.
		{
			valueAttribute->AttributeAmount = atoi(valueName);

			ItemMoveCharBufferIndexToNewData(charBuffer, charBufferIndex);
			GetName(charBuffer, valueName, charBufferIndex);

			strcpy(valueAttribute->AttributeName, valueName);
		}
		else
		{
			strcpy(valueAttribute->AttributeName, valueName);
		}

	}
}

void	GenerateItemClass::SetupItemsFromFile_ItemsHalf(	ItemType			*Item,	// the item we're trying to build
															ItemType			*ItemLL,	// the item linked list
															AttributeType		*AttributeLL,	// the attribute linked list
															char				itemCompleteFilePath[],	// most of the file path of the item we're trying to build
															char				itemName[])	// the name of the item we're trying to build
{
	char itemCompleteFilePathBackup[201] = {0};
	strcpy(itemCompleteFilePathBackup, itemCompleteFilePath);

	strcat(itemCompleteFilePath, itemName);
	strcat(itemCompleteFilePath, ".txt");

	if(Item->ToMap != NULL)	// if Item->ToMap points to the marker we set, to show that the item had already been built.
		return;	// get out of the function before any damage can be done.
	
	ItemType* CurrentLLItem = ItemLL->next;

	ifstream ActualItemFile(itemCompleteFilePath);	// open the item's file.

	if(! IfItemExists(itemName, ItemLL) )	// if the item does not exist in the item LL.
	{
		// set up the blank item.
		ItemType *BlankItem = new(ItemType);
		strcpy(BlankItem->ItemName, itemName);
		BlankItem->ItemID = 0;	// to show that this item does not exist in the item LL.
	//	return BlankItem;
	}
	else	// if the item does exist in the item LL.
	{
		// Find the item in the LL.
		while( strcmp(CurrentLLItem->ItemName, itemName) != 0)
			CurrentLLItem = CurrentLLItem->next;

	//	SetupItemsFromFile_ItemsHalf(Item, ItemLL, AttributeLL, itemCompleteFilePathBackup, itemName);
	}

	char charBuffer[2501] = {0};
	int  charBufferIndex  =  0 ;

	char attributeName[251] = {0};
	char valueName    [251] = {0};

	AttributeType *CurrentLLAttribute = AttributeLL->next;
	AttributeType *CurrentItemAttribute = Item->ToAttribute;

	GenerateAttributeClass GenerateAttributes;

	while(! ActualItemFile.eof() )
	{
		// while not 'something that will "contain' something else.."
		do	// In other words: get to the part of the file that needs to be worked on.
		{
			charBufferIndex = 0;
			ActualItemFile.getline(charBuffer, 2500);	// get the next line
			GetName(charBuffer, attributeName, charBufferIndex);
		}
		while(! (strcmp(attributeName, "Contains") == 0 || strcmp(attributeName, "Components") == 0 || strcmp(attributeName, "Reactions") == 0) );
	}

	if(strcmp(attributeName, "Contains") )
	{

		// Move CurrentItemAttribute to the end of the Linked List.
		if(Item->ToAttribute != NULL)
			while(CurrentItemAttribute->next != NULL)
				CurrentItemAttribute = CurrentItemAttribute->next;
		
		// set the name of the 'Contains' attribute to "Contains".
		AttributeType *ContainsAttribute = new(AttributeType);
		CurrentItemAttribute->next = ContainsAttribute;
		strcpy(ContainsAttribute->AttributeName, "Contains");

		ActualItemFile.getline(charBuffer, 2500);	// get the '{'

		while(charBuffer[0] != '}')
		{
			char itemName[251] = {0};
			charBufferIndex = 0;

			ActualItemFile.getline(charBuffer, 2500);	// get the next line of data.

			GetName(charBuffer, itemName, charBufferIndex);

			if(strcmp(itemName, "NOT_UNIQUE") == 0)
			{

			}

			ItemType *newItem = new(ItemType);

			if( isdigit(itemName[0]) )
			{
				
			}
		}
	}
	
	if(strcmp(attributeName, "Components") )
	{

	}
	
	if(strcmp(attributeName, "Reactions") )
	{

	}

	Item->ToMap = new(TileType);	// set a marker to show that the item has already been built.
}

ItemType* GenerateItemClass::SetupItemsFromLinkedList(char itemName[], ItemType *ItemLL, AttributeType *AttributeLL)
{
	// 'itemName' is the name of the item we want to build from
	// 'Item' had no use in the "attribute" version of this function.
	// 'ItemLL'-> same thing from 1 above ^
	// 'AttributeLL' was the attribute being worked on in the "attribute version of this function. It may now serve as the Actual attribute LL for use with the previous version of this function

//	char attributeName[] = {0};
	int itemNameIndex = 0;
	bool itemExists = false;
	bool unique = true;

	ItemType *CurrentItem = ItemLL->next;	// look at the pre-built LL.
	
	ItemType *newItem = new(ItemType);		// create the new item to return.
	strcpy(newItem->ItemName, itemName);	// set the new item's name.

	if( IfItemExists(itemName, ItemLL) )	// this is meaningless to check for.
	{
		itemExists = true;
	}

	if(strcmp(itemName, "NOT_UNIQUE") == 0)
	{
		unique = false;
	}

	// wip -> AttributeType *



	ItemType *CurrentLLItem = ItemLL->next;

	if(ItemLL->next != NULL)
	{
		while(true)
		{
			if(CurrentLLItem == NULL)
				break;

			if( strcmp(CurrentLLItem->ItemName, itemName) == 0)
				break;

			CurrentLLItem = CurrentLLItem->next;
		}
	}

	if(CurrentLLItem == NULL)	// if the item was not found in the item linked list.
		return newItem;


}

void GetName(char charBuffer[], char name[], int charBufferIndex)
{
	int nameIndex = 0;
	while(isalnum(charBuffer[charBufferIndex]) || charBuffer[charBufferIndex] == '.' || charBuffer[charBufferIndex] == '_') //charBuffer[charBufferIndex] != ' ' || charBuffer[charBufferIndex] != ';' || charBuffer[charBufferIndex] != ':'|| charBuffer[charBufferIndex] != ',')
	{
		name[nameIndex] = charBuffer[charBufferIndex];

		nameIndex++;
		charBufferIndex++;
	}
}

bool IfSpecialAttribute(char attributeName[])
{
	if(strcmp(attributeName, "Name") == 0)
		return true;
	
	if(strcmp(attributeName, "ID") == 0)
		return true;

	if(strcmp(attributeName, "Area_Constant") == 0)
		return true;

	if(strcmp(attributeName, "Contains") == 0)
		return true;

	if(strcmp(attributeName, "Properites") == 0)
		return true;

	if(strcmp(attributeName, "Components") == 0)
		return true;

	if(strcmp(attributeName, "Reactions") == 0)
		return true;

	if(strcmp(attributeName, "NOT_UNIQUE") == 0)
		return true;

	return false;
}

bool IfAttExists(char attributeName[], AttributeType *AttributeLL)
{
	AttributeType *CurrentAttribute = AttributeLL;

	while(CurrentAttribute != NULL)
	{
		if(strcmp(CurrentAttribute->AttributeName, attributeName) == 0)
		{
			return true;
		}
		
		CurrentAttribute = CurrentAttribute->next;
	}

	return false;
}

bool IfItemExists(char itemName[], ItemType *ItemLL)
{
	ItemType *CurrentItem = ItemLL;

	while(CurrentItem != NULL)
	{
		if(strcmp(CurrentItem->ItemName, itemName) == 0)
		{
			return true;
		}
		
		CurrentItem = CurrentItem->next;
	}

	return false;
}

//bool IfIsEmpty(char charBuffer[])
//{
//	int i = 0;
//	while(i != strlen(charBuffer) )
//	{
//		if(charBuffer[i] != ' ')
//			return false;
//	}
//
//	return true;
//}

AttributeType* CreateNewAttributeType(AttributeType *CurrentAttribute)
{
	AttributeType *newAttribute = new(AttributeType);

	strcpy(newAttribute->AttributeName, CurrentAttribute->AttributeName);
	newAttribute->AttributeID = CurrentAttribute->AttributeID;
	newAttribute->AttributeAmount = 0;

	newAttribute->ToCharacter = NULL;
	newAttribute->ToAttribute = NULL;
	newAttribute->ToMap = NULL;
	newAttribute->next = newAttribute->previous = NULL;

	return newAttribute;
}

AttributeType* CreateNewBlankAttributeType()
{
	AttributeType *newAttribute = new(AttributeType);

	strcpy(newAttribute->AttributeName, " ");
	newAttribute->AttributeID = 0;
	newAttribute->AttributeAmount = 0;

	newAttribute->ToCharacter = NULL;
	newAttribute->ToAttribute = NULL;
	newAttribute->ToMap = NULL;
	newAttribute->next = newAttribute->previous = NULL;

	return newAttribute;
}

void PlaceNewItem(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL, ifstream &ActualItemFile)	// for "contains" and it can probably be for "components".
{
	char charBuffer[2501] = {0};
	int  charBufferIndex = 0;
	
	char specialAttributeName[251] = {0};	//	Contains:
	char itemName[251] = {0};				//	Wood:
	char attributeName[251] = {0};			//	Wood: attributeName
	char attributeValue[251] = {0};			//	Wood: attributeName = attributeValue(,)(;)

	ActualItemFile.getline(itemName, 250);	// remove the '{' after "Contains:".

	ActualItemFile.getline(charBuffer, 2500);	// get the line that follows.

	GetName(charBuffer, itemName, charBufferIndex);

	if(charBuffer[charBufferIndex] == ':')
	{
		ItemMoveCharBufferIndexToNewData(charBuffer, charBufferIndex);	// move charBufferIndex to the first attribute;

		ItemType *newItem = new(ItemType);	// create a new item;

		if(IfItemExists(itemName, ItemLL))
		{

		}

		
	}

	if(charBuffer[charBufferIndex] == ';')
	{
		// do stuff
	}
}

void ItemMoveCharBufferIndexToNewData(char charBuffer[], int &charBufferIndex)
{
	while(! isalnum(charBuffer[charBufferIndex]) )	// moves charBufferIndex to the next number or character.
		charBufferIndex++;
}

void CreateAndPlaceItemSpecialAttributes(char attributeName[], char charBuffer[], int charBufferIndex, char valueName[], AttributeType *CurrentItemAttribute, ItemType *Item)
{
	if(strcmp(attributeName, "Name") == 0)
	{
		AttributeType *nameAttribute = new(AttributeType);
		strcpy(nameAttribute->AttributeName, attributeName);

		AttributeType *valueAttribute = new(AttributeType);
		nameAttribute->ToAttribute = valueAttribute;

		ItemMoveCharBufferIndexToNewData(charBuffer, charBufferIndex);
		GetName(charBuffer, valueName, charBufferIndex);
		strcpy(valueAttribute->AttributeName, valueName);

		if(CurrentItemAttribute == NULL)
			Item->ToAttribute = nameAttribute;
		else
			CurrentItemAttribute->next = nameAttribute;  

		CurrentItemAttribute = CurrentItemAttribute->next;
	}

	if(strcmp(attributeName, "ID") == 0)
	{
		AttributeType *idAttribute = new(AttributeType);

		ItemMoveCharBufferIndexToNewData(charBuffer, charBufferIndex);
		GetName(charBuffer, valueName, charBufferIndex);
		strcpy(idAttribute->AttributeName, valueName);

		if(CurrentItemAttribute == NULL)
			Item->ToAttribute = idAttribute;
		else
		CurrentItemAttribute->next = idAttribute;
	}

	if(strcmp(attributeName, "Area_Constant") == 0)
	{
		return;
	}

	if(strcmp(attributeName, "Contains") == 0)
	{

	}

	if(strcmp(attributeName, "Properites") == 0)
	{

	}

	if(strcmp(attributeName, "Components") == 0)
	{

	}

	if(strcmp(attributeName, "Reactions") == 0)
	{

	}

	if(strcmp(attributeName, "NOT_UNIQUE") == 0)
	{

	}
}

ItemType* TheContains_SpecialAttributeFunction(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL,
											   AttributeType *CurrentItemAttribute, ifstream &ActualItemFile, char charBuffer[], int charBufferIndex,
											   char itemCompleteFilePathBackup[])
{
	bool unique = true;
	bool itemExists = false;

	// Move CurrentItemAttribute to the end of the item's ToAttribute Linked List.
	if(Item->ToAttribute != NULL)	// if the item has attributes
		while(CurrentItemAttribute->next != NULL)	// if the item has more than 1 attribute in its 1st-level Attribute-LL
			CurrentItemAttribute = CurrentItemAttribute->next;
	else
	{
		Item->ToAttribute = new(AttributeType);
		CurrentItemAttribute = Item->ToAttribute;

		// make up some bull-shit attribute the item can have.
		strcpy(CurrentItemAttribute->AttributeName, "Fonzoness");
		CurrentItemAttribute->AttributeAmount = 40;
	}
		
	// set the name of the 'Contains' attribute to "Contains".
	AttributeType *ContainsAttribute = new(AttributeType);
	CurrentItemAttribute->next = ContainsAttribute;	// hook the 'contains' attribute onto the end of the item's attribute LL.
	ContainsAttribute->previous = CurrentItemAttribute;	// same as above ^, but in the other direction.
	strcpy(ContainsAttribute->AttributeName, "Contains");

	ItemType *CurrentContainsItem = NULL;	// CurrentContainsItem will point to the items in 'Contain's...' ToItem's... Linked list.

	ActualItemFile.getline(charBuffer, 2500);	// get the '{'

	while(charBuffer[0] != '}')
	{
		char itemName[251] = {0};
		charBufferIndex = 0;
		int itemAmount = 1;

		ActualItemFile.getline(charBuffer, 2500);	// get the next line of data.

		GetName(charBuffer, itemName, charBufferIndex);

		if(strcmp(itemName, "NOT_UNIQUE") == 0)
		{
			unique = false;
			continue;	// get the next line of data
		}

		if( isdigit(itemName[0]) )
		{
			itemAmount = atoi(itemName);
			ItemMoveCharBufferIndexToNewData(charBuffer, charBufferIndex);
			GetName(charBuffer, itemName, charBufferIndex);
		}

		if(IfItemExists(itemName, ItemLL) )	// checks if the item exists.
		{
			itemExists = true;
		}

		ItemType *CurrentLLItem = ItemLL->next;

		// get the location of the item that we may need to build.	// on the sheet, This item would be "Wood".
		while( strcmp(CurrentLLItem->ItemName, itemName) != 0 )
			CurrentLLItem = CurrentLLItem->next;

		GenerateItemClass GenerateItems;
		GenerateItems.SetupItemsFromFile_ItemsHalf(CurrentLLItem, ItemLL, AttributeLL, itemCompleteFilePathBackup, itemName);	// look on sheet: builds wood, so it can be used in shovel.

		if(charBuffer[charBufferIndex] == ';')	// if the item has no attributes following it.
		{
			ItemType *newItem = new(ItemType);	// Create the new item as a blank item with its value (Amount);
			newItem->ItemAmount = itemAmount;

			if(itemExists)
			{
				// if the linked list of 'ContainsAttribute->ToItem' has 1 or more "elements" "in" it.
				if(CurrentContainsItem != NULL)
				{
					CurrentContainsItem->next = newItem;
					newItem->previous = CurrentContainsItem;
				}
				else
				if(CurrentContainsItem == NULL)	// if 'ContainsAttribute->ToItem'... contains no items.
				{
					ContainsAttribute->ToItem = newItem;
					CurrentContainsItem = newItem;	// CurrentContainsItem = ContainsAttribute->ToItem;
					newItem->ToAttribute = ContainsAttribute;
				}



				if(! unique)	// if NOT_UNIQUE
				{
					strcpy(newItem->ItemName, "NOT_UNIQUE");	// self-explanatory.

					newItem->ToItem = CurrentLLItem;	// The newItem (ItemType) structure points to its own entry in the item linked list (ItemLL).
				}

				if( unique)
				{
					GenerateAttributeClass GenerateAttribute;
					AttributeType *CurrentLLItemAttributes = CurrentLLItem->ToAttribute;
					AttributeType *newItemAttributes = NULL;

					if(CurrentLLItemAttributes != NULL)
					{
						if( IfSpecialAttribute(CurrentLLItemAttributes->AttributeName) )
						{

						}

						newItem->ToAttribute = GenerateAttribute.SetupAttributesFromLinkedList(CurrentLLItemAttributes->AttributeName, ItemLL, AttributeLL);
						newItemAttributes = newItem->ToAttribute;

						CurrentLLItemAttributes = CurrentLLItemAttributes->next;
					}

					while(CurrentLLItemAttributes != NULL)
					{
						newItemAttributes->next = GenerateAttribute.SetupAttributesFromLinkedList(CurrentLLItemAttributes->AttributeName, ItemLL, AttributeLL);
						CurrentLLItemAttributes = CurrentLLItemAttributes->next;
					}
				}
			}
			else
			{
				
			}

			continue;
		}
	}

	return new(ItemType);
}