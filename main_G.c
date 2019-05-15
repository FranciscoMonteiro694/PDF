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
/*Estrutra queue FIFO*/

/*Cria um no e devolve um ponteiro dele mesmo*/
Queue* CriaQueue(int val){
    Queue *ponteiro;
    if ((ponteiro=malloc(sizeof(Queue)))== NULL)
        printf("Estoirou!\n");
    ponteiro->val=val;
    ponteiro->next=NULL;
    return ponteiro;
}
/*adiciona um no(cria um com a funcao de criar) ao fim da fila*/
void adicionaFim(int val,Queue* fila){
    Queue *ponteiro;
    ponteiro=fila;
    while(ponteiro->next!=NULL){
            ponteiro=ponteiro->next;
    }
    ponteiro->next=CriaQueue(val);
}
/*debug*/
void imprimeFila(Queue* fila){
    Queue *ponteiro;
    ponteiro=fila;
    while(ponteiro!=NULL){
           printf("%d   ",ponteiro->val);
           ponteiro=ponteiro->next;
    }
    printf("\n");
}
/*nao e usada*/
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
int **grafo;
int main(int argc, const char * argv[]) {
    int n,aux,aux2;
    int i,j;
    /*recebe input*/
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
    /*para cada no verificar se existe um ciclo(ou um caminho para ele mesmo)*/
    for(i=0;i<n;i++){
        if(veCivlos(i,n)==1){
                printf("%d\n",i);

        }
    }
    return 0;


}
/*recebe o numero de vertice e o no pelo qual começar*/
/*a fila e o essencial do bfs*/
int veCivlos(int aux,int n){
    int i,*visited,t;
    Queue *fila;
    visited=(int*)malloc(sizeof(int)*n);
    /*um array para sabermos por que nos ja passamos*/
    for (i=0;i<n;i++){
        visited[i]=0;
    }
    /*cria a fila e marka um no inicial como visitado*/
    visited[aux]=1;
    fila=CriaQueue(aux);
    while(fila!=NULL){
         /*Retira o valor do inicio da fila e elemina o no(come-o)*/
         t=fila->val;
         fila=fila->next;
         for(i=0;i<n;i++){
                /*e aqui que se ve se existe um ciclo se o no que tamos a olhar i,nos samos o t é o mesmo onde começamos*/
                if(grafo[t][i]>0&&i==aux){
                    return 1;
                }
                /*se nao for visitado e houver ligaçao visitamos e metemos na fila*/
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
