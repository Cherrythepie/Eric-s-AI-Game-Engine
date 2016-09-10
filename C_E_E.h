#ifndef C_E_E_CLASS
#define C_E_E_CLASS

#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cctype>
#include <cmath>
#include <math.h>

#include "Implementation.h"

using namespace std;

class C_E_E_Class
{
private:
	char textBufferIn[3601];	// Incoming uncompressed data
	char textBufferOut[2701];	// Outgoing compressed   data
	char FOURbyteBuffer[5];		// uncompressed data to be compressed and sent to "3byteBuffer"
	int  FOURbyteBufferDeciValues[5];	// holds the decimal values of the 4 uncompressed bytes.
	char ThirtyTwoBitBuffer[33];		// holds uncompressed bits;
	char THREEbyteBuffer[4];			// compressed data to be appended to "textBufferOut"
	int  THREEbyteBufferDeciValues[4];	// holds the decimal values of the 3(4) compressed bytes.
	char TwentyFourBitBuffer[25];	// holds compressed bits;
	char singleByteBufferUncompresed[9];	// holds the bit data from a byte that is not compressed. Takes from "4byteBuffer"
	int  singleByte;
	int  tbiByteCount;			// Counts the number of bytes still needed to take from "textBufferIn" and move to FOURbyteBuffer.

public:
			C_E_E_Class();
	void	CompressAndEncrypt(ifstream &saveGameFile);
	void	Extract(ifstream &compressedSaveGameFile);
	void	GetDataFromTextBufferIn();
	void	ConvertBytes();

};

#endif