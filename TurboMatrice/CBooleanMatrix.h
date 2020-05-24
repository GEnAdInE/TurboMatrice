#pragma once
#include "CMATRICE.h"

template <class T>
class CBooleanMatrix : public CMatrice<T>
{
private:
	CMatrice<bool> MATmatrix;

public:

	CBooleanMatrix(void);
	CBooleanMatrix(CBooleanMatrix *BOOparam);
	CBooleanMatrix(CMatrice<bool> MATmatrix);
	CBooleanMatrix(CMatrice<T> MATmatrix); //pour nico
	~CBooleanMatrix(void);


	CBooleanMatrix operator&(CBooleanMatrix &BOOmatrix);
	CBooleanMatrix operator|(CBooleanMatrix &BOOmatrix);

};

template<class T>
inline CBooleanMatrix<T>::CBooleanMatrix(void)
{
	MATmatrix = new CMatrice<bool>();
}

template<class T>
inline CBooleanMatrix<T>::CBooleanMatrix(CBooleanMatrix * BOOparam)
{

	MATmatrix = CMatrice<bool>(BOOparam);

}

template<class T>
inline CBooleanMatrix<T>::CBooleanMatrix(CMatrice<bool> MATmatrix)
{
	this->MATmatrix = CMatrice<bool>(MATmatrix);
}

template<class T>
inline CBooleanMatrix<T>::~CBooleanMatrix(void)
{
	MATmatrix.~CMatrice();
}

template <class T>
CBooleanMatrix<T> CBooleanMatrix<T>::operator&(CBooleanMatrix & BOOmatrix)
{
	try
	{
		if (MATmatrix.MATsameDimension(BOOmatrix)) throw (const char *)"BOOL MATRIX type ERROR: matrix need to be the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CBooleanMatrix *BOOresult = new CBooleanMatrix(this);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < MATmatrix.MATgetNbColumn(); nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < MATmatrix.MATgetNbRow();nIteratorRow++)
		{
			bool value;
			value = MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow) & BOOmatrix.MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow);
			BOOresult.MATmodify(nIteratorColumn, nIteratorRow, value);
		}
	}
	return BOOresult;
}

template<class T>
inline CBooleanMatrix<T> CBooleanMatrix<T>::operator|(CBooleanMatrix & BOOmatrix)
{
	r	try
	{
		if (MATmatrix.MATsameDimension(BOOmatrix)) throw (const char *)"BOOL MATRIX type ERROR: matrix need to be the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CBooleanMatrix *BOOresult = new CBooleanMatrix(this);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < MATmatrix.MATgetNbColumn(); nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < MATmatrix.MATgetNbRow(); nIteratorRow++)
		{
			bool value;
			value = MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow) | BOOmatrix.MATmatrix.MATgetElement(nIteratorColumn, nIteratorRow);
			BOOresult.MATmodify(nIteratorColumn, nIteratorRow, value);
		}
	}
	return BOOresult;
}
