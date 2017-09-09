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
int count_ac = 0;

//***************change this***********************************************
//int vertices = 15229;
const int vertices = 15229;
vector<vector<int>> spread(mc_simu,vector<int>(vertices, 0));
map<int, vector<int> > graph[mc_simu];
int size_s = 0;
vector<vector<bool>> tmp_active(mc_simu,vector<bool>(vertices, false));
vector<vector<bool>> max_active(mc_simu,vector<bool>(vertices, false));



//*******************************max_heap formation for optimization*****************************
struct  node{
    int u;
    double mg;
    int flag;
    int height;
    int size;
    node *left;
    node *right;
};
node *heap=NULL; 
void swap(int *a, int *b)
{
    int t = *a; *a = *b; *b = t;
}
 
int max(int a, int b){
    return (a>b)?a:b;
}
 
node* createNode(int val,double gain)
{
    node *temp = new node();
    temp->u = val;
    temp->mg=gain;
    temp->flag=0;
    temp->size=1;
    temp->height=0;
    temp->left=NULL;
    temp->right=NULL;
}
 
int Size(node *t)
{
    if(t==NULL)
        return 0;
    else
        return t->size;
}
 
int Height(node *t)
{
    if(t==NULL)
        return -1;
    else
        return t->height;
}
 
void updateHeightSize(node *t)
{
    t->height = max(Height(t->left),
                        Height(t->right))+1;
    t->size = Size(t->left) + Size(t->right)+1;
}
 
node* insert(node *n, int val, double gain)
{
    if(n==NULL){
        n = createNode(val,gain);
        return n;
    }
    if(n->left==NULL ||Size(n->left)< int(pow(2, Height(n->left)+1))-1 ||Size(n->right)==Size(n->left)) 
        n->left = insert(n->left,val,gain);
    else
        n->right = insert(n->right,val,gain);
 
    if((n->left!=NULL && n->left->mg > n->mg) ||(n->right!=NULL && n->right->mg>n->mg)){
        if(n->left==NULL){
            swap(n->mg, n->right->mg);
            swap(n->u, n->right->u);
            swap(n->flag, n->right->flag);
        }
        else if(n->right==NULL){
            swap(n->mg, n->left->mg);
            swap(n->u, n->left->u);
            swap(n->flag, n->left->flag);
        }
        else{
            if(n->left->mg > n->right->mg){
                swap(n->mg, n->left->mg);
                swap(n->u, n->left->u);
                swap(n->flag, n->left->flag);
            }
            else{
                swap(n->mg, n->right->mg);
                swap(n->u, n->right->u);
                swap(n->flag, n->right->flag);
            }
        }
    }
 
    updateHeightSize(n);
    return n;
}
 
int top(node *root){
    return root->mg;
}
 
void heapify(node *n)
{
    if(!n)
        return;
    while((n->left!=NULL && n->left->mg>n->mg) ||(n->right!=NULL && n->right->mg>n->mg)){
        if(n->left==NULL){
            swap(n->mg, n->right->mg);
            swap(n->u, n->right->u);
            swap(n->flag, n->right->flag);
            n = n->right;
        }
        else if(n->right==NULL){
            swap(n->mg, n->left->mg);
            swap(n->u, n->left->u);
            swap(n->flag, n->left->flag);
            n = n->left;
        }
        else{
            if(n->left->mg > n->right->mg){
                swap(n->mg, n->left->mg);
                swap(n->u, n->left->u);
                swap(n->flag, n->left->flag);
                n = n->left;
            }
            else{
                swap(n->mg, n->right->mg);
                swap(n->u, n->right->u);
                swap(n->flag, n->right->flag);
                n = n->right;
            }
        }
    }
}
 
node* remove(node *n, node *root)
{
    if(n==NULL)
        return NULL;
    if(n->left==NULL && n->right==NULL){
        swap(root->mg, n->mg);
        swap(root->u, n->u);
        swap(root->flag, n->flag);
        delete n;
        return NULL;
    }
    else if(Size(n->left) > Size(n->right))
        n->left = remove(n->left, root);
    else
        n->right = remove(n->right, root);
 
    updateHeightSize(n);
}
 
void pop(node **heap)
{
    *heap = remove(*heap, *heap);
    heapify(*heap);
}
 
void display(node *x)
{
    if(!x)
        return;
    display(x->left);
    cout<<x->mg<<" ";
    cout<<x->u<<"\n";    
    display(x->right);
}

