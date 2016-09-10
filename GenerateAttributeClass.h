// Builds the Attributes

#ifndef GENERATEATTRIBUTE_H
#define GENERATEATTRIBUTE_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "Implementation.h"
#include "StructureCopyingClass.h"

using namespace std;

class GenerateAttributeClass
{
private:

public:
//			GenerateAttributeClass();
AttributeType* SetupAttributesFromFile(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL, ifstream &ActualAttributeFile);
AttributeType* SetupAttributesFromLinkedList(char attributeName[], ItemType *ItemLL, AttributeType *AttributeLL);


};




#endif;