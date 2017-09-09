#include <iostream>
#include <stdlib.h>
#include <set>
#include <map>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <valarray>
#include <time.h>
#include <string.h>
#include <vector>
using namespace std;
int count_ac = 0;
const int mc_simu = 5000;
//***************change this***********************************************
const int vertices = 15229;			//number of vertices in graph
map<int, vector<int> > graph[mc_simu];

//*************************Calculate influence for neighbour of each actibvated node******************************
void cal_influence(vector<vector<bool>> &tmp_active, int v, int n)
{

	set<int>::iterator it;
	double tmp;
	int size = graph[n][v].size();
    for(int i=0;i<size;i++)
    {
		
		if(tmp_active[n][graph[n][v][i]]==0)
		{
				
				tmp_active[n][graph[n][v][i]] = true;
				count_ac++;
				cal_influence(tmp_active, graph[n][v][i],n);
			
		}
	}
    		
}

//*****************************Calculate influenvce for node******************************************************
int find_influence(int v, int n, vector<vector<bool>> &tmp_active)
{
	count_ac = 0;
	set<int>::iterator it;    	
	tmp_active[n][v] = true;
	count_ac++;
	cal_influence(tmp_active, v,n);
	return count_ac;

}
void max_influence(int k, int *A)
{
	clock_t startTime = clock();
	int tmp_influence;
	ofstream myfile;									
	cout<<"\nVertices "<<vertices<<" "<<"\n";				
	bool active[vertices] = { false }; 
	vector<vector<bool>> tmp_active(mc_simu,vector<bool>(vertices, false));						//active vertices array
	vector<vector<bool>> max_active(mc_simu,vector<bool>(vertices, false));
	vector<vector<bool>> max_active2(mc_simu,vector<bool>(vertices, false));
	double avg_influence[vertices];						
	double influence[k];																		//influence in kth simulations
	double sum_inf = 0.0;
	vector<double> tmp_sum_inf(mc_simu, 0.0);
	vector<double> max_sum_inf(mc_simu, 0.0);
	vector<double> max_sum_inf2(mc_simu, 0.0);
	double max_avg = 0.0;								
	int max_ind=-1;
	cout<<"\nNode 	influence\n";
	//****************calculating spread and corresponding seed***************************************************
	myfile.open("partdbb.txt",std::ios_base::app);										
	for(int i=0; i<k; i++)
	{
		max_avg = 0.0;
		for(int j=0; j<vertices; j++)
		{
			if(active[j]==false)						//check if jth vertex is active or not
			{
				tmp_active = max_active;					//change for each mc simulations

				tmp_sum_inf = max_sum_inf;
				sum_inf = 0;
				for(int n=0; n<mc_simu; n++)
				{
					if(tmp_active[n][j]==0)
    				{	 			
						tmp_influence = find_influence(j,n,tmp_active);
					}
					else
					{
						tmp_influence = 0;
					}
					tmp_sum_inf[n] += tmp_influence;
					sum_inf += tmp_sum_inf[n];
				}
	  			avg_influence[j] = sum_inf;
	  			avg_influence[j] = avg_influence[j]/mc_simu;

	  		}
	  		else
	  			avg_influence[j] = -1;
	  		
	  		if(avg_influence[j]>max_avg)
	  		{
	  			max_avg = avg_influence[j];
	  			max_ind = j;
	  			max_active2 = tmp_active;
	  			max_sum_inf2 = tmp_sum_inf;

	  		}
	  
		}
		
		max_active = max_active2;
		max_sum_inf = max_sum_inf2;	
		influence[i] = max_avg;
		cout<<max_ind<<"\t"<<influence[i]<<" "<<i<<"\n";
		A[i] = max_ind;
		active[max_ind] = true;
		if(i==1||i==10||i==25||i==50||i==100||i==200)
              	myfile<< double( clock() - startTime ) / (double)CLOCKS_PER_SEC<<"\n";
	fflush(stdout);
	}
	myfile.close();

}
int main(int argc, char *argv[])
{
  	map<int, vector<int> >::iterator graph_it;
  	ifstream infile;
  	int a, b, x;
  	string file_name= argv[2];
    //****************reading different graphs from file************************************
    for(int m=0; m<mc_simu;m++)
    {
        file_name = file_name + to_string(m);
        infile.open(file_name);
        while (infile >> a >> b)
        {
            if(graph[m].find(a)==graph[m].end())
            {
                vector<int> tmp_set;
                tmp_set.push_back(b);
                graph[m][a] = tmp_set;
            }
            else
            {
                graph[m][a].push_back(b);
            }
            if(graph[m].find(b)==graph[m].end())
            {
                vector<int> tmp_set;
                graph[m][b] = tmp_set;
            }
        }
        infile.close();
        file_name = argv[2];
    }
    cout<<"\nGraphs loaded"<<"\n";
    clock_t startTime = clock();
    int k = stoi(argv[1]);                         //number of seeds
    int A[k];							//final set of seeds
	max_influence(k, A);				//returns A
	cout<<"\nSeed set finally:\n";
	for(int z=0; z<k; z++)
    {
        cout<<A[z]<<" ";
    }
	cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds.\n";
	return 0;
}
