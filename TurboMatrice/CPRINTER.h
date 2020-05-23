#pragma once

#include "CSTRING.h"
#include "CVECTOR.h"
#include "CMATRICE.h"



/**
*  @brief  Print the CString to stdout.
*	@example print(myLine);
*/
void PRIprint(const CString &STRsentence) {
	cout << STRsentence.STRbegin() << endl;
}



/**
*  @brief  Print the Vector to stdout.
*	@example print(myVector);
*/
template <class T>
void PRIprint(const CVector<T> &VECvector) {
	unsigned int nIndex = 0;
	for (nIndex; nIndex < VECvector.VECsize(); nIndex++) {
		cout << VECvector.VECgetElement(nIndex) << ' ' << endl;
	}
}



/**
*  @brief  Print the Matrix to stdout.
*	@example print(myMatrix);
*/
template <class T>
void PRIprint(const CMatrice<T> &MATmatrix) {
	cout << "TypeMatrice=" << typeid(T).name() << endl;
	cout << "NBLignes=" << MATmatrix.MATgetNbRow() << endl;
	cout << "NBColonnes=" << MATmatrix.MATgetNbColumn() << endl;
	cout << "Matrice=[" << endl;
	for (unsigned int nIteratorRow = 0; nIteratorRow < MATmatrix.MATgetNbRow(); nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < MATmatrix.MATgetNbColumn(); nIteratorColumn++)
		{
			cout << MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow) << ' ';
		}
		cout << endl;
	}
	cout << "]" << endl << endl;

}



