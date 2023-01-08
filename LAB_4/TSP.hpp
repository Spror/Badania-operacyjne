#pragma once
#include <algorithm>
#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>
#include <iterator>
#include <random>
#include <ctime>
#include <cstdlib>
#include <fstream>

#define COOLING_FACTOR 0.96

void saveToFile();
struct city
{
    int x;
    int y;
    int ID;
};


class TSP
{
    std::vector<city> cities;

    int distance(city city_a, city city_b);
    unsigned long calculateDistance(std::vector<city>  tour);
    void swap_opt_2(std::vector<city>::iterator first, std::vector<city>::iterator last);

    public:
    TSP() = delete;
    TSP(const char * filename);

    void printCities();
    unsigned long calculateDistance();
    void opt_2();
    void simulatedAnnealingAlgorithm();
    
    
};