#include "CVECTOR.h"
#include "CSTRING.h"
#include "CPARSER.h"

template <class T> class CMatrice : private CVector<T>
{
private:

	unsigned int nNbRow;
	unsigned int nNbColumn;
	CVector<CVector<T>*> VECpVECmatrix;

public:

	//constructor and destructor
	CMatrice(void); //default constructor
	CMatrice(const CMatrice<T>& MATmat);//Copy construcort
	CMatrice(const CParser& PARparser);//Constructor with parser
	CMatrice(unsigned int nNbColumn, unsigned int nNbRow, CVector<CVector<T>*> VECpVECmat); //Confort Constructor
	~CMatrice(void);//Destructor 

	//Methodes utile
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

	bool MATsameDimension(CMatrice<T>& MATmatrice);

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
	void operator=(CMatrice<T> MATmatrice);
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
	nNbRow = 0;
	nNbColumn = 0;
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
 * @brief Constructor using parser
 *
 * @tparam T
 * @param PARparser
 */
template <class T>
CMatrice<T>::CMatrice(const CParser& PARparser) {

	CString STRtypeMatrice = PARparser.PARgetValueOfKey("TypeMatrice");

	try
	{
		if (STRtypeMatrice != (CString)"double") throw (const char *)"MATRIX type ERROR: only 'double' is handled";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CString STRnbRow = PARparser.PARgetValueOfKey("NBLignes");
	CString STRnbColumn = PARparser.PARgetValueOfKey("NBColonnes");
	CString STRmatrix = PARparser.PARgetValueOfKey("Matrice");

	CVector<CString*> VECTpSTRrowVector = PARparser.PARparseArray(STRmatrix);

	nNbRow = STRnbRow.STRtoInt();
	nNbColumn = STRnbColumn.STRtoInt();

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		VECpVECmatrix.VECpush(new CVector<T>);
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			CString STRvalue = *VECTpSTRrowVector.VECgetElement(nIteratorColumn + (nNbColumn*nIteratorRow));
			int iValue = STRvalue.STRtoInt();
			VECpVECmatrix.VECgetElement(nIteratorColumn)->VECpush(iValue);
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
CMatrice<T>::CMatrice(unsigned int nIteratorColumn, unsigned int nIteratorRow, CVector<CVector<T>*> VECpVECmat)
{
	try
	{
		if (nIteratorColumn <= 0 || nIteratorRow <= 0)throw (const char *)"MATRIX size ERROR: size of matrix can't be equal or inferior to 0";
		if (nIteratorColumn != VECpVECmat.VECsize() && nIteratorRow != VECpVECmat.VECgetElement(0)->VECsize())throw (const char *)"MATRIX size ERROR: size of your Vectors need to be the same as the size of the matrix you want to create"; //we can create a matrix that cut the value of a bigger array
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	nNbColumn = nIteratorColumn;
	nNbRow = nIteratorRow;
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECmatrix.VECpush(new CVector<T>);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			VECpVECmatrix.VECgetElement(nIteratorColumn)->VECpush(VECpVECmat.VECgetElement(nIteratorColumn)->VECgetElement(nIteratorRow));
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
	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		delete VECpVECmatrix.VECgetElement(nIteratorColumn);
	}
}

/**
 * @brief Set the number of row of a matrix
 *
 *
 * @param iNumberRow number of row
 */
template <class T>
inline void CMatrice<T>::MATsetNbRow(unsigned int nIteratorRow)
{
	try
	{
		if (nIteratorRow < 0) throw (const char *)"SIZE ERROR: matrix row size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	nNbRow = nIteratorRow;
}

/**
 * @brief Set the number of column of a matrix
 *
 * @param iNumberColumn number of column
 */
template <class T>
inline void CMatrice<T>::MATsetNbColumn(unsigned int nIteratorColumn)
{
	try
	{
		if (nIteratorColumn < 0) throw (const char *)"SIZE ERROR: matrix Column size bust be > 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	nNbColumn = nIteratorColumn;
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
	return nNbRow;
}

/**
 * @brief Get the number of Column from the matrix
 *
 * @return unsigned int
 */
template <class T>
inline unsigned int CMatrice<T>::MATgetNbColumn(void)
{
	return nNbColumn;
}

/**
 * @brief allow you to get the value of an element from the matrix by know is position
 *
 * @param iIteratorColumn column of the element
 * @param iTeratorRow row of the element
 * @return T value of the element
 */
template <class T>
inline T CMatrice<T>::MATgetElement(unsigned int nIteratorColumn, unsigned int nIteratorRow)
{
	try
	{
		if (nIteratorColumn < 0 || nIteratorColumn >= MATgetNbColumn()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (nIteratorColumn)";
		if (nIteratorRow < 0 || nIteratorRow >= MATgetNbRow()) throw (const char *)"GETelement ERROR: you can't something out of the matrix size (nIteratorRow)";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return 0;
	}
	return VECpVECmatrix.VECgetElement(nIteratorColumn)->VECgetElement(nIteratorRow);
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
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow) + MATmatrice.MATgetElement(nIteratorColumn, nIteratorRow));

		}
	}
	CMatrice<T> MATresult(nNbColumn, nNbRow, VECpVECtmpArray);

	//clear tmpArray
	for (unsigned int nIterator = 0; nIterator < MATresult.MATgetNbColumn(); nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}

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
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow) - MATmatrice.MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
	CMatrice<T> MATresult(nNbColumn, nNbRow, VECpVECtmpArray);

	//clear tmp array
	for (unsigned int nIterator = 0; nIterator < MATresult.MATgetNbColumn(); nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}

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
	for (unsigned int nCount = 0; nCount < nNbRow; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbRow; nIteratorColumn++)
		{
			for (unsigned int iIteratorAlternativ = 0; iIteratorAlternativ < nNbColumn; iIteratorAlternativ++)
			{
				if (iIteratorAlternativ == 0)
				{
					T var1 = MATgetElement(iIteratorAlternativ, nIteratorRow);
					T var2 = MATmatrice.MATgetElement(nIteratorColumn, iIteratorAlternativ);
					VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(var1 * var2);
				}
				else
				{
					T var1 = MATgetElement(iIteratorAlternativ, nIteratorRow);
					T var2 = MATmatrice.MATgetElement(nIteratorColumn, iIteratorAlternativ);
					T var3 = var1 * var2 + VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECgetElement(nIteratorRow);
					VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECmodify(var3, nIteratorRow);
				}
			}
		}
	}
	CMatrice<T> MATresult(nNbRow, nNbRow, VECpVECtmpArray);

	//clear tmparray
	for (unsigned int nIterator = 0; nIterator < MATresult.MATgetNbColumn(); nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}
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
	CMatrice<T> tmp = this->operator+(MATmatrice);
	return tmp;
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
	CMatrice<T> tmp = this->operator-(MATmatrice);
	return tmp;
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
	CMatrice<T> tmp = this->operator*(MATmatrice);
	return tmp;
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
	CMatrice<T> tmp = this->operator*(c);
	return tmp;
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
	CMatrice<T> tmp = this->operator/(c);
	return tmp;
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

		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
			{
				if (MATgetElement(nIteratorColumn, nIteratorRow) != MATmatrice.MATgetElement(nIteratorColumn, nIteratorRow))
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

		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
			{
				if (MATgetElement(nIteratorColumn, nIteratorRow) != MATmatrice.MATgetElement(nIteratorColumn, nIteratorRow))
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
 * @brief Modificator of element from the matrix by know his position
 *
 * @throw make sure that you modify a value inside the matrix
 * @param iIteratorColumn
 * @param iTeratorRow
 * @param val
 */
template<class T>
void CMatrice<T>::MATmodify(unsigned int nIteratorColumn, unsigned int nIteratorRow, T val)
{
	try
	{
		if (nIteratorColumn < 0 || nIteratorColumn >= MATgetNbColumn())throw (const char *)"Matrix modify: can't modify a value out of Column";
		if (nIteratorRow < 0 || nIteratorRow >= MATgetNbRow())throw (const char *)"Matrix modify: can't modify a value out of Row";
		//if (typeid(val) != typeid(MATgetElement(nIteratorRow,j))) throw (const char *)"Matrix modify: value need to be the same type of your matrix data";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}
	VECpVECmatrix.VECgetElement(nIteratorColumn)->VECmodify(val, nIteratorRow);
}

/**
 * @brief allow you to add a row to your matrix
 *
 * @throw make sure to enter correct position and row
 * @param iPos position where you want to add your row
 * @param row you row must be a 1 dimension CVector of a size = to the number of column
 */
template<class T>
void CMatrice<T>::MATaddRow(unsigned int nPos, CVector<T> VECrow)
{
	try
	{
		if (nPos < 0) throw (const char *)"AddRow error: can't add under 0";
		if (nPos > (nNbRow + 1)) throw (const char *)"AddRow error: can't be more than the nb of row+1";
		if (VECrow.VECsize() != nNbColumn)throw (const char *)"AddRow error: please provide a Vector with the same nb of Column";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorRow = 0; nIteratorRow < nPos; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(VECrow.VECgetElement(nIteratorColumn));
	}
	for (unsigned int nIteratorRow = nPos + 1; nIteratorRow < nNbRow + 1; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow - 1));
		}
	}
	
	CMatrice<T> tmpMatrix(nNbColumn, nNbRow + 1, VECpVECtmpArray);

	for (unsigned int nIterator = 0; nIterator < nNbColumn; nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}
	*this = tmpMatrix;
}

/**
 * @brief allow you to add Column to your matrix
 *
 * @throw make sure to enter correct position and Column
 * @param iPos position where you want to add your Column
 * @param Column you Column must be a 1 dimension CVector of a size = to the number of row
 */
template<class T>
void CMatrice<T>::MATaddColumn(unsigned int nPos, CVector<T> VECcolumn)
{
	try
	{
		if (nPos < 0) throw (const char *)"AddColumn error: can't add under 0";
		if (nPos > (nNbColumn + 1)) throw (const char *)"AddColumn error: can't be more than the nb of Column+1";
		if (VECcolumn.VECsize() != nNbRow)throw (const char *)"AddColumn error: please provide a Vector with the same nb of row";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int nCount = 0; nCount < nNbColumn + 1; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nPos; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbRow; nIteratorColumn++)
	{
		VECpVECtmpArray.VECgetElement(nPos)->VECpush(VECcolumn.VECgetElement(nIteratorColumn));
	}
	for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = nPos + 1; nIteratorColumn < nNbColumn + 1; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn - 1, nIteratorRow));
		}
	}

	CMatrice<T> tmpMatrix(nNbColumn+1, nNbRow, VECpVECtmpArray);

	for (unsigned int nIterator = 0; nIterator < nNbColumn+1; nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}

	*this = tmpMatrix;
}

