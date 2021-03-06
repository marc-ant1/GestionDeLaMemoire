#include "GestionMemoire.h"

#include <fstream>

using namespace std;

GestionMemoire::GestionMemoire(int n)
{
	MaxEntry = n;
	TLB_Find = 0;
	TP_Find = 0;
	TP_NotFind = 0;
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
			TLB_Find += 1;
			return i->back();
		}
	}
	return -1;
}

void GestionMemoire::CalculSucces()
{
	float SuccesTLB = TLB_Find / 1000;
	float PageFaultRate = TP_Find / (TP_Find + TP_NotFind);
}

int  * GestionMemoire::PageTableFind(int pageTable[256][3], int page)
{
	for (size_t i = 0; i < 256; i++)
	{
		if (pageTable[i][0] == page)
		{
			TP_Find += 1;
			return &pageTable[i][0];
		}
	}
	TP_NotFind += 1;
	return nullptr;
}

void GestionMemoire::extrairePageEtOffset(const std::vector<int> & adresseLogique, std::vector<int>& page, std::vector<int>& offset)
{
	//Cr��er un masque pour lire juste les bits 0 � 7 (offset)
	unsigned r = createMask(0, 7);

	//Cr�er un masque pour lire juste les bits 8 � 15 (page)
	unsigned r2 = createMask(8, 15);

	//Extraire la page et l'offset selon les masques d�finis pr�c�demment
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
	File.seekg(valeur, File.beg/*File.end*/);
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

	//Ajouter la page � la table de page
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

char  GestionMemoire::LireValeur(int bits_offset, int frame)
{
	return (RAM[frame])[bits_offset];
}

int GestionMemoire::TrouverDecimal(char valeur)
{
	int total = 0;
	for (int i = 7; i >= 0; i--)
	{
		total += pow(2 * valeur, 7 - i);
	}
	return total;
}
