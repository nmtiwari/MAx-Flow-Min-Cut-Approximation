#include<iostream>
#include<cstdlib>

double **graph1;

using namespace std;




double** RandomGraph( double density, int NodeCounts)
{
   double **graph;
   int max_edge=NodeCounts * (NodeCounts-1);
   int edge_count=density * max_edge;

   graph = (double **)calloc(NodeCounts,sizeof(double*));
   for(int i=0;i<NodeCounts;i++)
   {

       graph[i] = (double *)calloc(NodeCounts,sizeof(double));

   }

   srand(time(NULL));

       int x=0;
       int y=0;

   for(int i = 0; i < edge_count;i++)
   {

       x=rand()%NodeCounts;
       y=rand()%NodeCounts;
       while(x==y || graph[x][y])
       {
           y=rand()%NodeCounts;
           x=rand()%NodeCounts;
       }
	//starting from here
	int z=rand()%300;
	graph[x][y]=z;
	graph[y][x]=z;
       //graph[x][y]= rand();
   }
   return graph;
}

void create_file(int NodeCount)
{
cout<<NodeCount<<endl;
for(int i=0;i<NodeCount;i++)
{
for(int j=0;j<NodeCount;j++)
{
if(graph1[i][j]!=0 && i<j)
{
cout<<i<<" "<<j<<" "<<graph1[i][j]<<endl;
}
else
{

}
}
}
}

inline double closed_interval_rand(double x0, double x1)
{
return x0 + (x1 - x0) * rand() / ((double) RAND_MAX);
}


int main()
{
//double **graph1;
srand(time(NULL));
//int NodeCounts=rand()%55;
int NodeCounts=50;
float density=closed_interval_rand(0.01,0.500);
//float density=0.09;

graph1=RandomGraph(density,NodeCounts);
create_file(NodeCounts);
/*for(int i=0;i<NodeCounts;i++)
{
for(int j=0;j<NodeCounts;j++)
{
cout<<graph1[i][j]<<" ";
}
cout<<endl;
}
*/

return(density*100);
}
