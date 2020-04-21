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
		CMatrice(int iL, int iC,T** ppMat); //Confort Constructor
		~CMatrice(void);//Destructor , maybe rework on it !!
		
		//Methodes utile
		void MATsetNbRow(int l);
		void MATsetNbColumn(int c);
		int MATgetNbRow(void);
		int MATgetNbColumn(void);
		T MATgetElement(int i, int j);//return an element of the matrix by knowing his position 
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
		// faire operateur [] qui retroune une collone ou un ligne a voir , faire =+ =- =* == != et =

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
CMatrice<T>::CMatrice(int iL, int iC, T** ppMat)
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
		int iC2 = MATmatrice.MATgetNbColumn();

		//pas bon il faut associer une matrice de la bonne taille
		T** tmpArray = new T*[iC]; // allocate an array of iC int pointers — these are our rows
		for (int count = 0; count < iC; ++count)
			tmpArray[count] = new T[iL]; // these are our columns

		//revoir la methode de calcul car Mat3*2 * MAt2*3 marche pas bien
		for (int i = 0; i < iL; i++)
		{
			for (int j = 0; j < iC2; j++)
			{
				for (int k = 0; k < iC; k++)
				{
					if (k == 0)
					{
						tmpArray[i][j] = MATgetElement(i, k) * MATmatrice.MATgetElement(k, j);
					}
					else
					{
						tmpArray[i][j] += MATgetElement(i, k) * MATmatrice.MATgetElement(k, j);
					}
					

				}
			}
		}
		CMatrice<T>* MATresult = new CMatrice<T>(iL, iC, tmpArray);
		return *MATresult;

	}
	
}



