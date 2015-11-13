#include<iostream>
#include<cmath>
#include<string>
#include<cstring>
#include<algorithm>
#include<vector>
#include<map>
#include<queue>
#include<stack>
#include<stack>
#include<stdio.h>
#include<fstream>
#include<cstdio>










using namespace std;


class llink
{
public:
	int vertex,weight;
};









class node
{
public:
	vector<int>vertices;
	vector<llink>adjlist;
	int upperbound;
};









class stk_elt
{

public:
	vector<int>n1;
	int wt;
	stk_elt(vector<int>v,int w)
	{
	n1.assign(v.begin(),v.end());
	wt=w;
	}
};








class elt
{
	public:
	int upperbound;
	int index;
	elt(int u,int v)
	{
	upperbound=u;
	index=v;
	}
};





//compare fn to be used for sorting

bool cmp(elt a,elt b)
{
	return a.upperbound<b.upperbound;
}




stack<stk_elt>stk;


void merge(vector<node> & graph,vector<elt>& order,int n1,int n2,int profit);








int our()
{
ifstream fin("Min_Cut_Tree_in.txt");//input from Min_Cut_Tree_in.txt


//declare graph



vector<node>graph;

//initialize graph and read input

int num_vertices_org_graph,num_vertices_cur_graph;


//cout<<Enter the number of vertices in grapg:"<<endl;
fin>>num_vertices_org_graph;




for(int i=0;i<num_vertices_org_graph;i++)
{
node temp;
temp.vertices.push_back(i);
temp.adjlist.clear();
graph.push_back(temp);
}




//cout<"Enter edge details:<Start vertex><end vertex><weight>"<<endl;
//cout<<enter -1 to indicate End of Input"<<endl;
int start,end,weight;
while(fin>>start && start!=-1)
{
fin>>end>>weight;
llink temp;
temp.vertex=end;
temp.weight=weight;
//Edge start->end
graph[start].adjlist.push_back(temp);
//graph is undirected.So edge is bidirectional
temp.vertex=start;
/*Edge end->start*/
graph[end].adjlist.push_back(temp);

}//end while loop





num_vertices_cur_graph=num_vertices_org_graph;


vector<elt>order;   //to take vertices in increasing order of upperbound value





//calculate upperbound values of each node
int sum;

for(int i=0;i<graph.size();i++)
{
sum=0;
for(int j=0;j<graph[i].adjlist.size();j++)
{
sum+=graph[i].adjlist[j].weight;
}
graph[i].upperbound=sum;
order.push_back(elt(sum,i));

}//end for i


//display upperbounds of node
/*
for(int i=0;i<graph.size();i++)
{
cout<<graph[i].upperbound<<endl;
}
*/







//declare flow matrix and initialise it
int flow_matrix[num_vertices_org_graph][num_vertices_org_graph];
for(int i=0;i<num_vertices_org_graph;i++)
{
for(int j=0;j<num_vertices_org_graph;j++)
{
flow_matrix[i][j]=min(graph[i].upperbound,graph[j].upperbound);
}
}





//display flow matrix
/*
for(int i=0;i<num_vertices_org_graph;i++)
{
for(int j=0;j<num_vertices_org_graph;j++)
{
cout<<flow_matrix[i][j]<<" ";
}
cout<<endl;
}
cout<<endl<<endl;
*/

while(num_vertices_cur_graph>1)
{
sort(order.begin(),order.end(),cmp);

int profit=-10000000;//int_min
int n1,n2;
for(int i=0;i<num_vertices_cur_graph;i++)
{
int node_under_consideration=order[i].index;
for(int j=0;j<graph[node_under_consideration].adjlist.size();j++)
{
int tmp=graph[node_under_consideration].adjlist[j].vertex;//.edge;
//node_under_consideration-->tmp;
//int t1=graph[tmp].upperbound;
int temp_profit=2*graph[node_under_consideration].adjlist[j].weight-graph[tmp].upperbound;
int temp_profit2=2*graph[node_under_consideration].adjlist[j].weight-graph[node_under_consideration].upperbound;

if(temp_profit>profit)
{
profit=temp_profit;
n1=node_under_consideration;
n2=tmp;
}


if(temp_profit>0)
{
merge(graph,order,n1,n2,profit);
break;
}


if(temp_profit2>0)
{
profit=temp_profit2;
merge(graph,order,tmp,node_under_consideration,temp_profit2);
break;
}
}//end for j


if(profit>0)
{
break;
}
}



if(profit<=0)
{
//merge n1 and n2 with loss=-profit
merge(graph,order,n1,n2,profit);
}

num_vertices_cur_graph--;

}//end while


//calcualate and print matrix
///*

int arr[num_vertices_org_graph];

/*
while(!stk.empty())
{
stk_elt temp=stk.top();
stk.pop();

for(int i=0;i<num_vertices_org_graph;i++)
arr[i]=0;

for(int i=0;i<temp.n1.size();i++)
{
arr[temp.n1[i]]=1;
}


for(int i=0;i<temp.n1.size();i++)
{
for(int j=0;j<num_vertices_org_graph;j++)
{
if(arr[j]==0)
{
flow_matrix[temp.n1[i]][j]=min(temp.wt,flow_matrix[temp.n1[i]][j]);
flow_matrix[j][temp.n1[i]]=min(temp.wt,flow_matrix[j][temp.n1[i]]);
}
}
}

}//end while

*/

/*//print flow matrix
for(int i=0;i<num_vertices_org_graph;i++)
{
for(int j=0;j<num_vertices_org_graph;j++)
{
if(i==j)
cout<<"0 ";
else
cout<<flow_matrix[i][j]<<" ";
}
cout<<endl;
}
//*/
stk_elt min=stk.top();
while(!stk.empty())
{

stk_elt temp=stk.top();
if(min.wt>temp.wt)
{
min=temp;
}
stk.pop();

}

//cout<<min.wt;
return min.wt;



}//our

























