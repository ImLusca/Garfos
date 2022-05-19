#include<stdlib.h>
#include "garfos.h"

int main(){

    // MatrizAdjacencia mat = geraErdosRenyi(5,0.4);
    // printaMatriz(mat);

    // ListaAdjacencia gf = MatrizToLista(mat);

    FILE *fptr = fopen("tst.pjk", "r");

    ListaAdjacencia lst = lerPajeck(fptr);

    return 0;
}