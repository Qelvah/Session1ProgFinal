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

void levelUpCheck();

void writeOpen(fstream& file);
void writeClose(fstream& file);

void readOpen(fstream& file);
void readClose(fstream& file);

void sauvegarde();
void chargement();

void menu();
void initialiserPersonnage();

void menuJeu();
void afficherMonstre();
void afficherStats();
//void afficherALL();
void combatLoop();
void turnPlayer(int baseDamage);
void turnMonster(int baseDamage);
void magasin();

void pressKey();