
#include <iostream>
#include "CMatrice.h"


int main()
{
	std::cout << "Hello World!\n";


	
	CVector<CVector<double>*> pVector; // allocate an array of iC int pointers — these are our columns 


	pVector.VECpush(new CVector<double>{ 1 });
	pVector.VECpush(new CVector<double>{ 2 });
	pVector.VECpush(new CVector<double>{ 3 });

	

	
	CMatrice<double> mat(3, 1, pVector);
	for (int i = 0; i < 1; i++)
	{
		delete pVector.VECgetElement(i);
	}
	std::cout << mat.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat.MATgetElement(2, 0);
	std::cout << "\n";
	/*
	std::cout << mat.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat.MATgetElement(2, 1);
	std::cout << " ";
	std::cout << "\n";
	std::cout << "\n";*/


	CVector<CVector<double>*> pVector1; // allocate an array of iC double pointers — these are our columns
	pVector1.VECpush(new CVector<double>{ 4,5,6 });;
	//pVector1.VECpush(new CVector<double>{ 8,10,12 });
	CMatrice<double> mat4(1, 3, pVector1);
	for (int i = 0; i < 1; i++)
	{
		delete pVector1.VECgetElement(i);
	}
	std::cout << mat4.MATgetElement(0, 0);
	std::cout << "\n";
	std::cout << mat4.MATgetElement(0, 1);
	std::cout << "\n";
	std::cout << mat4.MATgetElement(0, 2);
	std::cout << "\n";

	CMatrice<double> mat0 = mat4 * mat;
	std::cout << mat0.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 0);
	std::cout << " ";
	std::cout << mat0.MATgetElement(2, 0);
	std::cout << "/n";
	std::cout << mat0.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 1);
	std::cout << " ";
	std::cout << mat0.MATgetElement(2, 1);
	std::cout << "/n";
	std::cout << mat0.MATgetElement(0, 2);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 2);
	std::cout << " ";
	std::cout << mat0.MATgetElement(2, 2);
	std::cout << " ";
	std::cout << mat0.MATgetElement(3, 3);

	return 0;
}