#pragma once
#include "CMATRICE.h"


class CBooleanMatrix : public CMatrice<bool>
{
private:
	CMatrice<bool> MATmatrix;

public:

	CBooleanMatrix(void);
	CBooleanMatrix(CBooleanMatrix *BOOparam);
	CBooleanMatrix(CMatrice<bool> MATmatrix);


	CMatrice<bool> BOOgetMatrix();

	CBooleanMatrix operator&(CBooleanMatrix &BOOmatrix);
	CBooleanMatrix operator|(CBooleanMatrix &BOOmatrix);

	template<class T>
	CBooleanMatrix(CMatrice<T> MAT1, CMatrice<T> MAT2);


};



template<class T>
CBooleanMatrix::CBooleanMatrix(CMatrice<T> MAT1, CMatrice<T> MAT2)
{
	try
	{
		if (MAT1.MATsameDimension(MAT2)) throw (const char *)"BOOL MATRIX type ERROR: matrix need to be the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CBooleanMatrix();
	}

	CBooleanMatrix result = new CBooleanMatrix(new CMatrice(MAT1.MATgetNbColumn, MAT1.MATgetNbRow));



	for (unsigned int nIteratorColumn = 0; nIteratorColumn < MAT1.MATgetNbColumn(); nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < MAT1.MATgetNbRow(); nIteratorRow++)
		{

			if (MAT1->MATgetElement(nIteratorColumn, nIteratorRow) < MAT1->MATgetElement(nIteratorColumn, nIteratorRow))
			{
				result.MATmatrix.MATmodify(nIteratorColumn, nIteratorRow, 1);
			}
			else
			{
				result.MATmatrix.MATmodify(nIteratorColumn, nIteratorRow, 0);

			}
		}
	}


	return result;
}

CMatrice<bool> CBooleanMatrix::BOOgetMatrix()
{
	return MATmatrix;
}

CBooleanMatrix::CBooleanMatrix(void)
{
	MATmatrix = new CMatrice<bool>();
}

CBooleanMatrix::CBooleanMatrix(CBooleanMatrix * BOOparam)
{

	MATmatrix = CMatrice<bool>(BOOparam);

}

CBooleanMatrix::CBooleanMatrix(CMatrice<bool> MATmatrix)
{
	this->MATmatrix = CMatrice<bool>(MATmatrix);
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
