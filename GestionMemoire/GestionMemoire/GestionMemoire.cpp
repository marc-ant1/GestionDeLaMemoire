#include "GestionMemoire.h"

#include <fstream>

using namespace std;

GestionMemoire::GestionMemoire() {}

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
	TLB.pop();
	TLB.push(adress);
}

bool GestionMemoire::TLB_Search(int adress)
{

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