#include <iostream>
#include "Liste.h"


template <typename T> class CMatrice : private CListe<T>
{
	private:
		
		int iNbLine;
		int iNbColumn;
		CListe<T>* pLISMatrix;

	public:
		
		//constructor and destructor
		CMatrice(void); //default constructor
		CMatrice(CMatrice& mat);//Copy construcor !not finished
		CMatrice(int iL, int iC, CListe<T>* pLISM); //Confort Constructor
		~CMatrice(void);//Destructor , maybe rework on it !!
		
		//Methodes utile
		void setNbLine(int l);
		void setNbColumn(int c);
		int getNbLine(void);
		int getNbColumn(void);
		T getPreciseElement(int i, int j);//return an element of the matrix by knowing his position 
		//type_info GetMatriceType(void); // !! gather information about type_info
		
		

		//Operateur matrice
		CMatrice* operator+(CMatrice& MATmatrice);
		CMatrice operator-(CMatrice MATmatrice);
		CMatrice operator*(CMatrice MATmatrice);
		// faire operateur [] 

		//Operateur scalaire
		CMatrice operator+(T c);
		CMatrice operator*(T c);
		CMatrice operator-(T c);
		CMatrice operator/(T c);

		//Autre operation
		CMatrice tr(void); //transposé
		CMatrice inv(void); //inverse

};

template <typename T>
CMatrice<T>::CMatrice(void)
{
	iNbLine = 0;
	iNbColumn = 0;
	pLISMatrix = new CListe<T>();
}

template <typename T>
CMatrice<T>::CMatrice(CMatrice& mat)
{
	iNbLine = mat.getNbLine();
	iNbColumn = mat.getNbColumn();
	pLISMatrix = new CListe<T>(mat.pLISMatrix);
	
}



template <typename T>
CMatrice<T>::CMatrice(int iL, int iC, CListe<T>* pLISM)
{
	iNbLine = iL;
	iNbColumn = iC;

	pLISMatrix = new CListe<T>(iC,NULL); // allocate an array of iC int pointers — these are our rows
	for (int count = 0; count < iC; ++count)
		pLISMatrix[count] = new CListe<T>(iL,NULL); // these are our columns

	for (int i = 0; i < iC; i++)
	{
		for (int j = 0; j < iL; j++)
		{

			pLISMatrix[i][j] = pLISM[i][j];
		}
	}

}

template <typename T>
CMatrice<T>::~CMatrice(void)
{
	if (pLISMatrix == NULL)
	{
		if (iNbLine == 0 && iNbColumn == 0)
		{
			free(this);
		}

	}
}

template <typename T>
void CMatrice<T>::setNbLine(int l)
{
	if (l >= 0)
	{
		iNbLine = l;
	}
	else
	{
		//raise exception with exception class
	}
}

template <typename T>
void CMatrice<T>::setNbColumn(int c)
{
	if (c >= 0)
	{
		iNbColumn = c;
	}
	else
	{
		//raise exception with exception class
	}
}

template <typename T>
int CMatrice<T>::getNbLine(void)
{
	return iNbLine;
}

template <typename T>
int CMatrice<T>::getNbColumn(void)
{
	return iNbColumn;
}

template <typename T>
T CMatrice<T>::getPreciseElement(int i, int j)
{
	if (i >= 0 && i < getNbColumn())
	{
		if (j >= 0 && j < getNbLine())
		{
			return pLISMatrix[i][j];
		}
	}

}

template<typename T>
CMatrice<T>* CMatrice<T>::operator+(CMatrice<T>& MATmatrice)
{

	if (getNbColumn() == MATmatrice.getNbColumn() && getNbLine() == MATmatrice.getNbLine())
	{
		int iL = getNbLine();
		int iC = getNbColumn();

		T** tmpArray = new T*[iC]; // allocate an array of iC int pointers — these are our rows
		for (int count = 0; count < iC; ++count)
			tmpArray[count] = new T[iL]; // these are our columns

		for (int i = 0; i < iC; i++)
		{
			for (int j = 0; j < iL; j++)
			{

				tmpArray[i][j] = getPreciseElement(i, j) + MATmatrice.getPreciseElement(i, j);
			}
		}
		CMatrice<T>* MATresult = new CMatrice<T>(iL, iC, tmpArray);
		return MATresult;

	}
	else
	{
		return NULL;
	}
}


