#include "C_E_E.h"

using namespace std;

C_E_E_Class::C_E_E_Class()
{
	int i = 0;
	while(i < (3600/sizeof("EndOfFile")))
		strcat(textBufferIn, "EndOfFile");
	
	while(i < (2700/sizeof("EndOfFile")))
		strcat(textBufferOut, "EndOfFile");

	strcpy(THREEbyteBuffer, "hat");	// THREEbyteBuffer might not need initializing
	tbiByteCount = 0;

}

void C_E_E_Class::CompressAndEncrypt(ifstream &saveGameFile)
{
	saveGameFile.getline(textBufferIn, 3600);




}


void C_E_E_Class::Extract(ifstream &compressedSaveGameFile)
{
	


}

void C_E_E_Class::GetDataFromTextBufferIn()
{
	FOURbyteBuffer[0] = textBufferIn[tbiByteCount];
	FOURbyteBuffer[1] = textBufferIn[++tbiByteCount];
	FOURbyteBuffer[2] = textBufferIn[++tbiByteCount];
	FOURbyteBuffer[3] = textBufferIn[++tbiByteCount];
}

void C_E_E_Class::ConvertBytes()
{
	int i = 0; // Which byte to work on

	if(FOURbyteBuffer[i] == 'a')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'b')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'c')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'd')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'e')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'f')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'g')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'h')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'i')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'j')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'k')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'l')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'm')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'n')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'o')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'p')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'q')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'r')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 's')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 't')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'u')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'v')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'w')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'x')
	{
		singleByte = 0;
		return;
	}
	if(FOURbyteBuffer[i] == 'y')
	{
		singleByte = 0;
		return;
	}
	if(isalpha(FOURbyteBuffer[i]) && FOURbyteBuffer[i] == 'z')
	{
		singleByte = 0;
		return;
	}

}





