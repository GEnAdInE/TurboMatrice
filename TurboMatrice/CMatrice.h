#include "CVECTOR.h"
#include "CSTRING.h"
#include "CPARSER.h"


template <class T> class CMatrice  : private CVector<T>
{
	private:
		
		unsigned int iNbRow;
		unsigned int iNbColumn;
		CVector<CVector<T>*> VECpVECmatrix;


	public:
		
		//constructor and destructor
		CMatrice(void); //default constructor
		CMatrice(const CMatrice<T>& MATmat);//Copy construcor 
		CMatrice(const CParser& PARparser);  //constructor using parser
		CMatrice(unsigned int nNbColumn, unsigned int nNbRow, CVector<CVector<T>*> VECpVECmat); //Confort Constructor
		~CMatrice(void);//Destructor
		
		//Manipulation of the matrix
		void MATsetNbRow(unsigned int nRow);
		void MATsetNbColumn(unsigned int nColumn);
		unsigned int MATgetNbRow(void);
		unsigned int MATgetNbColumn(void);
		T MATgetElement(unsigned int nIteratorColumn, unsigned int nIteratorRow);//return an element of the matrix (column,Line)
		void MATmodify(unsigned int nIteratorColumn, unsigned int nIteratorRow, T value);// pas besoin
		void MATaddRow(unsigned int nPos, CVector<T> VECrow);
		void MATaddColumn(unsigned int nPos, CVector<T> VECcolumn);
		void MATremoveRow(unsigned int nPos);
		void MATremoveColumn(unsigned int nPos);


		bool MATsameDimension(CMatrice<T>& MATmatrice); //test if the matrix have the same size
			
		//note for the user : if you use an operator with a custom object make sure to have a correctly devlopp your operator , or create your own function
		//Operator between Matrix
		CMatrice<T> operator+(CMatrice<T>& MATmatrice);
		CMatrice<T> operator-(CMatrice<T>& MATmatrice);
		CMatrice<T> operator*(CMatrice<T>& MATmatrice);
		CMatrice<T>& operator+=(CMatrice<T>& MATmatrice);
		CMatrice<T>& operator-=(CMatrice<T>& MATmatrice);
		CMatrice<T>& operator*=(CMatrice<T>& MATmatrice);
		

		//Operator with scalaire
		CMatrice<T> operator*(T c);
		CMatrice<T> operator/(T c);
		CMatrice<T>& operator*=(T c);
		CMatrice<T>& operator/=(T c);
		

		//Other operation
		//T* operator[](unsigned int iIterator); // maybe later if we have time
		CMatrice<T>& operator=(CMatrice<T> MATmatrice);
		bool operator==(CMatrice<T> MATmatrice);
		bool operator!=(CMatrice<T> MATmatrice);

		//Matrix specific calculation
		CMatrice<T> MATtr(void); //transpos�
		

};

/**
 * @brief Default constructor of the class CMatrice
 * 
 */
template <class T>
inline CMatrice<T>::CMatrice(void)
{
	iNbRow = 0;
	iNbColumn = 0;
	
}

/**
 * @brief Copy Constructor of the class CMatrice
 * 
 * @param mat matrice to be copied
 */
template <class T>
CMatrice<T>::CMatrice(const CMatrice<T>& MATmat)
{
	nNbRow = MATmat.nNbRow;
	nNbColumn = MATmat.nNbColumn;
	if (nNbRow >= 0 && nNbColumn >= 0)
	{
		for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
			VECpVECmatrix.VECpush(new CVector<T>);

		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
		{
			for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
			{
				VECpVECmatrix.VECgetElement(nIteratorColumn)->VECpush(MATmat.VECpVECmatrix.VECgetElement(nIteratorColumn)->VECgetElement(nIteratorRow));
			}
		}
	}

}

/**
 * @brief Confort constructor of the class CMatrice
 * 
 * @throw check if the argument are of the right size to generate a matrix
 * @param iNumberColumn number of Column
 * @param iNumberbRow number of Row
 * @param pMat the 2D Vector you want to be your matrix
 * @example CMatrice<TYPE>(2,2,Array)
 * the array need to be a 2d Vector create like so :
 * CVector<CVector<double>*> pVector; 	
 *	pVector.push(new CVector<double>{1,2}); //will be column 1
 *	pVector.push(new CVector<double>{ 3,4 }); //will be column 3 
 */
