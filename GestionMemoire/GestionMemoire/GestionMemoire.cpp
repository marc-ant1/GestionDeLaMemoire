#include "GestionMemoire.h"

#include <fstream>
#include <algorithm>

using namespace std;

GestionMemoire::GestionMemoire(int n)
{
	MaxEntry = n;
	TLB_Find = 0;
	TLB_NotFind = 0;
}

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
	if (TLB.size() == MaxEntry)
	{
		TLB.pop_front();
	}
	TLB.push_back(adress);
}

bool GestionMemoire::TLB_Search(int adress)
{
	if (find(0, (MaxEntry - 1), adress))
	{
		TLB_Find += 1;
		return true;
	}
	else
	{
		TLB_NotFind += 1;
		return false;
	}
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
	//Construire en bits et traduire en d�cimal
	//Obtenir la valeur du byte sign�
	//... = fct_SignedByte(bits_page[i],bits_offset[i]);
}

//int GestionMemoire::fct_SignedByte(int page, int offset)
//{
//
//	//Ouvrir le fichier
//
//	unsigned int LENGTH = 1; //Le byte sign� a une longueur de 1 byte
//
//	nomduFichier.seekg(...); //Trouver l'endroit correspondant au byte sign� dans le fichier
//	nomduFichier.read(...);	 //Lire cet emplacement
//
//							//Fermer le fichier
//	return 0;
//
//}
/**/