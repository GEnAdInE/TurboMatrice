#pragma once

#include <iostream>
#include <fstream>
#include "CVECTOR.h"
#include "CSTRING.h"

using namespace std;

class CParser
{
	public:

		//constructors
		CParser();
		CParser(const char *sFilePath, char cKeySeparator = ';', char cKeyValueAttribution = ':', bool bRemoveNewLine = true, bool bRemoveSpecCharacters = true);
		CParser(const CParser& CPAParam);

		//accessors
		const char *getValueOfKey(const char *key) const;
		CVector<CString*> parseArray(CString sArray, char cValueSeparator = ' ') const;


		//operators
		bool keyExist(const char *key, const char **value) const;

	private:

		CVector<const char*> vsKeyVector;
		CVector<const char*> vsValueVector;


};

