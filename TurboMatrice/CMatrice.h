#include "CVector.h"
#include "Cexception.h"

//attention fuite memoire a tout les endroit ou je fais des tmpArray

template <typename T> class CMatrice  : public CVector<T>
{
	private:
		
		int iNbRow;
		int iNbColumn;
		CVector<CVector<T>*> pVECmatrix;

	public:
		
		//constructor and destructor
		CMatrice(void); //default constructor
		CMatrice(const CMatrice<T>& mat);//Copy construcor !not finished
		CMatrice(int iNbColumn, int iNbRow, CVector<CVector<T>*> pVECmat); //Confort Constructor
		~CMatrice(void);//Destructor , maybe rework on it !!
		
		//Methodes utile
		void MATsetNbRow(int l);
		void MATsetNbColumn(int c);
		int MATgetNbRow(void);
		int MATgetNbColumn(void);
		T MATgetElement(int i, int j);//return an element of the matrix by knowing his position
		void MATmodify(int i, int j, T value);// pas besoin
		void MATaddRow(int iPos, CVector<T> row);		
		void MATaddColumn(int iPos,CVector<T> Column);
		void MATremoveRow(int iPos);
		void MATremoveColumn(int iPos);


		bool MATsameDimension(CMatrice<T>& MATmatrice);
		
		//type_info GetMatriceType(void); // !! gather information about type_info
		
		

		//Operateur matrice
		CMatrice<T> operator+(CMatrice<T>& MATmatrice);
		CMatrice<T> operator-(CMatrice<T>& MATmatrice);
		CMatrice<T> operator*(CMatrice<T>& MATmatrice);
		CMatrice<T>& operator+=(CMatrice<T>& MATmatrice);
		CMatrice<T>& operator-=(CMatrice<T>& MATmatrice);
		CMatrice<T>& operator*=(CMatrice<T>& MATmatrice);
		

		//Operateur scalaire
		
		CMatrice<T> operator*(T c);
		CMatrice<T> operator/(T c);
		CMatrice<T> operator*=(T& c);
		CMatrice<T> operator/=(T& c);
		

		//Autre operation
		T* operator[](int iIterator); //ca ou on garde MATgetElement , au choix !
		CMatrice<T>& operator=(CMatrice<T> MATmatrice);
		bool operator==(CMatrice<T> MATmatrice);
		bool operator!=(CMatrice<T> MATmatrice);
		CMatrice<T> MATtr(void); //transposé
		

};

template <typename T>
CMatrice<T>::CMatrice(void)
{
	iNbRow = 0;
	iNbColumn = 0;
	
}

template <typename T>
CMatrice<T>::CMatrice(const CMatrice<T>& mat)
{
	iNbRow = mat.iNbRow;
	iNbColumn = mat.iNbColumn;
	for (int count = 0; count < iNbColumn; ++count)
		pVECmatrix.push(new CVector<T>);

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{
			pVECmatrix.getElement(i)->push(mat.pVECmatrix.getElement(i)->getElement(j));
		}
	}
	
}

template <typename T>
CMatrice<T>::CMatrice(int iC, int iR, CVector<CVector<T>*> pMat)
{
	iNbRow = iR;
	iNbColumn = iC;
	for (int count = 0; count < iNbColumn; ++count)
		pVECmatrix.push(new CVector<T>);

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{
			pVECmatrix.getElement(i)->push(pMat.getElement(i)->getElement(j));
		}
	}

}

template <typename T>
CMatrice<T>::~CMatrice(void)
{
	
	if (pVECmatrix.getVectorElements() != NULL) {
		for (int i = 0; i < iNbColumn; i++)
		{
			if(pVECmatrix.getElement(i)!=NULL)
				free(pVECmatrix.getElement(i));
			
		}
	//pVECmatrix.~CVector();
		
				
	}

	
}

template <typename T>
inline void CMatrice<T>::MATsetNbRow(int l)
{
	if (l >= 0)
	{
		iNbRow = l;
	}
	else
	{
		//raise exception with exception class
	}
}

template <typename T>
inline void CMatrice<T>::MATsetNbColumn(int c)
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
inline int CMatrice<T>::MATgetNbRow(void)
{
	return iNbRow;
}

