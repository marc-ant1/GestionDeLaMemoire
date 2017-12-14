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
		result = result >> 8;
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

int GestionMemoire::LoadFrame(const int &bp, int * page, int tablePage[256][3])
{
	ifstream File("simuleDisque.bin", ifstream::binary);
	int valeur = 256 * bp;
	File.seekg(valeur, File.end);
	char* bit = new char[256];
	File.read(bit, 256);
	RAM.push_back(bit);
	int frame = Update(bp,page, tablePage);
	File.close();
	return frame;
}

int GestionMemoire::Update(const int & bp,int * page, int tablePage[256][3])
{
	int frame = FrameCourant;
	//Ajouter la page au TLB
	TLB_Queue(bp, FrameCourant);

	retirerFrame(tablePage, FrameCourant);

	//Ajouter la page à la table de page
	page[1] = FrameCourant;
	page[2] = 1;
	
	if (FrameCourant == 255)
	{
		FrameCourant = 0;
	}
	else
	{
		FrameCourant++;
	}
	return frame;
}

void GestionMemoire::retirerFrame(int tablePage[256][3], int frame)
{
	for (size_t i = 0; i < 256; i++)
	{
		if (tablePage[i][1] == frame)
		{
			tablePage[i][2] = 0;
		}
	}
}

char * GestionMemoire::LireValeur(int bits_offset, int frame)
{
	char value[2];
	std::memcpy(value, RAM.at(frame) + bits_offset, sizeof value);
	return value;
}

int GestionMemoire::TrouverDecimal(char* valeur)
{
	int total = 0;
	for (int i = 7; i >= 0; i--)
	{
		total += pow(2 * valeur[i], 8 - i);
	}
	return total;
}
