#include "TSP.hpp"
#include <chrono>
#include <fstream>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

int main(int argc, const char *argv[]) {

  if (argc != 2) {
    std::cerr << "ERROR! Too many or too few options" << std::endl;
    return (-1);
  } else {

    TSP obj("dane.txt");
    cout << obj.calculateDistance() << endl;
    if (argv[1] == std::string("2-opt")) {
      obj.opt_2();
      cout << obj.calculateDistance() << endl;
    } else if (argv[1] == std::string("sa")) {
      obj.simulatedAnnealingAlgorithm();
      cout << obj.calculateDistance() << endl;
    } else if (argv[1] == std::string("dp")) {
      TSP obj("dane.txt");
      std::cout << std::endl
                << "Wynik: " << obj.dynamicProgrammingAlgorithm() << std::endl;

    } else {
      std::cerr << "ERROR! the program can receive only 2 possibility "
                   "\"2-opt\" or \"sa\""
                << std::endl;
      return (-1);
    }
  }

  return 0;
}