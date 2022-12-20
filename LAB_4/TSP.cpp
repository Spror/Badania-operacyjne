#include "TSP.hpp"

TSP::TSP(const char *filename) {

  std::ifstream ReadFile(filename);
  if (!ReadFile.is_open()) {
    std::cerr
        << "TSP::TSP(const char * filename): Problem with file opening \n";
    exit(-1);
  }

  std::string str;

  while (ReadFile >> str) {
    if (str == "NODE_COORD_SECTION") {
      std::cout << str << std::endl;
      break;
    }
  }

  int temp;
  city temp_city;
  while (ReadFile >> temp) {
    temp_city.ID = temp;
    ReadFile >> temp;
    temp_city.x = temp;
    ReadFile >> temp;
    temp_city.y = temp;
    this->cities.push_back(temp_city);
  }

  ReadFile.close();
}

void TSP::printCities() {
  for (auto &it : this->cities) {
    std::cout << it.ID << " " << it.x << " " << it.y << std::endl;
  }
}

int TSP::distance(city city_a, city city_b) {
  auto disX = city_a.x - city_b.x;
  auto disY = city_a.y - city_b.y;

  return int(sqrt(disX * disX + disY * disY) + 0.5);
}

unsigned long TSP::calculateDistance() {
  unsigned long distance = 0;

  for (auto i = 0; i < this->cities.size(); i++) {
    auto city_a = this->cities[i];
    city city_b;

    if (i == this->cities.size() - 1)
      city_b = this->cities[0];

    else
      city_b = this->cities[i + 1];

    distance += this->distance(city_a, city_b);
  }

  return distance;
}

unsigned long TSP::calculateDistance(std::vector<city> tour) {
  unsigned long distance = 0;

  for (auto i = 0; i < tour.size(); i++) {
    auto city_a = tour[i];
    city city_b;

    if (i == tour.size() - 1)
      city_b = tour[0];

    else
      city_b = tour[i + 1];

    distance += this->distance(city_a, city_b);
  }

  return distance;
}

void TSP::opt_2() {
  auto citiesCopy = this->cities;
  auto tourSize = citiesCopy.size();
  auto tempDistance = INT32_MAX;

  auto working = true;
  while (working) {

    auto bestDistance = this->calculateDistance();
    auto newDistance = INT32_MAX;

    for (int i = 0; i < tourSize - 1; i++) {
      for (int j = i + 1; j < tourSize - 1; j++) {

        auto coppy = cities;
        auto first = coppy.begin() + i;
        auto last = coppy.begin() + j;

        this->swap_opt_2(first, last);

        newDistance = this->calculateDistance(coppy);
        if (newDistance < bestDistance) {

          citiesCopy = coppy;
          bestDistance = newDistance;
        }
      }
    }
    if (tempDistance == newDistance) {
      working = false;
    }

    tempDistance = newDistance;
    this->cities = citiesCopy;
  }
}

void TSP::swap_opt_2(std::vector<city>::iterator first,
                     std::vector<city>::iterator last) {
  while (first <= last) {
    std::iter_swap(first++, last--);
  }
}

