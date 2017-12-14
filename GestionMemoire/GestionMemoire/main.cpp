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
	int tablePage[256][3]={0};			//Table de page
	std::vector<int> adresseLogique;	//Adresses Logiques
	GestionMemoire Call(MaxEntryTLB);
	
	//Lire le fichier d'adresses à traduire
	Call.LireAdresse(adresseLogique);

	std::vector<int> bits_offset, bits_page;

	//Extraire les bits représentant la page et l'offset
	Call.extrairePageEtOffset(adresseLogique, bits_page, bits_offset);

	Call.InitialiserTablePage(tablePage);

	ofstream Write("resultat");
	int frame;
	for (int i = 0; i < bits_page.size(); i++)
	{
		frame = Call.TLB_Search(bits_page[i]);
		if (frame == -1)
		{
			int* page = Call.PageTableFind(tablePage, bits_page[i]);
			if (page[2] == 0) 
			{
				frame = Call.LoadFrame(bits_page[i],page,tablePage);
			}
			else
			{
				frame = page[1];
			}
		}
		char valeur;
		valeur = Call.LireValeur(bits_offset[i], frame);

		// adresse physique = frame*256 + bits_offset
		Write << "Virtuelle : " << adresseLogique[i] << " "
			<< "Physique : " << ((frame * 256) + bits_offset[i]) << " "
			<< "Valeur Dec : " << (int)valeur << " "
			<< "Valeur bin : " << valeur << "\n";
	}
	return 0;
}

