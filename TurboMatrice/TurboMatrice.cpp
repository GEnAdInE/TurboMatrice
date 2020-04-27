// TurboMatrice.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "CMatrice.h"


int main()
{
    std::cout << "Hello World!\n";

	
	CVector<CVector<int>*> pVector; // allocate an array of iC int pointers — these are our columns 

	
	pVector.push(new CVector<int>{1,2});
	pVector.push(new CVector<int>{ 3,4 });
	pVector.push(new CVector<int>{ 5,6 });

	


	
	
	
	CMatrice<int> mat(3, 2, pVector);
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
	
	
	CVector<CVector<int>*> pVector1; // allocate an array of iC int pointers — these are our columns 


	pVector1.push(new CVector<int>{ 1,2,3 });;
	pVector1.push(new CVector<int>{ 4,5,6 });
	CMatrice<int> mat4(2, 3, pVector1);


	CMatrice<int> mat0 = mat * mat4;
	std::cout << mat0.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 0);
	std::cout << "\n";
	std::cout << mat0.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat0.MATgetElement(1, 1);
	std::cout << "\n";

	
	CMatrice<int> mat1(mat);
	
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

	//mat1 += mat;
	std::cout << mat1.MATgetElement(0, 0);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 0);
	std::cout << "\n";
	std::cout << mat1.MATgetElement(0, 1);
	std::cout << " ";
	std::cout << mat1.MATgetElement(1, 1);
	std::cout << "\n";
	mat1 = mat1 * 2;
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

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Astuces pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
