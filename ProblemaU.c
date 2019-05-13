

/*
 
5
0 1 0 0 1
1 0 0 1 0
0 0 0 0 0
0 1 0 0 1
1 0 0 1 0
 
5
0 1 0 0 1
1 0 0 1 1
0 0 0 0 0
0 1 0 0 1
1 1 0 1 0

 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodeT *fila;
typedef struct nodeT{
    int val;
    int cor;
    struct nodeT *next;
}Queue;

void imprimeGrafos(int **grafo,int n);
Queue* CriaQueue(int val,int cor);
void adicionaFim(int val,int cor,Queue* fila);
void bfs(int **grafo,int n);
int QueueEmpty(int * queue,int tamanho);
int veBipartido(int **grafo,int aux,int n,int *visited,int * cores);
int main(int argc, const char * argv[]) {
    int nVertices,i,j,flag;
    int **matriz;
    flag=0;
    scanf("%d",&nVertices);
    /* Alocar matriz de adjacencia */
    matriz=(int**)malloc(sizeof(int*)*nVertices);
    for(i=0;i<nVertices;i++){
        matriz[i]=(int*)malloc(sizeof(int)*nVertices);
    }
    /* Ler matriz do teclado */
    for(i=0;i<nVertices;i++){
        for(j=0;j<nVertices;j++){
            scanf("%d",&matriz[i][j]);
        }
    }
    bfs(matriz,nVertices);
    return 0;
}

void bfs(int **grafo,int n){
    int *visited,*cores;
    int i,aux4,aux3;
    
    visited=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        visited[i]=0;
    }
    cores=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        cores[i]=-1;
    }
    aux4=0;
    while(QueueEmpty(visited,n)!=-1){
        aux3=QueueEmpty(visited,n);
        aux4=aux4+veBipartido(grafo,aux3,n,visited,cores);
        if(aux4>0){
            break;
        }
    }
    if(aux4>0){
        printf("False\n");
    }
    else{
        printf("True\n");
    }
}

Queue* CriaQueue(int val,int cor){
    Queue *ponteiro;
    if ((ponteiro=malloc(sizeof(Queue)))== NULL)
        printf("Estoirou!\n");
    ponteiro->val=val;
    ponteiro->cor=cor;
    ponteiro->next=NULL;
    return ponteiro;
}
void adicionaFim(int val,int cor,Queue* fila){
    Queue *ponteiro;
    ponteiro=fila;
    while(ponteiro->next!=NULL){
        ponteiro=ponteiro->next;
    }
    ponteiro->next=CriaQueue(val,cor);
}

int veBipartido(int **grafo,int aux,int n,int *visited,int * cores);
int QueueEmpty(int * queue,int tamanho);
int **grafo;


int QueueEmpty(int * queue,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        if(queue[i]==0){
            return i;
        }
    }
    return -1;
}

int veBipartido(int **grafo,int aux,int n,int *visited,int * cores){
    int i,t,corAnt;
    Queue *fila;
    /*mark v*/
    visited[aux]=1;
    fila=CriaQueue(aux,1);
    cores[aux]=1;
    while(fila!=NULL){
        t=fila->val;
        corAnt=fila->cor;
        fila=fila->next;
        for(i=0;i<n;i++){
            /*sera onde eu vou meter a codi�ao das cores i guees*/
            if(grafo[t][i]>0 && cores[i]==corAnt){
                return 1;
            }
            if(visited[i]==0 && grafo[t][i]>0){
                visited[i]=1;
                if(fila!=NULL){
                    if(corAnt==1){
                        cores[i]=2;
                        adicionaFim(i,2,fila);
                    }
                    else{
                        cores[i]=1;
                        adicionaFim(i,1,fila);
                    }
                    
                }
                else{
                    if(corAnt==1){
                        cores[i]=2;
                        fila=CriaQueue(i,2);
                        
                    }
                    else{
                        cores[i]=1;
                        fila=CriaQueue(i,1);
                    }
                    
                }
                
            }
        }
    }
    return 0;
    }
