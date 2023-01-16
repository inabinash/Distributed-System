#include<bits/stdc++.h>
using namespace std;
// Doing DFS To check Connectivity
void dfs(int v,vector<int> &visited,vector<int> g[])
{
    visited[v] = 1;
    for(auto &val:g[v])
    {
        if(!visited[val])
        {
            dfs(val,visited,g);
        }
    }
}
int main()
{
    int n;
    cout<<"Enter Number of Nodes: ";
    cin>>n;
    int m;
    cout<<"Enter Number of Edges: ";
    cin>>m;
    vector<int> adjacency_list[n + 1];
    vector<vector<int>> adjacency_matrix(n + 1,vector<int>(n + 1));
    vector<int> degree(n + 1);
    cout<<"Enter the connections: "<<endl;
    for(int i=0;i<m;i++)
    {
        int u,v;
        cin>>u>>v;
        adjacency_list[u].push_back(v);
        adjacency_list[v].push_back(u);
        adjacency_matrix[u][v] = 1;
        adjacency_matrix[v][u] = 1;
    }
    vector<int> visited(n + 1);
    dfs(1,visited,adjacency_list);
    bool ok = true;
    for(int i=1;i<=n;i++)
    {
        if(!visited[i])
        {
            cout<<"The given network is not connected"<<endl;
            ok = false;
            break;
        }
    }
    if(ok)
    {
        cout<<"The given network is connected"<<endl;
    }
    for(int i=1;i<=n;i++)
    {
        degree[i] = adjacency_list[i].size();
    }
    cout<<"The Adjacency List is: "<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<i<<": ";
        for(auto &val:adjacency_list[i])
        {
            cout<<val<<" ";
        }
        cout<<endl;
    }
    cout<<"The Adjacency Matrix is: "<<endl;
    for(int i=1;i<=n;i++)
    {
        for(int j=1;j<=n;j++)
        {
            cout<<adjacency_matrix[i][j]<<" ";
        }
        cout<<endl;
    }
    cout<<"The degree of the nodes are: "<<endl;
    for(int i=1;i<=n;i++)
    {
        cout<<"The node "<<i<<" :"<<degree[i]<<endl;
    }
    return 0;
}