void merge(vector<node>& graph,vector<elt>& order,int n1,int n2,int profit)
{
//merge n1 and n2
//update order
//update stack also

node tmp;
//calculatte vertices of now node
tmp.vertices.assign(graph[n1].vertices.begin(),graph[n1].vertices.end());
for(int i=0;i<graph[n2].vertices.size();i++)
{
tmp.vertices.push_back(graph[n2].vertices[i]);
}

//upperbound of new node
tmp.upperbound=graph[n1].upperbound-profit;

//push in stack
int n=graph[n1].upperbound<graph[n2].upperbound?n1:n2;
stk.push(stk_elt(graph[n].vertices,graph[n].upperbound));
//cout<<"lower of two upper bounds is:"<<graph[n].upperbound<<endl<<endl;
int num_vertices_cur_graph=graph.size();

int arr[num_vertices_cur_graph];

for(int i=0;i<num_vertices_cur_graph;i++)
arr[i]=0;


//traverse adlist of n1


for(int i=0;i<graph[n1].adjlist.size();i++)
{
int v=graph[n1].adjlist[i].vertex;//edge n1-->v
if(v==n2) continue;

arr[v]+=graph[n1].adjlist[i].weight;

for(int j=0;j<graph[v].adjlist.size();j++)
{
if(graph[v].adjlist[j].vertex==n1)
{
graph[v].adjlist[j].vertex=num_vertices_cur_graph;
break;
}//end if
}//end for j

}//end for i








//traverse adjlist of n2
for(int i=0;i<graph[n2].adjlist.size();i++)
	{
	int v=graph[n2].adjlist[i].vertex;//edge n2-->v
	if(v==n1)    continue;

	for(int j=0;j<graph[v].adjlist.size();j++)
		{
		if(graph[v].adjlist[j].vertex==n2)
			{
			if(arr[v]>0)
				{
				//delete n2 from v's adjlist
				graph[v].adjlist.erase((graph[v].adjlist.begin()+j));
				for(int k=0;k<graph[v].adjlist.size();k++)
					{
						if(graph[v].adjlist[k].vertex==num_vertices_cur_graph)	
						{
						graph[v].adjlist[k].weight+=graph[n2].adjlist[i].weight;
						break;
						}
					}
				}
		else
		{		
		graph[v].adjlist[j].vertex=num_vertices_cur_graph;
		}
	break;


		}//end if
}//end for j

arr[v]+=graph[n2].adjlist[i].weight;
}



//prepare adjlist of new node
for(int i=0;i<num_vertices_cur_graph;i++)
{
if(arr[i]>0)
{
llink t;
t.weight=arr[i];
t.vertex=i;
tmp.adjlist.push_back(t);
}
}

//push new node in graph
graph.push_back(tmp);

//delete n1 and n2 from graph

int min_n=min(n1,n2);
int max_n=max(n1,n2);
graph.erase(graph.begin()+max_n);
graph.erase(graph.begin()+min_n);
//update adjlista

for(int i=0;i<graph.size();i++)
{
for(int j=0;j<graph[i].adjlist.size();j++)
{
if(graph[i].adjlist[j].vertex>min_n && graph[i].adjlist[j].vertex<max_n)
graph[i].adjlist[j].vertex-=1;
else if(graph[i].adjlist[j].vertex>max_n)
graph[i].adjlist[j].vertex-=2;

}
}


//update order
int x1,x2;
order.push_back(elt(tmp.upperbound,num_vertices_cur_graph));
for(int i=0;i<=num_vertices_cur_graph;i++)
{
if(order[i].index==n1)
x1=i;
else if(order[i].index==n2)
x2=i;
else if(order[i].index>max_n)
order[i].index-=2;
else if(order[i].index>min_n)
order[i].index-=1;
}
order.erase(order.begin()+max(x1,x2));
order.erase(order.begin()+min(x1,x2));

}//merge





















