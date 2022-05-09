#ifndef GARFOS
#define GARFOS

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <queue>

// @Todo: Converter estrutura Para vetor de listas
class ListaAdjacencia{
    public:
        std::vector<std::vector<int>> estrutura;
        int numVertices;
    ListaAdjacencia(int numV){
        numVertices = numV;
        estrutura = std::vector<std::vector<int>>(numVertices);  
    }
};

class MatrizAdjacencia{
    public:
        float **matriz;
        int numVertices;

    MatrizAdjacencia(int numV){
        numVertices = numV;

        matriz = (float**)malloc(sizeof(float*) * numVertices);
        for(int i =0; i < numVertices; i++){
            matriz[i] = (float*)malloc(sizeof(float) * numVertices);
        }
    }
};

void DFS(struct ListaAdjacencia, int pos);
void BFS(struct ListaAdjacencia, int pos);

MatrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP);
ListaAdjacencia MatrizToLista(MatrizAdjacencia m);
void printaMatriz(MatrizAdjacencia m);

#endif