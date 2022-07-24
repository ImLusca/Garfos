#include <stdlib.h>
#include "garfos.h"
#include <stdio.h>
#include <unordered_map>
#include <vector>
#include <algorithm>

// responsável: Lucas Pereira (lusca)
// nºusp: 12543930

int grafoPercorrido(std::unordered_map<int, int> visited, int tamanho);

int main()
{

    char *nmArquivo;

    std::cin >> nmArquivo;

    FILE *fptr = fopen(nmArquivo, "r");

    if (!fptr)
    {
        printf("Arquivo inválido");
        return 0;
    }

    ListaAdjacencia lst = lerPajeck(fptr);

    std::unordered_map<int, int> grupos;
    for (int i = 1; i < lst.numVertices; i++)
    {
        grupos[i] = -1;
    }

    int numGrupos = 0, pos = 1;
    do
    {
        numGrupos++;
        DFS(lst, grupos, pos, numGrupos);
        pos = grafoPercorrido(grupos, lst.numVertices);

    } while (pos != 0);

    std::cout << numGrupos << std::endl;

    std::vector<int> contagem(numGrupos + 1, 0);

    for (int i = 1; i < lst.numVertices; i++)
    {
        contagem[grupos[i]]++;
    }

    std::sort(contagem.begin(), contagem.end(), std::greater<>());

    return 0;
}

int grafoPercorrido(std::unordered_map<int, int> visited, int tamanho)
{
    for (int i = 1; i < tamanho; i++)
    {
        if (visited[i] == -1)
        {
            return i;
        }
    }
    return 0;
}