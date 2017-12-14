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
public:
	GestionMemoire(int n);
	~GestionMemoire();
	void LireAdresse(std::vector<int> &AL);
	unsigned createMask(unsigned a, unsigned b);
	void TLB_Queue(int nbPage, int nbFrame);
	bool TLB_Search(int nbPage);
	int * PageTableFind(const int pageTable[256][3], int page);
	void extrairePageEtOffset(const std::vector<int> & adresseLogique,std::vector<int> & page, std::vector<int> & offset);
	void LoadFrame(const int &bp);
	void Update();
};

