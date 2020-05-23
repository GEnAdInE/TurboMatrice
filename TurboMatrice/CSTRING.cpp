#include "CSTRING.h"

/**
 *  @brief  Default constructor of the class.
 *	@example CString myLine;
 */
CString::CString() {
	STRnSize = 0;
	STRpcWord = nullptr;
}

/**
 *  @brief  Comfort constructor of the class.
 *  @param  nSize	Size of the sentence to work with.
 *	@example CString myLine(10);
 */
CString::CString(unsigned int nSize) {
	STRnSize = nSize;
	STRpcWord = new char[nSize];
}

/**
 *  @brief  Comfort constructor of the class.
 *  @param  pcSentence	Sentence to work with.
 *	@example CString myLine = (const char*)line;
 */
CString::CString(const char* pcSentence) {
	STRnSize = STRgetSizeOfChar(pcSentence);
	STRpcWord = new char[STRnSize+1];

	for (unsigned int nCStringIterator = 0; nCStringIterator <= STRnSize; nCStringIterator++) {
		STRpcWord[nCStringIterator] = *pcSentence;
		pcSentence++;
	}
}

/**
 *  @brief  Copy constructor of the class.
 *  @param  STRParam	Initializer CString.
 *	@example CString myLine2 = myLine1;
 */
CString::CString(const CString& STRParam) {
	unsigned int nCStringIterator = 0;
	STRnSize = STRParam.STRnSize;
	STRpcWord = new char[STRnSize+1];

	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		STRpcWord[nCStringIterator] = STRParam.STRpcWord[nCStringIterator];
	}
	STRpcWord[nCStringIterator] = '\0';
}

/**
 *  @brief  Return a new CString extracted from the old CString between nStart and end.
 *	@throws Indexes are out of range.
 *  @param  nStart	Start index of the new CString.
 *	@example myLine.STRsubstr(0); //Whole CString
 *	@example myLine.STRsubstr(0, 1);
 */
CString CString::STRsubstr(unsigned int nStart) {
	unsigned int nCStringIterator = 0;
	unsigned int nNewCStringIterator = 0;
	unsigned int nEnd = STRnSize;

	try
	{
		if (nEnd - nStart < 0 || nEnd > STRnSize || nStart < 0) throw (const char *)"SUBSTR ERROR: Indexes are out of range";
	}
	catch (const char *e)
	{
		cout << e << endl;
	}

	char *pcNewString = new char[nEnd - nStart + 1];
	for (nCStringIterator = nStart; nCStringIterator < nEnd; nCStringIterator++) {
		pcNewString[nNewCStringIterator] = STRpcWord[nCStringIterator];
		nNewCStringIterator++;
	}
	pcNewString[nNewCStringIterator] = '\0';
	CString STRnewCString = (const char*)pcNewString;
	delete[] pcNewString;

	return STRnewCString;

}

/**
 *  @brief  Return a new CString extracted from the old CString between nStart and nEnd.
 *	@throws Indexes are out of range.
 *  @param  nStart	Start index of the new CString.
 *	@param	nEnd		End index of the new CString.
 *	@example myLine.STRsubstr(0); //Whole CString
 *	@example myLine.STRsubstr(0, 1);
 */
CString CString::STRsubstr(unsigned int nStart, unsigned int nEnd) {
	unsigned int nCStringIterator = 0;
	unsigned int nNewCStringIterator = 0;
	if (nEnd == -1) nEnd = STRnSize;

	try
	{
		if(nEnd-nStart < 0 || nEnd > STRnSize || nStart < 0) throw (const char *)"SUBSTR ERROR: Indexes are out of range";
	}
	catch (const char *e)
	{
		cout << e << endl;
	}

	char *pcNewString = new char[nEnd - nStart + 1];
	for (nCStringIterator = nStart; nCStringIterator < nEnd; nCStringIterator++) {
		pcNewString[nNewCStringIterator] = STRpcWord[nCStringIterator];
		nNewCStringIterator++;
	}
	pcNewString[nNewCStringIterator] = '\0';
	CString STRnewCString = (const char*)pcNewString;
	delete[] pcNewString;

	return STRnewCString;

}

