// Builds the Maps

#ifndef STRUCTURECOPYINGCLASS_H
#define STRUCTURECOPYINGCLASS_H

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "Implementation.h"

using namespace std;

class StructureCopyingClass
{
private:

public:
//			GenerateItemClass();
void CopyItem(ItemType *Destination, ItemType *Source);
void CopyAttribute(AttributeType *Destination, AttributeType *Source);
void CopyCharacter(CharacterType *Destination, CharacterType *Source);




};




#endif;