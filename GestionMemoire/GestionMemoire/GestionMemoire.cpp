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
	else
	{
		TLB_NotFind += 1;
		return false;
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