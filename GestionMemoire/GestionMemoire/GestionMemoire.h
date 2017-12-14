#pragma once

#include <vector>
#include <list>

using namespace std;

class GestionMemoire
{
private:
	list<int> TLB;
	int MaxEntry;
	int TLB_Find;
	int TLB_NotFind;
public:
	GestionMemoire(int n);
	~GestionMemoire();
	void LireAdresse(std::vector<int> &AL);
	unsigned GestionMemoire::createMask(unsigned a, unsigned b);
	void TLB_Queue(int adress);
	bool TLB_Search(int adress);
};

