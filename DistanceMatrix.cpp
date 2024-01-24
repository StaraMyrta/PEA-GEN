#include "DistanceMatrix.h"

using namespace std;


// Sta³a oznaczaj¹ca brak krawêdzi
const int maxValue = INT_MAX;

// Struktura wêz³a
struct Node {
    int node_nr;
    int node_bound;
};

// Domyœlny konstruktor
DistanceMatrix::DistanceMatrix() {}

// Konstruktor przyjmuj¹cy liczbê wierzcho³ków grafu
DistanceMatrix::DistanceMatrix(int nodes) {
    size = nodes;
    generate(nodes);
}

// Ustawienie atrybutów pod nowy graf
void DistanceMatrix::generate(int nodes) {
    tab = new int* [nodes];
    for (int i = 0; i < nodes; i++)
        tab[i] = new int[nodes];
    for (int i = 0; i < nodes; i++)
        for (int j = 0; j < nodes; j++)
            tab[i][j] = maxValue;
}

// Wyœwietlanie grafu w postaci macierzy s¹siedztwa
void DistanceMatrix::show() {
    cout << "najlepszy wynik:"<<bestResult<<"\n";
    cout << "Reprezentacja macierzowa grafu:\n     ";
    for (int i = 0; i < size; i++)
        printf("%4d ", i);
    cout << endl << endl;
    for (int i = 0; i < size; i++) {
        printf("%3d  ", i);
        for (int j = 0; j < size; j++) {
            printf("%4d ", tab[i][j]);

        }
        cout << endl;
    }
}

// Dodanie krawêdzi miêdzy wierzcho³kami
void DistanceMatrix::addEdge(int x, int y, int dist) {
    tab[x][y] = dist;
}

// Tworzenie grafu z losowymi wartoœciami krawêdzi
void DistanceMatrix::createRandom(int testSize) {
    size = testSize;
    generate(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int d;
            if (i == j) d = -1;
            else d = rand() % 50 + 1; //krawêdŸ przyjmuje losow¹ wartoœæ od 1 do 50.
            addEdge(i, j, d);
        }
    }
}


// Wczytanie grafu z pliku txt
void DistanceMatrix::loadIt(string fileName) {
    fstream f;
    f.open(fileName, ios::in);
    if (!f.good()) {
        cout << "Nie mozna otworzyc pliku! \n" << endl;
    }
    else {
        cout << "Wczytywanie... \n" << endl;
    }

    f >> bestResult;
    f >> size;

    generate(size);
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            int d;
            f >> d;
            addEdge(i, j, d);
        }
    }
    f.close();
}