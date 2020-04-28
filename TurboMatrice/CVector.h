#pragma once

#include <iostream>

using namespace std;

template <class T>
class CVector
{
public:

	//constructors
	CVector();
	CVector(initializer_list<T> ILarrayParam);
	CVector(const CVector& VECParam);

	//mutators
	void VECpush(T value);
	void VECpop();
	bool VECmodify(T element, unsigned int nIndex);

	//accessors
	size_t VECsize() const;
	T VECbegin() const;
	T VECend() const;
	int VECfind(T element) const;
	T VECgetElement(unsigned int nIndex) const;
	T *VECgetVectorElements() const;


	//operators
	bool operator!=(CVector<T> VECvector);

	//misc
	void print();

	//destructor
	~CVector();

	//only use if you know what you are doing
	void setSize(int iSize);

private:

	size_t VECnCapacity;
	T *VECpValueList;

	

	//misc
	bool VECpointerValueEqual(const T element1, const T element2) const;

};


template<class T>
void CVector<T>::setSize(int iSize)
{
	VECnCapacity = iSize;
}

/**
 *  @brief		Default constructor of the class.
 */
template <class T>
CVector<T>::CVector() {
	VECnCapacity = 0;
	VECpValueList = NULL;
}

/**
 *  @brief		Comfort constructor of the class.
 *  @param		VECarrayParam	Initializer Array.
 *	@example	CVector<const char*>myVector = { "Hello", "World"};
 */
template<class T>
CVector<T>::CVector(initializer_list<T> ILarrayParam) {
	VECnCapacity = ILarrayParam.size();
	VECpValueList = new T[VECnCapacity];
	unsigned int nValueListIterator = 0;
	for (auto pArrayIterator = ILarrayParam.begin(); pArrayIterator != ILarrayParam.end(); pArrayIterator++) {

		VECpValueList[nValueListIterator] = *pArrayIterator;
		nValueListIterator++;
	}

}

/**
 *  @brief  Copy constructor of the class.
 *  @param  VECParam  CVector to copy.
 *	@example CVector<const char*>myVector2 = myVector;
 */
template<class T>
CVector<T>::CVector(const CVector<T>& VECParam) {
	unsigned int nValueListIterator = 0;
	VECnCapacity = VECParam.VECsize();
	VECpValueList = new T[VECnCapacity];

	T *pvectorValueList = VECParam.VECgetVectorElements();
	for (nValueListIterator; nValueListIterator < VECnCapacity; nValueListIterator++) {
		VECpValueList[nValueListIterator] = pvectorValueList[nValueListIterator];
	}
}

/**
 *  @brief  Push an element inside the vector.
 *  @param  value	New element to push.
 *	@example myVector.push("Hello");
 */
template<class T>
void CVector<T>::VECpush(T value) {

	T *pNewValueList = new T[VECnCapacity + 1];
	unsigned int nNewValueListIterator = 0;
	for (nNewValueListIterator; nNewValueListIterator < VECnCapacity; nNewValueListIterator++) {
		pNewValueList[nNewValueListIterator] = VECpValueList[nNewValueListIterator];
	}

	if (VECpValueList != NULL) delete[] VECpValueList;

	pNewValueList[nNewValueListIterator] = value;
	VECnCapacity++;
	VECpValueList = pNewValueList;
}

/**
 *  @brief  Pop an element from the vector.
*	@throws Empty vector.
 *  @example myVector.pop();
 */
