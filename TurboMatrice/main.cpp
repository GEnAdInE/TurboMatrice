
//#include "CPARSER.h"
#include "CVECTOR.h"
#include "CPARSER.h"
#include "CMATRICE.h"
#include "CPRINTER.h"
#include <iostream>

int main(unsigned int argc, const char* argv[])
{
	
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

	return 0;
}

