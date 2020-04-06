#include <iostream>

template <typename T> class CListe
{
	private:
		int iLISsize;
		T *pLISArray;

	public:
		CListe();
		CListe(CListe &param);
		CListe(int iSize, T *pElement);
		~CListe();

		//Methods
		int LISGetSize();
		T LISGetElement(int iPos);
		void LISRemove(int iPos);
		void LISModify(int iPos,T Value);
		void LISAdd(int iPos, T Value);

};

template <typename T>
CListe<T>::CListe()
{
	iLISsize = 0;
	pLISArray = NULL;
}
template <typename T>
CListe<T>::CListe(CListe<T> &param)
{
	iLISsize = param.LISGetSize();
	pLISArray = new T[iLISsize];
	for (int i = 0; i < iLISsize; i++)
	{
		pLISArray[i] = param.pLISArray[i];
	}

}
template <typename T>
CListe<T>::CListe(int iSize,T *pElement)
{
	iLISsize = iSize;
	pLISArray = new T[iLISsize];
	for (int i = 0; i < iLISsize; i++)
	{
		pLISArray[i] = pElement[i];
	}

}
template <typename T>
CListe<T>::~CListe()
{
	free(pLISArray);
}

template <typename T>
int CListe<T>::LISGetSize()
{
	return iLISsize;
}

template <typename T>
T CListe<T>::LISGetElement(int iPos)
{
	//pre cond a faire
	return pLISArray[iPos];
}

template <typename T>
void CListe<T>::LISAdd(int iPos, T iValue)
{
	//precondition a faire 
	iLISsize++;
	T *tmp = new T[iLISsize];
	for (int i = 0; i < iPos; i++)
	{
		tmp[i] = pLISArray[i];
	}
	tmp[iPos] = iValue;
	for (int i = iPos+1 ; i < iLISsize; i++)
	{
		tmp[i] = pLISArray[i - 1];
	}
	free(pLISArray);
	pLISArray = tmp;

}
template <typename T>
void CListe<T>::LISRemove(int iPos)
{
	//precondition a faire 
	iLISsize--;
	T *tmp = new T[iLISsize];
	for (int i = 0; i < iPos; i++)
	{
		tmp[i] = pLISArray[i];
	}
	for (int i = iPos; i < iLISsize; i++)
	{
		tmp[i] = pLISArray[i+1];
	}
	free(pLISArray);
	pLISArray = tmp;

}

template <typename T>
void CListe<T>::LISModify(int iPos, T Value)
{
	//pre cond a faire
	pLISArray[iPos] = Value;
}