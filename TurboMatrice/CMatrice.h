#include "CVector.h"


//attention fuite memoire a tout les endroit ou je fais des tmpArray

template <typename T> class CMatrice  : private CVector<T>
{
	private:
		
		int iNbRow;
		int iNbColumn;
		CVector<CVector<T>*> pVECmatrix;

		void VECfreeTmpArray(CVector<CVector<T>*> VECVEC2D, int iNbColumn);

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
		T MATgetElement(int i, int j);//return an element of the matrix (column,Line)
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

template<typename T>
 void CMatrice<T>::VECfreeTmpArray(CVector<CVector<T>*> VECVEC2D, int iNbColumn)
{

	if (VECVEC2D.getVectorElements() != NULL) {
		for (int i = iNbColumn - 1; i >= 0; i--)
		{
			if (VECVEC2D.getElement(i) != NULL)
			{
				free(VECVEC2D.getElement(i));
				VECVEC2D.pop();
			}
		}
	}
	
	
	

}

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
	if (iNbRow >= 0 && iNbColumn >= 0)
	{
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
	
	
}

template <typename T>
CMatrice<T>::CMatrice(int iC, int iR, CVector<CVector<T>*> pMat)
{
	try
	{
		if (iC <= 0 || iR <= 0 )throw (const char *)"MATRIX size ERROR: size of matrix can't be equal or inferior to 0";
		if (iC != pMat.size() && iR != pMat.getElement(0)->size())throw (const char *)"MATRIX size ERROR: size of your Vectors need to be the same as the size of the matrix you want to create"; //we can create a matrix that cut the value of a bigger array
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	 iNbColumn = iC;
	 iNbRow = iR;
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
	
		
	}
	
}

template <typename T>
inline void CMatrice<T>::MATsetNbRow(int iR)
{


	try
	{
		if (iR < 0) throw (const char *)"SIZE ERROR: matrix row size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	iNbRow = iR;
	
	
}

template <typename T>
inline void CMatrice<T>::MATsetNbColumn(int iC)
{
	try
	{
		if (iC < 0) throw (const char *)"SIZE ERROR: matrix Column size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
		iNbColumn = iC;

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
inline T CMatrice<T>::MATgetElement(int iC, int iL)
{

	try
	{
		if (iC < 0 || iC > MATgetNbColumn()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (iC)";
		if (iL < 0 || iL > MATgetNbRow()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (iR)";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return NULL;
	}
	return pVECmatrix.getElement(iC)->getElement(iL);
	

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
	try
	{
		if (!MATsameDimension(MATmatrice)) throw (const char *)"Matrix Addition error: your matrix must have the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CMatrice<T>();
	}
	
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
	//VECfreeTmpArray(tmpArray, iNbColumn);
	return MATresult;

	
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator-(CMatrice<T>& MATmatrice)
{
	try
	{
		if (!MATsameDimension(MATmatrice)) throw (const char *)"Matrix Soustraction error: your matrix must have the same size";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CMatrice<T>();
	}

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
	//VECfreeTmpArray(tmpArray, iNbColumn);
	//delete le tmp array
	return MATresult;

	
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator*(CMatrice<T>& MATmatrice)
{

	try
	{
		if (MATgetNbColumn() != MATmatrice.MATgetNbRow()) throw (const char *)"Matrix Multiplication error: MATRIX1 number of column must be equals to MATRIX2 number of row";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CMatrice<T>();
	}
	
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
	VECfreeTmpArray(tmpArray, MATresult.MATgetNbColumn());
	return MATresult;

	
	
}

template<typename T>
CMatrice<T>& CMatrice<T>::operator+=(CMatrice<T>& MATmatrice)
{
	return *this;
	//return *(this + *MATmatrice);
}

template<typename T>
bool CMatrice<T>::operator==(CMatrice<T> MATmatrice)
{
	if (MATsameDimension)
	{
	
		
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
	return false;
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
	return true;
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
				pVECmatrix.getElement(i)->modify(val, j);
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
	try
	{
		if (iPos<0) throw (const char *)"AddRow error: can't add under 0";
		if (iPos> (iNbRow+1)) throw (const char *)"AddRow error: can't be more than the nb of row+1";
		if (row.size() !=  iNbColumn)throw (const char *)"AddRow error: please provide a Vector with the same nb of Column";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}


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
	for (int i = iPos + 1; i < iNbRow + 1; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i - 1));
		}
	}
	MATsetNbRow(iNbRow + 1);
	pVECmatrix = *tmpArray;
	
	
}

template<typename T>
void CMatrice<T>::MATaddColumn(int iPos, CVector<T> Column)
{

	try
	{
		if (iPos < 0) throw (const char *)"AddColumn error: can't add under 0";
		if (iPos > (iNbColumn + 1)) throw (const char *)"AddColumn error: can't be more than the nb of Column+1";
		if (Column.size() != iNbRow)throw (const char *)"AddColumn error: please provide a Vector with the same nb of row";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn + 1; ++count)
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
		for (int j = iPos + 1; j < iNbColumn + 1; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j - 1, i));
		}
	}
	MATsetNbColumn(iNbColumn + 1);
	pVECmatrix = *tmpArray;

}

template<typename T>
void CMatrice<T>::MATremoveRow(int iPos)
{
	try
	{
		if (iPos < 0) throw (const char *)"RemoveRow error: can't remove under 0";
		if (iPos > (iNbRow)) throw (const char *)"RemoveRow error: iPos can't be more than the nb of row";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}


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
	for (int i = iPos; i < iNbRow-1; i++)
	{
		for (int j = 0; j < iNbColumn; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i + 1));
		}
	}
	MATsetNbRow(iNbRow - 1);
	pVECmatrix = *tmpArray;

}

template<typename T>
void CMatrice<T>::MATremoveColumn(int iPos)
{

	try
	{
		if (iPos < 0) throw (const char *)"RemoveColumn error: can't remove under 0";
		if (iPos > (iNbColumn)) throw (const char *)"RemoveColumn error: iPos can't be more than the nb of Column";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CVector<CVector<T>*> *tmpArray = new CVector<CVector<T>*>;
	for (int count = 0; count < iNbColumn - 1; ++count)
		tmpArray->push(new CVector<T>);

	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = 0; j < iPos; j++)
		{

			tmpArray->getElement(j)->push(MATgetElement(j, i));
		}
	}
	for (int i = 0; i < iNbRow; i++)
	{
		for (int j = iPos + 1; j < iNbColumn; j++)
		{

			tmpArray->getElement(j - 1)->push(MATgetElement(j, i));
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
	VECfreeTmpArray(tmpArray, iNbColumn);
	return *MATresult;

}



template<typename T>
CMatrice<T>& CMatrice<T>::operator=(CMatrice<T> MATmatrice)
{

	if (pVECmatrix.getVectorElements() != NULL) {
		for (int i = iNbColumn - 1; i >= 0; i--)
		{
			if (pVECmatrix.getElement(i) != NULL)
			{
				free(pVECmatrix.getElement(i));
				pVECmatrix.pop();
			}
		}
	}
	
	
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


	CVector<CVector<T>*> tmpArray;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray.push(new CVector<T>);

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{

			tmpArray.getElement(i)->push(MATgetElement(i, j)*c);
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, tmpArray);
	VECfreeTmpArray(tmpArray, iNbColumn);
	return MATresult;
	
}

template<typename T>
CMatrice<T> CMatrice<T>::operator/(T c)
{
	try
	{
		if (c == 0) throw (const char *)"Operator / error: can't divide by under 0";
		
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CMatrice<T>();
	}
	CVector<CVector<T>*> tmpArray;
	for (int count = 0; count < iNbColumn; ++count)
		tmpArray.push(new CVector<T>);

	for (int i = 0; i < iNbColumn; i++)
	{
		for (int j = 0; j < iNbRow; j++)
		{
			tmpArray.getElement(i)->push(MATgetElement(i, j)/c);
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, tmpArray);
	VECfreeTmpArray(tmpArray, iNbColumn);
	return MATresult;
}
