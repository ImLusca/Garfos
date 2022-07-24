#include <bits/stdc++.h>
using namespace std;

void printGraph(vector<pair<int, int>> adj[], int V)
{
    int v, w;
    for (int u = 0; u < V; u++)
    {
        cout << "Node " << u << " makes an edge with \n";
        for (auto it = adj[u].begin(); it != adj[u].end(); it++)
        {
            v = it->first;
            w = it->second;
            cout << "\tNode " << v << " with edge weight ="
                 << w << "\n";
        }
        cout << "\n";
    }
}

static void populalst(FILE *fptr, vector<pair<int, int>> adj[])
{

    int vert1, vert2, peso;
    char descarte[7];
    fgets(descarte, 7, fptr);

    do
    {
        if (fscanf(fptr, "%i %i %i", &vert1, &vert2, &peso) == -1)
        {
            break;
        }

        adj[vert1].push_back(make_pair(vert2, peso));

    } while (!feof(fptr));
}

static int leNumeroVertices(FILE *fptr)
{
    char texto[10];
    int numVertices = -1;

    fscanf(fptr, "%s %i\r\n", texto, &numVertices);

    return numVertices;
}

int minDist(int dist[], bool visitado[], int V)
{
    int min = INT_MAX;
    int index;

    for (int i = 0; i < V; i++)
    {
        if (!visitado[i] && dist[i] <= min)
        {
            min = dist[i];
            index = i;
        }
    }
    return index;
}

int *Dijkstra(vector<pair<int, int>> adj[], int src, int V) // adjacency matrix used is 6x6
{
    int *dist = (int*)malloc(sizeof(int) * V);  
    bool visitado[V];

    for (int i = 0; i < V; i++)
    {
        visitado[i] = false;
        dist[i] = INT_MAX;
    }

    dist[src] = 0;

    int v, w; 
    for (int u = 1; u <= V; u++)
    {
        int m = minDist(dist, visitado, V);
        visitado[m] = true; 

        for (auto it = adj[m].begin(); it != adj[m].end(); it++){
            v = it->first;
            w = it->second;
            
            if(!visitado[v] && w && dist[m] != INT_MAX && dist[m] + w < dist[v])
                dist[v] = dist[m] + w;

        }
    }

    return dist;

}

int main()
{
    char *nomeArq = (char *)malloc(sizeof(char) * 25);
    scanf("%s", nomeArq);
    FILE *fptr = fopen(nomeArq, "r");

    if (!fptr)
    {
        return 0;
    }

    int V = leNumeroVertices(fptr);
    vector<pair<int, int>> adj[V + 1];
    populalst(fptr, adj);
    
    V++;
    vector<vector<int>> res(V);

    for(int i =1; i <= V; i++ ){
        int *nums = Dijkstra(adj,i,V);

        vector<int> novo(V);
        res.push_back(novo);

        for(int j = 1; j <= V; j++){
            res[i].push_back(nums[j]);
        }
    }

    for(int i =1; i < V; i++ ){
        
        for(int j = 0; j < V-1; j++){
            cout << res[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}