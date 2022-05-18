#ifndef GARFOS
#define GARFOS

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <queue>

// @Todo: Converter estrutura Para vetor de listas
class ListaAdjacencia
{
public:
    std::vector<std::vector<int>> estrutura;
    int numVertices;
    ListaAdjacencia(int numV)
    {
        //@TODO pensar em solução melhor.
        numVertices = numV;
        estrutura = std::vector<std::vector<int>>(numVertices + 1);
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

void DFS(struct ListaAdjacencia, int pos);
void BFS(struct ListaAdjacencia, int pos);

MatrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP);
void printaMatriz(MatrizAdjacencia m);

ListaAdjacencia MatrizToLista(MatrizAdjacencia m);
ListaAdjacencia lerPajeck(FILE *fptr);

#endif