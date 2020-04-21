// TurboMatrice.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Matrice.h"

int main()
{
    std::cout << "Hello World!\n";

	
	int **Array = new int*[2]; // allocate an array of 2 int pointers — these are our rows
	for (int count = 0; count < 2; ++count)
		Array[count] = new int[3]; // these are our columns

	Array[0][0] = 1;
	Array[0][1] = 2;
	Array[0][2] = 3;
    Array[1][0] = 4;
	Array[1][1] = 5;
	Array[1][2] = 6;

	int **Array2 = new int*[3]; // allocate an array of 2 int pointers — these are our rows
	for (int count = 0; count < 3; ++count)
		Array2[count] = new int[2]; // these are our columns

	Array2[0][0] = 1;
	Array2[0][1] = 2;
	Array2[1][0] = 3;
	Array2[1][1] = 4;
	Array2[2][0] = 5;
	Array2[2][1] = 6;


	CMatrice<int> *mat = new CMatrice<int>(3,2 , Array);
	CMatrice<int> *mat2 = new CMatrice<int>(2,3, Array2);
	CMatrice<int> *mat3 = &mat2->operator*(*mat);
	std::cout << mat3->MATgetElement(0, 0);
	std::cout << "\n";
	std::cout << mat3->MATgetElement(0, 1);
	std::cout << "\n";
	std::cout << mat3->MATgetElement(1, 0);
	std::cout << "\n";
	std::cout << mat3->MATgetElement(1, 1);




	
	
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
