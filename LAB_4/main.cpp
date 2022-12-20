#include "TSP.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main() {
  TSP obj("dane.txt");

  cout << obj.calculateDistance() << endl;
  obj.opt_2();
  cout << obj.calculateDistance() << endl;

  return 0;
}