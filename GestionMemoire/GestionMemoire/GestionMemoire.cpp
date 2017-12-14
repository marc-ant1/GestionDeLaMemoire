#include "GestionMemoire.h"

#include <fstream>
#include <algorithm>

using namespace std;

GestionMemoire::GestionMemoire(int n)
{
	MaxEntry = n;
	TLB_Find = 0;
	TLB_NotFind = 0;
	FrameCourant = 0;
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

void GestionMemoire::InitialiserTablePage(int pageTable[256][3])
{
	for (int i = 0; i < 256; i++)
	{
		pageTable[i][0] = i;
		pageTable[i][1] = 0;
		pageTable[i][2] = 0;
	}
}

void GestionMemoire::TLB_Queue(int nbPage, int nbFrame)
{
	if (TLB.size() == MaxEntry)
	{
		TLB.pop_front();
	}
	list<int> tmp;
	tmp.push_back(nbPage);
	tmp.push_back(nbFrame);
	TLB.push_back(tmp);
}

int GestionMemoire::TLB_Search(int nbPage)
{
	for (list<list<int>>::iterator i = TLB.begin(); i != TLB.end(); i++)
	{
		if (i->front() == nbPage)
		{
			return i->back();
		}
	}
	return -1;
}

int  * GestionMemoire::PageTableFind(int pageTable[256][3], int page)
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

void GestionMemoire::LoadFrame(const int &bp)
{
	ifstream File("simuleDisque.bin", ifstream::binary);
	int valeur = 256 * bp;
	File.seekg(valeur, File.end);
	char* bit = new char[256];
	File.read(bit, 256);
	RAM.push_back(bit);
	Update(bp);
	File.close();
}

void GestionMemoire::Update(const int & bp)
{
	TLB_Queue(bp, FrameCourant);

}