template <class T>
CMatrice<T>::CMatrice(unsigned int iNumberColumn, unsigned int iNumberbRow, CVector<CVector<T>*> pMat)
{
	try
	{
		if (iNumberColumn<= 0 || iNumberbRow <= 0 )throw (const char *)"MATRIX size ERROR: size of matrix can't be equal or inferior to 0";
		if (iNumberColumn != pMat.size() && iNumberbRow != pMat.getElement(0)->size())throw (const char *)"MATRIX size ERROR: size of your Vectors need to be the same as the size of the matrix you want to create"; //we can create a matrix that cut the value of a bigger array
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	iNbColumn = iNumberColumn;
	iNbRow = iNumberbRow;
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

/**
 * @brief Destructor of the class CMatrice
 * 
 */
template <class T>
CMatrice<T>::~CMatrice(void)
{
	
	//faire quelque chose pour les fuites memoire ici du style :  delete[] VECpVECmatrix.getelement(i)
	
	
	
}

/**
 * @brief Set the number of row of a matrix
 * 
 * 
 * @param iNumberRow number of row 
 */
template <class T>
inline void CMatrice<T>::MATsetNbRow(unsigned int iNumberRow)
{
	try
	{
		if (iNumberRow < 0) throw (const char *)"SIZE ERROR: matrix row size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	iNbRow = iNumberRow;
}

/**
 * @brief Set the number of column of a matrix
 * 
 * @param iNumberColumn number of column
 */
template <class T>
inline void CMatrice<T>::MATsetNbColumn(unsigned int iNumberColumn)
{
	try
	{
		if (iNumberColumn < 0) throw (const char *)"SIZE ERROR: matrix Column size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	iNbColumn = iNumberColumn;
}

/**
 * @brief Get the number of row from the matrix
 * 
 *
 * @return unsigned int 
 */
template <class T>
inline unsigned int CMatrice<T>::MATgetNbRow(void)
{
	return iNbRow;
}

/**
 * @brief Get the number of Column from the matrix 
 * 
 * @return unsigned int 
 */
template <class T>
inline unsigned int CMatrice<T>::MATgetNbColumn(void)
{
	return iNbColumn;
}

/**
 * @brief allow you to get the value of an element from the matrix by know is position
 * 
 * @param iIteratorColumn column of the element
 * @param iTeratorRow row of the element
 * @return T value of the element
 */
template <class T>
inline T CMatrice<T>::MATgetElement(unsigned int iIteratorColumn, unsigned int iTeratorRow)
{
	try
	{
		if (iIteratorColumn < 0 || iIteratorColumn >= MATgetNbColumn()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (iIteratorColumn)";
		if (iTeratorRow < 0 || iTeratorRow >= MATgetNbRow()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (iTeratorRow)";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return NULL;
	}
	return VECpVECmatrix.getElement(iIteratorColumn)->getElement(iTeratorRow);
}

/**
 * @brief check if the matrix are of the same size
 * 
 * @param mat matrice to compare
 * @return true 
 * @return false 
 */
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

/**
 * @brief operator + to allow addition between matrix
 * 
 * @param MATmatrice 
 * @return CMatrice<T> return a new matrix with the result of the addition
 */
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

	//need to empty tmpArray to prevent memory leak
	
	return MATresult;
}

/**
 * @brief operator - to allow substraction between matrix
 * 
 * @param MATmatrice 
 * @return CMatrice<T> return a new matrix with the result of the substraction
 */
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

	//need to empty tmpArray to prevent memory leak

	return MATresult;
}

/**
 * @brief Multiplication of 2 matrix
 * @throw to multiply matrix matrix1 need to have the samne number of column than the matrix2 have column
 * @param MATmatrice 
 * @return CMatrice<T> return a new matrix with the result of the operation
 */
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
				if (iIteratorAlternativ == 0) //the tmpArray is empty at first so we can't do an equivalent of =+ we need to assign the first element first
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

/**
 * @brief operator += same as the operator + but return the value on the current matrix
 * 
 * @param MATmatrice 
 * @return CMatrice<T>& 
 */
template<class T>
inline CMatrice<T>& CMatrice<T>::operator+=(CMatrice<T>& MATmatrice)
{
	*this = this->operator+(MATmatrice);
	return *this;
}

/**
 * @brief operator -= same as the operator - but return the value on the current matrix
 * 
 * @param MATmatrice 
 * @return CMatrice<T>& 
 */
template<class T>
inline CMatrice<T>& CMatrice<T>::operator-=(CMatrice<T>& MATmatrice)
{
	*this = this->operator-(MATmatrice);
	return *this;
}

/**
 * @brief operator *= same as the operator * but return the value on the current matrix
 * 
 * @param MATmatrice 
 * @return CMatrice<T>& 
 */
template<class T>
inline CMatrice<T>& CMatrice<T>::operator*=(CMatrice<T>& MATmatrice)
{
	*this = this->operator*(MATmatrice);
	return *this;
}


/**
 * @brief operator *= same as the operator * but return the value on the current matrix
 *  
 * @param c 
 * @return CMatrice<T>& 
 */
template<class T>
inline CMatrice<T>& CMatrice<T>::operator*=(T c)
{
	*this = this->operator*(c);
	return *this;
}
/**
 * @brief operator /= same as the operator * but return the value on the current matrix
 * 
 * @param c 
 * @return CMatrice<T>& 
 */
template<class T>
inline CMatrice<T>& CMatrice<T>::operator/=(T c)
{
	*this = this->operator/(c);
	return *this;
}

/**
 * @brief comparator between 2 matrix
 * 
 * @param MATmatrice 
 * @return true 
 * @return false 
 */
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

/**
 * @brief compartor for difference between 2 matrix
 * 
 * @param MATmatrice 
 * @return true 
 * @return false 
 */
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

/**
 * @brief Modificator of an element from the matrix by know his position
 * 
 * @throw make sure that you modify a value inside the matrix
 * @param iIteratorColumn 
 * @param iTeratorRow 
 * @param val 
 */
template<class T>
void CMatrice<T>::MATmodify(unsigned int iIteratorColumn, unsigned int iTeratorRow, T val)
{
	try
	{
		if (iIteratorColumn < 0 || iIteratorColumn >= MATgetNbColumn())throw (const char *)"Matrix modify: can't modify a value out of Column";
		if (iTeratorRow < 0 || iTeratorRow >= MATgetNbRow())throw (const char *)"Matrix modify: can't modify a value out of Row";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	VECpVECmatrix.getElement(iIteratorColumn)->modify(val, iTeratorRow);
}

/**
 * @brief allow you to add a row to your matrix 
 * 
 * @throw make sure to enter correct position and row
 * @param iPos position where you want to add your row 
 * @param row you row must be a 1 dimension CVector of a size = to the number of column
 */
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
	//need to empty VECpVECmatrix before assigning it the new tmpArray;
}

/**
 * @brief allow you to add Column to your matrix
 * 
 * @throw make sure to enter correct position and Column
 * @param iPos position where you want to add your Column
 * @param Column you Column must be a 1 dimension CVector of a size = to the number of row
 */
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
	//need to empty VECpVECmatrix before assigning it the new tmpArray;
}

/**
 * @brief allow you to remove row from your matrix
 * 
 * @throw make sure to enter correct position
 * @param iPos position of the row to delete
 */
template<class T>
void CMatrice<T>::MATremoveRow(unsigned int iPos)
{
	//could have had a VECdelete(int iPos) function to CVector to make it easier;
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
	//need to empty VECpVECmatrix before assigning it the new tmpArray;
}

/**
 * @brief allow you to remove a column
 * @throw make sur to enter correct position
 * @param iPos position of the column you want to remove
 */
template<class T>
void CMatrice<T>::MATremoveColumn(unsigned int iPos)
{
	//could have had a VECdelete(int iPos) function to CVector to make it easier;
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
	//need to empty VECpVECmatrix before assigning it the new tmpArray;
}


/**
 * @brief Allow you to transpose your matrix
 * 
 * @return CMatrice<T> return the transposed matrix
 */
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
	//memory leak from tmpArray
	return *MATresult;
}

/**
 * @brief assignation operator , change the matrix value by a new one
 * 
 * @param MATmatrice 
 * @return CMatrice<T>& 
 */
template<class T>
CMatrice<T>& CMatrice<T>::operator=(CMatrice<T> MATmatrice)
{
	//need to empty the current matrix before assigning new value
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
/**
 * @brief operator * with a number
 * 
 * @param c 
 * @return CMatrice<T> 
 */
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
	//memory leak from tmpArary
	return MATresult;
}

/**
 * @brief operator / with a number
 * 
 * @throw can't divide by 0
 * @param c 
 * @return CMatrice<T> 
 */
template<class T>
CMatrice<T> CMatrice<T>::operator/(T c)
{
	try
	{
		if (c == 0) throw (const char *)"Operator / error: can't divide by 0";
		
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
	//memory leak from tmpArray
	return MATresult;
}


