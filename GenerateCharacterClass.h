// Builds the Characters

#ifndef GENERATECHARACTER_H
#define GENERATECHARACTER_H

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
#include "GenerateItemClass.h"

using namespace std;

class GenerateCharacterClass
{
private:

public:
//			GenerateAttributeClass();
AttributeType* SetupCharactersFromFile(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL, ifstream &ActualAttributeFile);
AttributeType* SetupCharactersFromLinkedList(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL);


};




#endif;