#pragma once
#include <chrono>

class Pomiar {
private:
    double czasTrwania;  // Przechowuje informacjê o d³ugoœci wykonywania akcji w sekundach.
    std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTime;

public:
    Pomiar(); // Konstruktor klasy.
    void czasStart(); // Rozpoczyna odmierzanie czasu.
    double jakiCzasTrwania(); // Zwraca czas w sekundach, który up³yn¹³ dla ostatniego pomiaru.
};