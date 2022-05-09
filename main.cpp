#include<stdlib.h>
#include "garfos.h"

int main(){

    MatrizAdjacencia mat = geraErdosRenyi(5,0.4);
    printaMatriz(mat);

    ListaAdjacencia gf = MatrizToLista(mat);

    BFS(gf,0);

    return 0;
}