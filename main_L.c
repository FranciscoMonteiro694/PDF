#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
/*estrutura que define uma arresta,o seu vertice inicial,o seu vertice final e o seu valor*/
typedef struct edge
{
	int src,dest;
	double weight;
}edge;
/*Estrutura de um ponto,é mais para o problema em si e para receber o input*/
typedef struct ponto
{
	int x,y;
}ponto;
/*em contexto do problema nada a ver com Truska*/
int javardice=0;

void quickSort(edge arr[], int low, int high);
double Kruskal(edge*edges,int nEdges,int nPontos);
void union_find(int a, int b,int*set,int*rank);
int find(int a,int*set);
double distance(int x1, int y1, int x2, int y2)
{
    int square_difference_x = (x2 - x1) * (x2 - x1);
    int square_difference_y = (y2 - y1) * (y2 - y1);
    int sum = square_difference_x + square_difference_y;
    double value = (double)sqrt(sum);
    return value;
}

int main()
{
    int nPontos,nEdges,i,j,src,dest,acum;
    ponto*pontos;
    edge *edges;/*array final a junçao do edges1 e edges2*/
    edge *edges1;/*array onde metemos as arrestas fixas,dadas no input*/
    edge *edges2;/*array onde metemos as combinaçoes todas de arrestas possivels*/
    int ** auxiliar;/*para descobrir as combinaçoes possiveis de n elementos (matriz n*n)*/
    int acum2;
    double resultado[50];
    acum2=0;
    /*input*/
    while(scanf("%d",&nPontos)!=EOF){
    acum=0;
    javardice=0;
    pontos=(ponto*)malloc(sizeof(ponto)*nPontos);
    auxiliar=(int**)malloc(sizeof(int*)*nPontos);
    /*recebemos todos os pontos possiveis e fazemos a matriz auxiliar para as combinaçoes*/
    for(i=0;i<nPontos;i++){
         auxiliar[i]=(int*)malloc(sizeof(int)*nPontos);
         for(j=0;j<nPontos;j++){
            auxiliar[i][j]=0;
         }
    }
    for(i=0;i<nPontos;i++){
         scanf("%d%d",&pontos[i].x,&pontos[i].y);
    }
    edges=(edge*)malloc(sizeof(edge)*(nPontos*nPontos));
    scanf("%d",&nEdges);
    edges1=(edge*)malloc(sizeof(edge)*nEdges*2);
    edges2=(edge*)malloc(sizeof(edge)*((nPontos*nPontos)-(nEdges*2)));
    /* edges ja definidas*/
	for(i=0;i<nEdges*2;i++){
            scanf("%d%d",&src,&dest);
            edges1[i].src=src;
            edges1[i].dest=dest;
            edges1[i].weight=distance(pontos[src-1].x,pontos[src-1].y,pontos[dest-1].x,pontos[dest-1].y);
            javardice=javardice+edges1[i].weight;
            auxiliar[src-1][dest-1]=1;/*para nao serem posta nos array das combinaçoes*/
            auxiliar[dest-1][src-1]=1;
            i++;
            /*ligaçao dupla*/
            edges1[i].src=dest;
            edges1[i].dest=src;
            edges1[i].weight=distance(pontos[src-1].x,pontos[src-1].y,pontos[dest-1].x,pontos[dest-1].y);

	}
	/* Cobinaçoes possveis sem ser as ja definidas anteriormente*/
	for(i=0;i<nPontos;i++){
            for(j=0;j<nPontos;j++){
                if(auxiliar[i][j]==0&&auxiliar[j][i]==0){
                    edges2[acum].src=i+1;
                    edges2[acum].dest=j+1;
                    edges2[acum].weight=distance(pontos[i].x,pontos[i].y,pontos[j].x,pontos[j].y);
                    acum++;
                }
                else{
                }
            }
	}
	/*ordenar os dois arrays paratica do kruskal*/
    quickSort(edges2,0,((nPontos*nPontos)-nEdges*2)-1);
    quickSort(edges1,0,nEdges-1);
    /*juntar os dos arrays no final*/
    memcpy(edges,edges1,nEdges*2*sizeof(edge));
    memcpy(edges + nEdges*2,edges2 , ((nPontos*nPontos)-nEdges*2) * sizeof(edge));
    /*ver qual a soma das arestas usadas na minum spaning tree*/
    resultado[acum2]=(Kruskal(edges,nPontos*nPontos,nPontos)-(double)javardice);
    acum2++;
    }
    for(i=0;i<acum2;i++){
        printf("%.2f\n",resultado[i]);
    }
    return 0;
}
/*
for each edge (u,v) in G, in non-decreasing order by
weight
if Find-Set(u)!=Find-Set(v)
A = A + {(u,v)}
Union(u,v)
return A*/
double Kruskal(edge*edges,int nEdges,int nPontos){/*cuidado com estes argumentos*/
    int* set;
    int* rank;
    double acum=0;
    int i;
    /*honestamente e o que o prof fez*/
    rank=(int*)malloc((sizeof(int)*nEdges));/*rank e tipo a depth do ser ou numero de filhos*/
    set=(int*)malloc((sizeof(int)*nEdges));/*set e o valor do pai*/
    for(i=0; i<nEdges; i++){
        set[i]=i;
        rank[i]=0;
    }
    /*por cada par de vertices que formam uma aresta por ordem crescente de valor,neste caso ja estao ordenadas mas deviamos ordenar aqui*/
    for(i=0;i<nEdges;i++){
        /*ver se os sets nao tem o mesma raiz,ou seja se nao pertecem ao mesmo subset*/
        if(find(edges[i].src,set)!=find(edges[i].dest,set)){
            /*entao esta arresta vai pertencer a minimun spaning tree logo acumular o valor dessa aresta*/
            acum=acum+edges[i].weight;
            /*unir os dois sets*/
            union_find(edges[i].src,edges[i].dest,set,rank);
        }
    }

return acum;

}


/*quick sort*/
void swap(edge* a, edge* b)
{
    edge t = *a;
    *a = *b;
    *b = t;
}

/*funçoes do professor*/
void link(int a, int b,int*rank,int*set){
if(rank[a]>rank[b]){
            set[b]=a;
    }
else {
    set[a]=b;
    if(rank[a]==rank[b])
        rank[b]++;
}
}
int find(int a,int*set){
if(set[a]!=a)
set[a]=find(set[a],set);
return set[a];
}
void union_find(int a, int b,int*set,int*rank){
link(find(a,set), find(b,set),rank,set);
}



/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (edge arr[], int low, int high)
{
    int j;
    int pivot = arr[high].weight;
    int i = (low - 1);

    for (j = low; j <= high- 1; j++)
    {
        if (arr[j].weight <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */
void quickSort(edge arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

/*
MST-Kruskal(G,w)
A = {}
for each vertex v in G
Make-Set(v)
sort the edges of E into non-decreasing order by weight w
for each edge (u,v) in G, in non-decreasing order by
weight
if Find-Set(u)!=Find-Set(v)
A = A + {(u,v)}
Union(u,v)
return A*/
