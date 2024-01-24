#include "GEN.h"

using namespace std;

void GEN::genethicAlgorithm() {

    srand(time(NULL)); // Inicjalizacja generatora liczb pseudolosowych

    pomiar.czasStart(); // Rozpocz�cie pomiaru czasu

    // Generacja pocz�tkowej populacji losowych tras
    for (int i = 0; i < populationSize; i++) {
        population.push_back(randomPath());
        int pathLength = calculatePathValue(population[i]);

        // Aktualizacja najlepszej trasy w populacji
        if (pathLength < bestPathValue) {
            bestPathValue = pathLength;
            bestPath = population[i];
        }

        // Obliczenie warto�ci przystosowania dla ka�dej trasy w populacji
        populationFitnessValues.push_back(1. / pathLength);
    }

    // Percentage Relative Deviation wzgl�dem rozwi�zania optymalnego
    prd = 100 * (double)bestPathValue / optimal;
    results << iteration << " " << bestPathValue << " " << prd << " ";

    // Rozpocz�cie g��wnej p�tli algorytmu na podstawie czasu
    while (pomiar.jakiCzasTrwania() < maxTime) {
        // Wygenerowanie nowej populacji tras na podstawie krzy�owania i mutacji
        makeNextGeneration(&population, &populationFitnessValues, mutationProbability, crossoverProbability);
        vector<double> newFitness;

        // Ocena nowej populacji tras
        for (int i = 0; i < populationSize; i++) {
            int pathLength = calculatePathValue(population[i]);

            // Aktualizacja najlepszej trasy w populacji
            if (pathLength < bestPathValue) {
                bestPathValue = pathLength;
                bestPath = population[i];
                prd = 100 * (double)bestPathValue / optimal;
                results << iteration << " " << bestPathValue << " " << prd << " ";
            }
            newFitness.push_back(1. / pathLength);
        }

        // Aktualizacja warto�ci przystosowania populacji
        populationFitnessValues = newFitness;
        iteration++;
    }

    // Zapis najlepszej znalezionej trasy
    bestPathResult << bestPath[0];
    for (int i = 1; i < size; i++) {
        bestPathResult << " " << bestPath[i];
    }
}

void GEN::clear() {
    // Zwolnienie pami�ci dla tablicy tab
    if (tab != nullptr) {
        for (int i = 0; i < size; ++i) {
            delete[] tab[i];
        }
        delete[] tab;
        tab = nullptr;
    }

    // Wyczy�� pozosta�e kontenery
    population.clear();
    populationFitnessValues.clear();
    bestPath.clear();
    results.clear();
    bestPathResult.clear();

    // Zresetuj zmienne algorytmu
    iteration = 1;
    bestPathValue = INT_MAX;
    prd = 0;
}


void GEN::makeNextGeneration(vector<vector<int>>* population, vector<double>* fitnessValues, double mutationProb, double crossProb) {

    vector<vector<int>> nextPopulation; // Nowa populacja, kt�ra b�dzie tworzona w oparciu o regu�y selekcji, krzy�owania i mutacji
    int tenPercent = ceil((*population).size() / 10); // Obliczenie 10% populacji, kt�rej najlepsze trasy przechodz� do nast�pnej generacji
    vector<pair<double, int>> help; // Wektor par (warto�� przystosowania, indeks trasy) do sortowania tras w oparciu o warto�� przystosowania

    // Tworzenie wektora par (warto�� przystosowania, indeks trasy) dla wszystkich tras w populacji
    for (int i = 0; i < (*fitnessValues).size(); i++) {
        help.push_back(make_pair((*fitnessValues)[i], i));
    }

    // Sortowanie tras od najlepiej przystosowanych do najmniej przystosowanych
    sort(help.rbegin(), help.rend());

    // Wyb�r 10% najlepiej przystosowanych tras, kt�re przechodz� bez zmian do nast�pnej generacji
    for (int i = 0; i < tenPercent; i++) {
        nextPopulation.push_back((*population)[help[i].second]);
    }

    // Tworzenie reszty nowej populacji na podstawie krzy�owania i mutacji
    for (int i = tenPercent; i < (*population).size(); i++) {
        // Losowe wybranie jednostki z aktualnej populacji
        vector<int> newIndividual = selectRandomFromPopulation(population);

        // Krzy�owanie z inn� jednostk� w populacji z okre�lonym prawdopodobie�stwem
        double random = (double)rand() / RAND_MAX;
        if (random < crossProb) {
            vector<int> newIndividual2 = selectRandomFromPopulation(population);
            crossoverOX(&newIndividual, &newIndividual2);
        }

        // Mutacja z okre�lonym prawdopodobie�stwem
        double random2 = (double)rand() / RAND_MAX;
        if (random2 < mutationProb)
            inversionMutation(&newIndividual);

        // Dodanie nowej jednostki do populacji
        nextPopulation.push_back(newIndividual);
    }

    // Zast�pienie aktualnej populacji now� populacj� (nast�pn� generacj�)
    *population = nextPopulation;
}

