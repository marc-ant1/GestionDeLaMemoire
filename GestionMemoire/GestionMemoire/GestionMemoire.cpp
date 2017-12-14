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
	if (find(TLB.begin(), TLB.end(), adress)!=TLB.end())
	{
		TLB_Find += 1;
		return true;
	}

	return false;
}

int * GestionMemoire::PageTableFind(int pageTable[256][3], int page)
{
	for (size_t i = 0; i < 256; i++)
	{
		if (pageTable[i][0] == page)
		{
			return &pageTable[i][0];
		}
	}

	return nullptr;
}

void GestionMemoire::extrairePageEtOffset(const std::vector<int> & adresseLogique, std::vector<int>& page, std::vector<int>& offset)
{
	//Crééer un masque pour lire juste les bits 0 à 7 (offset)
	unsigned r = createMask(0, 7);

	//Créer un masque pour lire juste les bits 8 à 15 (page)
	unsigned r2 = createMask(8, 15);

	//Extraire la page et l'offset selon les masques définis précédemment
	for (int i = 0; i< adresseLogique.size(); i++)
	{
		int result = r & adresseLogique[i];
		offset.push_back(result);
		
		result = r2 & adresseLogique[i];
		page.push_back(result);
	}
}

unsigned GestionMemoire::createMask(unsigned a, unsigned b)
{
	unsigned r = 0;
	for (unsigned i = a; i <= b; i++)
	{
		r |= 1 << i;
	}
	return r;
}