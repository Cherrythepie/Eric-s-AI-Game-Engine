// Builds the Items

#ifndef GENERATEITEM_H
#define GENERATEITEM_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "Implementation.h"
#include "StructureCopyingClass.h"
#include "GenerateAttributeClass.h"

using namespace std;

class GenerateItemClass
{
private:

public:
//			GenerateItemClass();
void	  SetupItemsFromFile_AttributesHalf	(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL, ifstream &ActualItemFile);
void	  SetupItemsFromFile_ItemsHalf		(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL, char itemCompleteFilePath[], char itemName[]);
ItemType* SetupItemsFromLinkedList			(char ItemName[], ItemType *ItemLL, AttributeType *AttributeLL);




};




#endif;