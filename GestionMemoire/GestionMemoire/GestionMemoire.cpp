#include "GestionMemoire.h"

#include <fstream>

using namespace std;

GestionMemoire::GestionMemoire() {}

GestionMemoire::~GestionMemoire() {}

void GestionMemoire::LireAdresse(std::vector<int> &AL)
{
	ifstream File("addresses.txt");
	while (!File.eof())
	{
		int tmp;
		File >> tmp;
		AL.push_back(tmp);
	}
	File.close();
}

/**
int GestionMemoire::fct_SignedByte(int page, int offset)
{
	
	//Ouvrir le fichier

	unsigned int LENGTH = 1; //Le byte signé a une longueur de 1 byte

	nomduFichier.seekg(...); //Trouver l'endroit correspondant au byte signé dans le fichier
	nomduFichier.read(...); //Lire cet emplacement

	//Fermer le fichier
	return 0;

}
/**/

unsigned GestionMemoire::createMask(unsigned a, unsigned b)
{

	unsigned r = 0;
	for (unsigned i = a; i <= b; i++)
	{
		r |= 1 << i;
	}
	return r;
}