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
    std::vector<std::vector<ulong>> estrutura;
    ulong numVertices;
    ListaAdjacencia(ulong numV)
    {
        numV++;
        numVertices = numV;
        estrutura = std::vector<std::vector<ulong>>(numVertices);
    }
    void addArestasBidirect(ulong vert1, ulong vert2)
    {

        if (vert1 > numVertices || vert2 > numVertices)
        {
            std::cerr << "Tentativa de inserção inválida na lista";
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

void DFS(struct ListaAdjacencia, ulong pos);
std::vector<ulong> BFS(struct ListaAdjacencia, ulong pos);

MatrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP);
void printaMatriz(MatrizAdjacencia m);

ListaAdjacencia MatrizToLista(MatrizAdjacencia m);
ListaAdjacencia lerPajeck(FILE *fptr);

#endif