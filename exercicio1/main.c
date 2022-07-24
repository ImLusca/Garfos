#include<stdio.h>
#include<stdlib.h>
#include<time.h>

void printaMatriz(int **matriz, int numVertices);
void liberaMatriz(int **matriz, int numVertices)

int main(){

    srand(time(NULL));

    // definindo variaveis
    int numVertices;
    printf("Informe o número de vertices:");
    scanf("%i", &numVertices);

    float tresholdP = rand();
    // printf("Informe o P:");
    // scanf("%f", &tresholdP);


    printf("treshold: %f\n", tresholdP);

    //alocando memória
    int **matriz = malloc(sizeof(int*) * numVertices);

    for(int i =0; i < numVertices; i++){
        matriz[i] = malloc(sizeof(int)* numVertices);
    }

    //Atribuindo valores
    for(int i =0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            if(i <= j && i != j){
                matriz[i][j] = rand() >= tresholdP;
                matriz[j][i] = matriz[i][j];
            }
        }
    }

    printaMatriz(matriz, numVertices);
    liberaMatriz(matriz,numVertices);

}


void printaMatriz(int **matriz, int numVertices){
    //printando matriz
    for(int i =0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            printf(" %i ",matriz[i][j]);
        }
        printf("\n");
    }
}

void liberaMatriz(int **matriz, int numVertices){
    //liberando memória
    for(int i =0; i < numVertices; i++){
        free(matriz[i]);
    }
    free(matriz);
}