/**
 *  @brief  Remove all occurences of a character.
 *	@param	cCharacter		Character to remove from the CString.
 *	@example myLine.STRremove('\n');
 */
void CString::STRremove(const char cCharacter) {
	unsigned int nOccurence = STRoccurence(cCharacter);

	if (nOccurence != 0) {
		unsigned int nCStringIterator = 0;
		unsigned int nNewCStringIterator = 0;
		char *pcNewString = new char[STRnSize-nOccurence+1];
		for (nCStringIterator; nCStringIterator <= STRnSize; nCStringIterator++) {
			if (STRpcWord[nCStringIterator] != cCharacter) {
				pcNewString[nNewCStringIterator] = STRpcWord[nCStringIterator];
				nNewCStringIterator++;
			}
		}
		delete[] STRpcWord;
		STRpcWord = pcNewString;
		STRnSize -= nOccurence;
	}
	

}

/**
 *  @brief  Replace all occurences of a character with cNewCharacter.
 *	@param	cCharacter			Character to be replaced.
 *	@param	cNewCharacter		Character to replace.
 *	@example myLine.STRreplace('\n', ' ');
 */
void CString::STRreplace(const char cCharacter, const char cNewCharacter) {
	unsigned int nOccurence = STRoccurence(cCharacter);

	if (nOccurence != 0) {
		unsigned int nCStringIterator = 0;
		unsigned int nNewCStringIterator = 0;
		char *pcNewString = new char[STRnSize+1];
		for (nCStringIterator; nCStringIterator <= STRnSize; nCStringIterator++) {
			if (STRpcWord[nCStringIterator] != cCharacter) {
				pcNewString[nNewCStringIterator] = STRpcWord[nCStringIterator];
				nNewCStringIterator++;
			}
			else {
				pcNewString[nNewCStringIterator] = cNewCharacter;
				nNewCStringIterator++;
			}
		}
		delete[] STRpcWord;
		STRpcWord = pcNewString;
	}
}

/**
 *  @brief  Return the index of the first specified cCharacter
 *	@param	cCharacter	Character to find.
 *	@example myLine.STRfind(':');
 */
int CString::STRfind(const char cCharacter) const {
	unsigned int nCStringIterator = 0;
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		if (STRpcWord[nCStringIterator] == cCharacter) {
			return nCStringIterator;
		}
	}
	return -1;
}

/**
 *  @brief  Count all occurences of a cCharacter inside CString
 *	@param	cCharacter	Character to count the occurences of.
 *	@example myLine.STRoccurrence('a');
 */
unsigned int CString::STRoccurence(const char cCharacter) const {
	unsigned int nCStringIterator = 0;
	unsigned int nOccurence = 0;
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		if (STRpcWord[nCStringIterator] == cCharacter) {
			nOccurence++;
		}
	}
	return nOccurence;
}

/**
 *  @brief  Return a the CString as a char*
 *	@example char *line = myLine.STRtoChar();
 */
char *CString::STRtoChar() const {
	unsigned int nCStringIterator = 0;
	char *pcNewString = new char[STRnSize+1];
	for (nCStringIterator = 0; nCStringIterator < STRnSize+1; nCStringIterator++) {
		pcNewString[nCStringIterator] = STRpcWord[nCStringIterator];
	}
	return pcNewString;
}

/**
 *  @brief  Try to return the CString as an integer
 *	@example int num = myLine.STRtoInt();
 */
int CString::STRtoInt() const {

	int iNewInt = 0;
	unsigned int nCStringIterator = 0;
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		if (STRpcWord[nCStringIterator] == '-') continue;
		iNewInt += (STRpcWord[nCStringIterator] - '0')*(int)pow(10, STRnSize-nCStringIterator-1);
	}
	if (STRfind('-') != -1) {
		iNewInt = -iNewInt;
	}
	return iNewInt;

}

/**
 *  @brief  Try to return the CString as an double
 *	@example double num = myLine.STRtoDouble();
 *	@warning Implements atof() because the conversion is complicated
 */
double CString::STRtoDouble() const {
	return atof(STRpcWord);
}

