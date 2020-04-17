// TurboMatrice.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include <iostream>
#include "Matrice.h"

int main()
{
    std::cout << "Hello World!\n";
	
	// test des listes
	/*
	int a[3] = { 1,2,3, };
	CListe<int> *testListe = new CListe<int>(3, NULL);
	testListe->LISAdd(3, 4);
	testListe->LISAdd(0, 0);
	std::cout << testListe->LISGetElement(2);
	testListe->LISRemove(3);
	testListe->LISRemove(1);
	*/
	
	/*double array
	int **array = new int*[2]; // allocate an array of 2 int pointers — these are our rows
	for (int count = 0; count < 2; ++count)
		array[count] = new int[2]; // these are our columns

	array[0][0] = 1;
	array[0][1] = 2;
	array[1][0] = 3;
	array[1][1] = 4;*/

	int a[3] = { 1,2,3 };
	int b[3] = { 4,5,6 };
	int c[3] = { 7,8,9 };
	CListe<int> *L1 = new CListe<int>(3, a);
	CListe<int> *L2 = new CListe<int>(3, b);
	CListe<int> *L3 = new CListe<int>(3, c);
	CListe<int> * LTab[3] = { L1, L2, L3 };
	CListe<CListe<int> *> *L4 = new CListe<CListe<int> *>(3, LTab);
	 std::cout << L4->LISGetElement(0)->LISGetElement(0);

	
	
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
