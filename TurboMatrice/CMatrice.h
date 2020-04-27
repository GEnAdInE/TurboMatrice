#include "CVector.h"


//attention fuite memoire a tout les endroit ou je fais des VECpVECtmpArray

template <class T> class CMatrice  : private CVector<T>
{
	private:
		
		unsigned int iNbRow;
		unsigned int iNbColumn;
		CVector<CVector<T>*> VECpVECmatrix;


	public:
		
		//constructor and destructor
		CMatrice(void); //default constructor
		CMatrice(const CMatrice<T>& mat);//Copy construcor !not finished
		CMatrice(unsigned int iNbColumn, unsigned int iNbRow, CVector<CVector<T>*> pVECmat); //Confort Constructor
		~CMatrice(void);//Destructor , maybe rework on it !!
		
		//Methodes utile
		void MATsetNbRow(unsigned int iRow);
		void MATsetNbColumn(unsigned int iColumn);
		unsigned int MATgetNbRow(void);
		unsigned int MATgetNbColumn(void);
		T MATgetElement(unsigned int iIteratorColumn, unsigned int iTeratorRow);//return an element of the matrix (column,Line)
		void MATmodify(unsigned int iIteratorColumn, unsigned int iTeratorRow, T value);// pas besoin
		void MATaddRow(unsigned int iPos, CVector<T> row);		
		void MATaddColumn(unsigned int iPos,CVector<T> Column);
		void MATremoveRow(unsigned int iPos);
		void MATremoveColumn(unsigned int iPos);


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
		CMatrice<T>& operator*=(T c);
		CMatrice<T>& operator/=(T c);
		

		//Autre operation
		T* operator[](unsigned int iIterator); //ca ou on garde MATgetElement , au choix !
		CMatrice<T>& operator=(CMatrice<T> MATmatrice);
		bool operator==(CMatrice<T> MATmatrice);
		bool operator!=(CMatrice<T> MATmatrice);
		CMatrice<T> MATtr(void); //transposé
		

};

template <class T>
CMatrice<T>::CMatrice(void)
{
	iNbRow = 0;
	iNbColumn = 0;
	
}

template <class T>
CMatrice<T>::CMatrice(const CMatrice<T>& mat)
{

	

	iNbRow = mat.iNbRow;
	iNbColumn = mat.iNbColumn;
	if (iNbRow >= 0 && iNbColumn >= 0)
	{
		for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
			VECpVECmatrix.push(new CVector<T>);

		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
		{
			for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
			{
				VECpVECmatrix.getElement(iIteratorColumn)->push(mat.VECpVECmatrix.getElement(iIteratorColumn)->getElement(iIteratorRow));
			}
		}
	}
	
	
}

template <class T>
CMatrice<T>::CMatrice(unsigned int iIteratorColumn, unsigned int iTeratorRow, CVector<CVector<T>*> pMat)
{
	try
	{
		if (iIteratorColumn <= 0 || iTeratorRow <= 0 )throw (const char *)"MATRIX size ERROR: size of matrix can't be equal or inferior to 0";
		if (iIteratorColumn != pMat.size() && iTeratorRow != pMat.getElement(0)->size())throw (const char *)"MATRIX size ERROR: size of your Vectors need to be the same as the size of the matrix you want to create"; //we can create a matrix that cut the value of a bigger array
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	 iNbColumn = iIteratorColumn;
	 iNbRow = iTeratorRow;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECmatrix.push(new CVector<T>);

	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{
			VECpVECmatrix.getElement(iIteratorColumn)->push(pMat.getElement(iIteratorColumn)->getElement(iIteratorRow));
		}
	}

}

template <class T>
CMatrice<T>::~CMatrice(void)
{
	
	//faire quelque chose pour les fuites memoire ici du style :  delete[] VECpVECmatrix.getelement(i)
	
	
	
}

template <class T>
inline void CMatrice<T>::MATsetNbRow(unsigned int iTeratorRow)
{


	try
	{
		if (iTeratorRow < 0) throw (const char *)"SIZE ERROR: matrix row size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	iNbRow = iTeratorRow;
	
	
}

template <class T>
inline void CMatrice<T>::MATsetNbColumn(unsigned int iIteratorColumn)
{
	try
	{
		if (iIteratorColumn < 0) throw (const char *)"SIZE ERROR: matrix Column size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
		iNbColumn = iIteratorColumn;

}

template <class T>
inline unsigned int CMatrice<T>::MATgetNbRow(void)
{
	return iNbRow;
}

template <class T>
inline unsigned int CMatrice<T>::MATgetNbColumn(void)
{
	return iNbColumn;
}

template <class T>
inline T CMatrice<T>::MATgetElement(unsigned int iIteratorColumn, unsigned int iTeratorRow)
{

	try
	{
		if (iIteratorColumn < 0 || iIteratorColumn > MATgetNbColumn()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (iIteratorColumn)";
		if (iTeratorRow < 0 || iTeratorRow > MATgetNbRow()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (iTeratorRow)";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return NULL;
	}
	return VECpVECmatrix.getElement(iIteratorColumn)->getElement(iTeratorRow);
	

}

template<class T>
inline bool CMatrice<T>::MATsameDimension(CMatrice<T> &mat)
{
	if (MATgetNbColumn() == mat.MATgetNbColumn())
	{
		if (MATgetNbRow() == mat.MATgetNbRow())
		{
			return true;
		}
	}
	return false;
}

template<class T>
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
	
	CVector<CVector<T>*> VECpVECtmpArray; 
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray.push(new CVector<T>);

	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{
				
			VECpVECtmpArray.getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow) + MATmatrice.MATgetElement(iIteratorColumn, iIteratorRow));
					
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, VECpVECtmpArray);

	//faire quelque chose pour les fuites memoire ici
	
	return MATresult;

	
	
}

template<class T>
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

	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray.push(new CVector<T>);

	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{

			VECpVECtmpArray.getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow) - MATmatrice.MATgetElement(iIteratorColumn, iIteratorRow));
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, VECpVECtmpArray);

	//faire quelque chose pour les fuites memoire ici
	return MATresult;

	
	
}

