#include "garfos.h"
#include <string.h>
#include <unordered_map>

//réu: Lucas Pereira (Lusca)
//nºusp: 12543930

// Buscas =================================================================

void DFS_aux(ListaAdjacencia gf, std::unordered_map<int,int> &visited, int pos, int grupo)
{

    visited[pos] = grupo;

    for (int i = 0; i < gf.estrutura[pos].size(); i++)
    {
        if (visited[gf.estrutura[pos][i]] == -1)
        {
            DFS_aux(gf, visited, gf.estrutura[pos][i], grupo);
        }
    }
}

void DFS(ListaAdjacencia gf, std::unordered_map<int,int> &visited,int pos,int grupo)
{
    DFS_aux(gf, visited, pos, grupo);
}

std::vector<int> BFS(ListaAdjacencia gf, int pos)
{
    //@TODO : Trocar -1 por ULLONG_MAX e int por Uint Long
    std::queue<int> q;
    std::vector<bool> visitado(gf.numVertices, false);
    std::vector<int> distancia(gf.numVertices, -1);

    q.push(pos);

    distancia[pos] = 0;
    visitado[pos] = true;

    int dist = 1;
    while (!q.empty())
    {
        int vert = q.front();
        q.pop();

        for (int i = 0; i < gf.estrutura[vert].size(); i++)
        {
            if (!visitado[gf.estrutura[vert][i]])
            {
                distancia[gf.estrutura[vert][i]] = distancia[vert] + 1;
                visitado[vert] = 1;
                q.push(gf.estrutura[vert][i]);
            }
        }
    }

    return distancia;
}

// @TODO: implementar Dijkstra

// Modelo Erdos-renyi =====================================================

MatrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP)
{

    srand(time(NULL));
    if (tresholdP == 0.0)
    {
        float tresholdP = rand();
    }

    MatrizAdjacencia mat(numVertices);

    // Atribuindo valores
    for (int i = 0; i < numVertices; i++)
    {
        for (int j = 0; j < numVertices; j++)
        {
            if (i <= j && i != j)
            {
                float rnd = ((double)rand() / (RAND_MAX));

                mat.matriz[i][j] = rnd >= tresholdP ? 1 : 0;
                mat.matriz[j][i] = mat.matriz[i][j];
            }
            if (i == j)
            {
                mat.matriz[i][j] = 0;
            }
        }
    }

    return mat;
}

// utils ===================================================================

void printaMatriz(MatrizAdjacencia m)
{
    for (int i = 0; i < m.numVertices; i++)
    {
        for (int j = 0; j < m.numVertices; j++)
        {
            printf(" %.0f ", m.matriz[i][j]);
        }
        printf("\n");
    }
}

ListaAdjacencia MatrizToLista(MatrizAdjacencia m)
{

    int nv = m.numVertices;
    ListaAdjacencia lst(nv);

    for (int i = 0; i < nv; i++)
    {
        for (int j = 0; j < nv; j++)
        {
            if (m.matriz[i][j])
            {
                lst.estrutura[i].push_back(j);
            }
        }
    }

    return lst;
}

static int leNumeroVertices(FILE *fptr);
static void populalst(FILE *fptr, ListaAdjacencia &lst);

ListaAdjacencia lerPajeck(FILE *fptr)
{

    if (!fptr)
    {
        std::perror("Deu ruim ao abrir o arquivo");
    }

    ListaAdjacencia lst(leNumeroVertices(fptr));

    populalst(fptr, lst);

    return lst;
}

static int leNumeroVertices(FILE *fptr)
{
    char texto[10];
    int numVertices = -1;

    fscanf(fptr, "%s %i\r\n", texto, &numVertices);

    return numVertices;
}

static void populalst(FILE *fptr, ListaAdjacencia &lst)
{

    int vert1, vert2, tmp;
    char descarte[7], chr;
    fgets(descarte, 7, fptr);

    do
    {
        if (fscanf(fptr, "%i %i", &vert1, &vert2) == -1)
        {
            break;
        }
        lst.addArestasBidirect(vert1, vert2);
    } while (!feof(fptr));
}
