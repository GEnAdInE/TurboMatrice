#include <iostream>



template <typename T> class CMatrice 
{
	private:
		
		int iNbRow;
		int iNbColumn;
		T** ppMatrix;

	public:
		
		//constructor and destructor
		CMatrice(void); //default constructor
		CMatrice(CMatrice<T>& mat);//Copy construcor !not finished
		CMatrice(int iC, int iL,T** ppMat); //Confort Constructor
		~CMatrice(void);//Destructor , maybe rework on it !!
		
		//Methodes utile
		void MATsetNbRow(int l);
		void MATsetNbColumn(int c);
		int MATgetNbRow(void);
		int MATgetNbColumn(void);
		T MATgetElement(int i, int j);//return an element of the matrix by knowing his position 
		void MATmodify(int i, int j, T value);
		void MATaddRow(int iPos,T* row);
		void MATaddColumn(int iPos,T* Column);
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
		CMatrice<T> operator[](int iRow);
		CMatrice<T>& operator=(CMatrice<T> MATmatrice);
		bool operator==(CMatrice<T> MATmatrice);
		bool operator!=(CMatrice<T> MATmatrice);
		CMatrice<T> MATtr(void); //transposé
		CMatrice<T> MATinv(void); //inverse

};

template <typename T>
CMatrice<T>::CMatrice(void)
{
	iNbRow = 0;
	iNbColumn = 0;
	ppMatrix = NULL;
}

template <typename T>
CMatrice<T>::CMatrice(CMatrice<T>& mat)
{
	iNbRow = mat.MATgetNbRow();
	iNbColumn = mat.MATgetNbColumn();
	ppMatrix = new T*[iNbColumn]; // allocate an array of iC int pointers — these are our columns 

	for (int count = 0; count < iNbColumn; ++count)
		ppMatrix[count] = new T[iNbRow]; // these are our rows

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{
			ppMatrix[i][j] = mat.ppMatrix[i][j];
		}
	}
	
}

template <typename T>
CMatrice<T>::CMatrice(int iC, int iL, T** ppMat)
{
	iNbRow = iL;
	iNbColumn = iC;
	ppMatrix = new T*[iC]; // allocate an array of iC int pointers — these are our columns 

	for (int count = 0; count < iC; ++count)
		ppMatrix[count] = new T[iL]; // these are our rows

	for (int i = 0; i < iC; i++)
	{
		for (int j = 0; j < iL; j++)
		{
			ppMatrix[i][j] = ppMat[i][j];
		}
	}

}

template <typename T>
CMatrice<T>::~CMatrice(void)
{
	if (ppMatrix == NULL)
	{
		if (iNbRow == 0 && iNbColumn == 0)
		{
			free(this);
		}

	}
}

template <typename T>
void CMatrice<T>::MATsetNbRow(int l)
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
void CMatrice<T>::MATsetNbColumn(int c)
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
int CMatrice<T>::MATgetNbRow(void)
{
	return iNbRow;
}

template <typename T>
int CMatrice<T>::MATgetNbColumn(void)
{
	return iNbColumn;
}

template <typename T>
T CMatrice<T>::MATgetElement(int i, int j)
{
	if (i >= 0 && i < MATgetNbColumn())
	{
		if (j >= 0 && j < MATgetNbRow())
		{
			return ppMatrix[i][j];
		}
	}
	else
	{
		//erreur
	}

}

template<typename T>
bool CMatrice<T>::MATsameDimension(CMatrice<T> &mat)
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
		int iL = MATgetNbRow();
		int iC = MATgetNbColumn();

		T** tmpArray = new T*[iC]; // allocate an array of iC int pointers — these are our rows
		for (int count = 0; count < iC; ++count)
			tmpArray[count] = new T[iL]; // these are our columns

		for (int i = 0; i < iC; i++)
		{
			for (int j = 0; j < iL; j++)
			{
				tmpArray[i][j] = MATgetElement(i, j) + MATmatrice.MATgetElement(i, j);
			}
		}
		CMatrice<T>* MATresult = new CMatrice<T>(iL, iC, tmpArray);
		return *MATresult;

	}
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator-(CMatrice<T>& MATmatrice)
{
	if (MATsameDimension(MATmatrice))
	{
		int iL = MATgetNbRow();
		int iC = MATgetNbColumn();

		T** tmpArray = new T*[iC]; // allocate an array of iC int pointers — these are our rows
		for (int count = 0; count < iC; ++count)
			tmpArray[count] = new T[iL]; // these are our columns

		for (int i = 0; i < iC; i++)
		{
			for (int j = 0; j < iL; j++)
			{

				tmpArray[i][j] = MATgetElement(i, j) - MATmatrice.MATgetElement(i, j);
			}
		}
		CMatrice<T>* MATresult = new CMatrice<T>(iL, iC, tmpArray);
		return *MATresult;

	}
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator*(CMatrice<T>& MATmatrice)
{
	if (MATgetNbColumn()==MATmatrice.MATgetNbRow())
	{
		int iL = MATgetNbRow();
		int iC = MATgetNbColumn();
	

		//matrice carré de la taille iC
		T** tmpArray = new T*[iL]; // allocate an array of iC int pointers — these are our rows
		for (int count = 0; count < iL; ++count)
			tmpArray[count] = new T[iL]; // these are our columns

		
		for (int i = 0; i < iL; i++)
		{
			for (int j = 0; j < iL; j++)
			{
				for (int k = 0; k < iC; k++)
				{
					if (k == 0)
					{
						T var1 = MATgetElement(k, i);
						T var2 = MATmatrice.MATgetElement(j, k);
						tmpArray[j][i] = var1 * var2;
						
					
					}
					else
					{
						T var1 = MATgetElement(k, i);
						T var2 = MATmatrice.MATgetElement(j, k);
						tmpArray[j][i] += var1 * var2 ;
					
					}
					

				}
			}
		}
		CMatrice<T>* MATresult = new CMatrice<T>(iL, iL, tmpArray);
		return *MATresult;

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
	
		int iL = MATgetNbRow();
		int iC = MATgetNbColumn();
		for (int i = 0; i < iL; i++)
		{
			for (int j = 0; j < iC; j++)
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

		int iL = MATgetNbRow();
		int iC = MATgetNbColumn();
		for (int i = 0; i < iL; i++)
		{
			for (int j = 0; j < iC; j++)
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
	if (typeid(val) == typeid(ppMatrix))
	{
		if (i >= 0 && i < MATgetNbColumn())
		{
			if (j >= 0 && j < MATgetNbRow())
			{
				ppMatrix[i][j] = val;
			}
		}
	}
	else
	{
		//erreur
	}
}

template<typename T>
CMatrice<T> CMatrice<T>::MATinv(void)
{
	if (MATgetNbColumn() == MATgetNbRow())
	{

	}
	else
	{
		//pas matrice carré
	}
	
}

template<typename T>
CMatrice<T> CMatrice<T>::MATtr(void)
{
	int iL = MATgetNbRow();
	int iC = MATgetNbColumn();


	//matrice carré de la taille iC
	T** tmpArray = new T*[iL]; // allocate an array of iC int pointers —
	for (int count = 0; count < iL; ++count)
		tmpArray[count] = new T[iC]; 

	for (int i = 0; i < iL; i++)
	{
		for (int j = 0; j < iC; j++)
		{

			tmpArray[i][j] = MATgetElement(j, i);
		}
	}
	CMatrice<T>* MATresult = new CMatrice<T>(iL, iC, tmpArray);
	return *MATresult;

}