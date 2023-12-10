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

string monsterName[6] = { "Goblin", "Hobgoblin", "Troll", "Dragon", " ", "Big Daddy" };

int monsterStats[6][8] = { { 3,300,2,2,2,2,2, 5 },
					{ 6,1300,4,4,4,3,4,15},
					{ 12,3300,6,6,5,6,2, 30},
					{ 24,6300,10,10,7,8, 12, 50},
					{ 0 },
					{ 100, 0, 15, 15, 12, 14, 30, 0} };

/// 0 = Niveau, 1 = EXP, 2 = curHP, 3 = maxHP, 4 = ATK, 5 = DEF, 6 = SPE, 7 = GOLD
int monsterActive[8];

void menu() {

	do {

		cout << "===========================" << endl;
		cout << "Bienvenue a C++ adventures!" << endl;
		cout << "===========================" << endl << endl;

		cout << "A) Crée votre personnage" << endl;
		cout << "B) Reprendre a la dernière sauvegarde" << endl;
		cout << "Q) Quitter l'aventure" << endl << endl;

		cout << "Votre Action: ";

		cin >> answer;
		answer = toupper(answer);

		switch (answer) {
		case 'A':
			system("cls");
			initialiserPersonnage();
			menuJeu();
			break;
		case 'B':
			system("cls");
			chargement();
			levelUpCheck();
			menuJeu();
			break;
		case 'Q':
			exit;
			break;
		default:
			cout << "Commande entrez érroné." << endl;
			pressKey();
			system("cls");
		}
	} while (answer != 'Q');
}

void initialiserPersonnage()
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

	for (int i = 3; i < 7; i++) {
		stats[i] = rand() % (5 + 1 - 3) + 3;
	}

	stats[2] = stats[3];
	stats[0] = 1;
	stats[1] = 0;
	stats[7] = 0;
	stats[8] = 0;

	sauvegarde();
}

void menuJeu() {
	do {
		system("cls");
		afficherStats();
		pressKey();

		if (stats[8] == 6){
			system("cls");
			afficherStats();
			cout << "Vous avez battu le jeu!" << endl;
			pressKey();
			system("cls");
			menu();
		}
		else if (stats[8] == 4) {
			magasin();
		}
		else{
			for (int i = 0; i < 8; i++) {
				monsterActive[i] = monsterStats[stats[8]][i];
			}
			combatLoop();
			break;
		}
	} while (answer != 'Q');
}

void afficherMonstre()
{
	int x = stats[8];

		cout << "---------------------------------------------------" << endl;
		cout << monsterName[x] << endl;
		cout << "Niveau : " << monsterActive[0] << endl;
		cout << "Points de vie : " << monsterActive[2] << "/" << monsterActive[3] << endl;
		cout << "Attaque : " << monsterActive[4] << endl;
		cout << "Defense : " << monsterActive[5] << endl;
		cout << "Vitesse : " << monsterActive[6] << endl;
		cout << "---------------------------------------------------" << endl;
}

void afficherStats()
{
		cout << "---------------------------------------------------" << endl;
		cout << "Votre personnage : " << name << endl;
		cout << "Niveau : " << stats[0] << " | EXP : " << stats[1] << "/" << stats[0]*100 << endl;
		cout << "Points de vie : " << stats[2] << "/" << stats[3] << endl;
		cout << "Attaque : " << stats[4] << " | Defense : " << stats[5] << endl;
		cout << "Vitesse : " << stats[6] << " | Gold : " << stats[7] << endl;
		cout << "---------------------------------------------------" << endl;	
}

//void afficherALL(int monsterActive[], int stats[]) {
//	system("cls");
//	afficherStats(stats);
//	afficherMonstre(monsterActive, stats);
//}

void combatLoop() {
	int baseDamage = 0;
	system("cls");
	afficherStats();
	cout << monsterName[stats[8]] << " bloque votre chemin!" << endl; 
	pressKey();
	system("cls");


	do {
		if (stats[6] > monsterActive[6]) {
			turnPlayer(baseDamage);
			turnMonster(baseDamage);
		}
		else if (stats[6] < monsterActive[6]){
			turnMonster(baseDamage);
			turnPlayer(baseDamage);
		} 
		else {
			int tempValue = rand () % (1 + 1 - 0 ) - 0;
			if (tempValue == 0) {
				turnMonster(baseDamage);
				turnPlayer(baseDamage);
			} 
			else {
				turnPlayer(baseDamage);
				turnMonster(baseDamage);
			} 
		}

	} while (stats[2] > 0 && monsterActive[2] > 0);

	stats[8]++; 
	cout << endl << endl;

	if (monsterActive[2] < 1) {
		cout << "Vous êtes vainqueur!" << endl;
		stats[1] += monsterActive[1];
		stats[7] += monsterActive[7];
		levelUpCheck();
		stats[2] = stats[3];
		menuJeu();
	}
	else {
		cout << "Vous avez perdu ... " << endl; 
		pressKey();
		remove("sauvegarde.txt");
		system("cls");
		menu();
	}
}

