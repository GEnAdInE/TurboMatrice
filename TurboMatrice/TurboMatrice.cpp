
#include <iostream>
#include "CMatrice.h"


int main()
{
	std::cout << "Hello World!\n";


	CVector<CVector<double>*> pVector; // allocate an array of iC int pointers — these are our columns 


	pVector.VECpush(new CVector<double>{ 1,2 });
	pVector.VECpush(new CVector<double>{ 3,4 });
	pVector.VECpush(new CVector<double>{ 5,6 });

	

	
	CMatrice<double> mat(3, 2, pVector);
	for (int i = 0; i < 3; i++)
	{
		delete pVector.VECgetElement(i);
	}
	std::cout << mat.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat.MATgetElement(2, 0);
	std::cout << "\n";
	std::cout << mat.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat.MATgetElement(2, 1);
	std::cout << " ";
	std::cout << "\n";
	std::cout << "\n";


	CVector<CVector<double>*> pVector1; // allocate an array of iC double pointers — these are our columns
	pVector1.VECpush(new CVector<double>{ 1,2,3 });;
	pVector1.VECpush(new CVector<double>{ 4,5,6 });
	CMatrice<double> mat4(2, 3, pVector1);
	for (int i = 0; i < 2; i++)
	{
		delete pVector1.VECgetElement(i);
	}

	CMatrice<double> mat0 = mat * mat4;
	std::cout << mat0.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 0);
	std::cout << "\n";
	std::cout << mat0.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 1);
	std::cout << "\n";

	CMatrice<double> mat1(mat);

	mat1.MATaddRow(2, { 10,10,10 });

	//mat1 = (mat1+mat1); ne marche pas ??
	std::cout << mat1.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 0);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 1);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 2);
	std::cout << "\n";

	std::cout << "\n";
	std::cout << "addColl";
	std::cout << "\n";
	mat1.MATaddColumn(2, { 6,5,6 });
	std::cout << mat1.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(3, 0);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(3, 1);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(3, 2);
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "";
	mat1.MATremoveColumn(3);
	std::cout << mat1.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 0);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 1);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 2);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 2);
	std::cout << "\n";
	mat1.MATremoveRow(1);
	std::cout << mat1.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 0);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(2, 1);
	std::cout << "\n";

	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	std::cout << "\n";
	mat = mat+mat+mat;
	std::cout << mat.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat.MATgetElement(1, 0);
	std::cout << "\n";
	std::cout << mat.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat.MATgetElement(1, 1);
	std::cout << "\n";
	mat1 *= 2;
	mat += mat;
	mat *mat1;
	mat1.MATmodify(0, 0, 69);
	std::cout << mat1.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 0);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 1);
	std::cout << "\n";


	return 0;
}