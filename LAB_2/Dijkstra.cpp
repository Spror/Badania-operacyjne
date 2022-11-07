#include <iostream>
#include <vector>
#include <fstream>
#include <set>
#include <list>
#include <utility> 
#include <algorithm>
#include <iterator>

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
    auto graph_size = graph.size();
    std::vector<int> minimal_distance, previous;
    minimal_distance.clear();
    minimal_distance.resize(graph_size, INT32_MAX);
    minimal_distance[start] = 0;
    previous.resize(graph_size, -1);

    std::set<pair<int,int>> ver_queue;
    ver_queue.insert(std:: make_pair(minimal_distance[start],start));

    while(!ver_queue.empty())
    {
        auto dist = ver_queue.begin()->first;
        auto u = ver_queue.begin()->second;
        ver_queue.erase(ver_queue.begin());
        
        const auto neighbors = graph[u];
        for(vector<neighbor>::const_iterator neighbor_iter = neighbors.begin(); neighbor_iter != neighbors.end(); neighbor_iter++)
        {
            auto v = neighbor_iter->target;
            auto weight = neighbor_iter->weight;
            auto distance_through_u = dist + weight;
	        if (distance_through_u < minimal_distance[v]) 
            {
                ver_queue.erase(make_pair(minimal_distance[v], v));

                minimal_distance[v] = distance_through_u;
                previous[v] = u;
                ver_queue.insert(make_pair(minimal_distance[v], v));

	         }
        }

    }
    list<int> path;
    
    for(auto i = 0; i < graph.size(); i++)
    {
        auto final = i;
        for ( ; final != -1; final = previous[final])
            path.push_front(final);

        cout << start << "-->" << i << "   " ;
        for (auto & it: path)
        {
            cout << it << " ";
        }
        cout << " min distance: " << minimal_distance[i]<< endl;
        path.clear();
    }


}

int main()
{
    adjacency_list_t warehouse_graph;
    int start_vertex = 0;

     if(!reading_from_file("dane.txt", warehouse_graph,start_vertex)){ cout << "!poszlo" << endl; }
     print_graph(warehouse_graph);
     dijkstra_algorithm(warehouse_graph, start_vertex);

    return 0;
}