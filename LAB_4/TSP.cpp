#include "TSP.hpp"
#include <chrono>

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

  auto start_2opt = std::chrono::steady_clock::now();
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
  auto end_2opt = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end_2opt - start_2opt;
  std::cout << "elapsed time [2-opt]: " << elapsed_seconds.count() << "s\n";
}

void TSP::swap_opt_2(std::vector<city>::iterator first,
                     std::vector<city>::iterator last) {
  while (first <= last) {
    std::iter_swap(first++, last--);
  }
}

void TSP::simulatedAnnealingAlgorithm() {

  auto newCities = cities;
  auto bestCities = cities;
  auto const tourSize = newCities.size();
  double T = 500.0;

  // hardware RNG
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distr(0, tourSize - 1);
  std::uniform_real_distribution<> dis_nor(0.0, 1.0);

  auto const iteration = 30;
  auto const maxEpoch = 1000;

  auto epoch = 0;

  auto start_SA = std::chrono::steady_clock::now();

  while (epoch < maxEpoch) {
    for (auto i = 0; i < iteration; i++) {

      int first = distr(gen);
      int second;

      do {
        second = distr(gen);
      } while (first == second);

      newCities = bestCities;
      swap_opt_2(newCities.begin() + first, newCities.begin() + second);
      int diff = calculateDistance(bestCities) - calculateDistance(newCities);

      if (diff > 0) {
        bestCities = newCities;
      } else {
        auto propability = exp(double(diff) / T); //         e(f(X)−f(X'))/T
        auto randomValue = dis_nor(gen);
        if (randomValue <= propability)
          bestCities = newCities;
      }
    }
    T *= COOLING_FACTOR;
    epoch++;
  }

  cities = bestCities;
  std::cout << "Koncowe T: " << T << std::endl;
  auto end_SA = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end_SA - start_SA;
  std::cout << "elapsed time [Simulated Annealing]: " << elapsed_seconds.count()
            << "s\n";
}

int TSP::TSPDynamic(int mark, int position, std::vector<std::vector<int>> &memo_vec, std::vector<std::vector<int>> &distance_vec) {
  if (mark == ((1 << position )| 3)) {
    return distance_vec[1][position];
  }

  if(memo_vec[position][mark] != 0)
  {
    return memo_vec[position][mark];
  }

  auto res = 90000000; 
  int n = distance_vec.size()-1;

  for (int j = 1; j <= n; j++)
        if ((mark & (1 << j)) && j != position && j != 1)
            res = std::min(res, TSPDynamic(mark & (~(1 << position)), j , memo_vec, distance_vec)
                                    + distance_vec[j][position]);
    return memo_vec[position][mark] = res;
}

int TSP::dynamicProgrammingAlgorithm() {

  int n = this->cities.size();
  std::vector<std::vector<int>> distance_vec(n+1);

  auto start_DP = std::chrono::steady_clock::now();

  for (auto i = 0; i < n+1; i++) {
    for (auto j = 0; j < n+1; j++) {
      if (i == j || i == 0 || j == 0)
        distance_vec[i].push_back(0);
      else
        distance_vec[i].push_back(this->distance(cities[i-1], cities[j-1]));
    }
  }


  std::vector<std::vector<int>> memo_vec;

  for(auto i = 0; i < (n + 1); i++){
    std::vector<int> tmp;
    for(auto j =0; j <( 1 << (n + 1)); j++){
      tmp.push_back(0);
    }
    memo_vec.push_back(tmp);

  }


  int solution = 90000000;
  for(auto i = 1; i <= n; i++){
    solution = std::min( solution, TSPDynamic((1 << (n + 1)) - 1, i, memo_vec, distance_vec) + distance_vec[i][1]);
  }

  auto end_DP = std::chrono::steady_clock::now();
  std::chrono::duration<double> elapsed_seconds = end_DP - start_DP;
  std::cout << "elapsed time [Dynamic Programing]: " << elapsed_seconds.count() << "s\n";

  return solution;
}