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