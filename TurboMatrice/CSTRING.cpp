#include "CSTRING.h"

CString::CString() {
	STRIiSize = 0;
	STRIcWord = nullptr;
}

CString::CString(unsigned int size) {
	STRIiSize = size;
	STRIcWord = new char[size];
}
/**
 *  @brief  Comfort constructor of the class.
 *  @param  sentence	Sentence to work with.
 *	@example CString myLine = (const char*)line;
 */
CString::CString(const char* sentence) {
	STRIiSize = size(sentence);
	STRIcWord = new char[STRIiSize+1];

	for (unsigned int cstringIterator = 0; cstringIterator <= STRIiSize; cstringIterator++) {
		STRIcWord[cstringIterator] = *sentence;
		sentence++;
	}
}

/**
 *  @brief  Copy constructor of the class.
 *  @param  STRParam	Initializer CString.
 *	@example CString myLine2 = myLine1;
 */
CString::CString(const CString& STRParam) {
	unsigned int cstringIterator = 0;
	STRIiSize = STRParam.STRIiSize;
	STRIcWord = new char[STRIiSize+1];

	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		STRIcWord[cstringIterator] = STRParam.STRIcWord[cstringIterator];
	}
	STRIcWord[cstringIterator] = '\0';
}

/**
 *  @brief  Return a new CString extracted from the old CString between start and end. If no index is set to end then end takes the end of the old CString
 *	@throws Indexes are out of range.
 *  @param  start	Start index of the new CString.
 *	@param	end		End index of the new CString.
 *	@example myLine.substr(0); //Whole CString
 *	@example myLine.substr(0, 1);
 */
CString CString::substr(unsigned int start, int end) {
	unsigned int cstringIterator = 0;
	unsigned int newCStringIterator = 0;
	if (end == -1) end = STRIiSize;

	try
	{
		if(end-start < 0 || end > STRIiSize || start < 0) throw (const char *)"SUBSTR ERROR: Indexes are out of range";
	}
	catch (const char *e)
	{
		cout << e << endl;
	}

	char *newString = new char[end - start + 1];
	for (cstringIterator = start; cstringIterator < end; cstringIterator++) {
		newString[newCStringIterator] = STRIcWord[cstringIterator];
		newCStringIterator++;
	}
	newString[newCStringIterator] = '\0';
	CString newCString = (const char*)newString;
	delete[] newString;

	return newCString;

}

/**
 *  @brief  Remove all occurences of a character.
 *	@param	character		Character to remove from the CString.
 *	@example myLine.remove('\n');
 */
void CString::remove(const char character) {
	unsigned int nOccurence = occurence(character);

	if (nOccurence != 0) {
		unsigned int cstringIterator = 0;
		unsigned int newCStringIterator = 0;
		char *newString = new char[STRIiSize-nOccurence+1];
		for (cstringIterator; cstringIterator <= STRIiSize; cstringIterator++) {
			if (STRIcWord[cstringIterator] != character) {
				newString[newCStringIterator] = STRIcWord[cstringIterator];
				newCStringIterator++;
			}
		}
		delete[] STRIcWord;
		STRIcWord = newString;
		STRIiSize -= nOccurence;
	}
	

}
void CString::replace(const char character, const char newcharacter) {
	unsigned int nOccurence = occurence(character);

	if (nOccurence != 0) {
		unsigned int cstringIterator = 0;
		unsigned int newCStringIterator = 0;
		char *newString = new char[STRIiSize+1];
		for (cstringIterator; cstringIterator <= STRIiSize; cstringIterator++) {
			if (STRIcWord[cstringIterator] != character) {
				newString[newCStringIterator] = STRIcWord[cstringIterator];
				newCStringIterator++;
			}
			else {
				newString[newCStringIterator] = newcharacter;
				newCStringIterator++;
			}
		}
		delete[] STRIcWord;
		STRIcWord = newString;
	}
}

/**
 *  @brief  Return the index of the first specified character
 *	@param	character	Character to find.
 *	@example myLine.find(':');
 */
int CString::find(const char character) const {
	unsigned int cstringIterator = 0;
	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		if (STRIcWord[cstringIterator] == character) {
			return cstringIterator;
		}
	}
	return -1;
}

/**
 *  @brief  Count all occurences of a character inside CString
 *	@param	character	Character to count the occurences of.
 *	@example myLine.occurrence('a');
 */
