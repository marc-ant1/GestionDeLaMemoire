#include "GestionMemoire.h"

#include <fstream>

using namespace std;

GestionMemoire::GestionMemoire() {}

GestionMemoire::~GestionMemoire() {}

void GestionMemoire::LireAdresse(std::vector<int> AL)
{
	ifstream File("addresses");
	while (File.eof() == false)
	{
		int tmp;
		File >> tmp;
		AL.push_back(tmp);
	}
}

void GestionMemoire::TLB_Queue(int adress)
{
	TLB.pop();
	TLB.push(adress);
}

bool GestionMemoire::TLB_Search(int adress)
{

}

/**
unsigned GestionMemoire::createMask(unsigned a, unsigned b)
{

	unsigned r = 0;
	for (unsigned i = a; i <= b; i++)
	{
		r |= 1 << i;
	}
	return r;
}
/**/

/**
//Calcul de l'adresse physique
for (int i = 0; i < bits_page.size(); i++)
{
	//Construire en bits et traduire en décimal
	//Obtenir la valeur du byte signé
	//... = fct_SignedByte(bits_page[i],bits_offset[i]);
}

//int GestionMemoire::fct_SignedByte(int page, int offset)
//{
//
//	//Ouvrir le fichier
//
//	unsigned int LENGTH = 1; //Le byte signé a une longueur de 1 byte
//
//	nomduFichier.seekg(...); //Trouver l'endroit correspondant au byte signé dans le fichier
//	nomduFichier.read(...);	 //Lire cet emplacement
//
//							//Fermer le fichier
//	return 0;
//
//}
/**/