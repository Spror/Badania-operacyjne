#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <queue>
using namespace std;


using matrix = vector<vector<int>>;

/* czytanie danych z pliku */
bool reading_from_file(const char * filename, matrix &graph)
{
    int graph_size;
    ifstream ReadFile(filename);

    if(!ReadFile.is_open())
    {
        cerr << "read_from_file: Problem with file opening \n";
        exit(-1);
    }
    ReadFile >> graph_size;
    vector<int> buffor;
    int temp_var;
    
    while(ReadFile >> temp_var)
    {
        buffor.push_back(temp_var);
    }

    if(buffor.size() != graph_size*graph_size)
    {
        cerr << "Reading file failed" << endl;
        exit(-1);
    }

    ReadFile.close();
    auto inc = 0;
    graph.resize(graph_size);
    
    for(auto i =0; i < buffor.size(); i++)
    {
        if(i % graph_size == 0 && i!=0)
            inc++;
        
        graph[inc].push_back(buffor[i]);
    }

    return true;
}

void print_graph(matrix graph)
{
    for(auto & it: graph)
    {
        for(auto & it2: it)
        {
            cout << it2 << " ";
        }
        cout << endl;
    }
}










int main()
{
    matrix graph;
    
    if(!reading_from_file("dane.txt", graph)){ cout << "!poszlo" << endl; }
    print_graph(graph);
 


    return 0;
}