/**
 *  @brief  Return a pointer on the first character of the CString.
 *	@example myLine.STRbegin();
 */
char *CString::STRbegin() const {
	return STRpcWord;
}

/**
 *  @brief  Return a pointer on the last character of the CString.
 *	@example myLine.STRend();
 */
char *CString::STRend() const {
	return STRpcWord + STRnSize + 1;
}

/**
 *  @brief  Return true if the CString is empty, false otherwise.
 *	@example myLine.STRempty();
 */
bool CString::STRempty() {
	if (*STRpcWord == '\0') {
		return true;
	}
	else {
		return false;
	}
}

/**
 *  @brief  Concatenate a character to a new CString.
 *	@param	cCharacter	Character to add at the end of the CString.
 *	@example myLine+='\0';
 */
void CString::operator+=(const char cCharacter) {

	unsigned int nCStringIterator = 0;
	char *pcNewString = new char[STRnSize + 2];
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		pcNewString[nCStringIterator] = STRpcWord[nCStringIterator];
	}

	if (cCharacter != '\0') STRnSize += 1;
	for (nCStringIterator; nCStringIterator < STRnSize + 1; nCStringIterator++) {
		pcNewString[nCStringIterator] = cCharacter;
	}

	if (STRpcWord != NULL) delete[] STRpcWord;

	STRpcWord = pcNewString;
}

/**
 *  @brief  Concatenate a sentence to a new CString.
 *	@param	pcSentence	Sentence to add at the end of the CString.
 *	@example myLine+="Hello";
 */
void CString::operator+=(const char *pcSentence) {

	unsigned int nCStringIterator = 0;
	char *pcNewString = new char[STRnSize + STRgetSizeOfChar(pcSentence) + 1];
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		pcNewString[nCStringIterator] = STRpcWord[nCStringIterator];
	}

	unsigned int nNewCStringIterator = 0;
	STRnSize += STRgetSizeOfChar(pcSentence);
	for (nCStringIterator; nCStringIterator < STRnSize+1; nCStringIterator++) {
		pcNewString[nCStringIterator] = pcSentence[nNewCStringIterator];
		nNewCStringIterator++;
	}

	if (STRpcWord != NULL) delete[] STRpcWord;

	STRpcWord = pcNewString;
}

/**
 *  @brief  Concatenate a CString to a new CString.
 *	@param	STRsentence	 CString to add at the end of the CString.
 *	@example myLine+= myLine2;
 */
void CString::operator+=(const CString &STRsentence) {

	unsigned int nCStringIterator = 0;
	char *pcNewString = new char[STRnSize + STRsentence.STRnSize + 1];
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		pcNewString[nCStringIterator] = STRpcWord[nCStringIterator];
	}

	unsigned int nNewCStringIterator = 0;
	STRnSize += STRsentence.STRnSize;
	for (nCStringIterator; nCStringIterator < STRnSize + 1; nCStringIterator++) {
		pcNewString[nCStringIterator] = STRsentence.STRpcWord[nNewCStringIterator];
		nNewCStringIterator++;
	}

	if (STRpcWord != NULL) delete[] STRpcWord;

	STRpcWord = pcNewString;
}

/**
 *  @brief  Return true if the two CString are equal character by character, false otherwise.
 *	@param	STRsentence	Sentence to test with current CString.
 *	@example myLine != myLine2;
 */
bool CString::operator!=(const CString &STRsentence) {

	if (STRnSize != STRsentence.STRnSize) return true;

	unsigned int nCStringIterator = 0;
	for (nCStringIterator; nCStringIterator < STRnSize; nCStringIterator++) {
		if (STRpcWord[nCStringIterator] != STRsentence.STRpcWord[nCStringIterator]) return true;
	}
	
	return false;
}

/**
 *  @brief  Destructor of the class.
 */
CString::~CString() {
	delete[] STRpcWord;
}

/**
 *  @brief  Return the size of a const char*
 *	@example myLine.STRgetSizeOfChar(line);
 */
size_t CString:: STRgetSizeOfChar(const char *pcSentence) const {
	size_t nSize = 0;
	while (*pcSentence) {
		pcSentence++;
		nSize++;
	}
	return nSize;
}

