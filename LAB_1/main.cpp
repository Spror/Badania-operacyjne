#include <iostream>
#include <vector>
#include <fstream>
#include <memory>


using AdjacencyMatrix = std::vector<std::vector<int>>;
using namespace std;


class CPM{
    public:
    int processTime; // całkowity czas projektu
	int Dependencies = 0;
    int ES = -1; // Early Start
    int EF = -1; // Early Finish
    int LS = -1; // Late Start
    int LF = -1; // Late Finish

    void Calculate_Early(int tasks);
    void Calculate_Late(int tasks);
    void PrintResults(); 
};


void CPM::Calculate_Early(int tasks){
    if(ES == -1)
    {
        if(Dependencies == 0)
        {
            ES = 0;
        } 
        else 
        {
            // obliczenia
        }
        EF = ES + processTime;
    }

}








bool reading_from_file(const char * filename, AdjacencyMatrix &graph, std::vector<int> &duration_times);
std::vector<int> find_start_vertices(AdjacencyMatrix graph);


int main(){

    AdjacencyMatrix graph;
    std::vector<int> v_Duration_times;
    
    if(!reading_from_file("matrix_1", graph, v_Duration_times))
    {
        std::cout << "!poszlo" << std::endl;
    }

    std::vector<int> v_starts_vertices = find_start_vertices(graph);

    for(auto & it: graph)
    {
        std::cout << std::endl;
        for(auto & it2: it)
        {
            std::cout << it2 << " ";
        }

    }

    std::cout << std::endl;

    for(auto const & it: v_starts_vertices)
    {
        std::cout << it << std::endl;
    }

    return 0;
}


bool reading_from_file(const char * filename, AdjacencyMatrix &graph,  std::vector<int> &duration_times)
{
    std::ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        std::cerr << "read_from_file: Problem with file opening \n";
        exit(-1);
    }

    std::vector<int> data_buff_1;
    std::vector<int> data_buff_2;
    data_buff_1.clear();
    data_buff_2.clear();
    unsigned int N, M, temp_var;

    ReadFile >> N >> M;
    std::cout << N << " " << M << std::endl;

    for(auto i = 0; i < N; i++)
    {
        ReadFile >> temp_var;
        data_buff_1.push_back(temp_var);
    }
    
    while(ReadFile >> temp_var)
    {
        data_buff_2.push_back(temp_var);
    }
    

    graph.resize(N);
    
    for(auto & it: graph)
    {
        it.resize(N);

    }
    
    for(auto i = 0; i < data_buff_2.size(); i+=2)
    {
        graph[data_buff_2[i+1]-1][data_buff_2[i]-1]=1;
    }
    
    duration_times = data_buff_1;
    ReadFile.close();
    return true;
}

std::vector<int> find_start_vertices(AdjacencyMatrix graph)
{

    std::vector<int> v_starts_vertices;

    for(auto i = 1; i <= graph.size(); i++)
    {
        bool start_vertex = true;
        for(auto const & it: graph[i-1])
        {
            if(it == 1)
            {
                start_vertex = false;
                break;
            }
        }
        if(start_vertex)
        {
            v_starts_vertices.push_back(i);
        }
    }

    return v_starts_vertices;
}