//************************Optimization code actually starts here*******************************************

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
int find2_influence(int v, int n)
{

    max_active[n][v] = true;
    count_ac++;
    int size = graph[n][v].size();
    for(int i=0;i<size;i++)
    {
        
        if(max_active[n][graph[n][v][i]]==0)
        {
                
            find2_influence(graph[n][v][i],n);
            
        }
    }
    return count_ac;

}
void update_spread(int j, int n, int sp)
{
    if(!spread[n][j])
    {
        int size = graph[n][j].size();
        spread[n][j] = sp;   
        for(int i=0;i<size;i++)
        {
            update_spread(graph[n][j][i],n,sp);
        }
    }
    
}
void max_influence(int k, int *S)
{
	clock_t startTime = clock();
	ofstream myfile;
	double total=0.0;
    cout<<"\nVertices "<<vertices<<" "<<"\n";
    bool active[vertices] {0}; 
    int tmp_gain;
    double sum_gain = 0.0;
    vector<double> sum_gain_v(vertices, 0.0);
    vector<double> influence(k,0.0);
    //**************************calculating spread for each node first time*********************************
    for(int n=0; n<mc_simu; n++)
    {

        tmp_active[n] = max_active[n];        
        for(int j=0; j<vertices; j++)
        {
            if(spread[n][j]==0)
            {
                count_ac = 0;
                update_spread(j,n,find_influence(j,n));
            }
            sum_gain_v[j] += spread[n][j];
            if(n==mc_simu-1)
            {
                sum_gain_v[j] = sum_gain_v[j]/mc_simu;
            
                heap = insert(heap,j,sum_gain_v[j]);
            }
            
        }
        

    }

    cout<<"\nDone influence calculation for each node"<<"\n";
    
    tmp_active = max_active;
    cout<<"\nnode 	gain 	spread\n";
    //myfile.open("output.txt");

    // myfile.open("partda.txt",std::ios_base::app);					//uncomment for partd b

    //****************************************calculating seed set***********************************************
    while(size_s<k)
    {
        if(heap->flag==size_s)
        {
            S[size_s] = heap->u;
            size_s++;
            sum_gain = 0;
            for(int n=0; n<mc_simu; n++)
            {
                if(max_active[n][heap->u]==0)
                {               
                    count_ac = 0;
                    
                    tmp_gain = find2_influence(heap->u,n);			//find influence of selected node

                }
                else
                {
                    tmp_gain = 0;
                }
                sum_gain += tmp_gain;
            }
            sum_gain = sum_gain/mc_simu;
            total+=sum_gain;
            influence[size_s-1]=total;
            cout<<heap->u<<"\t"<<sum_gain<<"\t"<<influence[size_s-1]<<"\n";
            //********************************uncomment this for part (a)************************************

            // if(size_s==1||size_s==10||size_s==25||size_s==50||size_s==100||size_s==200)
            // 	myfile<<influence[size_s-1]<<"\n";

            //********************************uncomment this for part (d)(a) time************************************

            // if(size_s==1||size_s==10||size_s==25||size_s==50||size_s==100||size_s==200)
            //   	myfile<< double( clock() - startTime ) / (double)CLOCKS_PER_SEC<<"\n";
            //********************************uncomment this for part (d)(b) time************************************

            // if(size_s==50)
            //   	myfile<< double( clock() - startTime ) / (double)CLOCKS_PER_SEC<<"\n";

            pop(&heap);

        }
        else
        {

            sum_gain = 0;
            for(int n=0; n<mc_simu; n++)
            {
                if(max_active[n][heap->u]==0)
                {               
                    count_ac = 0;
                    tmp_gain = spread[n][heap->u];
                }
                else
                {
                    tmp_gain = 0;
                }
                sum_gain += tmp_gain;
            }
            sum_gain = sum_gain/mc_simu;

            heap->mg= sum_gain; 
            heap->flag = size_s;
            heapify(heap);

        }
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
    int k = stoi(argv[1]);                         	//number of seeds
    int S[k];                           			//final set of seeds
    max_influence(k, S);             				//returns Seed set
    cout<<"\nSeed set finally:\n";
    //*************************print seed set**********************************************
    for(int z=0; z<k; z++)
    {
        cout<<S[z]<<" ";
    }
    cout<<"\n" << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds.\n";
    return 0;
}
