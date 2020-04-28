#pragma once

#include <iostream>

using namespace std;

class CString
{
	public:

		//constructors
		CString();
		CString(unsigned int size);
		CString(const char* sentence);
		CString(const CString& STRParam);
 
		//mutators
		CString substr(unsigned int start, int end = -1);
		void remove(const char character);
		void replace(const char character, const char newcharacter);

		//accessors
		int find(const char character) const;
		unsigned int occurence(const char character) const;
		char *tochar() const;
		int toint() const;
		double todouble() const;
		char *begin() const;
		char *end() const;

		//operators
		bool empty();
		void operator+=(const char character);
		void operator+=(const char* sentence);
		void operator+=(CString sentence);
		bool operator!=(CString sentence);
		CString* clone();

		//misc
		void print();

		//destructor
		~CString();

	
	private:

		char *STRIcWord;
		size_t STRIiSize;

		//operators
		size_t size(const char* sentence) const;
};
