#pragma once

#include "CVECTOR.h"
#include "CPARSER.h"
#include "CMATRICE.h"
#include "CPRINTER.h"
#include "CBooleanMatrix.h"
#include <iostream>

int main(unsigned int argc, const char* argv[])
{

	
	CVector<bool> *vect1 = new CVector<bool>{ true, false };
	CVector<bool> *vect2 = new CVector<bool>{ false, true };
	CVector<CVector<bool>*> array1;
	array1.VECpush(vect1);
	array1.VECpush(vect2);
	CMatrice<bool> testbool(2, 2, array1);




	CVector<bool> *vect3 = new CVector<bool>{ true, true };
	CVector<bool> *vect4 = new CVector<bool>{ true, true };
	CVector<CVector<bool>*> array2;
	array2.VECpush(vect3);
	array2.VECpush(vect4);

	CMatrice<bool> testbool2(2, 2, array2);

	PRIprint(testbool);
	PRIprint(testbool2);

	CBooleanMatrix test(testbool);
	CBooleanMatrix test2(testbool2);
	PRIprint(test.BOOgetMatrix());

	CBooleanMatrix result = test.operator&(test2);
	PRIprint(result.BOOgetMatrix());
	std::cout << "test" << endl;
	CBooleanMatrix result2 = test.operator|(test2);
	PRIprint(result2.BOOgetMatrix());
	/*
		if (argc == 1) {
		cout << "NO INPUT FILE ENTERED ... EXITING" << endl;
		return 1;
	}

	CVector<CMatrice<double>> VECMATmatrixVector;

	cout << "Please enter C value : ";
	char pcUserInput[20];
	cin >> pcUserInput;
	CString STRuserInput(pcUserInput);
	double fUserInput = STRuserInput.STRtoDouble();

	for (unsigned int argvIterator = 1; argvIterator < argc; argvIterator++) {

		const char* pcFiles = argv[argvIterator];
		CParser PARparser(pcFiles, '\n', '=', false);

		if (PARparser.PARisOpen()) {

			CMatrice<double> MATcurrentMatrix(PARparser);

			VECMATmatrixVector.VECpush(MATcurrentMatrix);

			cout << "SHOWING " << pcFiles << " MATRIX : " << endl << endl;
			PRIprint(MATcurrentMatrix);

			cout << "SHOWING " << pcFiles << " MATRIX * " << pcUserInput << ": " << endl << endl;
			PRIprint(MATcurrentMatrix*fUserInput);

			cout << "SHOWING " << pcFiles << " MATRIX / " << pcUserInput << ": " << endl << endl;
			PRIprint(MATcurrentMatrix/fUserInput);
		}
	}

	CMatrice<double> MATsumMatrix = VECMATmatrixVector.VECgetElement(0);
	CMatrice<double> MATdifSumMatrix = VECMATmatrixVector.VECgetElement(0);
	CMatrice<double> MATprodMatrix = VECMATmatrixVector.VECgetElement(0);

	for (unsigned int nVectorIterator = 1; nVectorIterator < VECMATmatrixVector.VECsize(); nVectorIterator++) {
		CMatrice<double> MATcurrentMatrix = VECMATmatrixVector.VECgetElement(nVectorIterator);

		MATsumMatrix += MATcurrentMatrix;

		if (nVectorIterator % 2 == 0) {
			MATdifSumMatrix -= MATcurrentMatrix;
		}
		else {
			MATdifSumMatrix += MATcurrentMatrix;
		}

		MATprodMatrix *= MATcurrentMatrix;
	}

	cout << "SHOWING RESULT OPERATOR + MATRIX : " << endl << endl;
	PRIprint(MATsumMatrix);

	cout << "SHOWING RESULT OPERATOR +- MATRIX : " << endl << endl;
	PRIprint(MATdifSumMatrix);

	cout << "SHOWING RESULT OPERATOR * MATRIX : " << endl << endl;
	PRIprint(MATprodMatrix);
	*/

	return 0;
}

