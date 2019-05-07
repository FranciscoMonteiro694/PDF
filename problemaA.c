/*
6 6
1 0 1 2 8 -1 -1
2 -1 0 -1 -1 3 -1
3 -1 -1 0 5 3 8
4 -1 -1 -1 0 -1 12
5 -1 -1 -1 -1 0 4
6 -1 -1 -1 -1 -1 0
 */
#include <stdio.h>
#include <stdlib.h>
int visitednotEmpty(int *visited, int n);
int indDistMaisPequena(int **tabela,int nrLinha,int size);
int funcaonova(int *distancias,int n,int *visited);
int main(int argc, const char * argv[]) {
    int n,final;
    int ignorar;
    int **grafo,i,j;
    int *distance,*visited,u;
    scanf("%d %d",&n,&final);
    
    grafo=(int**)malloc(sizeof(int*)*n);
    for (i=0;i<n;i++){
        grafo[i]=(int*)malloc(sizeof(int)*n);
    }
    for(i=0;i<n;i++){
        for(j=0;j<=n;j++){
            if(j==0){
                scanf("%d",&ignorar);
            }
            else{
                scanf("%d",&grafo[i][j-1]);
            }
        }
    }
    distance=(int*)malloc(sizeof(int)*n);
    distance[0]=0;
    for (i=1;i<n;i++){
        distance[i]=999999;
        
    }
    visited=(int*)malloc(sizeof(int)*n);
    visited[0]=1;
    for (i=1;i<n;i++){
        visited[i]=0;
        
    }
    u=1;
    while(visitednotEmpty(visited,n)){
        u=funcaonova(distance,n,visited);
        visited[u]=1;
        if (u==final){
            break;
        }
        for(i=0;i<n;i++){
            if(distance[i]>distance[u]+grafo[u][i] && grafo[u][i] >0  && visited[i]==0){
                distance[i]=distance[u]+grafo[u][i];
            }
        }
    }
    printf("%d\n",distance[final-1]);

    
}

int visitednotEmpty(int *visited, int n){
    int i;
    for(i=0;i<n;i++){
        if(visited[i]==0)
            return 1;
    }
    return 0;
}
int indDistMaisPequena(int **tabela,int nrLinha,int size){
    int i,minAtual,ind;
    ind=0;
    minAtual=999999;
    for(i=0;i<size;i++){
        if(minAtual>tabela[nrLinha][i] && tabela[nrLinha][i]>0){
            minAtual=tabela[nrLinha][i];
            ind=i;
        }
    }
    
    return ind;
}

int funcaonova(int *distancias,int n,int *visited){
    int i,minAtual,ind;
    ind=0;
    minAtual=999999;
    for(i=0;i<n;i++){
        if(minAtual>distancias[i] && distancias[i]>0 && visited[i]!=1){
            minAtual=distancias[i];
            ind=i;
        }
    }
    
    return ind;
}
