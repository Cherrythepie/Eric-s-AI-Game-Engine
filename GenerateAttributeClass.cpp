#include "GenerateAttributeClass.h"

bool IfAttExists(char charBuffer[], AttributeType *AttributeLL, AttributeType *CurrentAttribute);
bool IfIsEmpty(char charBuffer[]);

AttributeType* GenerateAttributeClass::SetupAttributesFromFile(ItemType *Item, ItemType *ItemLL, AttributeType *AttributeLL, ifstream &ActualAttributeFile)
{
	char charBuffer[2501] = {0};
	int  charBufferIndex = 0;

	AttributeType *CurrentAttribute = AttributeLL->next;	// = NULL

	if(!ActualAttributeFile.eof() )
	{
		ActualAttributeFile.getline(charBuffer, 2500);

		AttributeType *newAttribute = new(AttributeType);

		if(IfAttExists(charBuffer, AttributeLL, CurrentAttribute) )
		{
			newAttribute->AttributeAmount = 0;
			newAttribute->AttributeID = CurrentAttribute->AttributeID;
			strcpy(newAttribute->AttributeName, CurrentAttribute->AttributeName);
		}
		else	// if the attribute does not exist in the attribute LL.
		{
			newAttribute->AttributeAmount = 0;
			newAttribute->AttributeID = 0;
			strcpy(newAttribute->AttributeName, charBuffer);
		}

		if(Item != NULL)
			Item->ToAttribute = newAttribute;

		newAttribute->next = SetupAttributesFromFile(NULL, NULL, AttributeLL, ActualAttributeFile);	// goes to the next line of the file.

		return newAttribute;
	}

	return NULL;
	
}


AttributeType* GenerateAttributeClass::SetupAttributesFromLinkedList(char attributeName[], ItemType *ItemLL, AttributeType *AttributeLL)
{
//	char attributeName[] = {0};
	int attributeNameIndex = 0;

	AttributeType *CurrentAttribute = AttributeLL->next;	// look at the pre-built LL.
	
	AttributeType *newAttribute = new(AttributeType);

	if(IfIsEmpty(attributeName) )	// if this recursion is after working with an item (false) or an attribute (true).	// 'attributeName' is the name of the attribute ->
	//								// -> being passed from the item (or attribute) that needs to be deep-copied to the item (or attribute). This means that ->
	{								// -> the attribute file that has the same name as 'attributeName'... needs to be read and checked to make sure it exists and stuff like that.
		newAttribute->AttributeAmount = 0;
		newAttribute->AttributeID = CurrentAttribute->AttributeID;
		strcpy(newAttribute->AttributeName, CurrentAttribute->AttributeName);

		if(CurrentAttribute->ToAttribute != NULL)	// go up.
			newAttribute->ToAttribute = SetupAttributesFromLinkedList("          ", NULL, CurrentAttribute->ToAttribute);	// the reason 'attributeName' is blank... is because->
																																// the next attribute has already been built and ->
																																// its file does not need to be read again.
		if(CurrentAttribute->next != NULL)	// go to the right.
			newAttribute->next = SetupAttributesFromLinkedList("          ", NULL, CurrentAttribute->next);
	}

	if(IfAttExists(attributeName, AttributeLL, CurrentAttribute) )	// checks if the attributeName exists. if so, returns the location in the attribute LL where you can find it.
	{
		newAttribute->AttributeAmount = 0;
		newAttribute->AttributeID = CurrentAttribute->AttributeID;
		strcpy(newAttribute->AttributeName, CurrentAttribute->AttributeName);
	}
	else	// if the attribute does not exist in the attribute LL
	{
		newAttribute->AttributeAmount = 0;
		newAttribute->AttributeID = 0;
		strcpy(newAttribute->AttributeName, attributeName);
	}

	if(CurrentAttribute->ToAttribute != NULL)	// go up.
		newAttribute->ToAttribute = SetupAttributesFromLinkedList("          ", NULL, CurrentAttribute->ToAttribute);

	if(CurrentAttribute->next != NULL)	// go to the right.
		newAttribute->next = SetupAttributesFromLinkedList("          ", NULL, CurrentAttribute->next);

	return newAttribute;
}

bool IfAttExists(char charBuffer[], AttributeType *AttributeLL, AttributeType *CurrentAttribute)	// tests if an attribute exists within the AttributeLL or not.
{																									// also returns where the attribute that exists is in the LL... if it exists ;)
	CurrentAttribute = AttributeLL->next;	// point to the first real attribute in the LL

	while(CurrentAttribute != NULL)
	{
		if(strcmp(charBuffer, CurrentAttribute->AttributeName) == 0)
			return true;
		else
			CurrentAttribute = CurrentAttribute->next;
	}

	return false;
}

bool IfIsEmpty(char charBuffer[])
{
	int i = 0;
	while(i != strlen(charBuffer) )
	{
		if(charBuffer[i] != ' ')
			return false;
	}

	return true;
}