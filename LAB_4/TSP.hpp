#pragma once
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <iterator>
#include <random>
#include <vector>

#define COOLING_FACTOR 0.95

void saveToFile();
struct city {
  int x;
  int y;
  int ID;
};

class TSP {
  std::vector<city> cities;

  int distance(city city_a, city city_b);
  unsigned long calculateDistance(std::vector<city> tour);
  void swap_opt_2(std::vector<city>::iterator first,
                  std::vector<city>::iterator last);

  int TSPDynamic(int mark, int position, std::vector<std::vector<int>> &memo_vec, std::vector<std::vector<int>> &distance_vec);

public:
  TSP() = delete;
  TSP(const char *filename);

  void printCities();
  unsigned long calculateDistance();
  void opt_2();
  void simulatedAnnealingAlgorithm();
  int dynamicProgrammingAlgorithm();
};