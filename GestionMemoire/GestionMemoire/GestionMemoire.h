#pragma once

#include <vector>

class GestionMemoire
{
public:
	GestionMemoire();
	~GestionMemoire();
	void LireAdresse(std::vector<int> &AL);
	unsigned GestionMemoire::createMask(unsigned a, unsigned b);
};

