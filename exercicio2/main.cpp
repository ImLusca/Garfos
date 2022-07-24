#include <stdlib.h>
#include "garfos.h"
#include <stdio.h>

// responsável: Lucas Pereira (lusca)
// nºusp: 12543930

void printaMatriz(int numVertices, std::vector<std::vector<int>> matrix);
void populaMatriz(ListaAdjacencia lst, std::vector<std::vector<int>> &matrix);

int main()
{

    ListaAdjacencia lst = lerPajeck(stdin);

    std::vector<std::vector<int>> matriz(lst.numVertices);

    populaMatriz(lst, matriz);

    printaMatriz(lst.numVertices, matriz);

    return 0;
}

void printaMatriz(int numVertices, std::vector<std::vector<int>> matrix)
{
    for (int i = 1; i < numVertices; i++)
    {
        for (int j = 1; j < numVertices; j++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
}

void populaMatriz(ListaAdjacencia lst, std::vector<std::vector<int>> &matrix)
{
    for (int i = 1; i < lst.numVertices; i++)
    {
        matrix[i] = BFS(lst, i);
    }
}