void turnPlayer(int baseDamage) {

	if (stats[2] > 0 ){
		baseDamage = rand() % ( (stats[4]+1) + 1 - (stats[4]-1)) + (stats[4]-1);
		baseDamage -= monsterActive[5] ;

		if (baseDamage < 1) {
			baseDamage = 1;
		}

		monsterActive[2] -=  baseDamage;

		system("cls");
		afficherStats();
		afficherMonstre();

		cout << "Vous attaquez le monstre pour " << baseDamage << " de degats! " << endl;
		pressKey();
	}
	else {

	}
}

void turnMonster(int baseDamage) {
	if (monsterActive[2] > 0) {
		baseDamage = rand() % ((monsterActive[4] + 1) + 1 - (monsterActive[4] - 1)) + (monsterActive[4] - 1);
		baseDamage -= stats[5];

		if (baseDamage < 1) {
			baseDamage = 1;
		}

		stats[2] -= baseDamage;

		system("cls");
		afficherStats();
		afficherMonstre();

		cout << "Le " << monsterName[stats[8]] << " vous fait " << baseDamage << " de degats! " << endl;
		pressKey();
	}
	else {

	}
}

void levelUpCheck() {

	do {
		if (stats[1] >= stats[0] * 100) {
			system("cls");
			cout << "Vous avez monté de niveau!" << endl;
			stats[1] -= stats[0] * 100;
			//Niveau
			stats[0]++;
			cout << "Niveau " << stats[0] << " atteint!" << endl;

			//maxHP
			temp = rand() % (2 +1 - 0) + 0;
			cout << "Points de Vie +" << temp << endl;
			stats[3] += temp;

			//ATK
			temp = rand() % (2 + 1 - 0) + 0;
			cout << "Attaque +" << temp << endl;
			stats[4] += temp;

			//DEF
			temp = rand() % (2 + 1 - 0) + 0;
			cout << "Defense +" << temp << endl;
			stats[5] += temp;

			//SPEED
			temp = rand() % (2 + 1 - 0) + 0;
			cout << "Vitesse +" << temp << endl;
			stats[6] += temp;
			pressKey();
			sauvegarde();
		}
	} while (stats[1] >= stats[0] * 100);
}

void magasin() {
	system("cls");
	afficherStats();
	cout << "Vous avez trouvé un lieu de prière." << endl;
	pressKey();

	do {
		system("cls");
		afficherStats();
		cout << "---------------------------------------------------" << endl;
		cout << "			ALTAR OF PRAYER			" << endl;
		cout << "---------------------------------------------------" << endl << endl;

		cout << "A) Gain de vie (20gp)" << endl;
		cout << "B) Gain d'attaque (30gp)" << endl;
		cout << "C) Gain de defense (40gp)" << endl;
		cout << "D) Gain de Vitesse (50gp)" << endl;
		cout << "Q) Quittez la zone de prière" << endl << endl;

		cout << "Votre action : ";

		cin >> answer;
		answer = toupper(answer);

		switch (answer) {
			case 'A': 
				if (stats[7] >= 20) {
					stats[3]++;
					stats[2]++;
					stats[7] -= 20;
					cout << "Vous avez obtenu un point de vie." << endl;
				}
				else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
				}
				pressKey();
				break;
			case 'B':
				if (stats[7] >= 30) {
					stats[4]++;
					stats[7] -= 30; cout << "Vous avez obtenu un point d'attaque." << endl;
					}
					else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
					}
				pressKey();
				break;
			case 'C':
				if (stats[7] >= 40) {
					stats[5]++;
					stats[7] -= 40; cout << "Vous avez obtenu un point de defense." << endl;
				}
				else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
				}
				pressKey();
				break;
			case 'D':
				if (stats[7] >= 50) {
					stats[6]++;
					stats[7] -= 50; cout << "Vous avez obtenu un point de vitesse." << endl;
				}
				else {
					cout << "Vous n'avez pas assez de GP pour priez." << endl;
				}
				pressKey();
				break;
			case 'Q':
				cout << "Vous avez quittez la zone de prière." << endl;
				pressKey();
				break;
			default: 
				cout << "La commande entrez est érronée." << endl;
				pressKey();
		}
	} while (answer != 'Q');
	answer = ' ';
	stats[8]++;
}

void sauvegarde() {
	writeOpen();

	file << name << " ";

	for (int i = 0; i < 9; i++) {
		file << stats[i] << " ";
	}

	writeClose();
}

void chargement() {
	readOpen();

	file >> name;
	for (int i = 0; i < 9; i++) {
		file >> stats[i];
	}
	readClose();
}

void writeOpen() {
	file.open("sauvegarde.txt", ios::out);
	if (!file) {
		cout << "ERREUR DE FICHIER (ECRITURE)" << endl;
	}
}

void writeClose() {
	file.close();
}

void readOpen() {
	file.open("sauvegarde.txt", ios::in);
	if (!file) {
		cout << "ERREUR DE FICHIER (LECTURE)" << endl;
	}
}

void readClose() {
	file.close();
}

void pressKey() {
	cout << "Appuyez sur une touche pour continuer." << endl;
	system("pause>0");
}