unsigned int CString::occurence(const char character) const {
	unsigned int cstringIterator = 0;
	unsigned int occurence = 0;
	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		if (STRIcWord[cstringIterator] == character) {
			occurence++;
		}
	}
	return occurence;
}

/**
 *  @brief  Return a the CString as a char*
 *	@example char *line = myLine.tochar();
 */
char *CString::tochar() const {
	unsigned int cstringIterator = 0;
	char *newString = new char[STRIiSize+1];
	for (cstringIterator = 0; cstringIterator < STRIiSize+1; cstringIterator++) {
		newString[cstringIterator] = STRIcWord[cstringIterator];
	}
	return newString;
}

int CString::toint() const {

	int newInt = 0;
	unsigned int cstringInterator = 0;
	for (cstringInterator; cstringInterator < STRIiSize; cstringInterator++) {
		if (STRIcWord[cstringInterator] == '-') continue;
		newInt += (STRIcWord[cstringInterator] - '0')*pow(10, STRIiSize-cstringInterator-1);
	}
	if (find('-') != -1) {
		newInt = -newInt;
	}
	return newInt;

}
double CString::todouble() const {
	return (double)1;
}

/**
 *  @brief  Return a pointer on the first character of the CString.
 *	@example myLine.begin();
 */
char *CString::begin() const {
	return STRIcWord;
}

/**
 *  @brief  Return a pointer on the last character of the CString.
 *	@example myLine.end();
 */
char *CString::end() const {
	return STRIcWord + STRIiSize + 1;
}

/**
 *  @brief  Return true if the CString is empty, false otherwise.
 *	@example myLine.empty();
 */
bool CString::empty() {
	if (*STRIcWord == '\0') {
		return true;
	}
	else {
		return false;
	}
}

void CString::operator+=(const char character) {

	unsigned int cstringIterator = 0;
	char *newString = new char[STRIiSize + 2];
	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		newString[cstringIterator] = STRIcWord[cstringIterator];
	}

	if (character != '\0') STRIiSize += 1;
	for (cstringIterator; cstringIterator < STRIiSize + 1; cstringIterator++) {
		newString[cstringIterator] = character;
	}

	if (STRIcWord != NULL) delete[] STRIcWord;

	STRIcWord = newString;
}

void CString::operator+=(const char *sentence) {

	unsigned int cstringIterator = 0;
	char *newString = new char[STRIiSize + size(sentence) + 1];
	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		newString[cstringIterator] = STRIcWord[cstringIterator];
	}

	unsigned int newCStringIterator = 0;
	STRIiSize += size(sentence);
	for (cstringIterator; cstringIterator < STRIiSize+1; cstringIterator++) {
		newString[cstringIterator] = sentence[newCStringIterator];
		newCStringIterator++;
	}

	if (STRIcWord != NULL) delete[] STRIcWord;

	STRIcWord = newString;
}

void CString::operator+=(CString sentence) {

	unsigned int cstringIterator = 0;
	char *newString = new char[STRIiSize + sentence.STRIiSize + 1];
	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		newString[cstringIterator] = STRIcWord[cstringIterator];
	}

	unsigned int newCStringIterator = 0;
	STRIiSize += sentence.STRIiSize;
	for (cstringIterator; cstringIterator < STRIiSize + 1; cstringIterator++) {
		newString[cstringIterator] = sentence.STRIcWord[newCStringIterator];
		newCStringIterator++;
	}

	if (STRIcWord != NULL) delete[] STRIcWord;

	STRIcWord = newString;
}

bool CString::operator!=(CString sentence) {

	if (STRIiSize != sentence.STRIiSize) return true;

	unsigned int cstringIterator = 0;
	for (cstringIterator; cstringIterator < STRIiSize; cstringIterator++) {
		if (STRIcWord[cstringIterator] != sentence.STRIcWord[cstringIterator]) return true;
	}
	
	return false;
}

CString *CString::clone() {
	CString *cloned = new CString(*this);
	return cloned;
}

/**
 *  @brief  Print the CString to stdout.
 *	@example myLine.print();
 */
void CString::print() {
	cout << *STRIcWord << endl;
}

/**
 *  @brief  Destructor of the class.
 */
CString::~CString() {
	delete[] STRIcWord;
}

/**
 *  @brief  Return the size of a const char*
 *	@example myLine.size(line);
 */
size_t CString:: size(const char *sentence) const {
	size_t size = 0;
	while (*sentence) {
		sentence++;
		size++;
	}
	return size;
}

