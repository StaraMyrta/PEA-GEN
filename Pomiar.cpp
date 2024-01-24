#include "Pomiar.h"
#include <chrono>

Pomiar::Pomiar() : czasTrwania(0) {}

void Pomiar::czasStart() {
    czasTrwania = 0;
    startTime = std::chrono::high_resolution_clock::now();
}

double Pomiar::jakiCzasTrwania() {
    endTime = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = endTime - startTime;
    czasTrwania = elapsed.count();
    return czasTrwania;
}