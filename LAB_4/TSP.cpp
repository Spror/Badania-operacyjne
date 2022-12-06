#include "TSP.hpp"
#include <cmath>

TSP::TSP(const char * filename)
{

    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "TSP::TSP(const char * filename): Problem with file opening \n";
        exit(-1);
    }
   
    std::string str;

    while(ReadFile >> str)
    {
        if(str == "NODE_COORD_SECTION")
        {
            std::cout << str << std::endl;
            break;
        }
            
    }

    int temp;
    city temp_city;
    while(ReadFile >> temp)
    {
        temp_city.ID = temp;
        ReadFile >> temp;
        temp_city.x = temp;
        ReadFile >> temp;
        temp_city.y = temp;
        this->cities.push_back(temp_city);
    }

    ReadFile.close();
}

void TSP::printCities()
{
    for(auto &it: this->cities)
    {
        std::cout << it.ID << " " << it.x << " " << it.y << std::endl;
    }
}

int TSP::distance(city city_a, city city_b)
{
    auto disX = city_a.x-city_b.x;
    auto disY = city_a.y-city_b.y;

    return int(sqrt(disX*disX+disY*disY));
}

unsigned long TSP::calculateDistance()
{
    unsigned long distance = 0;

    for(auto i=0; i<this->cities.size()-1; i++)
    {
        auto city_a = this->cities[i];
        auto city_b = this->cities[i+1];
        distance+=this->distance(city_a, city_b);
    }

    return distance;
}