void GEN::fitnessToProbability(vector<double>* fitnessValues) {
    // Obliczenie sumy warto�ci przystosowania wszystkich jednostek w populacji
    double sum = 0;
    for (int i = 0; i < (*fitnessValues).size(); i++) {
        sum += (*fitnessValues)[i];
    }
    // Normalizacja warto�ci przystosowania do zakresu [0, 1]
    for (int i = 0; i < (*fitnessValues).size(); i++) {
        (*fitnessValues)[i] /= sum;
    }
}

vector<int> GEN::selectRandomFromPopulation(vector<vector<int>>* population) {
    // Losowe wybranie jednej jednostki z populacji
    int random = rand() % (*population).size();
    return (*population)[random];
}

vector<int> GEN::selectFromPopulationByFitness(vector<vector<int>>* population, vector<double>* probabilities) {
    int number = 0;
    // Wyb�r jednostki z populacji na podstawie prawdopodobie�stwa przystosowania
    double random = (double)rand() / RAND_MAX;
    while (random >= 0) {
        if (number == (*population).size()) {
            break;
        }
        random -= (*probabilities)[number];
        number++;
    }

    number--; // Korekta indeksu, aby nie wyj�� poza zakres
    return (*population)[number];
}

void GEN::crossoverOX(vector<int>* individual, vector<int>* individual2) {
    // Losowanie dw�ch punkt�w, one i two, dla krzy�owania
    int one = rand() % (*individual).size();
    int two;
    do {
        two = rand() % (*individual).size();
    } while (two == one);
    // Upewnienie si�, �e one < two
    if (one > two) {
        int temp = two;
        two = one;
        one = temp;
    }

    // Inicjalizacja dw�ch potomk�w
    vector<int> child1;
    vector<int> child2;

    // Tworzenie potomk�w poprzez kopiowanie gen�w z rodzic�w
    for (int i = 0; i < (*individual).size(); i++) {
        if (i >= one && i <= two) {
            // Dziecko 1 otrzymuje geny z drugiego rodzica, dziecko 2 z pierwszego
            child1.push_back((*individual2)[i]);
            child2.push_back((*individual)[i]);
        }
        else {
            // Pozosta�e geny s� oznaczone warto�ciami -1
            child1.push_back(-1);
            child2.push_back(-1);
        }
    }

    // Obliczenie pozosta�ych gen�w do wstawienia dla obu potomk�w
    int remaining1 = (*individual).size() - two + one - 1;
    int remaining2 = (*individual).size() - two + one - 1;
    int parentIndex = two + 1;
    int child1Index = two + 1;
    int child2Index = two + 1;
    if (parentIndex == (*individual).size()) {
        parentIndex = 0;
        child1Index = 0;
        child2Index = 0;
    }

    // Wstawianie brakuj�cych gen�w do potomk�w, zapobiegaj�c powt�rzeniom
    while (remaining1 || remaining2) {
        // Sprawdzenie czy istniej� jeszcze brakuj�ce geny do wstawienia w potomku 1
        if (remaining1) {
            // Sprawdzenie, czy gen z rodzica nie istnieje ju� w potomku 1
            if (!ifVectorContains((*individual)[parentIndex], child1)) {
                // Dodanie genu z rodzica do potomka 1
                child1[child1Index] = (*individual)[parentIndex];
                // Aktualizacja indeksu potomka 1
                if (child1Index == (*individual).size() - 1)
                    child1Index = 0;
                else
                    child1Index++;
                // Zmniejszenie liczby brakuj�cych gen�w w potomku 1
                remaining1--;
            }
        }
        // Sprawdzenie czy istniej� jeszcze brakuj�ce geny do wstawienia w potomku 2
        if (remaining2) {
            // Sprawdzenie, czy gen z rodzica nie istnieje ju� w potomku 2
            if (!ifVectorContains((*individual2)[parentIndex], child2)) {
                // Dodanie genu z rodzica do potomka 2
                child2[child2Index] = (*individual2)[parentIndex];
                // Aktualizacja indeksu potomka 2
                if (child2Index == (*individual).size() - 1)
                    child2Index = 0;
                else
                    child2Index++;
                // Zmniejszenie liczby brakuj�cych gen�w w potomku 2
                remaining2--;
            }
        }
        // Przej�cie do kolejnego genu z rodzic�w
        if (parentIndex == (*individual).size() - 1)
            parentIndex = 0;
        else
            parentIndex++;
    }

    // Wyb�r lepszego potomka na podstawie warto�ci funkcji przystosowania
    if (calculatePathValue(child1) > calculatePathValue(child2))
        (*individual) = child1;
    else
        (*individual) = child2;
}

