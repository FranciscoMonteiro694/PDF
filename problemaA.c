//
//  main.c
//  ProblemaA
//
//  Created by Francisco Monteiro on 06/05/2019.
//  Copyright © 2019 Francisco Monteiro. All rights reserved.
//
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
int main(int argc, const char * argv[]) {
    int n,final;
    int ignorar;
    scanf("%d %d",&n,&final);
    int **grafo,i,j;
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
    /*
    printf("Conteudo do grafo\n");
    for(i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d    ",grafo[i][j]);
        }
        printf("\n");
    }
    return 0;
     */
    
    int *distance,*visited,u;
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
    u=0;
    while(visitednotEmpty(visited,n)){
        printf("Estamos no nó %d\n",u);
        u=indDistMaisPequena(grafo,u,n)+1;
        visited[u]=1;
        if (u==final){
            break;
        }
        for(i=0;i<n;i++){
            if(distance[i]>distance[u]+grafo[i][u] && grafo[i][u] >0  && visited[i]==0){
                distance[i]=distance[u]+grafo[i][u];
            }
        }
    }
    printf("Valor final %d\n",distance[final-1]);
    for(i=0;i<n;i++){
        printf("%d \n",distance[i]);
    }
    
}

// Devolve 1 se ainda for para continuar o ciclo
// 1 quer dizer que foi visitado
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
        if(minAtual>tabela[nrLinha][i] && tabela[nrLinha][i]!=-1){
            minAtual=tabela[nrLinha][i];
            ind=i;
        }
    }
    
    return ind;
}
