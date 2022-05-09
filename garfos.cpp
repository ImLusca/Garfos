#include "garfos.h"

// Buscas =================================================================

void DFS_aux(ListaAdjacencia gf,std::vector<bool> &visited, int pos){

    visited[pos] = true;

    for(int i =0; i < gf.estrutura[pos].size(); i++){
        if(visited[gf.estrutura[pos][i]] == false){
            DFS_aux(gf, visited, gf.estrutura[pos][i]);
        }
    }
}

void DFS(ListaAdjacencia gf, int pos){
    std::vector<bool> vs(false,gf.numVertices);

    DFS_aux(gf,vs,pos);
}


//@TODO: Consertar isso aqui
void BFS(ListaAdjacencia gf, int pos){
    std::queue<int> q;
    std::vector<int> visitado(gf.numVertices, -1);
    q.push(pos);

    int dist = 0;
    while(!q.empty()){

        int vert = q.front();
        q.pop();

        visitado[vert] = dist;

        for(int i =0; i < gf.estrutura[vert].size(); i++){
            if(visitado[gf.estrutura[vert][i]] == -1 ){
                q.push(gf.estrutura[vert][i]);
            }
        }
        dist++;
    }

    for(int i =0; i < gf.numVertices; i++){
        printf("%i ", visitado[i]);
    }
    printf("\n");

}

// @TODO: implementar Dijkstra

// Modelo Erdos-renyi =====================================================

MatrizAdjacencia geraErdosRenyi(int numVertices, float tresholdP){

    srand(time(NULL));
    if(tresholdP == 0.0){
        float tresholdP = rand();
    }

    MatrizAdjacencia mat(numVertices);

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

void printaMatriz(MatrizAdjacencia m){
    for(int i =0; i < m.numVertices; i++){
        for(int j = 0; j < m.numVertices; j++){
            printf(" %.0f ",m.matriz[i][j]);
        }
        printf("\n");
    }
}

ListaAdjacencia MatrizToLista(MatrizAdjacencia m){

    int nv = m.numVertices;
    ListaAdjacencia lst(nv);

    for(int i = 0; i < nv; i++){
        for(int j = 0; j < nv; j++){
            if(m.matriz[i][j]){
                lst.estrutura[i].push_back(j);
            }
        }
    }

    return lst;
}

//@TODO: Fazer conversor de Pajeck para Lista de Adjacência
