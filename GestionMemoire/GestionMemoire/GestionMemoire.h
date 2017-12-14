#pragma once

#include <vector>
#include <list>

using namespace std;

class GestionMemoire
{
private:
	list<list<int>> TLB;
	int MaxEntry;
	int TLB_Find;
	int TLB_NotFind;
	vector<char*> RAM;
	int FrameCourant;
public:
	GestionMemoire(int n);
	~GestionMemoire();
	void InitialiserTablePage(int pageTable[256][3]);
	void LireAdresse(std::vector<int> &AL);
	unsigned createMask(unsigned a, unsigned b);
	void TLB_Queue(int nbPage, int nbFrame);
	int * PageTableFind(int pageTable[256][3], int page);
	int TLB_Search(int nbPage);
	void extrairePageEtOffset(const std::vector<int> & adresseLogique,std::vector<int> & page, std::vector<int> & offset);
	int LoadFrame(const int &bp,int * page, int tablePage[256][3]);
	int Update(const int & bp, int * page, int tablePage[256][3]);
	void retirerFrame(int tablePage[256][3], int frame);
	char * LireValeur(int bits_offset,int frame);
	int TrouverDecimal(vector<int> offset, vector<int> page);
	void Afficher(vector<int> logique, int physique[1000]);
};

