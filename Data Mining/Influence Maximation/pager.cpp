#include "table.cpp"
#include <iostream>
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
#include <math.h>
using namespace std;
const int mc_simu = 5000;
int vertices = 15229;
vector<double> page_rank(vertices, 0.0);
int count_ac = 0;
//***************change this***********************************************

vector<vector<int>> spread(mc_simu,vector<int>(vertices, 0));
map<int, vector<int> > graph[mc_simu];
int size_s = 0;
vector<vector<bool>> tmp_active(mc_simu,vector<bool>(vertices, false));
vector<vector<bool>> max_active(mc_simu,vector<bool>(vertices, false));

struct Cmp
{
    bool operator ()(const pair<int, double> &a, const pair<int, double> &b)
    {
        return a.second < b.second;
    }
};

//***********find influence of given node**************************
int find_influence(int v, int n)
{
    tmp_active[n][v] = true;
    count_ac++;
    int size = graph[n][v].size();
    for(int i=0;i<size;i++)
    {
        
        if(tmp_active[n][graph[n][v][i]]==0)
        {
                
            find_influence(graph[n][v][i],n);
            
        }
    }
    return count_ac;
}
int main(int argc, char *argv[])
{
	Table t;
    ofstream myfile;
    myfile.open("output.txt");
	set<pair<int, double>, Cmp>::reverse_iterator it;
	set<pair<int, double>, Cmp> pg;
	t.set_delim(" ");
	int m;
	map<int, vector<int> >::iterator graph_it;
    ifstream infile;
    int a, b, x;
	t.set_numeric(true);
	string file_name=argv[2];
    //*****************calculate page rank for each graph**************************************
	for(m=0; m<mc_simu;m++)
  	{
  		file_name = file_name + to_string(m);
		t.read_file(file_name);
		t.pagerank();
		for(int i=0;i<t.pr.size(); i++)
		{
			page_rank[i]+=t.pr[i];	
		}
		file_name=argv[2];
	}
    cout<<"\nCalculated Page Rank\n";
    //****************insert pagerank into sorted set***************************************
	int size=page_rank.size();
	for(m=0;m<size;m++)
	{
		pg.insert(make_pair(m,page_rank[m]));
	}
    //***************find influence of k highest page rank nodes**********************************
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

    int k = stoi(argv[1]);                         
    cout<<"\nVertices "<<vertices<<" "<<"\n";
    bool active[vertices] = { false }; 
    int tmp_gain;
    vector<double> tmp_sum_inf(mc_simu, 0.0);
    double sum_inf = 0.0;
    int tmp_influence;
    double avg_influence[size];
    vector<double> sum_gain_v(vertices, 0.0);
    m=0;
    cout<<"\nNode   Influence"<<"\n";
    //****************************iterating each element in set upto k to find influence**************************
    for(it=pg.rbegin(); (it!=pg.rend())&&(m<k); ++it)
    {
    	m++;
		sum_inf = 0;
		for(int n=0; n<mc_simu; n++)
		{
			if(tmp_active[n][it->first]==0)
			{	 		
				count_ac=0;
				tmp_influence = find_influence(it->first,n);
			}
			else
			{
				tmp_influence = 0;
			}
			tmp_sum_inf[n] += tmp_influence;
			sum_inf += tmp_sum_inf[n];
		}
			avg_influence[it->first] = sum_inf;
			avg_influence[it->first] = avg_influence[it->first]/mc_simu;

		cout<<it->first<<"\t"<<avg_influence[it->first]<<"\n";

        if(m==1||m==10||m==25||m==50||m==100||m==200)
            myfile<<avg_influence[it->first]<<"\n";
		
	}

    return 0;
}