int their()
{
ifstream fin("Min_Cut_Tree_in.txt");//input from Min_Cut_Tree_in.txt
int best=-1;
int next_vertex=-1;
int phasecut=0;
int min;
//declare graph


vector<int>phase_cut;
vector<node>graph;

//initialize graph and read input

int num_vertices_org_graph,num_vertices_cur_graph;


//cout<<Enter the number of vertices in grapg:"<<endl;
fin>>num_vertices_org_graph;



for(int i=0;i<num_vertices_org_graph;i++)
{
node temp;
temp.vertices.push_back(i);
temp.adjlist.clear();
graph.push_back(temp);
}





//cout<"Enter edge details:<Start vertex><end vertex><weight>"<<endl;
//cout<<enter -1 to indicate End of Input"<<endl;
int start,end,weight;
while(fin>>start && start!=-1)
{
fin>>end>>weight;
llink temp;
temp.vertex=end;
temp.weight=weight;
//Edge start->end
graph[start].adjlist.push_back(temp);
//graph is undirected.So edge is bidirectional
temp.vertex=start;
/*Edge end->start*/
graph[end].adjlist.push_back(temp);

}//end while loop


int set[num_vertices_org_graph];
int status[num_vertices_org_graph-1][num_vertices_org_graph];


for(int k=0;k<num_vertices_org_graph;k++)
{
for(int i=0;i<num_vertices_org_graph;i++)
{
 set[i]=0;
}
set[k]=1;

for(int i=0;i<num_vertices_org_graph-2;i++)
{
 for(int j=0;j<num_vertices_org_graph;j++)
 status[i][j]=0;
}






for(int l=0;l<num_vertices_org_graph;l++)
   {

    if(set[l]==1)
    {
        for(int j=0;j<graph[l].adjlist.size();j++)
        {
	         if(set[graph[l].adjlist[j].vertex]==0)
        	 {
  	        phasecut=phasecut+graph[l].adjlist[j].weight;
        	 }
       	   else
		     {

	         }

        }
    }

   }
//   cout<<"phase cut for phase 0"<<" "<<phasecut<<endl<<endl<<endl;

    phase_cut.push_back(phasecut);
    phasecut=0;
for(int a=0;a<num_vertices_org_graph;a++)
   {
    status[0][a]=set[a];
   }









for(int k=0;k<num_vertices_org_graph-2;k++)
{


//cout<<"running for phase"<<(k+1)<<endl;

     for(int i=0;i<num_vertices_org_graph;i++)
 {
  //   cout<<"checking in node"<<i<<endl;
  if(set[i]==1)
  {
    //  cout<<"in list of node"<<i<<endl;
    for(int j=0;j<graph[i].adjlist.size();j++)
    {
        if(set[graph[i].adjlist[j].vertex]==0)
        {
            if(best<graph[i].adjlist[j].weight)
            {
            best=graph[i].adjlist[j].weight;
            next_vertex=graph[i].adjlist[j].vertex;
            }
        }
    }
  }
 }
   set[next_vertex]=1;
  best=-1;
   //cout<<"next vertex is="<<next_vertex<<endl;
/*for(int a=0;a<num_vertices_org_graph;a++)
   {
    status[(k+1)][a]=set[a];
    cout<<status[k][a]<<" ";
   }

*/

  // cout<<"finding phase cut for phase"<<(k+1)<<endl;
   for(int l=0;l<num_vertices_org_graph;l++)
   {

    if(set[l]==1)
    {
        for(int j=0;j<graph[l].adjlist.size();j++)
        {
	         if(set[graph[l].adjlist[j].vertex]==0)
        	 {
  	        phasecut=phasecut+graph[l].adjlist[j].weight;
        	 }
       	   else
		     {

	         }

        }
    }

   }
   //cout<<"phase cut for phase"<<k+1<<" "<<phasecut<<endl<<endl<<endl;

    phase_cut.push_back(phasecut);
    phasecut=0;


/*for(int a=0;a<num_vertices_org_graph;a++)
   {
    status[k][a]=set[a];
   }
*/







//cout<<endl<<endl<<endl<<endl;

}
 min=phase_cut[0];
 int phase=0;
 for(int a=0;a<phase_cut.size();a++)
 {
 if(min>phase_cut[a])
 {
  min=phase_cut[a];
  phase=a;
 }
 }
//cout<<min;

/*
for(int a=0;a<num_vertices_org_graph;a++)
{

 cout<<status[phase][a]<<" ";
}
*/
}
//cout<<" "<<min<<endl;
return min;
}





int main()
{
cout<<"running the project..."<<endl;
cout<<endl<<endl;
sleep(2);
cout<<"running your algorithm..."<<endl;
cout<<endl;
int our_result=our();
sleep(2);
cout<<"running their algoritm..."<<endl;
cout<<endl;
int their_result=their();
sleep(2);
cout<<"************************************************************************************************************"<<endl;
cout<<"												your result= "<<our_result<<endl;
cout<<"												their result= "<<their_result<<endl;
int error=their_result-our_result;
cout<<"												error="<<error<<endl;
int percentage_error=(error*100)/their_result;
cout<<"												percentage error="<<percentage_error<<endl;
cout<<"************************************************************************************************************"<<endl;
if(error==0)
cout<<"\t\t\tCongratulations !!!!!!      you got no error.";
else
cout<<"Something Went wrong you got"<<percentage_error<<"%  \\error"<<endl;
}
