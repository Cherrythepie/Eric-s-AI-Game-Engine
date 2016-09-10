#include "StructureCopyingClass.h"

void StructureCopyingClass::CopyItem(ItemType *Destination, ItemType *Source)	// "Destination" is assumed to have no usable data inside.
{
	Destination->Item = Source->Item;

	strcpy(Destination->ItemName, Source->ItemName);

	Destination->ItemAmount = Source->ItemAmount;
	Destination->ItemID = Source->ItemID;
	
	Destination->ToMap = NULL;
	Destination->ToCharacter = Source->ToCharacter;
}

void CopyAttributes(AttributeType *Destination, AttributeType *Source)
{
	AttributeType *CurrentSource = Source->ToAttribute;

	while(CurrentSource != NULL) // while not at the end of the Attributes LL of the "Source"
	{
		Destination->Attribute = CurrentSource->Attribute;
		Destination->AttributeAmount = CurrentSource->AttributeAmount;
		Destination->AttributeID = CurrentSource->AttributeID;
		
		strcpy(Destination->AttributeName, CurrentSource->AttributeName);
		
		/*	// These will be dealt with in "Copy<Something>".
		Destination->next
		Destination->previous
		*/

		Destination->ToCharacter = NULL;
		Destination->ToItem = NULL;
		Destination->ToMap = NULL;

		if(Source->ToAttribute != NULL)
		{
			Destination->ToAttribute = new(AttributeType);

			CopyAttributes(Destination->ToAttribute, CurrentSource);
		}

		CurrentSource = CurrentSource->next;	// move the pointer up
	}

	//while(CurrentAttributeSource != NULL)	// copy the attributes over
	//{
	//	AttributeType *DestinationNewAttribute = new(AttributeType);

	//	DestinationNewAttribute->Attribute = CurrentAttributeSource->Attribute;

	//	strcpy(DestinationNewAttribute->AttributeName, CurrentAttributeSource->AttributeName);

	//	DestinationNewAttribute->AttributeAmount = CurrentAttributeSource->AttributeAmount;
	//	DestinationNewAttribute->AttributeID = CurrentAttributeSource->AttributeID;

	//	DestinationNewAttribute->ToMap = NULL;
	//	DestinationNewAttribute->ToCharacter = CurrentAttributeSource->ToCharacter;
	//	DestinationNewAttribute->ToAttribute = CurrentAttributeSource->ToAttribute;

	//}

}