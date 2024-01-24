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
// Klasa reprezentuj¹ca algorytm genetyczny dla problemu TSP
class GEN {
public:
    // Inicjalizacja zmiennej macierzy, rozmiaru grafu oraz optymalnego rozwi¹zania
    int** tab;
    int size, optimal;

    // Strumienie wynikowe dla ostatecznych rezultatów oraz najlepszej œcie¿ki
    stringstream results, bestPathResult;

    // Ustawienia domyœlnych parametrów algorytmu genetycznego
    double maxTime = 0.5;
    double mutationProbability = 0.15;
    double crossoverProbability = 0.10;
    int populationSize = 10;

    // Metoda g³ówna wykonuj¹ca algorytm genetyczny dla problemu TSP
    void genethicAlgorithm();

    // Metoda zwalniaj¹ca pamiêæ
    void clear();

private:
    // Inicjalizacja zmiennych u¿ywanych w algorytmie
    int iteration = 1;
    vector<vector<int>> population;
    vector<double> populationFitnessValues;
    Pomiar pomiar;

    vector<int> bestPath;
    int bestPathValue = INT_MAX;
    double prd;

    // Tworzy nowe pokolenie osobników w algorytmie genetycznym
    void makeNextGeneration(vector<vector<int>>* population, vector<double>* fitnessValues, double mutationProb, double crossProb);

    // Przekszta³ca wartoœci przystosowania w prawdopodobieñstwa dla populacji
    void fitnessToProbability(vector<double>* population);

    // Wybiera losowego osobnika z populacji
    vector<int> selectRandomFromPopulation(vector<vector<int>>* population);

    // Wybiera osobnika z populacji na podstawie przystosowania
    vector<int> selectFromPopulationByFitness(vector<vector<int>>* population, vector<double>* probabilities);

    // Wykonuje operacjê krzy¿owania Order Crossover (OX) dla dwóch osobników
    void crossoverOX(vector<int>* individual, vector<int>* individual2);

    // Sprawdza, czy dany element znajduje siê w wektorze
    bool ifVectorContains(int element, vector<int> elements);

    // Mutacja przez transpozycjê dwóch losowych genów w pojedynczym osobniku
    void transpositionMutation(vector<int>* individual);

    /// Mutacja przez inwersjê losowego fragmentu genów w pojedynczym osobniku
    void inversionMutation(vector<int>* individual);

    // Generuje losow¹ œcie¿kê
    vector<int> randomPath();

    // Oblicza wartoœæ œcie¿ki
    int calculatePathValue(vector<int> path); 
};