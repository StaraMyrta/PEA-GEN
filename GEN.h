#pragma once
#include "DistanceMatrix.h"
#include "Pomiar.h"
#include <string.h>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include <math.h>
#include <algorithm>

using namespace std;
// Klasa reprezentuj�ca algorytm genetyczny dla problemu TSP
class GEN {
public:
    // Inicjalizacja zmiennej macierzy, rozmiaru grafu oraz optymalnego rozwi�zania
    int** tab;
    int size, optimal;

    // Strumienie wynikowe dla ostatecznych rezultat�w oraz najlepszej �cie�ki
    stringstream results, bestPathResult;

    // Ustawienia domy�lnych parametr�w algorytmu genetycznego
    double maxTime = 0.5;
    double mutationProbability = 0.15;
    double crossoverProbability = 0.10;
    int populationSize = 10;

    // Metoda g��wna wykonuj�ca algorytm genetyczny dla problemu TSP
    void genethicAlgorithm();

    // Metoda zwalniaj�ca pami��
    void clear();

private:
    // Inicjalizacja zmiennych u�ywanych w algorytmie
    int iteration = 1;
    vector<vector<int>> population;
    vector<double> populationFitnessValues;
    Pomiar pomiar;

    vector<int> bestPath;
    int bestPathValue = INT_MAX;
    double prd;

    // Tworzy nowe pokolenie osobnik�w w algorytmie genetycznym
    void makeNextGeneration(vector<vector<int>>* population, vector<double>* fitnessValues, double mutationProb, double crossProb);

    // Przekszta�ca warto�ci przystosowania w prawdopodobie�stwa dla populacji
    void fitnessToProbability(vector<double>* population);

    // Wybiera losowego osobnika z populacji
    vector<int> selectRandomFromPopulation(vector<vector<int>>* population);

    // Wybiera osobnika z populacji na podstawie przystosowania
    vector<int> selectFromPopulationByFitness(vector<vector<int>>* population, vector<double>* probabilities);

    // Wykonuje operacj� krzy�owania Order Crossover (OX) dla dw�ch osobnik�w
    void crossoverOX(vector<int>* individual, vector<int>* individual2);

    // Sprawdza, czy dany element znajduje si� w wektorze
    bool ifVectorContains(int element, vector<int> elements);

    // Mutacja przez transpozycj� dw�ch losowych gen�w w pojedynczym osobniku
    void transpositionMutation(vector<int>* individual);

    /// Mutacja przez inwersj� losowego fragmentu gen�w w pojedynczym osobniku
    void inversionMutation(vector<int>* individual);

    // Generuje losow� �cie�k�
    vector<int> randomPath();

    // Oblicza warto�� �cie�ki
    int calculatePathValue(vector<int> path); 
};