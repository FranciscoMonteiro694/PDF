#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

5
5 1 2 3 4
0
6
2 1 3
5 4 6 2
0
0
*/
int acumulador, tempo = 0;
int indexGlobal = 0;
void dfsAlgorithm(int **grafo, int *visited, int *dfs, int nPlaces, int index);
void analisa(int nPlaces);
void imprimeGrafos(int **grafo,int n);
void art(int v,int *dfs, int *low, int **grafo,int nPlaces,int *parent);
int min(int a,int b);

int main(int argc, const char * argv[]) {
    acumulador=0;
    int nPlaces;
    char*temp = (char*)malloc(sizeof(char)*50);
    while(1){/* Usar breaks aqui à campeão */
        /*printf("ou seja, estou aqui certo?\n");*/
        gets(temp);
        /*printf("e deu isto: %d !\n", nPlaces);*/
        if(atoi(temp)==0) {
            /*printf("entrei aqui portanto sai");*/
            break;
        }
        nPlaces = atoi(temp);
        analisa(nPlaces);
    }

    return 0;
}
/* Se estrabuchar a imprimir, tentar por esta funcao a retornar int */
void analisa(int nPlaces){
    int **grafo;
    int i;
    char *buffer;
    char *token;
    grafo=(int**)malloc(sizeof(int*)*nPlaces);
    buffer=(char*)malloc(sizeof(char)*200);

    for (i=0;i<nPlaces;i++){
        grafo[i]=(int*)malloc(sizeof(int)*nPlaces);
        memset (grafo[i], 0, sizeof (int) * nPlaces);
    }
    
    int *visited = (int*)malloc(sizeof(int)*nPlaces);
    memset(visited, 0, sizeof(int)*nPlaces);
    int *dfs = (int*)malloc(sizeof(int)*nPlaces);
    int *low = (int*)malloc(sizeof(int)*nPlaces);
    int *parent = (int*)malloc(sizeof(int)*nPlaces);
    

    for (i=0;i<nPlaces;i++){
        low[i] = nPlaces+1;
        dfs[i] = -1;
        parent[i] = -1;
    }
    
    while(gets(buffer)){
        if (strcmp(buffer,"0")==0){
            /*printf("Fodasse\n");*/
            break;
        }
        
        //printf("valor do buffer %s\n",buffer);
        token=strtok(buffer," ");
        i = atoi(token); /*inicial*/
        while(1){
            /*printf("Valor do token %s\n",token);*/
            token = strtok(NULL," ");
            if(token != NULL) {
                grafo[i-1][atoi(token)-1] = 1; /*criar a ligacao*/
                grafo[atoi(token)-1][i-1] = 1; /*criar a ligacao (bidirecional)*/
            } else
                break;
        }
        fflush(stdin);
        /*imprimeGrafos(grafo, nPlaces);*/
    }
    
    /*dfsAlgorithm(grafo, visited, dfs, nPlaces, 0);*/
    indexGlobal=0;
    for(i=0;i<nPlaces;i++){
        art(i,dfs,low,grafo,nPlaces,parent);
        tempo=0;
    }
    /*printf("Valor do acumulador %d\n",acumulador);*/
    acumulador = 0;
}

void art(int v,int *dfs, int *low, int **grafo,int nPlaces,int *parent){
    
    int j;
    int children;
    children=0;
    low[v]=dfs[v]=++tempo;
    /* Percorre o grafo */
    for(j=0;j<nPlaces;j++){
        if(grafo[v][j]==1){
            if(dfs[j]==-1){
                children++;
                parent[v]=j;
                art(j,dfs,low,grafo,nPlaces,parent);
                low[v]=min(low[v],low[j]);
                if(dfs[v]==1 && dfs[j]!=2)
                    acumulador++;
                if(dfs[v]!=1 && low[j]>=dfs[v])
                    acumulador++;
            }
            else if(j!=parent[v]){
                low[v]=min(low[v],dfs[j]);
            }
        }
    }
}

int min(int a,int b){
    if (a>b)
        return b;
    else
        return a;
}

void dfsAlgorithm(int**grafo, int*visited, int*dfs, int nPlaces, int index){
    int j;
    dfs[indexGlobal++] = index+1;
    visited[index] = 1;
    
    for(j= 0; j<nPlaces; j++){
        if(!visited[j] && grafo[index][j] == 1) {
            dfsAlgorithm(grafo, visited, dfs, nPlaces, j);
        }
    }
}

void imprimeGrafos(int **grafo,int n){
    printf("Conteudo do grafo\n");
    int i,j;
    for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d\t",grafo[i][j]);
        }
        printf("\n");
    }
}
