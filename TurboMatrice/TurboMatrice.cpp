// TurboMatrice.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Matrice.h"
#include "Liste.h"

int main()
{
    std::cout << "Hello World!\n";
	int a[3] = { 1,2,3, };
	CListe<int> *testListe = new CListe<int>(3, a);
	testListe->LISAdd(3, 4);
	testListe->LISAdd(0, 0);
	std::cout << testListe->LISGetElement(2);
	testListe->LISRemove(3);
	testListe->LISRemove(1);
	/*
	int **array = new int*[2]; // allocate an array of 2 int pointers — these are our rows
	for (int count = 0; count < 2; ++count)
		array[count] = new int[2]; // these are our columns

	array[0][0] = 1;
	array[0][1] = 2;
	array[1][0] = 3;
	array[1][1] = 4;

	CMatrice<int> *test = new CMatrice<int>(2,2,array);
	CMatrice<int> *test2 = new CMatrice<int>(2, 2, array);
	std::cout << test->getNbColumn();
	std::cout << "\n";
	std::cout << test->getNbLine();
	std::cout << "\n";
	std::cout << "\n";
	std::cout << test->getPreciseElement(0, 0);
	std::cout << test->getPreciseElement(0, 1);
	std::cout << "\n";
	std::cout << test->getPreciseElement(1, 0);
	std::cout << test->getPreciseElement(1, 1);
	std::cout << "\n";
	CMatrice<int>* result = (*test+*test2);
	std::cout << "\n";
	std::cout << result->getPreciseElement(0, 0);
	std::cout << result->getPreciseElement(0, 1);
	std::cout << "\n";
	std::cout << result->getPreciseElement(1, 0);
	std::cout << result->getPreciseElement(1, 1);
	std::cout << "\n";
	//test->GetMatriceType().name();
	*/
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
