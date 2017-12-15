#pragma once

#include <vector>
#include <list>

using namespace std;

class GestionMemoire
{
private:
	int MaxEntry;
	int TLB_Find;
	int FrameCourant;
	int TP_Find;
	int TP_NotFind;
	vector<char*> RAM;
	list<list<int>> TLB;
public:
	GestionMemoire(int n);
	~GestionMemoire();

	void InitialiserTablePage(int pageTable[256][3]);
	void LireAdresse(std::vector<int> &AL);
	void TLB_Queue(int nbPage, int nbFrame);
	void extrairePageEtOffset(const std::vector<int> & adresseLogique,std::vector<int> & page, std::vector<int> & offset);
	void retirerFrame(int tablePage[256][3], int frame);

	char LireValeur(int bits_offset,int frame);

	unsigned createMask(unsigned a, unsigned b);

	int TrouverDecimal(char valeur);
	int LoadFrame(const int &bp, int * page, int tablePage[256][3]);
	int Update(const int & bp, int * page, int tablePage[256][3]);
	int * PageTableFind(int pageTable[256][3], int page);
	int TLB_Search(int nbPage);

	void CalculSucces();
};

