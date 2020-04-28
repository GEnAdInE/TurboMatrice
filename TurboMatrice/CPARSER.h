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
		CParser(const char *pcFilePath, char cKeySeparator = ';', char cKeyValueAttribution = ':', bool bRemoveNewLine = true, bool bRemoveSpecCharacters = true);
		CParser(const CParser& PARParam);

		//accessors
		const char *PARgetValueOfKey(const char *pcKey) const;
		CVector<CString*> PARparseArray(CString STRsentence, char cValueSeparator = ' ') const;


		//operators
		bool PARkeyExist(const char *pcKey, const char **ppcValue) const;

	private:

		CVector<const char*> VECpcKeyVector;
		CVector<const char*> VECpcValueVector;


};

