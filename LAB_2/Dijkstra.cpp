#include <iostream>
#include <vector>
#include <fstream>

using namespace std;



struct neighbor{
    int target;
    int  weight;
    neighbor(int target_arg, int weight_arg): target(target_arg), weight(weight_arg) {}
};


using adjacency_list_t = std::vector<std::vector<neighbor>>;

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

    ReadFile.close();
  

    for(auto i = 0; i < graph_size; i++)
    {
        vector<neighbor> temp_vecN;
        for(auto j = 0; j < graph_size; j++)
        {
            
            if(buffor[i*graph_size+j])
            {
                neighbor temp_neighbor((i*graph_size+j)%graph_size, buffor[i*graph_size+j]);
                temp_vecN.push_back(temp_neighbor);
            }
        }
        graph.push_back(temp_vecN);
    }

    
    
    return true;
}

void print_graph(adjacency_list_t graph)
{
     for (auto i = 0; i <graph.size(); i++)
     {

        cout << i << ": " ;
        for (auto & it: graph[i])
        {   
            cout << it.target << "//" << it.weight << "   ";
        }
        cout << endl;
     }
}


void dijkstra_algorithm(adjacency_list_t graph, int start)
{
    
}

int main()
{
    adjacency_list_t warehouse_graph;
    int start_vertex = 0;

     if(!reading_from_file("dane.txt", warehouse_graph,start_vertex)){ cout << "!poszlo" << endl; }
     print_graph(warehouse_graph);

    return 0;
}