/*
AUTHOR: Kevin Larochelle, Mathis Ouellet-Masson
DATE: December 1st, 2023
PROJECT: Projet Final
FILENAME: mesFonctions.cpp
DESCRIPTION: Petit jeu rogue-lite
*/

#include "mesFonctions.h"
#include <iostream>
using namespace::std;
#include <fstream>

/// <summary>
/// 0 = Niveau, 1 = EXP, 2 = curHP, 3 = maxHP, 4 = ATK, 5 = DEF, 6 = SPE, 7 = GOLD, 8 = ENC
/// </summary>
int stats[9] = { 0 };
int temp;

fstream file;
string filename;

void levelUpCheck(int statistics[]) {

	if (stats[1] >= stats[0] * 100) {
		system("cls");
		cout << "Vous avez monté de niveau!" << endl;
		stats[1] -= stats[0] * 100;
		//Niveau
		stats[0]++;
		cout << "Niveau " << stats[0] << " atteint!" << endl;

		//maxHP
		temp = rand() % 1 - 0;
		stats[3] += temp;

		//ATK
		temp = rand() % 1 - 0;
		stats[4] += temp;

		//DEF
		temp = rand() % 1 - 0;
		stats[5] += temp;

		//SPEED
		temp = rand() % 1 - 0;
		stats[6] += temp;

	}
}

void writeOpen(fstream& file, string filename) {
	file.open(filename, ios::out);
	if (!file) {
		cout << "ERREUR DE FICHIER (ECRITURE)" << endl;
	}
}

void writeClose(fstream& file, string filename) {
	file.close();
}

void readOpen(fstream& file, string filename) {
	file.open(filename, ios::in);
	if (!file) {
		cout << "ERREUR DE FICHIER (LECTURE)" << endl;
	}
}

void readClose(fstream& file, string filename) {
	file.close();
}