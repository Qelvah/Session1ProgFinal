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

// Nom du joueur
string name = "";

//Variable utilisé dans levelUpCheck
int temp;

//Variable utilisé pour les choix demadné
char answer;

fstream file;
string filename = "sauvegarde.txt";

string monsterName[5] = { "Goblin", "Hobgoblin", "Troll", "Dragon", "Big Daddy" };

int monsterStats[5][7] = { { 3,300,2,2,2,2, 10 },
					{ 6,1300,3,3,5,1,30},
					{ 12,3300,4,4,6,4,50},
					{ 24,6300,8,8,7,8,70},
					{ 100,0,15,15,12,14,0} };

void menu() {
	
	cout << "===========================" << endl;
	cout << "Bienvenue a C++ adventures!" << endl;
	cout << "===========================" << endl << endl;

	cout << "A) Crée votre personnage" << endl;
	cout << "B) Reprendre a la dernière sauvegarde" << endl;
	cout << "Q) Quitter l'aventure" << endl;

	cin >> answer;

		switch(answer) {
			case 'A':
				initialiserPersonnage(name, stats);
				sauvegarde(file, filename, name, stats);
				menuJeu();
				break;
			case 'B':
				break;
			case 'Q':
				exit;
		}
}

void initialiserPersonnage(string& name, int stats[])
{
	cout << "========================================" << endl;
	cout << "   	Création de votre personnage!	 " << endl;
	cout << "========================================" << endl;

	cout << "========================================" << endl;
	cout << "   Quel est le nom de votre guerrier?	 " << endl;
	cout << "========================================" << endl;

	cin >> name;
	//Initialise les statistiques. Niveau 1, exp de debut = 0, gold de depart 0 et nous n'avons pas encore eu de encounter alors 0
	// les autres stats sont une valeure entre 3 et 5 aleatoire
	stats[0] = 1;
	stats[1] = 0;
	stats[7] = 0;
	stats[8] = 0;

	for (int i = 3; i < 7; i++) {
		stats[i] = rand() % 5 - 3;
	}

	stats[2] = stats[3];

	sauvegarde(file, filename, name, stats);
}

void menuJeu() {
	do {
		system("cls");
		afficherStats(stats);

		switch (stats[8]) {
			case 1: 
				break;
			case 2:
				break;
			case 3:
				break;
			case 4: 
				break;
			case 5: 
				cout << "Vous avez trouvez une zone de prière! Utiliser votre GP pour augmenter vos stats!" << endl;
				system("pause>0");
				magasin(stats);
				break;
			case 6:
				break;
		}



	} while (answer != 'Q');
}

void afficherMonstre(int monsterStats[][7], int stats[])
{
	int x = stats[8];

	if (x == 5) {
		x = 4;
	}

	cout << "---------------------------------------------------" << endl;
			cout << monsterName[x] << endl;
			cout << "Niveau : " << monsterStats[x][0];
			cout << "Points de vie : " << monsterStats[x][2] << "/" << monsterStats[x][3];
			cout << "Attaque : " << monsterStats[x][4] << endl;
			cout << "Defense : " << monsterStats[x][5] << endl;
			cout << "Vitesse : " << monsterStats[x][6] << endl;
			cout << "---------------------------------------------------" << endl;
}

void afficherStats(int stats[])
{
		cout << "---------------------------------------------------" << endl;
		cout << "Votre personnage : " << name << endl;
		cout << "Niveau : " << stats[0] << " | EXP : " << stats[1] << "/" << stats[0]*100 << endl;
		cout << "Points de vie : " << stats[2] << "/" << stats[3] << endl;
		cout << "Attaque : " << stats[4] << " | Defense : " << stats[5] << endl;
		cout << "Vitesse : " << stats[6] << " | Gold : " << stats[7] << endl;
		cout << "---------------------------------------------------" << endl;
		
}



void levelUpCheck(int stats[]) {

	do {
		if (stats[1] >= stats[0] * 100) {
			system("cls");
			cout << "Vous avez monté de niveau!" << endl;
			stats[1] -= stats[0] * 100;
			//Niveau
			stats[0]++;
			cout << "Niveau " << stats[0] << " atteint!" << endl;

			//maxHP
			temp = rand() % 1 - 0;
			cout << "Points de Vie +" << temp;
			stats[3] += temp;

			//ATK
			temp = rand() % 1 - 0;
			cout << "Attaque +" << temp;
			stats[4] += temp;

			//DEF
			temp = rand() % 1 - 0;
			cout << "Defense +" << temp;
			stats[5] += temp;

			//SPEED
			temp = rand() % 1 - 0;
			cout << "Vitesse +" << temp;
			stats[6] += temp;
			system("pause>0");
		}
	} while (stats[1] > stats[0] * 100);
}

void magasin(int stats[]) {

	do {
		system("cls");
		afficherStats(stats);
		cout << "===========================" << endl;
		cout << "		ALTAR OF PRAYER		" << endl;
		cout << "===========================" << endl << endl;

		cout << "A) Gain de vie (5gp)" << endl;
		cout << "B) Gain d'attaque (6gp)" << endl;
		cout << "C) Gain de defense (12gp)" << endl;
		cout << "D) Gain de Vitesse (25gp)" << endl;
		cout << "Q) Quittez la zone de prière" << endl << endl;

		cin >> answer;

		switch (answer) {
			case 'A': 
				if (stats[7] > 5) {
					stats[3]++;
					stats[7] -= 5;
				}
				else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
				}
				system("pause>0");
				break;
			case 'B':
				if (stats[7] > 6) {
					stats[4]++;
					stats[7] -= 6;
					}
					else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
					}
				system("pause>0");
				break;
			case 'C':
				if (stats[7] > 12) {
					stats[5]++;
					stats[7] -= 12;
				}
				else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
				}
				system("pause>0");
				break;
			case 'D':
				if (stats[7] > 25) {
					stats[6]++;
					stats[7] -= 25;
				}
				else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
				}
				system("pause>0");
				break;
			case 'Q':
				cout << "Vous avez quittez la zone de prière." << endl;
				system("pause>0");
			default: 
				cout << "La commande entrez est érronée." << endl;
				system("pause>0");
		}
	} while (answer != 'Q');

}

void sauvegarde(fstream& file, string filename, string name, int stats[]) {
	writeOpen(file, filename);

	file << name << " ";

	for (int i = 0; i < 9; i++) {
		file << stats[i] << " ";
	}

	writeClose(file, filename);
}

void chargement(fstream& file, string filename) {
	readOpen(file, filename);

	file >> name;
	for (int i = 0; i < 9; i++) {
		file >> stats[i];
	}
	readClose(file, filename);
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


