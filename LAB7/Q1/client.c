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

void printGraph(struct Graph* graph) 
{
	int v;
	printf("\nAdjacency List of the Topology :-\n");
	for (v = 0; v < graph->n; v++) 
    {
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
int main()
{
	int serverSocket;
	struct sockaddr_in clientAddr;
	//char buf[1024];
    int buf[2];
	serverSocket =	socket(AF_INET,SOCK_STREAM,0);
	printf("socket created...\n");
	
	memset(&clientAddr,'\0',sizeof(clientAddr));
	
	clientAddr.sin_family = AF_INET;
	clientAddr.sin_port = htons(6363);
	//clientAddr.sin_addr.s_addr=inet_addr("192.168.124.255");
	clientAddr.sin_addr.s_addr=inet_addr("127.0.0.10");

	connect(serverSocket,(struct sockaddr*)&clientAddr,sizeof(clientAddr));
	printf("connected to server successfully...\n");

		//code
		//char buf[1024];
        printf("Enter\n1.Tree\n2.Ring\n3.Star\n");
		printf("Enter Your choice : ");
		scanf("%d",&buf[0]);
        printf("Enter Number of nodes : ");
        scanf("%d",&buf[1]);
		//fgets(buf,1024,stdin);
		send(serverSocket,(int*)buf,1024,0);
        //struct Graph* g=malloc(sizeof(struct Graph));
        int p=buf[1];
        int A[p][p+1];
		recv(serverSocket,(int**)A,sizeof(A),0);
        printf("Adjacency List along with degrees\n");
        for(int i=0;i<p;i++)
		{
            printf("%d-> ",i);
			for(int j=0;j<p;j++)
			{
                if(A[i][j]!=-1)
				    printf("%d->",A[i][j]);
			}
			printf("\tDegree - %d\n",A[i][p]);
		}
        //printGraph(g);
}