#include "HexTranslator.h"

string HexTranslator::Transform(char & character)
{
	string temp;
	const char hexArr[] = "0123456789ABCDEF";
	unsigned char c = static_cast<unsigned char>(character);
	temp += hexArr[c >> 4];
	temp += hexArr[c & 0xf];
	return temp;
}