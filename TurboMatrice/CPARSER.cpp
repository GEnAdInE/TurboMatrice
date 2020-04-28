#include "CPARSER.h"

/**
 *  @brief  Default constructor of the class. SHOULD NOT BE USED.
 */
CParser::CParser() {
	try
	{
		throw (const char *)"CONSTRUCTOR ERROR: this constructor is not supported";
	}
	catch (const char *e)
	{
		cout << e << endl;
	}
}

/**
 *  @brief  Comfort constructor of the class.
 *	@throws Integrity errors, malformed file.
 *	@throws File errors, could not open file.
 *  @param  sFilePath				Path of the file to read from.
 *	@param	cKeySeparators			Character that separates each key/value pair, default : ';'.
 *	@param	cKeyValueAttribution	Character that separates each the key from the value, default : ':'.
 *	@param	bRemoveNewLine			True : automaticaly removes then new line character '\n'.
 *	@example CParser myParser("data.txt");
 */
CParser::CParser(const char *pcFilePath, char cKeySeparator, char cKeyValueAttribution, bool bRemoveNewLine, bool bRemoveSpecCharacters) {
	ifstream fileStream;

	fileStream.open(pcFilePath);
	try
	{
		if (fileStream.is_open(), ios::in) {
			while (!fileStream.eof()) {
				char line[40];
				fileStream.getline(line, 40, cKeySeparator);

				CString cline = (const char*)line;

				if (bRemoveNewLine) {
					cline.remove('\n');
				}
				if (bRemoveSpecCharacters) {
					cline.remove('\t');
				}
				if (cline.empty()) {
					break;
				}
				size_t delPos = cline.find(cKeyValueAttribution);

				CString key = cline.substr(0, delPos);

				CString value;

				if (cline.find('[') != -1) {
					fileStream.getline(line, 40, ']');
					CString cArray = (const char*)line;
					cArray.replace('\n', ' ');
					value += cArray;
				}
				else {
					value += cline.substr(delPos + 1);
				}


				//INTEGRITY CHECK
				if (key.empty()) {
					throw (const char *)"INTEGRITY ERROR: key empty";
				}
				if (value.empty()) {
					throw  (const char *)"INTEGRITY ERROR: value empty";
				}

				vsKeyVector.push(key.tochar());
				vsValueVector.push(value.tochar());
								
			}


		}
		else {
			throw (const char *)"FILE ERROR: File failed to open";
		}
	}
	catch (const char *e)
	{
		cout << e << endl;
	}

	fileStream.close();
}

/**
 *  @brief  Copy constructor of the class.
 *	@param	CPAParam			Initializer CParser.
 *	@example CParser myParser2 = myParser;
 */
CParser::CParser(const CParser& CPAParam) {
	vsKeyVector = CPAParam.vsKeyVector;
	vsValueVector = CPAParam.vsValueVector;
}

/**
 *  @brief  Return the value of the selected key.
 *	@param	key			Key to get the value of.
 *	@example myParser.getValueOfKey("Structure");
 */
const char* CParser::getValueOfKey(const char *key) const {
	const char *value =  NULL;
	if (keyExist(key, &value)) {
		return value;
	}
	return (char*)nullptr;
}
/**
 *  @brief  Return true if the key was found in the file and fill a pointer to its value, return false and nullptr otherwise.
 *  @param  key						Key to check.
 *	@param	value					Pointer to the value of key.
 *	@example keyExist(key, &value);
 */
bool CParser::keyExist(const char *key, const char **value) const {
	int keyIndex = vsKeyVector.find(key);
	if (keyIndex == -1) {
		value = nullptr;
		return false;
	}
	else {
		*value = vsValueVector.getElement(keyIndex);
		return true;
	}
}
//FAIRE GAFFE A PAS FAIRE DE PUSH BACK PCQ 100 != 1 0 0 
CVector<CString*> CParser::parseArray(CString sArray, char cValueSeparator) const {
	char *cstringIterator;
	CVector<CString*> vsArray;

	
	for (cstringIterator = sArray.begin()+1; cstringIterator < sArray.end()-2; cstringIterator++) {
		CString value;
		while (*cstringIterator != cValueSeparator) {
			if (*cstringIterator == ']') break;
			value += *cstringIterator;
			cstringIterator++;
		}
		value += '\0';
		vsArray.push(value.clone());
	}
	return vsArray;
}