template <typename T>
inline int CMatrice<T>::MATgetNbColumn(void)
{
	return iNbColumn;
}

template <typename T>
inline T CMatrice<T>::MATgetElement(int i, int j)
{
	if (i >= 0 && i < MATgetNbColumn())
	{
		if (j >= 0 && j < MATgetNbRow())
		{
			return pVECmatrix.getElement(i)->getElement(j);
		}
	}
	else
	{
		//erreur
	}

}

template<typename T>
inline bool CMatrice<T>::MATsameDimension(CMatrice<T> &mat)
{
	if (MATgetNbColumn() == mat.MATgetNbColumn())
	{
		if (MATgetNbRow() == mat.MATgetNbRow())
		{
			return true;
		}
	}
	else
		return false;
}

template<typename T>
CMatrice<T> CMatrice<T>::operator+(CMatrice<T>& MATmatrice)
{

	if (MATsameDimension(MATmatrice))
	{
		CVector<CVector<T>*> tmpArray; 
		for (int count = 0; count < iNbColumn; ++count)
			tmpArray.push(new CVector<T>);

		for (int i = 0; i < iNbColumn; i++)
		{
			for (int j = 0; j < iNbRow; j++)
			{
				
				tmpArray.getElement(i)->push(MATgetElement(i, j) + MATmatrice.MATgetElement(i, j));
					
			}
		}
		CMatrice<T> MATresult(iNbColumn, iNbRow, tmpArray);
		
		//delete tous le tmp array
		
		return MATresult;

	}
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator-(CMatrice<T>& MATmatrice)
{
	if (MATsameDimension(MATmatrice))
	{
		CVector<CVector<T>*> tmpArray;
		for (int count = 0; count < iNbColumn; ++count)
			tmpArray.push(new CVector<T>);

		for (int i = 0; i < iNbColumn; i++)
		{
			for (int j = 0; j < iNbRow; j++)
			{

				tmpArray.getElement(i)->push(MATgetElement(i, j) - MATmatrice.MATgetElement(i, j));
			}
		}
		CMatrice<T> MATresult(iNbColumn, iNbRow, tmpArray);

		//delete le tmp array
		return MATresult;

	}
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator*(CMatrice<T>& MATmatrice)
{
	if (MATgetNbColumn()==MATmatrice.MATgetNbRow())
	{
		

		CVector<CVector<T>*> tmpArray;
		for (int count = 0; count < iNbRow; ++count)
			tmpArray.push(new CVector<T>);

		
		for (int i = 0; i < iNbRow; i++)
		{
			for (int j = 0; j < iNbRow; j++)
			{
				for (int k = 0; k < iNbColumn; k++)
				{
					if (k == 0)
					{
						T var1 = MATgetElement(k, i);
						T var2 = MATmatrice.MATgetElement(j, k);
						tmpArray.getElement(j)->push(var1 * var2);
						
					
					}
					else
					{
						T var1 = MATgetElement(k, i);
						T var2 = MATmatrice.MATgetElement(j, k);
						T var3 = var1 * var2 + tmpArray.getElement(j)->getElement(i) ;
						tmpArray.getElement(j)->modify(var3, i);
					
					}
					

				}
			}
		}
		CMatrice<T> MATresult(iNbRow, iNbRow, tmpArray);
		return MATresult;

	}
	else
	{
		std::cout << "erreur";
	}
	
}

template<typename T>
bool CMatrice<T>::operator==(CMatrice<T> MATmatrice)
{
	if (MATsameDimension)
	{
	
		//int iNbRow = MATgetNbRow();
		//int iNbColumn = MATgetNbColumn();
		for (int i = 0; i < iNbRow; i++)
		{
			for (int j = 0; j < iNbColumn; j++)
			{
				if (MATgetElement(i, j) != MATmatrice.MATgetElement(i, j))
				{
					return false;
				}
			}
		}
		return true;
	}
}

template<typename T>
bool CMatrice<T>::operator!=(CMatrice<T> MATmatrice)
{
	if (MATsameDimension)
	{

		//int iNbRow = MATgetNbRow();
		//int iNbColumn = MATgetNbColumn();
		for (int i = 0; i < iNbRow; i++)
		{
			for (int j = 0; j < iNbColumn; j++)
			{
				if (MATgetElement(i, j) != MATmatrice.MATgetElement(i, j))
				{
					return true;
				}
			}
		}
		return false;
	}
}

template<typename T>
void CMatrice<T>::MATmodify(int i, int j, T val)
{
	if (typeid(val) == typeid(pVECmatrix))
	{
		if (i >= 0 && i < MATgetNbColumn())
		{
			if (j >= 0 && j < MATgetNbRow())
			{
				pVECmatrix.getElement(i).modify(val, j);
			}
		}
	}
	else
	{
		//erreur
	}
}

template<typename T>
void CMatrice<T>::MATaddRow(int iPos, CVector<T> row)
{

	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray->push(new CVector<T>);


	for (int i = 0; i < iPos; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i));
		}
	}
	for (int j = 0; j < iNbColumn; j++)
	{
		tmpArray->getElement(j)->push(row.getElement(j));
	}
	for (int i = iPos+1; i < iNbRow+1; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i-1));
		}
	}
	MATsetNbRow(iNbRow + 1);
	pVECmatrix = *tmpArray;
	
}