template<class T>
void CVector<T>::VECpop() {
	try
	{
		if (VECnCapacity == 0) throw (const char *)"POP ERROR: No element inside vector";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	T *pNewValueList = new T[VECnCapacity - 1];
	unsigned int nNewValueListIterator = 0;
	for (nNewValueListIterator; nNewValueListIterator < VECnCapacity - 1; nNewValueListIterator++) {
		pNewValueList[nNewValueListIterator] = VECpValueList[nNewValueListIterator];
	}
	delete[] VECpValueList;
	VECpValueList = pNewValueList;
	VECnCapacity--;
}

/**
 *  @brief  Return true if the modification has been done correctly, return false otherwise.
 *	@throws Index is out of vector range.
 *  @param  element	 New element to set.
 *	@param	index	 Index of the element that will be modified.
 *	@example myVector.modify("World", 1);
 */
template<class T>
bool CVector<T>::VECmodify(T element, unsigned int nIndex) {
	try
	{
		if (nIndex < 0 || nIndex > VECnCapacity - 1) throw (const char *)"MODIFY ERROR: index is out of vector range";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return false;
	}

	VECpValueList[nIndex] = element;
	return true;
}

/**
 *  @brief  Return the size of the vector.
 *	@example size_t myVectorSize = myVector.size();
 */
template<class T>
size_t CVector<T>::VECsize() const {
	return VECnCapacity;
}

/**
 *  @brief  Return the address of the first element.
 *	@example const char* myVectorBegin = myVector.begin();
 */
template<class T>
T CVector<T>::VECbegin() const {
	return VECpValueList[0];
}

/**
 *  @brief  Return the address of the last element.
 *	@example const char* myVectorEnd = myVector.end();
 */
template<class T>
T CVector<T>::VECend() const {
	return VECpValueList[VECnCapacity - 1];
}

/**
 *  @brief  Return a pointer pointing to the searched element, if not found return NULL.
 *  @param  element  Element to search in the vector.
 *	@example const char* myWord = myVector.find("Hello");
 */
template<class T>
int CVector<T>::VECfind(T element) const {
	unsigned int nValueListIterator = 0;
	for (nValueListIterator; nValueListIterator < VECnCapacity; nValueListIterator++) {
		if (VECpointerValueEqual(VECpValueList[nValueListIterator], element)) {
			return nValueListIterator;
		}
	}
	return -1;
}

/**
 *  @brief  Return the element stored at index.
 *	@throws Index is out of vector range.
 *  @param  index Index of the element to retrieve.
 *	@example const char* myWord = myVector.getElement(1);
 */
template<class T>
T CVector<T>::VECgetElement(unsigned int nIndex) const {
	try
	{
		if (nIndex < 0 || nIndex > VECnCapacity - 1) throw (const char *)"GET ERROR: index is out of vector range";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return NULL;
	}

	return VECpValueList[nIndex];
}

/**
 *  @brief  Return the whole vector as an Array.
 *	@example const char** mySentence = myVector.getVectorElements();
 */
template<class T>
T *CVector<T>::VECgetVectorElements() const {
	return VECpValueList;
}

/**
 *  @brief  Overcharge of != operator
 *	@param	Vector	Vector to compare to
 *	@example myVector1 != myVector2
 */
template<class T>
bool CVector<T>::operator!=(CVector<T> VECvector)
{
	if (VECsize() != VECvector.VECsize()) return true;

	unsigned int nValueListIterator = 0;
	for (nValueListIterator; nValueListIterator < VECsize(); nValueListIterator++) {
		if (VECgetElement(nValueListIterator) != VECvector.VECgetElement(nValueListIterator)) return true;
	}

	return false;


}

/**
 *  @brief  Print the vector to stdout.
 *  @example myVector.print();
 */
template<class T>
void CVector<T>::print() {
	unsigned int nValueListIterator = 0;
	for (nValueListIterator; nValueListIterator < VECnCapacity; nValueListIterator++) {
		cout << VECpValueList[nValueListIterator] << endl;
	}
}

/**
 *  @brief  Destructor of the class
 */
template<class T>
CVector<T>::~CVector() {
	delete[] VECpValueList;
	
}

/**
 *  @brief  Return true if two pointers are deep copies, false otherwise.
 *  @param  element1  First element.
 *  @param  element2  Second element.
 *	@example pointerValueEqual(element1, element2);
 */
template<class T>
bool CVector<T>::VECpointerValueEqual(T element1, T element2) const {
	while (*element1) {
		if (*element1 != *element2) {
			return false;
		}
		element1++;
		element2++;
	}
	return true;
}