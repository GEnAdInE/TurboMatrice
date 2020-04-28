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
	ifstream IFSfileStream;

	IFSfileStream.open(pcFilePath);
	try
	{
		if (IFSfileStream.is_open(), ios::in) {
			while (!IFSfileStream.eof()) {
				char pcLine[40];
				IFSfileStream.getline(pcLine, 40, cKeySeparator);

				CString STRline = (const char*)pcLine;

				//SENTENCE MUTATIONS
				if (bRemoveNewLine) {
					STRline.STRremove('\n');
				}
				if (bRemoveSpecCharacters) {
					STRline.STRremove('\t');
				}
				if (STRline.STRempty()) {
					break;
				}
				size_t nDelPos = STRline.STRfind(cKeyValueAttribution);

				CString STRkey = STRline.STRsubstr(0, nDelPos);

				CString STRvalue;

				//ARRAY HANDLING
				if (STRline.STRfind('[') != -1) {
					IFSfileStream.getline(pcLine, 40, ']');
					CString STRarray = (const char*)pcLine;
					STRarray.STRreplace('\n', ' ');
					STRvalue += STRarray;
				}
				else {
					STRvalue += STRline.STRsubstr(nDelPos + 1);
				}


				//INTEGRITY CHECK
				if (STRkey.STRempty()) {
					throw (const char *)"INTEGRITY ERROR: key empty";
				}
				if (STRvalue.STRempty()) {
					throw  (const char *)"INTEGRITY ERROR: value empty";
				}

				//FINAL PUSH
				VECpcKeyVector.VECpush(STRkey.STRtoChar());
				VECpcValueVector.VECpush(STRvalue.STRtoChar());
								
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

	IFSfileStream.close();
}

/**
 *  @brief  Copy constructor of the class.
 *	@param	CPAParam			Initializer CParser.
 *	@example CParser myParser2 = myParser;
 */
CParser::CParser(const CParser& CPAParam) {
	VECpcKeyVector = CPAParam.VECpcKeyVector;
	VECpcValueVector = CPAParam.VECpcValueVector;
}

/**
 *  @brief  Return the value of the selected key.
 *	@param	key			Key to get the value of.
 *	@example myParser.getValueOfKey("Structure");
 */
const char* CParser::PARgetValueOfKey(const char *pcKey) const {
	const char *pcValue =  NULL;
	if (PARkeyExist(pcKey, &pcValue)) {
		return pcValue;
	}
	return (char*)nullptr;
}
/**
 *  @brief  Return true if the key was found in the file and fill a pointer to its value, return false and nullptr otherwise.
 *  @param  key						Key to check.
 *	@param	value					Pointer to the value of key.
 *	@example keyExist(key, &value);
 */
bool CParser::PARkeyExist(const char *pcKey, const char **ppcValue) const {
	int iKeyIndex = VECpcKeyVector.VECfind(pcKey);
	if (iKeyIndex == -1) {
		ppcValue = nullptr;
		return false;
	}
	else {
		*ppcValue = VECpcValueVector.VECgetElement(iKeyIndex);
		return true;
	}
}

/**
 *  @brief  Return a vector of the sentences that were separated by cValueSeparator.
 *  @param  STRsentence						Initial sentence.
 *	@param	cValueSeparator					Separator character.
 *	@example CVector<CString*> myVector = parser.PARparseArray(mySentence, ' ');
 */
CVector<CString*> CParser::PARparseArray(CString STRsentence, char cValueSeparator) const {
	char *pcCStingIterator;
	CVector<CString*> VECSTRarray;

	
	for (pcCStingIterator = STRsentence.STRbegin(); pcCStingIterator < STRsentence.STRend(); pcCStingIterator++) {
		CString value;
		while (*pcCStingIterator != cValueSeparator) {
			if (*pcCStingIterator == '\0') break;
			value += *pcCStingIterator;
			pcCStingIterator++;
		}
		value += '\0';
		VECSTRarray.VECpush(value.STRclone());
	}
	return VECSTRarray;
}
