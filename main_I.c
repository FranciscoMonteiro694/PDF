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
    int cor;
    struct nodeT *next;
}Queue;
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
int veBipartido(int aux,int n,int *visited,int * cores);
void enqueue(int * queue,int x,int tamanho);
int deque(int * queue,int tamanho);
int QueueEmpty(int * queue,int tamanho);
void printQueue(int * queue,int tamanho);
int **grafo;
int main(int argc, const char * argv[]) {
    int n,m,aux,aux2,aux3,aux4;
    int i,j;
    int *visited,*cores;


    while(scanf("%d%d",&n,&m)!=EOF){
    grafo=(int**)malloc(sizeof(int*)*n);
    for (i=0;i<n;i++){
        grafo[i]=(int*)malloc(sizeof(int)*n);
        for(j=0;j<n;j++){
            grafo[i][j]=-1;
        }
    }

    for(i=0;i<m;i++){
        scanf("%d%d",&aux,&aux2);
        grafo[aux-1][aux2-1]=10;
        grafo[aux2-1][aux-1]=10;
    }
     visited=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        visited[i]=0;

    }
    /*queue=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        queue[i]=-1;

    }*/
    cores=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        cores[i]=-1;

    }
    /*for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d  ",grafo[i][j]);
        }
        printf("\n");
    }*/
    aux4=0;
    while(QueueEmpty(visited,n)!=-1){
           /* printf("\n\n\n");
            printf("------Visited-----\n");
            printQueue(visited,n);
             printf("------Cores-----\n");
            printQueue(cores,n);
            printf("\n\n\n");*/
            aux3=QueueEmpty(visited,n);
            aux4=aux4+veBipartido(aux3,n,visited,cores);
            if(aux4>0){
                break;
            }
    }
    if(aux4>0){
                printf("Yes\n");
            }
    else{
          printf("No\n");
    }
   /* printf("------Visited-----\n");
    printQueue(visited,n);
    printf("------Cores-----\n");
    printQueue(cores,n);*/
   /* for(i=0;i<n;i++){
        if(veBipartido(i,n,visited,cores)==1){
                printf("Yes\n");
        }
        else{
            printf("No\n");
        }
    }*/
   /* for (i=0;i<n;i++){
        for(j=0;j<n;j++){
            printf("%d  ",grafo[i][j]);
        }
        printf("\n");
    }*/
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
        if(queue[i]==0){
            return i;
        }
    }
    return -1;
    }

void printQueue(int * queue,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
            printf("%d    ",queue[i]);
        }
    printf("\n");
    }

int veBipartido(int aux,int n,int *visited,int * cores){
    int i,t,corAnt;
    Queue *fila;
    /*mark v*/
    visited[aux]=1;
    fila=CriaQueue(aux,1);
    cores[aux]=1;
    /*enqueue(queue,aux,n);*/
    while(fila!=NULL){
         t=fila->val;
         corAnt=fila->cor;
         fila=fila->next;
         for(i=0;i<n;i++){
                /*sera onde eu vou meter a codiçao das cores i guees*/
                if(grafo[t][i]>0&&cores[i]==corAnt){
                    return 1;
                }
                if(visited[i]==0&&grafo[t][i]>0){
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
