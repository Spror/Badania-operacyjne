#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <queue>
#include "TSP.hpp"
using namespace std;



int main()
{
    TSP obj("dane.txt");

    cout << obj.calculateDistance() << endl;
 


    return 0;
}