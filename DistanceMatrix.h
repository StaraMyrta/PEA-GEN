#pragma once
#include <string.h>
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

class DistanceMatrix
{
public:
	int** tab;
	int size, bestResult;
	string name;

	// Domyœlny konstruktor
	DistanceMatrix();

	// Konstruktor przyjmuj¹cy liczbê wierzcho³ków grafu
	DistanceMatrix(int nodes);

	// Ustawienie atrybutów pod nowy graf
	void generate(int nodes);

	// Wyœwietlanie grafu w postaci macierzy s¹siedztwa
	void show();

	// Dodanie krawêdzi miêdzy wierzcho³kami
	void addEdge(int x, int y, int dist);

	// Tworzenie grafu z losowymi wartoœciami krawêdzi
	void createRandom(int testSize);

	// Wczytanie grafu z pliku txt
	void loadIt(string fileName);

};