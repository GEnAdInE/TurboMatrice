#pragma once

#include <iostream>

using namespace std;

template <class T>
class CVector
{
public:

	//constructors
	CVector();
	CVector(initializer_list<T> ArrayParam);
	CVector(const CVector& VECParam);

	//mutators
	void push(T value);
	void pop();
	bool modify(T element, unsigned int index);

	//accessors
	size_t size() const;
	T begin() const;
	T end() const;
	T find(T element) const;
	T getElement(unsigned int index) const;
	T *getVectorElements() const;

	//operators
	bool operator!=(CVector<T> Vect);

	//misc
	void print();

	//destructor
	
	~CVector();

private:

	size_t VECiCapacity;
	T *pValueList;

	//misc
	bool pointerValueEqual(const T element1, const T element2) const;

};


/**
 *  @brief		Default constructor of the class.
 */
template <class T>
CVector<T>::CVector() {
	VECiCapacity = 0;
	pValueList = NULL;
}

/**
 *  @brief		Comfort constructor of the class.
 *  @param		ArrayParam	Initializer Array.
 *	@example	CVector<const char*>myVector = { "Hello", "World"};
 */
template<class T>
CVector<T>::CVector(initializer_list<T> ArrayParam) {
	VECiCapacity = ArrayParam.size();
	pValueList = new T[VECiCapacity];
	unsigned int valueListIterator = 0;
	for (auto ArrayIterator = ArrayParam.begin(); ArrayIterator != ArrayParam.end(); ArrayIterator++) {

		pValueList[valueListIterator] = *ArrayIterator;
		valueListIterator++;
	}

}

/**
 *  @brief  Copy constructor of the class.
 *  @param  VECParam  CVector to copy.
 *	@example CVector<const char*>myVector2 = myVector;
 */
template<class T>
CVector<T>::CVector(const CVector<T>& VECParam) {
	unsigned int valueListIterator = 0;
	VECiCapacity = VECParam.size();
	pValueList = new T[VECiCapacity];

	T *vectorValueList = VECParam.getVectorElements();
	for (valueListIterator; valueListIterator < VECiCapacity; valueListIterator++) {
		pValueList[valueListIterator] = vectorValueList[valueListIterator];
	}
}

/**
 *  @brief  Push an element inside the vector.
 *  @param  value	New element to push.
 *	@example myVector.push("Hello");
 */
template<class T>
void CVector<T>::push(T value) {
	T *newValueList = new T[VECiCapacity + 1];
	unsigned int newValueListIterator = 0;
	for (newValueListIterator; newValueListIterator < VECiCapacity; newValueListIterator++) {
		newValueList[newValueListIterator] = pValueList[newValueListIterator];
	}
	newValueList[newValueListIterator] = value;
	VECiCapacity++;
	if (pValueList != NULL)
		delete[] pValueList;
	pValueList = newValueList;
}

/**
 *  @brief  Pop an element from the vector.
*	@throws Empty vector.
 *  @example myVector.pop();
 */
template<class T>
void CVector<T>::pop() {
	try
	{
		if (VECiCapacity == 0) throw (const char *)"POP ERROR: No element inside vector";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	T *newValueList = new T[VECiCapacity - 1];
	unsigned int newValueListIterator = 0;
	for (newValueListIterator; newValueListIterator < VECiCapacity - 1; newValueListIterator++) {
		newValueList[newValueListIterator] = pValueList[newValueListIterator];
	}
	delete[] pValueList;
	pValueList = newValueList;
	VECiCapacity--;
}

/**
 *  @brief  Return true if the modification has been done correctly, return false otherwise.
 *	@throws Index is out of vector range.
 *  @param  element	 New element to set.
 *	@param	index	 Index of the element that will be modified.
 *	@example myVector.modify("World", 1);
 */
template<class T>
bool CVector<T>::modify(T element, unsigned int index) {
	try
	{
		if (index < 0 || index > VECiCapacity - 1) throw (const char *)"MODIFY ERROR: index is out of vector range";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return false;
	}

	pValueList[index] = element;
	return true;
}

/**
 *  @brief  Return the size of the vector.
 *	@example size_t myVectorSize = myVector.size();
 */
template<class T>
size_t CVector<T>::size() const {
	return VECiCapacity;
}

/**
 *  @brief  Return the address of the first element.
 *	@example const char* myVectorBegin = myVector.begin();
 */
template<class T>
T CVector<T>::begin() const {
	return pValueList[0];
}

/**
 *  @brief  Return the address of the last element.
 *	@example const char* myVectorEnd = myVector.end();
 */
template<class T>
T CVector<T>::end() const {
	return pValueList[VECiCapacity - 1];
}

/**
 *  @brief  Return a pointer pointing to the searched element, if not found return NULL.
 *  @param  element  Element to search in the vector.
 *	@example const char* myWord = myVector.find("Hello");
 */
template<class T>
T CVector<T>::find(T element) const {
	unsigned int valueListIterator = 0;
	for (valueListIterator; valueListIterator < VECiCapacity; valueListIterator++) {
		if (pointerValueEqual(pValueList[valueListIterator], element)) {
			return pValueList[valueListIterator];
		}
	}
	return nullptr;
}

/**
 *  @brief  Return the element stored at index.
 *	@throws Index is out of vector range.
 *  @param  index Index of the element to retrieve.
 *	@example const char* myWord = myVector.getElement(1);
 */
template<class T>
T CVector<T>::getElement(unsigned int index) const {
	try
	{
		if (index < 0 || index > VECiCapacity - 1) throw (const char *)"GET ERROR: index is out of vector range";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return NULL;
	}

	return pValueList[index];
}


/**
 *  @brief  Return the whole vector as an Array.
 *	@example const char** mySentence = myVector.getVectorElements();
 */
template<class T>
T *CVector<T>::getVectorElements() const {
	return pValueList;
}

/**
 *  @brief  Overcharge of != operator
 *	@param	Vector	Vector to compare to
 *	@example myVector1 != myVector2
 */
template<class T>
bool CVector<T>::operator!=(CVector<T> Vect)
{
	if (size() == Vect.size())
	{
		unsigned int valueListIterator = 0;
		for (valueListIterator; valueListIterator < size(); valueListIterator++) {
			if (getElement(valueListIterator) != Vect.getElement(valueListIterator)) return true;
		}

	}
	return false;
}

/**
 *  @brief  Print the vector to stdout.
 *  @example myVector.print();
 */
template<class T>
void CVector<T>::print() {
	unsigned int valueListIterator = 0;
	for (valueListIterator; valueListIterator < VECiCapacity; valueListIterator++) {
		cout << pValueList[valueListIterator] << endl;
	}
}

/**
 *  @brief  Destructor of the class
 */
template<class T>
CVector<T>::~CVector() {

	delete[] pValueList;
}

/**
 *  @brief  Return true if two const char* pointers have the same values (not necessarily the same addresses), return false otherwise.
 *  @param  element1  First element.
 *  @param  element2  Second element.
 *	@example pointerValueEqual(element1, element2);
 */
template<class T>
bool CVector<T>::pointerValueEqual(T element1, T element2) const {
	while (*element1) {
		if (*element1 != *element2) {
			return false;
		}
		element1++;
		element2++;
	}
	return true;
}

