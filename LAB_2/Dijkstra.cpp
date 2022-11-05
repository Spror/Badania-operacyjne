#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

using adjacency_list_t = std::vector<std::vector<neighbor>>;

struct neighbor{
    int target;
    int  weight;
    neighbor(int target_arg): target(target_arg) {}
};



/* czytanie danych z pliku */
bool reading_from_file(const char * filename, adjacency_list_t &graph, int &start)
{
    int graph_size;
    ifstream ReadFile(filename);

    if(!ReadFile.is_open())
    {
        cerr << "read_from_file: Problem with file opening \n";
        exit(-1);
    }

    ReadFile >> start;
    ReadFile >> graph_size;
    vector<int> buffor;
    
    int temp_var;


    while(ReadFile >> temp_var)
    {
        buffor.push_back(temp_var);
    }
    
    for(auto i = 0; i < graph_size; i++)
    {
        for(auto j = 0; j < graph_size; j++)
        {

        }
        
    }

  
    
    return true;
}

int main()
{
    adjacency_list_t warehouse_graph;
    int start_vertex = 0;

    reading_from_file


    return 0;
}