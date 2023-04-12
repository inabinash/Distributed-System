#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <netinet/in.h>

struct node 
{
	int vertex;
	struct node* next;
};
struct node* createNode(int);
struct Graph 
{
	int n;
	struct node** adjLists;
	int* degree;
};
struct node* createNode(int v)
{
	struct node* newNode = malloc(sizeof(struct node));
	newNode->vertex = v;
	newNode->next = NULL;
	return newNode;
}
struct Graph* createGraph(int vertices)
{
	struct Graph* graph = malloc(sizeof(struct Graph));
	graph->n = vertices;
	graph->adjLists = malloc(vertices * sizeof(struct node*));
	graph->degree = malloc(vertices * sizeof(int));
	int i;
	for (i = 0; i < vertices; i++)
	{
	graph->degree[i]=0;
	graph->adjLists[i] = NULL;
	}
	return graph;
}
void addEdge(struct Graph* graph, int s, int d)
{
	struct node* newNode = createNode(d);
	newNode->next = graph->adjLists[s];
	graph->adjLists[s] = newNode;
	newNode = createNode(s);
	newNode->next = graph->adjLists[d];
	graph->adjLists[d] = newNode;
	graph->degree[s] +=1;
	graph->degree[d] +=1;
}
void printGraph(struct Graph* graph) 
{
	int v;
	printf("\nAdjacency List of the Topology :-\n");
	for (v = 0; v < graph->n; v++) {
	struct node* temp = graph->adjLists[v];
	printf("Node %d ", v);
	while (temp) 
	{
		printf("-->%d ", temp->vertex);
		temp = temp->next;
	}
	printf("\t(Degree = %d)", graph->degree[v]);
	printf("\n");
	}
}
struct Graph* tree(int n)
{
	struct Graph* g= createGraph(n);
	int i=0;
	while((2*i) +1 <n)
	{
		addEdge(g, i, (2*i) +1);
		if((2*i)+2 <n)
		addEdge(g, i, (2*i)+2);
		i++;
	}
	return g;
}
struct Graph* ring(int n)
{
	struct Graph* g = createGraph(n);
	for (int v = 0; v < n; ++v)
	addEdge(g, v, (v+1)%n);
	return g;
}
struct Graph* star(int n)
{
	struct Graph* g= createGraph(n);
	for (int v = 1; v < n; ++v)
		addEdge(g, 0, v);
	return g;
}

int main()
{
	int server_sock,client_sock,len;
	struct sockaddr_in server,client;
	
	int buf[2];

	memset(&server,'\0',sizeof(server));
	memset(&client,'\0',sizeof(client));
	
	server_sock = socket(AF_INET,SOCK_STREAM,0);
	printf("Server Socket created..\n");

	server.sin_family = AF_INET;
	server.sin_port = htons(6363);
	server.sin_addr.s_addr=inet_addr("127.0.0.10");
	
	bind(server_sock,(struct sockaddr*)&server,sizeof(server));
	printf("Bind Successfully created..\n");
	
	listen(server_sock,0);
	len = sizeof(client);
	client_sock = accept(server_sock,(struct sockaddr*)&client,&len);
	while(1)
	{
		
		recv(client_sock,(int*)buf,1024,0);
		struct Graph* g=malloc(sizeof(struct Graph));
		switch(buf[0])
		{
			case 1: g = tree(buf[1]);
					break;
			case 2: g = ring(buf[1]);
					break;
			case 3: g = star(buf[1]);
					break;
			default: printf("Invalid Input\n");
					break;
		}
		//printGraph(g);
		int p=buf[1];
		int A[p][p+1];
		for(int i=0;i<p;i++)
		{
			for(int j=0;j<p+1;j++)
			{
				A[i][j]=-1;
			}
		}
		for (int v = 0; v < g->n; v++) 
		{
			struct node* temp = g->adjLists[v];
			int j=0;
			while (temp) 
			{
				A[v][j++]=temp->vertex;
				temp = temp->next;
			}
			A[v][p]=g->degree[v];
		}
		printf("Sending Solution...");
		send(client_sock,(int**)A,sizeof(A),0);
		//exit(0);
	}
}
