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
	int tablePage[256][2]={0};			//Table de page
	std::vector<int> adresseLogique;	//Adresses Logiques
	GestionMemoire Call(MaxEntryTLB);
	
	//Lire le fichier d'adresses à traduire
	Call.LireAdresse(adresseLogique);

	//Traduire l'adresse logique en adresse physique
	//1. Traduire l'entier en bits
		
	//Stocker les nombres binaires dans un vecteur
	std::vector<int>bits_offset,bits_page; //Un vecteur pour les bits de page et un autre pour les bits d'offset
		
	//Crééer un masque pour lire juste les bits 0 à 7 (offset)
	unsigned r = 0;
	r = Call.createMask(0,7);
		
	//Créer un masque pour lire juste les bits 8 à 15 (page)
	unsigned r2 = 0;
	r2 = Call.createMask(8,15);
		
	//Boucler sur les 1000 adresses
	for(int i =0; i< adresseLogique.size() ; i++)
	{
				
		//Traduire en bits, EXEMPLE
		//std::bitset<16>A = adresseLogique[i];
		//EXEMPLE DE SYNTAXE POUR UTILISER LE MASQUE
		int result = r & adresseLogique[i];
		bits_offset.push_back(result);
		//ETC...
		result = r2 & adresseLogique[i];
		bits_page.push_back(result);
	}	
	//	
	//	
	//	
	//	
	//	//Table de pages
	//	//Une adresse à la fois, vérifier si elle est dans la table de page
	//	
	//	for(int i=0;i<bits_page.size();i++)
	//	{
	//			
	//			if( tablePage[bits_page[i]][1]  != 1)
	//			{
	//				std::cout << "Page non-chargée dans la table" << std::endl;
	//				//Charger la page 
	//						
	//				
	//				
	//			}
	//	}
	//	
	//	
	//
	//	
	//	
	//	
	//	//Ecrire le fichier de sortie
	return 0;
}

