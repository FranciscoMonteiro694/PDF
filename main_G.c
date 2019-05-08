/*
5
2 1 3
2 2 4
1 0
0
0
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct nodeT *fila;
typedef struct nodeT{
    int val;
    struct nodeT *next;
}Queue;
Queue* CriaQueue(int val){
    Queue *ponteiro;
    if ((ponteiro=malloc(sizeof(Queue)))== NULL)
        printf("Estoirou!\n");
    ponteiro->val=val;
    ponteiro->next=NULL;
    return ponteiro;
}
void adicionaFim(int val,Queue* fila){
    Queue *ponteiro;
    ponteiro=fila;
    while(ponteiro->next!=NULL){
            ponteiro=ponteiro->next;
    }
    ponteiro->next=CriaQueue(val);
}
void imprimeFila(Queue* fila){
    Queue *ponteiro;
    ponteiro=fila;
    while(ponteiro!=NULL){
           printf("%d   ",ponteiro->val);
           ponteiro=ponteiro->next;
    }
    printf("\n");
}
int retiraPrimeiro(Queue* fila){
    Queue *auxF;
    int aux;
    aux=fila->val;
    auxF=fila;
    fila=fila->next;
    free(auxF);
    return aux;
}
int veCivlos(int aux,int n);
void enqueue(int * queue,int x,int tamanho);
int deque(int * queue,int tamanho);
int QueueEmpty(int * queue,int tamanho);
void printQueue(int * queue,int tamanho);
int **grafo;
int main(int argc, const char * argv[]) {
    int n,aux,aux2;
    int i,j;

    scanf("%d",&n);

    grafo=(int**)malloc(sizeof(int*)*n);
    for (i=0;i<n;i++){
        grafo[i]=(int*)malloc(sizeof(int)*n);
        for(j=0;j<n;j++){
            grafo[i][j]=-1;
        }
    }

    for(i=0;i<n;i++){
        scanf("%d",&aux);
        for(j=0;j<aux;j++){
            scanf("%d",&aux2);
            grafo[i][aux2]=10;
        }
    }
    for(i=0;i<n;i++){
        if(veCivlos(i,n)==1){
                printf("%d\n",i);

        }
    }
    return 0;


}
void enqueue(int * queue,int x,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        if(queue[i]==-1){
             queue[i]=x;
             i=tamanho+2;
        }
    }
    }
int deque(int * queue,int tamanho){
    int i,aux;
    for(i=0;i<tamanho;i++){
        if(queue[i]!=-1){
            aux=queue[i];
            queue[i]=-1;
            return aux;
        }
    }
    return -1;
    }
int QueueEmpty(int * queue,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        if(queue[i]!=(-1)){

            return 0;
        }
    }
    return 1;
    }

void printQueue(int * queue,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
            printf("%d    ",queue[i]);
        }
    printf("\n");
    }

int veCivlos(int aux,int n){
    int i,*visited,*queue,t;
    Queue *fila;
    visited=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        visited[i]=0;

    }
    queue=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        queue[i]=-1;

    }
    /*mark v*/
    visited[aux]=1;
    fila=CriaQueue(aux);
    /*enqueue(queue,aux,n);*/
    while(fila!=NULL){
         t=fila->val;
         fila=fila->next;
         for(i=0;i<n;i++){
                if(grafo[t][i]>0&&i==aux){
                    return 1;
                }
                if(visited[i]==0&&grafo[t][i]>0){
                     visited[i]=1;
                     if(fila!=NULL){
                        adicionaFim(i,fila);
                     }
                     else{
                        fila=CriaQueue(i);
                     }

                }
         }
    }
    return 0;
    }
