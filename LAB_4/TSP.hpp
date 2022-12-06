#pragma once

#include <vector>
#include <fstream>
#include <iostream>
#include <cmath>

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

    public:
    TSP() = delete;
    TSP(const char * filename);

    void printCities();
    unsigned long calculateDistance();

 
};