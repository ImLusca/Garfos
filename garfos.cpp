#include "garfos.h"
#include <string.h>
#include <limits.h>

// Buscas =================================================================

void DFS_aux(ListaAdjacencia gf, std::vector<bool> &visited, ulong pos)
{

    visited[pos] = true;

    for (int i = 0; i < gf.estrutura[pos].size(); i++)
    {
        if (visited[gf.estrutura[pos][i]] == false)
        {
            DFS_aux(gf, visited, gf.estrutura[pos][i]);
        }
    }
}

void DFS(ListaAdjacencia gf, ulong pos)
{
    std::vector<bool> vs(gf.numVertices, false);

    DFS_aux(gf, vs, pos);
}

std::vector<ulong> BFS(ListaAdjacencia gf, ulong pos)
{
    std::queue<ulong> q;
    std::vector<bool> visitado(gf.numVertices, false);
    std::vector<ulong> distancia(gf.numVertices, ULONG_MAX);

    q.push(pos);

    int dist = 1;
    distancia[pos] = 0;
    while (!q.empty())
    {
        int vert = q.front();
        q.pop();
        visitado[vert] = 1;

        for (int i = 0; i < gf.estrutura[vert].size(); i++)
        {
            if (!visitado[gf.estrutura[vert][i]] && distancia[gf.estrutura[vert][i]] == ULONG_MAX)
            {
                distancia[gf.estrutura[vert][i]] = dist;
                q.push(gf.estrutura[vert][i]);
            }
        }
        dist++;
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

    //@TODO: O ideal seria throwar uma exceção. talvez faça isso no futuro
    if (!fptr)
    {
        std::perror("Deu ruim ao abrir o arquivo");
        return NULL;
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
