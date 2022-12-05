#include <iostream>
#include <vector>
#include <fstream>
#include <chrono>
#include <queue>
#include <set>
#include <list>



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


bool findPath(matrix graph, int start, int final, vector<int> &path)
{
    vector<bool> visited;
    visited.resize(graph.size(), 0);

    queue<int> qset;
    qset.push(start);
    visited[start] = true;
    path[start]= -1;

    while(!qset.empty())
    {
        auto u = qset.front();
        qset.pop();

        for(int i = 0; i < graph.size(); i++)
        {
            if(visited[i] == false && graph[u][i] > 0)
            {
                if(i == final)
                {
                    path[i] = u;
                    return true;
                }
                qset.push(i);
                path[i] = u;
                visited[i] = true;
            }
        }
    }
    return false;
}

bool dijkstraAlgorithm(matrix graph, int start, int final, vector<int> &path )
{
    auto graph_size = graph.size();
    vector<int> minimal_distance, previous;
    minimal_distance.clear();
    minimal_distance.resize(graph_size, INT32_MAX);
    minimal_distance[start] = 0;
    previous.resize(graph_size, -1);
    
    set<pair<int,int>> ver_queue;
    ver_queue.insert(make_pair(minimal_distance[start],start));

    while(!ver_queue.empty())
    {
        auto dist = ver_queue.begin()->first;
        auto u = ver_queue.begin()->second;
        ver_queue.erase(ver_queue.begin());
        
        const auto neighbors = graph[u];
        for(auto i = 0; i < graph_size; i++)
        {
            if(graph[u][i] != 0 )
            {
                auto v = i;
                auto weight = graph[u][i];
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
    }
    path.clear();
    path.resize(graph_size, 0);
    auto inc =final;
    for ( ; inc != -1; inc = previous[inc])
        path[inc] = previous[inc];

    if(path[final] == -1)
        return false;

    return true;
}


void fordFulkerson(matrix graph, int start, int final)
{
    matrix graph_copy = graph;
    auto graph_size = graph.size();
    auto maxFlow = 0;
    vector<int> path;
    path.resize(graph_size, 0);
    
  
    
    while(/*findPath(graph_copy, start, final, path)*/ dijkstraAlgorithm(graph_copy, start, final, path))
    {

        cout << endl;
        int pathFlow = INT32_MAX;

        for(auto i = final; i!=start; i = path[i])
        {
            auto temp = path[i];
            pathFlow = min(pathFlow, graph_copy[temp][i]);
        }

        for(auto i = final; i!=start; i = path[i])
        {
            auto temp = path[i];
            graph_copy[temp][i] -= pathFlow;
            graph_copy[i][temp] += pathFlow;
        }

        maxFlow += pathFlow;
    }

    cout << "max flow: " << maxFlow << endl;
}

int main()
{
    matrix graph;
    
    if(!reading_from_file("dane2.txt", graph)){ cout << "!poszlo" << endl; }
    print_graph(graph);

    fordFulkerson(graph, 0, graph.size()-1);
   
    
    return 0;
}