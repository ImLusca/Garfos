#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Aresta
{
  int src, dest, peso;
} aresta;

typedef struct Grafo
{
  int vert, arest;
  aresta **arestas;
} garfo;

typedef struct subset
{
  int pai, rank;
} subSetUF;

void printarVerts(garfo *gf)
{
  for (int i = 1; i < gf->arest; i++)
  {
    printf("%i %i %i\n", gf->arestas[i]->src, gf->arestas[i]->dest, gf->arestas[i]->peso);
  }
}

int find(subSetUF subsets[], int elemento)
{
  if (subsets[elemento].pai != elemento)
    subsets[elemento].pai = find(subsets, subsets[elemento].pai);

  return subsets[elemento].pai;
}

void Union(subSetUF subsets[], int x, int y)
{
  int xroot = find(subsets, x);
  int yroot = find(subsets, y);

  if (subsets[xroot].rank > subsets[yroot].rank)
  {
    subsets[yroot].pai = xroot;
  }
  else if (subsets[xroot].rank < subsets[yroot].rank)
  {
    subsets[xroot].pai = yroot;
  }
  else
  {
    subsets[yroot].pai = xroot;
    subsets[xroot].rank++;
  }
}

// Comparação para o Qsort
int comparacao(const void *arest1, const void *arest2)
{
  aresta *a = (aresta *)arest1;
  aresta *b = (aresta *)arest2;
  return a->peso - b->peso;
}

int kruskal(garfo *gf)
{
  int vert = gf->vert;
  aresta MST[vert];

  // ordena as arestas de forma crescente pelo peso

  for (int i = 1; i <= gf->arest; i++)
  {
    for (int j = 1; j < gf->arest - 1; j++)
    {
      if(gf->arestas[j]->peso > gf->arestas[j+1]->peso){
        aresta *tmp = gf->arestas[j];
        gf->arestas[j] = gf->arestas[j+1];
        gf->arestas[j+1] = tmp;
      }
    } 
  }

  // Aloca memória para criar subsets
  subSetUF *subsets = malloc(sizeof(subSetUF) * (vert + 1));

  // Inicializando o subsets
  for (int i = 1; i <= vert; i++)
  {
    subsets[i].pai = i;
    subsets[i].rank = 0;
  }

  int auxArest = 0, i = 1;
  int resultado = 0;

  while (auxArest < vert && i < gf->arest)
  {

    // Pega a aresta com menor valor
    aresta *proxArest = gf->arestas[i++];

    // Verifica se foi causado um ciclo e se não, adiciona na MST
    int x = find(subsets, proxArest->src);
    int y = find(subsets, proxArest->dest);
    if (x != y)
    {
      MST[auxArest++] = *proxArest;
      Union(subsets, x, y);
    }
  }

  for (int i = 0; i < auxArest; i++)
  {
    resultado += MST[i].peso;
  }

  return resultado;
}

garfo *lerArquivoPajeck(FILE *fptr)
{

  garfo *gf = malloc(sizeof(garfo));
  gf->arest = 1;

  fseek(fptr, 10, SEEK_SET);

  fscanf(fptr, "%i", &gf->vert);

  fseek(fptr, 8, SEEK_CUR);

  int limArestas = 64;
  gf->arestas = malloc(sizeof(aresta *) * limArestas);
  aresta *lixo = malloc(sizeof(aresta *));
  lixo->peso = __INT32_MAX__;
  gf->arestas[0] = lixo;

  for (int i = 1;; i++)
  {
    aresta *nAresta = malloc(sizeof(aresta));

    fscanf(fptr, "%i %i %i\n", &nAresta->src, &nAresta->dest, &nAresta->peso);

    // nAresta->src -= 1;
    // nAresta->dest -= 1;

    if (gf->arest == limArestas)
    {
      limArestas += limArestas;
      gf->arestas = realloc(gf->arestas, sizeof(aresta) * limArestas);
    }

    gf->arestas[i] = nAresta;
    gf->arest += 1;

    char tmp;
    if ((tmp = getc(fptr)) == EOF)
    {
      break;
    }
    fseek(fptr, -1, SEEK_CUR);
  }

  // printarVerts(gf);

  return gf;
}

int main()
{
  char nomeArquivo[100];
  scanf("%s", nomeArquivo);

  FILE *fptr = fopen(nomeArquivo, "r");
  garfo *gf = lerArquivoPajeck(fptr);

  printf("%i", kruskal(gf));

  return 0;
}