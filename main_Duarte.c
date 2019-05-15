#include <stdio.h>
#include <stdlib.h>
#include <math.h>
typedef struct edge
{
	int src,dest;
	double weight;
}edge;

typedef struct ponto
{
	int x,y;
}ponto;
/*
typedef struct nodeT{
    int val;
    int rank;
    struct nodeT *next;
}Set;

Set* CriaSet(int val){
    Set *ponteiro;
    if ((ponteiro=malloc(sizeof(Set)))== NULL)
        printf("Estoirou!\n");
    ponteiro->val=val;
    ponteiro->rank=0;
    ponteiro->next=ponteiro;
    return ponteiro;
}


int FindSet(int val,Set**sets){
    Set *ponteiro;
    ponteiro=sets[val];
    if(ponteiro->next->val!=val){
           ponteiro=FindSet(val,ponteiro->next);
    }
    return ponteiro->next->val;
}*/
/*
void link(int a, int b){
if(rank[a]>rank[b])
set[b]=a;
else {
set[a]=b;
if(rank[a]==rank[b])
rank[b]++;
}
}
*/
/*supostamente ja fizemos o find*/
/*
void linkSet(int a,int b,Set**sets){
    if(sets[a]->rank>sets[b]->rank){
            sets[b]->val=a;
    }
    else{
          sets[a]->val=b;
          if(sets[a]->rank==sets[b]->rank){
                sets[b]->rank=sets[b]->rank+1;
          }

    }


}*/
/*


void union_find(int a, int b){
link(find(a), find(b));
}

*/
void quickSort(edge arr[], int low, int high);
int Kruskal(edge*edges,int nEdges,int nPontos);
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
    edge *edges;
    int **grafo;
    int weight;
    nEdges=0;
    acum=0;
    printf("\nEnter number of vertices:");
    scanf("%d",&nPontos);
    grafo=(int**)malloc(sizeof(int*)*nPontos);
    for (i=0;i<nPontos;i++){
        grafo[i]=(int*)malloc(sizeof(int)*nPontos);
        for(j=0;j<nPontos;j++){
            grafo[i][j]=0;
        }
    }
	printf("\nEnter the adjacency matrix:\n");
	for(i=0;i<nPontos;i++){
        for(j=0;j<nPontos;j++){
            scanf("%d",&grafo[i][j]);
            printf("%d  %d\n",i,j);
            if(grafo[i][j]>0){
                nEdges++;
            }
		}
	}
	printf("\n\n\n\n");
	printf("--------------Matrix---------\n");
    for(i=0;i<nPontos;i++){
        for(j=0;j<nPontos;j++){
			printf("%d   ",grafo[i][j]);
		}
		printf("\n");
    }
    edges=(edge*)malloc(sizeof(edge)*nEdges);
	for(i=0;i<nPontos;i++){
        for(j=0;j<nPontos;j++){
            if(grafo[i][j]>0){
                edges[acum].src=i;
                edges[acum].dest=j;
                edges[acum].weight=grafo[i][j];
                acum++;
            }
		}
	}
    /*pontos=(ponto*)malloc(sizeof(ponto)*nPontos);
    grafo=(int**)malloc(sizeof(ponto)*nPontos);
    for(i=0;i<nPontos;i++){
         grafo[i]=(int*)malloc(sizeof(int)*nPontos);
        for(j=0;j<nPontos;j++){
            grafo[i][j]=-1;
        }
    }*/
   /* for(i=0;i<nPontos;i++){
        scanf("%d%d",&pontos[i].x,&pontos[i].y);
    }

    printf("-------Pontos--------\n");
    for(i=0;i<nPontos;i++){
        printf("%d.  x.%d    y.%d\n",i,pontos[i].x,pontos[i].y);
    }
*/
    /*
    scanf("%d",&nEdges);
    edges=(edge*)malloc(sizeof(edge)*nEdges);
    for(i=0;i<nEdges;i++){
        scanf("%d%d%d",&src,&dest,&weight);
        src=src-1;
        dest=dest-1;
        edges[i].src=src;
        edges[i].dest=dest;
        edges[i].weight=weight;
        */
       /* edges[i].weight=distance(pontos[src].x,pontos[src].y,pontos[dest].x,pontos[dest].y);*/
    /*}*/
    printf("---------Edges--------------\n");
    for(i=0;i<nEdges;i++){
        printf("%d.  %d  %d  %f\n",i,edges[i].src,edges[i].dest,edges[i].weight);
    }
    /*quickSort(edges,0,nEdges-1);*/
    printf("haaaaaaaaaaaaa------------->%d\n",Kruskal(edges,nEdges,nPontos));
    return 0;
}/*
for each edge (u,v) in G, in non-decreasing order by
weight
if Find-Set(u)!=Find-Set(v)
A = A + {(u,v)}
Union(u,v)
return A*/
int Kruskal(edge*edges,int nEdges,int nPontos){
    int* set;
    int* rank;
    int acum=0;
    int i;
    rank=(int*)malloc((sizeof(int)*nPontos));
    set=(int*)malloc((sizeof(int)*nPontos));
    for(i=0; i<nPontos; i++){
        set[i]=i;
        rank[i]=0;
    }
    quickSort(edges,0,nEdges-1);
    printf("---------Edges--------------\n");
    for(i=0;i<nEdges;i++){
        printf("%d.  %d  %d  %f\n",i,edges[i].src,edges[i].dest,edges[i].weight);
    }
    for(i=0;i<nEdges;i++){
        if(find(edges[i].src,set)!=find(edges[i].dest,set)){
            acum=acum+edges[i].weight;
            union_find(edges[i].src,edges[i].dest,set,rank);
            /*link(edges[i].src,edges[i].dest,rank,set);*/
        }
        /*union_find(edges[i].src,edges[i].dest,set,rank);*/
    }

return acum;

}



void swap(edge* a, edge* b)
{
    edge t = *a;
    *a = *b;
    *b = t;
}

void link(int a, int b,int*rank,int*set){
if(rank[a]>rank[b]){
            set[b]=a;
            printf("%d    %d\n",b,a);
    }
else {
    set[a]=b;
    printf("%d    %d\n",a,b);
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
