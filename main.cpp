/*
AUTHOR: Kevin Larochelle, Mathis Ouellet-Masson
DATE: December 1st, 2023
PROJECT: Projet Final
FILENAME: main.cpp
DESCRIPTION: Petit jeu rogue-lite
*/

/* SESSION 5 - NOUVELLES TECHNO LAB WITH GIT
HELLO*/

#include "mesFonctions.h"
#include <iostream>
using namespace::std;

int main(){ 

	locale::global(locale{ "" });
	srand(time(NULL));
	std::print("Salut, c'est moi le print super utile !");
	menu();
}

