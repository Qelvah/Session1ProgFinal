/*
AUTHOR: Kevin Larochelle, Mathis Ouellet-Masson
DATE: December 1st, 2023
PROJECT: Projet Final
FILENAME: mesFonctions.h
DESCRIPTION: Petit jeu rogue-lite
*/

#pragma once

#include <iostream>
using namespace::std;
#include <fstream>

void levelUpCheck(int statistics[]);

void writeOpen(fstream& file, string filename);
void writeClose(fstream& file, string filename);

void readOpen(fstream& file, string filename);
void readClose(fstream & file, string filename);

void sauvegarde(fstream& file, string filename, string name, int stats[]);
void chargement(fstream& file, string filename);

void menu();
void menuJeu();
void afficherMonstre(int monstre[][7], int stats[]);
void afficherStats(int stats[]);
void initialiserPersonnage(string &name,int stats[]);

void magasin(int stats[]);