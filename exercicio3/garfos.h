#ifndef GARFOS
#define GARFOS

//réu: Lucas Pereira (Lusca)
//nºusp: 12543930

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <queue>
#include <unordered_map>

// @Todo: Converter estrutura Para vetor de listas
class ListaAdjacencia
{
public:
    std::vector<std::vector<int>> estrutura;
    int numVertices;
    ListaAdjacencia(int numV)
    {
        numV++;
        numVertices = numV;
        estrutura = std::vector<std::vector<int>>(numVertices);
    }
    void addArestasBidirect(int vert1, int vert2)
    {

        if (vert1 > numVertices || vert2 > numVertices)
        {
            return;
        }

        estrutura[vert1].push_back(vert2);
        estrutura[vert2].push_back(vert1);
    }
};

class MatrizAdjacencia
{
public:
    float **matriz;
    int numVertices;

    MatrizAdjacencia(int numV)
    {
        numVertices = numV;

        matriz = (float **)malloc(sizeof(float *) * numVertices);
        for (int i = 0; i < numVertices; i++)
        {
            matriz[i] = (float *)malloc(sizeof(float) * numVertices);
        }
    }
};

void DFS(struct ListaAdjacencia, std::unordered_map<int,int> &visited, int pos, int grupo = 0);
std::vector<int> BFS(struct ListaAdjacencia, int pos);

MatrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP);
void printaMatriz(MatrizAdjacencia m);

ListaAdjacencia MatrizToLista(MatrizAdjacencia m);
ListaAdjacencia lerPajeck(FILE *fptr);

#endif