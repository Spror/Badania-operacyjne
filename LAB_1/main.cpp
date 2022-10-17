#include <iostream>
#include <vector>
#include <fstream>
#include <memory>

using AdjacencyMatrix = std::vector<std::vector<int>>;
using namespace std;

class CPM{
    public:
    int ID = -1; //ID of a vertex 
    int processTime; // całkowity czas wykonywania projektu
	int dependenciesNumber = 0; // liczba zależności
    int ES = -1; // Early Start
    int EF = -1; // Early Finish
    int LS = -1; // Late Start
    int LF = -1; // Late Finish
    int TF = -1; // Total Float
    vector<int> v_predecessors; // Poprzednicy (wierzchołki)
    vector<int> v_temp_predecessors; // Poprzednicy (wierzchołki) -> wektor tymczasowych poprzedników
    vector<int> v_successors; // Następcy (wierzchołki)

    void Calculate_Early(vector<CPM> &v_cpm);
    void Calculate_Late(vector<CPM> &v_cpm);
};

void CPM::Calculate_Late(vector<CPM> &v_cpm)
{
    if(this->v_successors.size() > 0)
    {
        for(auto i=0; i < this->v_successors.size(); i++)
        {
            if(v_cpm[v_successors[i]-1].LS < this->LF || this->LF == -1)
            {
                this->LF = v_cpm[v_successors[i]-1].LS;
                this->LS = this->LF - processTime;
                this->TF = this-> LF - this->EF;
            } 
        }
    }
}


void CPM::Calculate_Early(vector<CPM> &v_cpm)
{
   if(this->v_predecessors.size() == 0)
   {
        this->ES = 0;
        this->EF = this->processTime;
   }

   else
   {
        for(int i=0; i< this->v_predecessors.size(); i++)
        {
            if(v_cpm[v_predecessors[i]-1].EF > this->ES)
            {               
                this->ES = v_cpm[v_predecessors[i]-1].EF; // ES = najpóźniejszy z EF wszystkich poprzedników
                this->EF = this->ES + processTime; // EF = ES + czas trwania operacji
            }
        }
   }

}

bool reading_from_file(const char * filename, AdjacencyMatrix &graph, vector<int> &v_duration_times);
vector<int> v_find_start_vertices(AdjacencyMatrix graph);
void algorihtm(AdjacencyMatrix graph, vector<CPM> &v_cpm);
void find_Predecessor(AdjacencyMatrix graph, vector<CPM> &v_cpm);
vector<int> v_return_next_vertices(vector<int> checked_predecessor, vector<CPM> &v_cpm);


int main()
{
    AdjacencyMatrix graph;
    vector<int> v_Duration_times;
    
    if(!reading_from_file("matrix_1", graph, v_Duration_times)){ cout << "!poszlo" << endl; }
    
    for(auto & it: graph)
    {
        cout << endl;
        for(auto & it2: it){ cout << it2 << " "; }
    }

    vector<CPM> v_CPM;
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


bool reading_from_file(const char * filename, AdjacencyMatrix &graph,  vector<int> &v_duration_times)
{
    ifstream ReadFile(filename);
    if(!ReadFile.is_open())
    {
        cerr << "read_from_file: Problem with file opening \n";
        exit(-1);
    }

    vector<int> data_buff_1;
    vector<int> data_buff_2;
    data_buff_1.clear();
    data_buff_2.clear();
    unsigned int N, M, temp_var;

    ReadFile >> N >> M;
    cout << N << " " << M << endl;

    for(int i=0; i < N; i++)
    {
        ReadFile >> temp_var;
        data_buff_1.push_back(temp_var);
    }
    
    while(ReadFile >> temp_var){ data_buff_2.push_back(temp_var); } 
    graph.resize(N);
    
    for(auto & it: graph){ it.resize(N); } 
    for(auto i = 0; i < data_buff_2.size(); i+=2)
    {
        graph[data_buff_2[i+1]-1][data_buff_2[i]-1]=1;
    }
    
    v_duration_times = data_buff_1;
    ReadFile.close();
    return true;
}

vector<int> v_find_start_vertices(AdjacencyMatrix graph)
{
    vector<int> v_starts_vertices;

    for(int i = 1; i <= graph.size(); i++)
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

void find_Predecessor(AdjacencyMatrix graph,  vector<CPM> &v_cpm)
{
    for(auto i = 0; i < graph.size(); i++)
    {
        for(auto j = 0; j < graph.size(); j++)
        {
            if( graph[i][j] == 1)
            {
                v_cpm[i].v_predecessors.push_back(j+1);
                v_cpm[i].v_temp_predecessors.push_back(j+1);
            }
        }
    }
    

    for(int i = 0; i < graph.size(); i++)
    {
        for(int j = 0; j < graph.size(); j++)
        {
            if( graph[j][i] == 1)
            {
                v_cpm[i].v_successors.push_back(j+1);
            }
        }
    }
}

vector<int> v_return_next_vertices(int checked_predecessor, vector<CPM> &v_cpm)
{ 
    vector<int> buffor;
   
    for(auto & it: v_cpm)
    {        
        // iteruj po wszystkich elementach wektora v_temp_predecessors
        for (vector<int>::iterator it2 = it.v_temp_predecessors.begin(); it2 != it.v_temp_predecessors.end();) 
        {
            if(*it2 == checked_predecessor)
            {
                 it2 = it.v_temp_predecessors.erase(it2);
                 if(it.v_temp_predecessors.size() == 0)
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

void algorihtm(AdjacencyMatrix graph, vector<CPM> &v_cpm)
{
    vector<int> list_of_vertices = v_find_start_vertices(graph);
    vector<int> checked_predecessors;
    find_Predecessor(graph, v_cpm);
    vector<int> temp;
     
    for(int i = 0; i < v_cpm.size(); i++)
    {
        temp = v_return_next_vertices(list_of_vertices[i], v_cpm);
        for(int j = 0; j <temp.size(); j++)
        {
            list_of_vertices.push_back(temp[j]);
        }
        temp.clear();
    }

    for(int i =0; i < v_cpm.size(); i++)
    {
        v_cpm[list_of_vertices[i]-1].Calculate_Early(v_cpm);
    }

    // Finding procces time
    int max_time = -1; // max process time

    for(int i = 0; i < v_cpm.size(); i++)
    {
        if(max_time < v_cpm[i].EF){ max_time = v_cpm[i].EF; }
    }

    cout << endl;

    for(int i = v_cpm.size(); i > 0; i--)
    {
        if(i == v_cpm.size() || v_cpm[list_of_vertices[i-1]-1].v_successors.size() == 0 )
        {
            v_cpm[list_of_vertices[i-1]-1].LF = max_time;
            v_cpm[list_of_vertices[i-1]-1].LS = max_time -v_cpm[list_of_vertices[i-1]-1].processTime;
            v_cpm[list_of_vertices[i-1]-1].TF = max_time -v_cpm[list_of_vertices[i-1]-1].EF ;
        }
        else
        {
             v_cpm[list_of_vertices[i-1]-1].Calculate_Late(v_cpm);
        }
    }

    vector<int> critical_path;
    for(int i = 0; i < v_cpm.size(); i++)
    {
        if(v_cpm[list_of_vertices[i]-1].TF == 0)
        {
            critical_path.push_back(list_of_vertices[i]);
        }
    }

    for(auto & it: v_cpm) { cout << it.ID << ":" << it.ES << " " << it.EF << " " << it.LS << " " << it.LF  << " " << it.TF << endl; }
    for(auto & it: critical_path){ cout << it << " "; }
}
