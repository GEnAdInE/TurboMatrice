#pragma once
#include "CBooleanMatrix.h"


inline CMatrice<bool> CBooleanMatrix::BOOgetMatrix()
{
	return MATmatrix;
}

inline CBooleanMatrix::CBooleanMatrix(void)
{
	MATmatrix = new CMatrice<bool>();
}

inline CBooleanMatrix::CBooleanMatrix(CBooleanMatrix * BOOparam)
{

	MATmatrix = CMatrice<bool>(BOOparam);

}

inline CBooleanMatrix::CBooleanMatrix(CMatrice<bool> MATmatrix)
{
	this->MATmatrix = CMatrice<bool>(MATmatrix);
}


inline CBooleanMatrix::~CBooleanMatrix(void)
{
	MATmatrix.~CMatrice();
}

CBooleanMatrix CBooleanMatrix::operator&(CBooleanMatrix & BOOmatrix)
{
	try
	{
		if (MATmatrix.MATsameDimension(BOOmatrix)) throw (const char *)"BOOL MATRIX type ERROR: matrix need to be the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CBooleanMatrix();
	}

	CBooleanMatrix *BOOresult = new CBooleanMatrix(this);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < MATmatrix.MATgetNbColumn(); nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < MATmatrix.MATgetNbRow(); nIteratorRow++)
		{
			bool value;
			value = MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow) & BOOmatrix.MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow);
			BOOresult->MATmodify(nIteratorColumn, nIteratorRow, value);
		}
	}
	return BOOresult;
}

CBooleanMatrix CBooleanMatrix::operator|(CBooleanMatrix & BOOmatrix)
{
	try
	{
		if (MATmatrix.MATsameDimension(BOOmatrix)) throw (const char *)"BOOL MATRIX type ERROR: matrix need to be the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CBooleanMatrix();
	}

	CBooleanMatrix *BOOresult = new CBooleanMatrix(this);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < MATmatrix.MATgetNbColumn(); nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < MATmatrix.MATgetNbRow(); nIteratorRow++)
		{
			bool value;
			value = MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow) | BOOmatrix.MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow);
			BOOresult->MATmodify(nIteratorColumn, nIteratorRow, value);
		}
	}
	return BOOresult;
}

