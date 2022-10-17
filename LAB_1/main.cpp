#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

using AdjacencyMatrix = std::vector<std::vector<int>>;
using namespace std;


class CPM{
    public:
    int ID = -1; //ID of a vertex 
    int processTime; // całkowity czas projektu
	int dependenciesNumber = 0; // liczba zależności
    int ES = -1; // Early Start
    int EF = -1; // Early Finish
    int LS = -1; // Late Start
    int LF = -1; // Late Finish
    int TF = -1; // Total Float
    vector<int> predecessors; // NASTĘPCA (wierzchołki)
    vector<int> temp_predecessors; // NASTĘPCA (wierzchołki)
    vector<int> successors; // NASTĘPCA (wierzchołki)
    bool isEarlyDone = false;
    bool isFalseDone = false;

    void Calculate_Early(vector<CPM> &cpm_vector);
    void Calculate_Late(vector<CPM> &cpm_vector);
};

void CPM::Calculate_Late(vector<CPM> &cpm_vector)
{
    if(this->successors.size() >0)
    {
        for(auto i=0; i< this->successors.size(); i++)
        {
            if(cpm_vector[successors[i]-1].LS < this->LF || this->LF == -1)
            {
                this->LF = cpm_vector[successors[i]-1].LS;
                this->LS = this->LF - processTime;
                this->TF = this-> LF - this->EF;
            } 
        }
    }
}


void CPM::Calculate_Early(vector<CPM> &cpm_vector)
{
   if(this->predecessors.size() == 0)
   {
        this->ES = 0;
        this->EF = this->processTime;
   }

   else
   {
        for(auto i=0; i< this->predecessors.size(); i++)
        {
            if(cpm_vector[predecessors[i]-1].EF > this->ES)
            {
                this->ES = cpm_vector[predecessors[i]-1].EF;
                this->EF = this->ES + processTime;
            }
        }
   }

}


bool reading_from_file(const char * filename, AdjacencyMatrix &graph, std::vector<int> &duration_times);

std::vector<int> find_start_vertices(AdjacencyMatrix graph);

void algorihtm(AdjacencyMatrix graph,  vector<CPM> &cpm_vector);

void find_Predecessor(AdjacencyMatrix graph,  vector<CPM> &cpm_vector);

vector<int> return_next_vertices(vector<int> checked_predecessor, vector<CPM> &cpm_vector);


int main(){

    AdjacencyMatrix graph;
    std::vector<int> v_Duration_times;
    
    if(!reading_from_file("matrix_1", graph, v_Duration_times))
    {
        std::cout << "!poszlo" << std::endl;
    }

    
    for(auto & it: graph)
    {
        std::cout << std::endl;
        for(auto & it2: it)
        {
            std::cout << it2 << " ";
        }
    }

    vector<CPM>  v_CPM;
    v_CPM.reserve(graph.size());
    
    for(auto i = 1; i <= graph.size(); i++)
    {
        CPM temp;
        temp.ID = i;
        temp.processTime = v_Duration_times[i-1];
        v_CPM.push_back(temp);
    }

    algorihtm(graph, v_CPM);
    

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

void find_Predecessor(AdjacencyMatrix graph,  vector<CPM> &cpm_vector)
{
    for(auto i = 0; i < graph.size(); i++)
    {
        for(auto j = 0; j < graph.size(); j++)
        {
            if( graph[i][j] == 1)
            {
                cpm_vector[i].predecessors.push_back(j+1);
                cpm_vector[i].temp_predecessors.push_back(j+1);
            }
        }
    }
    

    for(auto i = 0; i < graph.size(); i++)
    {
        for(auto j = 0; j < graph.size(); j++)
        {
            if( graph[j][i] == 1)
            {
                cpm_vector[i].successors.push_back(j+1);
            }
        }
    }
}

vector<int> return_next_vertices(int checked_predecessor, vector<CPM> &cpm_vector)
{ 
    vector<int> buffor;
   
    for(auto & it: cpm_vector)
    {
         
        // iteruj po wszystkich elementach wektora temp_predecessors
        for (vector<int>::iterator it2 = it.temp_predecessors.begin(); it2 != it.temp_predecessors.end();) 
        {
            if(*it2 == checked_predecessor)
            {
                 it2 = it.temp_predecessors.erase(it2);
                 if(it.temp_predecessors.size() == 0)
                 {
                    buffor.push_back(it.ID);
                 }
            } 
            else
                ++it2;
        }
    }
    return buffor;
}

void algorihtm(AdjacencyMatrix graph, vector<CPM> &cpm_vector)
{

    vector<int> list_of_vertices = find_start_vertices(graph);
    vector<int> checked_predecessors;
    find_Predecessor(graph, cpm_vector);
    vector<int> temp;
   
   
    for(auto i = 0; i < cpm_vector.size(); i++)
    {
        temp = return_next_vertices(list_of_vertices[i], cpm_vector);
        for(auto j = 0; j <temp.size(); j++)
        {
            list_of_vertices.push_back(temp[j]);
        }
        temp.clear();
    }

    for(auto i =0; i < cpm_vector.size(); i++)
    {
        cpm_vector[list_of_vertices[i]-1].Calculate_Early(cpm_vector);
    }

    // Finding procces time
    int max_process_time = -1;

    for(auto i = 0; i < cpm_vector.size(); i++)
    {
        if(max_process_time < cpm_vector[i].EF)
        {
            max_process_time = cpm_vector[i].EF;
        }
    }

  
    cout << endl;

    for(auto i = cpm_vector.size(); i > 0; i--)
    {
        if(i == cpm_vector.size() || cpm_vector[list_of_vertices[i-1]-1].successors.size() == 0 )
        {
            cpm_vector[list_of_vertices[i-1]-1].LF = max_process_time;
            cpm_vector[list_of_vertices[i-1]-1].LS = max_process_time -cpm_vector[list_of_vertices[i-1]-1].processTime;
            cpm_vector[list_of_vertices[i-1]-1].TF = max_process_time -cpm_vector[list_of_vertices[i-1]-1].EF ;
        }
        else
        {
             cpm_vector[list_of_vertices[i-1]-1].Calculate_Late(cpm_vector);
        }
    }

    vector<int> critical_path;
    for(auto i = 0; i < cpm_vector.size(); i++)
    {
        if(cpm_vector[list_of_vertices[i]-1].TF == 0)
        {
            critical_path.push_back(list_of_vertices[i]);
        }
    }

    for(auto & it: cpm_vector)
    {
        cout << it.ID << ":" << it.ES << " " << it.EF << " " << it.LS << " " << it.LF  << " " << it.TF << endl;
    }

    for(auto & it: critical_path)
    {
        cout << it << " ";
    }


    
}
