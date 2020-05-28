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
	~CBooleanMatrix(void);


	CMatrice<bool> BOOgetMatrix();

	CBooleanMatrix operator&(CBooleanMatrix &BOOmatrix);
	CBooleanMatrix operator|(CBooleanMatrix &BOOmatrix);

	template<class T>
	CBooleanMatrix BOOgenerator(CMatrice<T> MAT1, CMatrice<T> MAT2);


};



template<class T>
CBooleanMatrix CBooleanMatrix::BOOgenerator(CMatrice<T> MAT1, CMatrice<T> MAT2)
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
