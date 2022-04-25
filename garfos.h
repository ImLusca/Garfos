#ifndef GARFOS
#define GARFOS

#include <iostream>
#include <vector>
#include <map>
#include <stdlib.h>
#include <queue>

typedef struct _matrizAdjacencia{
    float **matriz;
    int numVertices;
}matrizAdjacencia;

typedef struct _garfo{
    std::vector<std::vector<int>> estrutura;
    int numVertices;
}grafo;

void DFS(struct _garfo, int pos);
void BFS(struct _garfo, int pos);


struct _matrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP);
grafo converteAdjEstrutura(matrizAdjacencia m);
void printaMatriz(struct _matrizAdjacencia);

#endif