template<class T>
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
	
	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int iCount = 0; iCount < iNbRow; ++iCount)
		VECpVECtmpArray.push(new CVector<T>);

		
	for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbRow; iIteratorColumn++)
		{
			for (unsigned int iIteratorAlternativ = 0; iIteratorAlternativ < iNbColumn; iIteratorAlternativ++)
			{
				if (iIteratorAlternativ == 0)
				{
					T var1 = MATgetElement(iIteratorAlternativ, iIteratorRow);
					T var2 = MATmatrice.MATgetElement(iIteratorColumn, iIteratorAlternativ);
					VECpVECtmpArray.getElement(iIteratorColumn)->push(var1 * var2);
						
					
				}
				else
				{
					T var1 = MATgetElement(iIteratorAlternativ, iIteratorRow);
					T var2 = MATmatrice.MATgetElement(iIteratorColumn, iIteratorAlternativ);
					T var3 = var1 * var2 + VECpVECtmpArray.getElement(iIteratorColumn)->getElement(iIteratorRow) ;
					VECpVECtmpArray.getElement(iIteratorColumn)->modify(var3, iIteratorRow);
					
				}
					

			}
		}
	}
	CMatrice<T> MATresult(iNbRow, iNbRow, VECpVECtmpArray);

	//faire quelque chose pour les fuites memoire ici

	return MATresult;

	
	
}

template<class T>
inline CMatrice<T>& CMatrice<T>::operator+=(CMatrice<T>& MATmatrice)
{
	*this = this->operator+(MATmatrice);
	return *this;
}

template<class T>
inline CMatrice<T>& CMatrice<T>::operator-=(CMatrice<T>& MATmatrice)
{
	*this = this->operator-(MATmatrice);
	return *this;
}

template<class T>
inline CMatrice<T>& CMatrice<T>::operator*=(CMatrice<T>& MATmatrice)
{
	*this = this->operator*(MATmatrice);
	return *this;
}

template<class T>
inline CMatrice<T>& CMatrice<T>::operator*=(T c)
{
	*this = this->operator*(c);
	return *this;
}
template<class T>
inline CMatrice<T>& CMatrice<T>::operator/=(T c)
{
	*this = this->operator/(c);
	return *this;
}


template<class T>
bool CMatrice<T>::operator==(CMatrice<T> MATmatrice)
{
	if (MATsameDimension)
	{

		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{
			for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
			{
				if (MATgetElement(iIteratorColumn, iIteratorRow) != MATmatrice.MATgetElement(iIteratorColumn, iIteratorRow))
				{
					return false;
				}
			}
		}
		return true;
	}
	return false;
}

template<class T>
bool CMatrice<T>::operator!=(CMatrice<T> MATmatrice)
{
	if (MATsameDimension)
	{

		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{
			for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
			{
				if (MATgetElement(iIteratorColumn, iIteratorRow) != MATmatrice.MATgetElement(iIteratorColumn, iIteratorRow))
				{
					return true;
				}
			}
		}
		return false;
	}
	return true;
}

template<class T>
void CMatrice<T>::MATmodify(unsigned int iIteratorColumn, unsigned int iTeratorRow, T val)
{
	try
	{
		
		if (iIteratorColumn < 0 || iIteratorColumn >= MATgetNbColumn())throw (const char *)"Matrix modify: can't modify a value out of Column";
		if (iTeratorRow < 0 || iTeratorRow >= MATgetNbRow())throw (const char *)"Matrix modify: can't modify a value out of Row";
		//if (typeid(val) != typeid(MATgetElement(iIteratorRow,j))) throw (const char *)"Matrix modify: value need to be the same type of your matrix data";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	VECpVECmatrix.getElement(iIteratorColumn)->modify(val, iTeratorRow);
}

template<class T>
void CMatrice<T>::MATaddRow(unsigned int iPos, CVector<T> row)
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


	CVector<CVector<T>*> *VECpVECtmpArray = new CVector<CVector<T>*>;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray->push(new CVector<T>);


	for (unsigned int iIteratorRow = 0; iIteratorRow < iPos; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow));
		}
	}
	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		VECpVECtmpArray->getElement(iIteratorColumn)->push(row.getElement(iIteratorColumn));
	}
	for (unsigned int iIteratorRow = iPos + 1; iIteratorRow < iNbRow + 1; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow - 1));
		}
	}
	MATsetNbRow(iNbRow + 1);
	VECpVECmatrix = *VECpVECtmpArray;
	
	
}