bool GEN::ifVectorContains(int element, vector<int> elements) {
    // Przeszukiwanie wszystkich element�w w wektorze
    for (int i = 0; i < elements.size(); i++) {
        // Je�li znaleziono poszukiwany element, zwraca prawd�
        if (elements[i] == element)
            return true;
    }
    // Zwraca fa�sz, gdy ��dany element nie zosta� znaleziony
    return false;
}

void GEN::transpositionMutation(vector<int>* individual) {
    // Losuje dwie r�ne pozycje w wektorze gen�w
    int one = rand() % (*individual).size();
    int two;
    do {
        two = rand() % (*individual).size();
    } while (two == one);

    // Zamienia miejscami dwa wylosowane geny
    int help = (*individual)[one];
    (*individual)[one] = (*individual)[two];
    (*individual)[two] = help;
}

void GEN::inversionMutation(vector<int>* individual) {
    // Losuje dwie r�ne pozycje w wektorze gen�w
    int one = rand() % (*individual).size();
    int two;
    do {
        two = rand() % (*individual).size();
    } while (two == one);

    // Ustawia indeksy w odpowiedniej kolejno�ci, je�li s� odwrotnie
    if (one > two) {
        int temp = two;
        two = one;
        one = temp;
    }

    // Odwraca kolejno�� gen�w w wybranym fragmencie
    while (one < two) {
        int temp = (*individual)[two];
        (*individual)[two] = (*individual)[one];
        (*individual)[one] = temp;
        one++;
        two--;
    }
}

vector<int> GEN::randomPath() {
    int remaining = size;
    vector<int> verticies;
    vector<int> randomRoute;

    // Tworzy wektor wierzcho�k�w od 0 do 'size - 1'
    for (int i = 0; i < remaining; i++)
        verticies.push_back(i);

    // Tworzy losow� �cie�k� przez wierzcho�ki
    while (remaining) {
        // Losuje indeks z pozosta�ych wierzcho�k�w
        int randomNumber = rand() % remaining;

        // Dodaje wylosowany wierzcho�ek do �cie�ki
        randomRoute.push_back(verticies[randomNumber]);

        // Usuwa wylosowany wierzcho�ek z listy pozosta�ych
        verticies.erase(verticies.begin() + randomNumber);
        remaining--;
    }
    return randomRoute; // Zwraca losow� �cie�k�
}

int GEN::calculatePathValue(vector<int> path) {
    int pathValue = 0;

    // Sumuje odleg�o�ci mi�dzy kolejnymi wierzcho�kami �cie�ki
    for (int i = 0; i < size - 1; i++) {
        pathValue += tab[path[i]][path[i + 1]];
    }

    // Dodaje odleg�o�� mi�dzy ostatnim a pierwszym wierzcho�kiem
    pathValue += tab[path[size - 1]][path[0]];
    return pathValue; // Zwraca ca�kowit� warto�� �cie�ki (koszt)
}
