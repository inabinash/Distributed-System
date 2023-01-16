
#include<bits/stdc++.h>
using namespace std;
int neighbour(int node, int d)
{
if(node&(1<<d))
return node&~(1<<d);
else
return node|(1<<d);
}
int main()
{
freopen("input.txt", "r", stdin);
freopen("output.txt", "w", stdout);
int degree=5;
int nodes=1<<degree;
//cin>>nodes;
vector<vector<int>> adjacency_list(nodes+1);
vector<vector<int>> adjacency_matrix(nodes+1,vector<int>(nodes+1,0));
int next;
//cin>>edges;
for(int node=0;node<nodes;node++)
{
cout<<node<<" : ";
for(int d=0;d<degree;d++)
{
next=neighbour(node,d);
cout<<next<<" ";
adjacency_list[node].push_back(next);
adjacency_matrix[node][next]=1;
}
cout<<endl;
}
cout<<"\n\nAdjacency list of the network:\n Node\t:\t Adjacenct Nodes\n"<<endl;
for(int i=0;i<nodes;i++)
{
cout<<i<<"\t:\t";
if(adjacency_list[i].size()==0)
cout<<"NULL ";
else
{
int n=adjacency_list[i].size();
for(int j=0;j<n;j++)
{
if(j==n-1)
cout<<adjacency_list[i][j]<<endl;
else
cout<<adjacency_list[i][j]<<" ";
}
}
}
cout<<"\n\nAdjacency Matrix of the network\t \n ";
for(int i=1;i<=nodes;i++)
cout<<i<<' ';
cout<<endl;
for(int i=1;i<=nodes;i++)
{
cout<<i<<"\t";
for(int j=1;j<=nodes;j++)
cout<<adjacency_matrix[i][j]<<" ";
cout<<endl;
}
cout<<"Showing degree of every node in the network\n";
cout<<"================================";
cout<<"node \t:\t degree\n";
for(int i=1;i<=nodes;i++)
cout<<i<<"\t:\t"<<adjacency_list[i].size()<<'\n';
}