template<class T>
void CMatrice<T>::MATaddColumn(unsigned int iPos, CVector<T> Column)
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

	CVector<CVector<T>*> *VECpVECtmpArray = new CVector<CVector<T>*>;
	for (unsigned int iCount = 0; iCount < iNbColumn + 1; ++iCount)
		VECpVECtmpArray->push(new CVector<T>);

	for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iPos; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow));
		}
	}
	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbRow; iIteratorColumn++)
	{
		VECpVECtmpArray->getElement(iPos)->push(Column.getElement(iIteratorColumn));
	}
	for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = iPos + 1; iIteratorColumn < iNbColumn + 1; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn - 1, iIteratorRow));
		}
	}
	MATsetNbColumn(iNbColumn + 1);
	VECpVECmatrix = *VECpVECtmpArray;

}

template<class T>
void CMatrice<T>::MATremoveRow(unsigned int iPos)
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


	CVector<CVector<T>*> *VECpVECtmpArray = new CVector<CVector<T>*>;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray->push(new CVector<T>);

	for (unsigned int iIteratorRow = 0; iIteratorRow < iPos; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow));
		}
	}
	for (unsigned int iIteratorRow = iPos; iIteratorRow < iNbRow-1; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow + 1));
		}
	}
	MATsetNbRow(iNbRow - 1);
	VECpVECmatrix = *VECpVECtmpArray;

}

template<class T>
void CMatrice<T>::MATremoveColumn(unsigned int iPos)
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

	CVector<CVector<T>*> *VECpVECtmpArray = new CVector<CVector<T>*>;
	for (unsigned int iCount = 0; iCount < iNbColumn - 1; ++iCount)
		VECpVECtmpArray->push(new CVector<T>);

	for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = 0; iIteratorColumn < iPos; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow));
		}
	}
	for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
	{
		for (unsigned int iIteratorColumn = iPos + 1; iIteratorColumn < iNbColumn; iIteratorColumn++)
		{

			VECpVECtmpArray->getElement(iIteratorColumn - 1)->push(MATgetElement(iIteratorColumn, iIteratorRow));
		}
	}
	MATsetNbColumn(iNbColumn - 1);
	VECpVECmatrix = *VECpVECtmpArray;



}

template<class T>
CMatrice<T> CMatrice<T>::MATtr(void)
{
	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray.push(new CVector<T>);


	for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbColumn; iIteratorRow++)
		{

			VECpVECtmpArray.getElement(iIteratorRow)->push(MATgetElement(iIteratorRow, iIteratorRow));
		}
	}
	CMatrice<T>* MATresult = new CMatrice<T>(iNbRow, iNbColumn, VECpVECtmpArray);
	//faire quelque chose pour les fuites memoire ici
	return *MATresult;

}



template<class T>
CMatrice<T>& CMatrice<T>::operator=(CMatrice<T> MATmatrice)
{

	if (VECpVECmatrix.getVectorElements() != NULL) {
		for (unsigned int iIteratorColumn = VECpVECmatrix.size()-1; iIteratorColumn >0; iIteratorColumn--)
		{
			if (VECpVECmatrix.getElement(iIteratorColumn) != NULL)
			{
				VECpVECmatrix.pop();
			
			}
			
		}
		VECpVECmatrix.pop();
	}
	
	
	for (unsigned int iCount = 0; iCount < MATmatrice.MATgetNbColumn(); ++iCount)
		VECpVECmatrix.push(new CVector<T>);

	MATsetNbColumn(MATmatrice.MATgetNbColumn());
	MATsetNbRow(MATmatrice.MATgetNbRow());

	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{
			VECpVECmatrix.getElement(iIteratorColumn)->push(MATmatrice.MATgetElement(iIteratorColumn,iIteratorRow));
			
		}
	}


	return *this;
	
}

template<class T>
CMatrice<T> CMatrice<T>::operator*(T c)
{


	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray.push(new CVector<T>);

	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{

			VECpVECtmpArray.getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow)*c);
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, VECpVECtmpArray);
	//faire quelque chose pour les fuites memoire ici
	return MATresult;
	
}

template<class T>
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
	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int iCount = 0; iCount < iNbColumn; ++iCount)
		VECpVECtmpArray.push(new CVector<T>);

	for (unsigned int iIteratorColumn = 0; iIteratorColumn < iNbColumn; iIteratorColumn++)
	{
		for (unsigned int iIteratorRow = 0; iIteratorRow < iNbRow; iIteratorRow++)
		{
			VECpVECtmpArray.getElement(iIteratorColumn)->push(MATgetElement(iIteratorColumn, iIteratorRow)/c);
		}
	}
	CMatrice<T> MATresult(iNbColumn, iNbRow, VECpVECtmpArray);
	//faire quelque chose pour les fuites memoire ici
	return MATresult;
}


