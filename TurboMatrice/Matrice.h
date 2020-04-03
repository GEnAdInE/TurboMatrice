
template <typename T>
class Matrice
{
	private:
		
		int iNbLigne;
		int iNbColonne;
		T** ppMatrix;

	public:
		//constructor and destructor
		Matrice();
		Matrice(const Matrice mat);
		Matrice(int iL, int iC, T** ppM);
		~Matrice();
		
		//Methodes utile
		void setNbLigne(int l);
		void setNbColonne(int c);
		int getNbLigne();
		int getNbColonne();
		T getPriceseElement(int i, int j);//retourne un element des la matrice de pars sa position
		type_info GetMatriceType(); // !! se renseigner sur la calsse type_info 


		//Operateur matrice
		Matrice operator+(Matrice mat);
		Matrice operator-(Matrice mat);
		Matrice operator*(Matrice mat);

		//Operateur scalaire
		Matrice operator+(T c);//verifier si T est une bonne idée
		Matrice operator*(T c);
		Matrice operator-(T c);
		Matrice operator/(T c);

		//Autre operation
		Matrice tr(); //transposé
		Matrice inv(); //inverse



};

