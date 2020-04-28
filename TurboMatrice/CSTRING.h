#pragma once

#include <iostream>

using namespace std;

class CString
{
	public:

		//constructors
		CString();
		CString(unsigned int nSize);
		CString(const char* pcSentence);
		CString(const CString& STRParam);
 
		//mutators
		CString STRsubstr(unsigned int nStart, int iEnd = -1);
		void STRremove(const char cCharacter);
		void STRreplace(const char cCharacter, const char cNewcharacter);

		//accessors
		int STRfind(const char cCharacter) const;
		unsigned int STRoccurence(const char cCharacter) const;
		char *STRtoChar() const;
		int STRtoInt() const;
		double STRtoDouble() const;
		char *STRbegin() const;
		char *STRend() const;

		//operators
		bool STRempty();
		void operator+=(const char cCharacter);
		void operator+=(const char* pcSentence);
		void operator+=(CString STRsentence);
		bool operator!=(CString STRsentence);
		CString* STRclone();

		//misc
		void print();

		//destructor
		~CString();

	
	private:

		char *STRpcWord;
		size_t STRnSize;

		//operators
		size_t STRgetSizeOfChar(const char* pcSentence) const;
};
