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

/* SESSION 5 I WAS HERE */

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

string monsterName[6] = { "Goblin", "Hobgoblin", "Troll", "Dragon", " ", "(Quickened) Big Daddy" };

/// 0 = Niveau, 1 = EXP_Gain, 2 = curHP, 3 = maxHP, 4 = ATK, 5 = DEF, 6 = SPE, 7 = GOLD_Gain
int monsterStats[6][8] = { { 3,300,2,2,2,2,2, 5 },
					{ 6,1300,6,6,4,3,4,15},
					{ 12,3300,12,12,7,6,2, 30},
					{ 24,6300,22,22,13,9,12, 50},
					{ 0 },
					{ 100, 0, 36, 36, 22, 14, 30, 0} };

int monsterActive[8];

// Menu principale à l'ouverture. Création de personnage ou chargement d'une sauvegarde
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
			if (stats[0] != 0) {
				levelUpCheck();
				menuJeu();
			}
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

// Création d'un personnage, demande du nom du personnage et initialisation des statistiques.
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

	// 2 = current HP, 3 = maximum HP, 0 = Niveau, 1 = Experience, 7 = Gold, 8 = Game Progress / Encounters
	stats[2] = stats[3];
	stats[0] = 1;
	stats[1] = 0;
	stats[7] = 0;
	stats[8] = 0;

	sauvegarde();
}

// Déroulement du jeu, basé sur le progrès du jeu / encounters (stats[8])
// Boss à 6, magasin à 5, 1-4 combat normal.
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

			if (stats[8] == 5) {
				temp = rand() % (4 + 1 - 1) + 1;
				switch (temp) {
				case 1: 
					monsterName[5] = "(Angry) Big Daddy";
					monsterActive[4] *= 1.2;
					break;
				case 2: 
					monsterName[5] = "(Hardened) Big Daddy";
					monsterActive[5] *= 1.2;
					break;
				case 3:
					monsterName[5] = "(Quickened) Big Daddy";
					monsterActive[6] *= 1.2;
					break;
				case 4:
					monsterName[5] = "(Healthy) Big Daddy";
					monsterActive[2] *= 1.2;
					monsterActive[3] *= 1.2;
					break;
				}
			}

			combatLoop();
			break;
		}
	} while (answer != 'Q');
}

// Affiche les statistiques du monstre.
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

// Affiche les statistiques du joueur.
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

//void afficherALL() {
//	system("cls");
//	afficherStats(stats);
//	afficherMonstre(monsterActive, stats);
//}

// Combat tour par tour, basé sur la vitesse du joueur et du monstre.
void combatLoop() {
	int baseDamage = 0;
	system("cls");
	afficherStats();
	cout << monsterName[stats[8]] << " bloque votre chemin!" << endl; 
	pressKey();
	system("cls");

	// Tant que quelqu'un est en vie
	do {
		// Si le joueur est plus vite, attaque en premier.
		if (stats[6] > monsterActive[6]) {
			turnPlayer(baseDamage);
			turnMonster(baseDamage);
		}
		// Sinon, le monstre attaque en premier.
		else if (stats[6] < monsterActive[6]){
			turnMonster(baseDamage);
			turnPlayer(baseDamage);
		} 
		// Si la vitesse des deux individus est égal, déterminer aléatoirement.
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

	cout << endl << endl;

	// Après avoir éliminé le monstre, obtient expérience et gold, ainsi que check les conditions pour monter de niveau.
	if (monsterActive[2] < 1) {
		system("cls");
		afficherStats();
		afficherMonstre();

		// Après le combat, augmente le progrès du jeu de 1.
		stats[8]++;

		cout << "Vous êtes vainqueur!" << endl;
		pressKey();
		stats[1] += monsterActive[1];
		stats[7] += monsterActive[7];
		levelUpCheck();
		stats[2] = stats[3];



		menuJeu();
	}
	// Si échoué à éliminé le monstre, jeu perdu, sauvegarde supprimé.
	else {
		system("cls");
		afficherStats();
		afficherMonstre();
		remove("sauvegarde.txt");
		cout << "Vous avez perdu ... " << endl; 		
		pressKey();

		system("cls");
		menu();
	}


}

// Détermine le nombre de dégat que le joueur causera basé sur les statistiques du monstre.
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

// Détermine le nombre de dégat que le monstre causera basé sur les statistiques du joueur.
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

// Regarde les conditions pour monter de niveau. Sauvegarde après chaque check, au cas que le jeu ferme durant cette procédure.
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

// Magasin pour acheter des statistiques pour devenir plus fort, utilise Gold comme monnaie.
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
				// 7 = Gold, 2 = current HP, 3 = max HP
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
				// 7 = Gold, 4 = Attaque
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
				// 7 = Gold, 5 = Defense
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
				// 7 = Gold, 6 = Vitesse
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

// Sauvegarde du jeu. Écrit le nom et le tableau stats[] dans un fichier qui peut être utilisé pour charger le jeu à nouveau. Perdu lors d'une défaite.
void sauvegarde() {
	fstream file;

	writeOpen(file);

	file << name << " ";

	for (int i = 0; i < 9; i++) {
		file << stats[i] << " ";
	}

	writeClose(file);
}

// Chargement du jeu. Écrit le nom dans la variable name et les valeurs numériques dans stats[].
void chargement() {
	fstream file;

	readOpen(file);
	if (!file) {
		cout << "ERREUR DE FICHIER (LECTURE)" << endl;
		for (int i = 0; i < 9; i++) {
			stats[i] = 0;
		}
		pressKey();
		system("cls");
	}
	else {
		file >> name;
		for (int i = 0; i < 9; i++) {
			file >> stats[i];
		}
	}
	readClose(file);
}

// Ouverture du fichier sauvegarde en écriture.
void writeOpen(fstream& file) {
	file.open("sauvegarde.txt", ios::out);
	if (!file) {
		cout << "ERREUR DE FICHIER (ECRITURE)" << endl;
		pressKey();
	}
}

// Fermeture du fichier sauvegarde en écriture.
void writeClose(fstream& file) {
	file.close();
}

// Ouverture du fichier de sauvegarde en lecture.
void readOpen(fstream& file) {
	file.open("sauvegarde.txt", ios::in);
}

// Fermeture du fichier de sauvegarde en lecture.
void readClose(fstream& file) {
	file.close();
}

// Demande d'appuyez sur une touche avant de continuer.
void pressKey() {
	cout << "Appuyez sur une touche pour continuer." << endl;
	system("pause>0");
}