/**
 * @brief allow you to remove row from your matrix
 *
 * @throw make sure to enter correct position
 * @param iPos position of the row to delete
 */
template<class T>
void CMatrice<T>::MATremoveRow(unsigned int nPos)
{
	try
	{
		if (nPos < 0) throw (const char *)"RemoveRow error: can't remove under 0";
		if (nPos > (nNbRow)) throw (const char *)"RemoveRow error: nPos can't be more than the nb of row";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorRow = 0; nIteratorRow < nPos; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
	for (unsigned int nIteratorRow = nPos; nIteratorRow < nNbRow - 1; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow + 1));
		}
	}

	CMatrice<T> tmpMatrix(nNbColumn, nNbRow - 1, VECpVECtmpArray);

	for (unsigned int nIterator = 0; nIterator < nNbColumn; nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}
	*this = tmpMatrix;
}

/**
 * @brief allow you to remove a column
 * @throw make sur to enter correct position
 * @param iPos position of the column you want to remove
 */
template<class T>
void CMatrice<T>::MATremoveColumn(unsigned int nPos)
{
	try
	{
		if (nPos < 0) throw (const char *)"RemoveColumn error: can't remove under 0";
		if (nPos > (nNbColumn)) throw (const char *)"RemoveColumn error: nPos can't be more than the nb of Column";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return;
	}

	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int nCount = 0; nCount < nNbColumn - 1; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = 0; nIteratorColumn < nPos; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
	for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
	{
		for (unsigned int nIteratorColumn = nPos + 1; nIteratorColumn < nNbColumn; nIteratorColumn++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorColumn - 1)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
	CMatrice<T> tmpMatrix(nNbColumn-1, nNbRow , VECpVECtmpArray);

	for (unsigned int nIterator = 0; nIterator < nNbColumn-1; nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}

	*this = tmpMatrix;
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
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbColumn; nIteratorRow++)
		{

			VECpVECtmpArray.VECgetElement(nIteratorRow)->VECpush(MATgetElement(nIteratorRow, nIteratorRow));
		}
	}
	CMatrice<T> MATresult(nNbRow, nNbColumn, VECpVECtmpArray);
	
	//clear tmparray
	for (unsigned int nIterator = 0; nIterator < nNbColumn; nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}
	return MATresult;
}