template<typename T>
void CMatrice<T>::MATaddColumn(int iPos, CVector<T> Column)
{

	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn+1; ++count)
		tmpArray->push(new CVector<T>);

	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = 0; j < iPos; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i));
		}
	}
	for (int j = 0; j < iNbRow; j++)
	{
		tmpArray->getElement(iPos)->push(Column.getElement(j));
	}
	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = iPos+1; j < iNbColumn+1; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j-1, i));
		}
	}
	MATsetNbColumn(iNbColumn+1);
	pVECmatrix = *tmpArray;

}

template<typename T>
void CMatrice<T>::MATremoveRow(int iPos)
{
	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray->push(new CVector<T>);

	for (int i = 0; i < iPos; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i));
		}
	}
	for (int i = iPos; i < iNbRow; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i+1));
		}
	}
	MATsetNbRow(iNbRow - 1);
	pVECmatrix = *tmpArray;

}

template<typename T>
void CMatrice<T>::MATremoveColumn(int iPos)
{
	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn -1; ++count)
		tmpArray->push(new CVector<T>);

	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = 0; j < iPos; j++)
		{

			tmpArray->getElement(i)->push(MATgetElement(j, i));
		}
	}
	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = iPos+1; j < iNbColumn; j++)
		{

			tmpArray->getElement(j-1)->push(MATgetElement(j, i));
		}
	}
	MATsetNbColumn(iNbColumn - 1);
	pVECmatrix = *tmpArray;

}

template<typename T>
CMatrice<T> CMatrice<T>::MATtr(void)
{
	CVector<CVector<T>*> tmpArray;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray.push(new CVector<T>);


	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray.getElement(i)->push(MATgetElement(j, i));
		}
	}
	CMatrice<T>* MATresult = new CMatrice<T>(iNbRow, iNbColumn, tmpArray);
	return *MATresult;

}



template<typename T>
CMatrice<T>& CMatrice<T>::operator=(CMatrice<T> MATmatrice)
{

	iNbRow = MATmatrice.iNbRow;
	iNbColumn = MATmatrice.iNbColumn;

	for (int i = iNbColumn-1; i >= 0; i--)
	{
		free(pVECmatrix.getElement(i));
		pVECmatrix.pop();
	}
	MATsetNbColumn(0);
	MATsetNbRow(0);

	

	for (int count = 0; count < MATmatrice.MATgetNbColumn(); ++count)
		pVECmatrix.push(new CVector<int>);

	MATsetNbColumn(MATmatrice.MATgetNbColumn());
	MATsetNbRow(MATmatrice.MATgetNbRow());

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{
			pVECmatrix.getElement(i)->push(MATmatrice.MATgetElement(i,j));
			
		}
	}


	return *this;
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator*(T c)
{
	//int iNbRow = MATgetNbRow();
	//int iNbColumn = MATgetNbColumn();

	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray->push(new CVector<T>);

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{

			tmpArray->getElement(i)->push(MATgetElement(i, j)*c);
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, *tmpArray);
	return MATresult;
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator/(T c)
{
	
	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray->push(new CVector<T>);

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{
			tmpArray->getElement(i)->push(MATgetElement(i, j)/c);
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, *tmpArray);
	return MATresult;
}
