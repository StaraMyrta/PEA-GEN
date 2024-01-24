#include <iostream>
#include <stdio.h>
#include "DistanceMatrix.h"
#include "GEN.h"


using namespace std;
string fileName;

// Funkcja wyświetlająca menu opcji
void showMenu(void) {
    cout << "\n\n----PROBLEM KOMIWOJAZERA----\n";
    cout << "   Wybierz odpowiednia opcje:\n";
    cout << "1. Wczytaj graf z pliku\n";
    cout << "2. Wyswietl macierz sasiedztwa\n";
    cout << "3. Przeprowadz algorytm genetyczny\n";
    cout << "4. Przeprowadz testy algorytmu genetycznego\n";
    cout << "5. Zmien kryterium stopu (domyslnie 60s)\n";
    cout << "6. Zmien prawdopodobienstwo wystapienia mutacji (domyslnie 0.01)\n";
    cout << "7. Zmien prawdopodobienstwo wystapienia krzyzowania (domyslnie 0.1)\n";
    cout << "8. Zmien rozmiar populacji (domyslnie 100)\n";
    cout << "9. Stworz graf\n";
    cout << "0. Zamknij program\n";
}

// Główna funkcja programu
int main(void)
{
    int size; // Zmienna przechowująca rozmiar
    int val;  // Zmienna pomocnicza

    DistanceMatrix matrix;// Obiekt macierzy odległości
    GEN gen; // Obiekt algorytmu Tabu Search

    int iteration, bestPathValue, bestPath;
    float prd;

    while (true) {
        showMenu();
        int wybor;
        cin >> wybor;
        switch (wybor) {
        case 1:
            // Wczytanie pliku z macierzą
            cout << "Podaj sciezke do pliku\n";
            cin >> fileName;
            matrix.loadIt(fileName + ".txt");
            gen.size = matrix.size;
            break;
        case 2:
            // Wyświetlenie macierzy sąsiedztwa
            matrix.show();
            break;
        case 3:
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult;
            // Uruchomienie algorytmu genetycznego z odpowiednimi parametrami
            gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.bestPathResult >> bestPath;
            cout << bestPath;
            while (gen.bestPathResult >> bestPath) {
                cout << "->" << bestPath;
            }
            gen.clear();
            break;
        case 4:
            // 17x17
            matrix.loadIt("br17.txt");
            cout << "rozmiar: " << matrix.size << endl;
            gen.size = matrix.size;
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult; gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.clear();

            // 33x33
            matrix.loadIt("ftv33.txt");
            cout << "rozmiar: " << matrix.size << endl;
            gen.size = matrix.size;
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult; gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.clear();

            // 70x70
            matrix.loadIt("ft70.txt");
            cout << "rozmiar: " << matrix.size << endl;
            gen.size = matrix.size;
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult; gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.clear();

            // 124x124
            matrix.loadIt("kro124p.txt");
            cout << "rozmiar: " << matrix.size << endl;
            gen.size = matrix.size;
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult; gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.clear();

            // 323x323
            matrix.loadIt("rbg323.txt");
            cout << "rozmiar: " << matrix.size << endl;
            gen.size = matrix.size;
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult; gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.clear();

            // 403x403
            matrix.loadIt("rbg403.txt");
            cout << "rozmiar: " << matrix.size << endl;
            gen.size = matrix.size;
            gen.tab = matrix.tab;
            gen.optimal = matrix.bestResult; gen.genethicAlgorithm();
            while (gen.results >> iteration >> bestPathValue >> prd) {
                cout << iteration << " " << bestPathValue << " " << prd << "%\n";
            }
            gen.clear();

            break;
        case 5:
            // Ustawienie kryterium stopu
            cout << endl << "Podaj maksymalny czas (w sekundach) szukania rozwiazania: " << endl;
            cin >> gen.maxTime;
            break;
        case 6:
            // Wybór prawdopodobieństwa wystąpienia mutacji
            cout << endl << "Podaj ile % wynosi prawdopodobienstwo wystapienia mutacji" << endl;
            cin >> val;
            gen.mutationProbability = val / 100;
            break;
        case 7:
            // Wybór prawdopodobieństwa wystąpienia krzyżowania
            cout << endl << "Podaj ile % wynosi prawdopodobienstwo wystapienia krzyzowania" << endl;
            cin >> val;
            gen.crossoverProbability = val / 100;
            break;
        case 8:
            // Wybór rozmiaru populacji
            cout << endl << "Podaj rozmiar populacji" << endl;
            cin >> gen.populationSize;
            break;
        case 9:
            // Tworzenie losowej macierzy
            cout << "Podaj ilosc wierzcholkow" << endl;
            cin >> size;
            matrix.createRandom(size);
            matrix.show();
            gen.size = size;
            break;
        case 0:
            // Zamknięcie programu
            exit(0);
        }
    }
    return 0;
}