/**
 * @brief assignation operator , change the matrix value by a new one
 *
 * @param MATmatrice
 * @return CMatrice<T>&
 */
template<class T>
void CMatrice<T>::operator=(CMatrice<T> MATmatrice)
{
	//remove data from current matrix
	if (VECpVECmatrix.VECgetVectorElements() != NULL) {
		for (unsigned int nIterator = 0; nIterator < nNbColumn; nIterator++)
		{
			delete VECpVECmatrix.VECgetElement(nIterator);
		}
		VECpVECmatrix.setSize(0);
	}

	for (unsigned int nCount = 0; nCount < MATmatrice.MATgetNbColumn(); ++nCount)
		VECpVECmatrix.VECpush(new CVector<T>);

	MATsetNbColumn(MATmatrice.MATgetNbColumn());
	MATsetNbRow(MATmatrice.MATgetNbRow());

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			VECpVECmatrix.VECgetElement(nIteratorColumn)->VECpush(MATmatrice.MATgetElement(nIteratorColumn, nIteratorRow));
		}
	}
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
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow)*c);
		}
	}
	CMatrice<T> MATresult(nNbColumn, nNbRow, VECpVECtmpArray);

	//clear tmparray
	for (unsigned int nIterator = 0; nIterator < MATresult.MATgetNbColumn(); nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}
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
		if (c == 0) throw (const char *)"Operator / error: can't divide by under 0";
	}
	catch (const char *e)
	{
		cout << e << endl;
		return CMatrice<T>();
	}
	CVector<CVector<T>*> VECpVECtmpArray;
	for (unsigned int nCount = 0; nCount < nNbColumn; ++nCount)
		VECpVECtmpArray.VECpush(new CVector<T>);

	for (unsigned int nIteratorColumn = 0; nIteratorColumn < nNbColumn; nIteratorColumn++)
	{
		for (unsigned int nIteratorRow = 0; nIteratorRow < nNbRow; nIteratorRow++)
		{
			VECpVECtmpArray.VECgetElement(nIteratorColumn)->VECpush(MATgetElement(nIteratorColumn, nIteratorRow) / c);
		}
	}
	CMatrice<T> MATresult(nNbColumn, nNbRow, VECpVECtmpArray);
	
	//clear tmparray
	for (unsigned int nIterator = 0; nIterator < MATresult.MATgetNbColumn(); nIterator++)
	{
		delete VECpVECtmpArray.VECgetElement(nIterator);
	}
	return MATresult;
}