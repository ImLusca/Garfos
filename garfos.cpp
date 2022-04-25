#include "garfos.h"

// Buscas =================================================================

void DFS_aux(grafo gf,std::vector<bool> &visited, int pos){

    visited[pos] = true;

    for(int i =0; i < gf.estrutura[pos].size(); i++){
        if(visited[gf.estrutura[pos][i]] == false){
            DFS_aux(gf, visited, gf.estrutura[pos][i]);
        }
    }
}

void DFS(grafo gf, int pos){
    std::vector<bool> vs(false,gf.numVertices);

    DFS_aux(gf,vs,pos);
}

void BFS(grafo gf, int pos){
    std::queue<int> q;
    std::vector<bool> visitado(false, gf.numVertices);
    q.push(pos);

    while(!q.empty()){

        int vert = q.front();
        q.pop();

        printf(" %i-->", vert);

        visitado[vert] = true;

        for(int i =0; i < gf.estrutura[vert].size(); i++){

            if(!visitado[gf.estrutura[vert][i]]){
                q.push(gf.estrutura[vert][i]);
            }

        }

    }

}

// implementar Dijkstra

// Modelo Erdos-renyi =====================================================

matrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP){

    srand(time(NULL));
    if(tresholdP == 0.0){
        float tresholdP = rand();
    }

    matrizAdjacencia mat;
    mat.numVertices = numVertices;

    mat.matriz = (float**)malloc(sizeof(float*) * numVertices);
    for(int i =0; i < numVertices; i++){
        mat.matriz[i] = (float*)malloc(sizeof(float) * numVertices);
    }

    //Atribuindo valores
    for(int i =0; i < numVertices; i++){
        for(int j = 0; j < numVertices; j++){
            if(i <= j && i != j){
                float rnd = ((double) rand() / (RAND_MAX));

                mat.matriz[i][j] = rnd >= tresholdP? 1 : 0;
                mat.matriz[j][i] = mat.matriz[i][j];
            }
            if(i == j){
                mat.matriz[i][j] = 0;
            }
        }
    }

    return mat;
}

//utils ===================================================================

void printaMatriz(matrizAdjacencia m){
    for(int i =0; i < m.numVertices; i++){
        for(int j = 0; j < m.numVertices; j++){
            printf(" %.0f ",m.matriz[i][j]);
        }
        printf("\n");
    }
}

grafo converteAdjEstrutura(matrizAdjacencia m){

    grafo gf;
    int nv = m.numVertices;
    gf.numVertices = nv;
    std::vector<std::vector<int>> estrutura(nv);   


    for(int i = 0; i < nv; i++){
        for(int j = 0; j < nv; j++){
            if(m.matriz[i][j]){
                estrutura[i].push_back(j);
            }
        }
    }

    gf.estrutura = estrutura;

    return gf;

}

