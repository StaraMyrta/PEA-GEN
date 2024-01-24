#pragma once
#include <chrono>

class Pomiar {
private:
    double czasTrwania;  // Przechowuje informacj� o d�ugo�ci wykonywania akcji w sekundach.
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

public:
    Pomiar(); // Konstruktor klasy.
    void czasStart(); // Rozpoczyna odmierzanie czasu.
    double jakiCzasTrwania(); // Zwraca czas w sekundach, kt�ry up�yn�� dla ostatniego pomiaru.
};