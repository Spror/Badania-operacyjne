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


bool findPath(matrix &graph, int start, int final, vector<int> &path)
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

        for(auto i = 0; i < graph.size(); i++)
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

void fordFulkerson(matrix graph, int start, int final)
{
    matrix graph_copy = graph;
    auto graph_size = graph.size();
    auto maxFlow = 0;
    vector<int> path;
    path.resize(graph_size);
    

    
    while(findPath(graph_copy, start, final, path))
    {
        auto pathFlow = INT32_MAX;

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

    fordFulkerson(graph,0 ,14);
 


    return 0;
}