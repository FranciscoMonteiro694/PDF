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
/*BFs esta na dos verCiclos*/
typedef struct nodeT *fila;
typedef struct nodeT{
    int val;
    int cor;/*unica difereça e este atributo parasaber qual a cor do no ao o tirarmos da fila*/
    struct nodeT *next;
}Queue;
/*Bfs*/
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
int QueueEmpty(int * queue,int tamanho);
int **grafo;

/*Para saber que o grafo e bipartido,ou seja dividido em dois grupos,basta colorir um grafo com duas core e no final nao pode haver cores seguidas*/
int main(int argc, const char * argv[]) {
    int n,m,aux,aux2,aux3,aux4;
    int i,j;
    int *visited,*cores;
    /*input*/
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
    /*array para saber qual os nos/verices ja visitatos pois temos de passar por todos*/
    visited=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        visited[i]=0;

    }
    /*array que nos diz qual a cor de cada vertice*/
    cores=(int*)malloc(sizeof(int)*n);
    for (i=0;i<n;i++){
        cores[i]=-1;

    }
    aux4=0;
    /*enquanto nao visitarmos todos os nos (o nome engana XD)*/
    while(QueueEmpty(visited,n)!=-1){
            /*indica qual o no que ainda nao passamos*/
            aux3=QueueEmpty(visited,n);
            /*os grafos podem tar partidos*/
            /*ver se essa parte do grafo e bipartida*/
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
    }
    return 0;


}
/*funcao que devolve o indice onde se encotra o primeiro 0 de um array*/
int QueueEmpty(int * queue,int tamanho){
    int i;
    for(i=0;i<tamanho;i++){
        if(queue[i]==0){
            return i;
        }
    }
    return -1;
    }
int veBipartido(int aux,int n,int *visited,int * cores){
    /*BFS normal com apenas mais um atributo que e a cor*/
    int i,t,corAnt;
    Queue *fila;
    /*visitamos o primeiro no e metemos-o na fila e damoslhe uma cor*/
    visited[aux]=1;
    fila=CriaQueue(aux,1);
    cores[aux]=1;
    while(fila!=NULL){
         /*retira o primeiro elemento da fila gurdamos a cor*/
         t=fila->val;
         corAnt=fila->cor;
         fila=fila->next;
         for(i=0;i<n;i++){
                /*Se a cor do no anterior for igual a do nosso vizinho quer dizer que nao e bipartido*/
                if(grafo[t][i]>0&&cores[i]==corAnt){
                    return 1;
                }
                /*Bfs classico apenas muda a cor*/
                if(visited[i]==0&&grafo[t][i]>0){
                     visited[i]=1;
                     if(fila!=NULL){
                        if(corAnt==1){
                            /*dar a cor ao no que visitamos,com a cor contraria ao no anterior*/
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
