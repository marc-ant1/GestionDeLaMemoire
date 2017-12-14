#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <sstream>
#include <vector>
#include <bitset>
#include <fstream>
#include <string>

#include "GestionMemoire.h"

#define TaillePage 256;

using namespace std;


int main()
{
	//Initialisation et déclarations
	int MaxEntryTLB = 16;
	int memPhysique[256] = {0};			//Mémoire physique
	int adressePhysique[1000] = {0};	//Adresses Physiques
	int tablePage[256][3]={0};			//Table de page
	std::vector<int> adresseLogique;	//Adresses Logiques
	GestionMemoire Call(MaxEntryTLB);
	
	//Lire le fichier d'adresses à traduire
	Call.LireAdresse(adresseLogique);

	//Traduire l'adresse logique en adresse physique
	//1. Traduire l'entier en bits
		
	//Stocker les nombres binaires dans un vecteur
	std::vector<int>bits_offset,bits_page; //Un vecteur pour les bits de page et un autre pour les bits d'offset
		
	Call.extrairePageEtOffset(adresseLogique, bits_page, bits_offset);

	
	//	
	//	
	//	//Ecrire le fichier de sortie
	return 0;
}

