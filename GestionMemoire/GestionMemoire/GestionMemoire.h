#pragma once

#include <vector>
#include <queue>

class GestionMemoire
{
private:
	queue<int> TLB;
public:
	GestionMemoire();
	~GestionMemoire();
	void LireAdresse(std::vector<int> &AL);
	unsigned GestionMemoire::createMask(unsigned a, unsigned b);
	void LireAdresse(std::vector<int> AL);
	void TLB_Queue(int adress);
	bool TLB_Search(int adress);
};

