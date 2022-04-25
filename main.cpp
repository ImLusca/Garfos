#include<stdlib.h>
#include "garfos.h"

int main(){

    matrizAdjacencia mat = geraErdosRenyi(5,0.3);

    grafo gf = converteAdjEstrutura(mat);

    printaMatriz(mat);

    return 0;

}