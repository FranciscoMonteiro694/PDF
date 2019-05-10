/*
 
2
3 3
0 1 1000
1 2 15
2 1 -42
4 4
0 1 10
1 2 20
2 3 30
3 0 -60

1
4 4
0 1 10
1 2 20
2 3 30
3 0 -60
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void analisa(int *array, int indice);
void imprimeGrafos(int **grafo,int n);
int belmanFord(int **grafo,int nEstrelas,int nBuracos,int source,int *array,int indice);
int main(int argc, const char * argv[]) {
    int nCasos,i;
    int *array;
    scanf("%d",&nCasos);
    /* Cria e inicializa array a 0 */
    array=(int*)malloc(sizeof(int)*nCasos);
    memset (array, 0, sizeof (int) * nCasos);
    for(i=0;i<nCasos;i++){
        analisa(array,i);
    }
    for(i=0;i<nCasos;i++){
        if(array[i]==0)
            printf("possible\n");
        else
            printf("not possible\n");
    }
    
    return 0;
}

void analisa(int *array, int indice){
    /* Os buracos sao as ligacoes */
    int nEstrelas,nBuracos;
    int i;
    int **grafo1;
    int auxLinha,auxCol,auxValor;
    /* Ler o nº de estrelas e buracos */
    scanf("%d %d",&nEstrelas,&nBuracos);
    /* Inicializar grafo nEstrelas x nBuracos */
    grafo1=(int**)malloc(sizeof(int*)*nEstrelas);
    for (i=0;i<nEstrelas;i++){
        grafo1[i]=(int*)malloc(sizeof(int)*nEstrelas);
    }
    /* Para inicializar a matriz a 0 */
    for (i=0;i<nEstrelas;i++){
        memset (grafo1[i], 0, sizeof (int) * nEstrelas);
    }
    /* Para ler do teclado */
    for(i=0;i<nBuracos;i++){
        scanf("%d %d %d",&auxLinha,&auxCol,&auxValor);
        grafo1[auxLinha][auxCol]=auxValor;
    }
    /* imprimeGrafos(grafo1,nEstrelas); */
    belmanFord(grafo1,nEstrelas,nBuracos, 0, array, indice);
    
}

/* Debug */
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
/* Coloca 1 no array, se tiver ciclos negativos */
int belmanFord(int **grafo,int nEstrelas,int nBuracos,int source,int *array,int indice){
    int i,j;
    int *distancia;
    /* Alocar e inicializar o array das distancias */
    distancia=(int*)malloc(sizeof(int)*nEstrelas);
    distancia[source]=0;
    for(i=1;i<nEstrelas;i++)
        distancia[i]=999999;
    for(i=0;i<nEstrelas-1;i++){
        for (j=0;j<nBuracos;j++){
            if(distancia[i]>distancia[j]+grafo[j][i]){
                distancia[i]=distancia[j]+grafo[j][i];
            }
        }
    }
    /* Repetir o mesmo ? */
    for(i=0;i<nEstrelas-1;i++){
        for (j=0;j<nBuracos;j++){
            if(distancia[i]>distancia[j]+grafo[j][i]){
                /* Ciclo negativo */
                array[indice]=1;
                return 1;
            }
        }
    }
    /*
    printf("Vetor das distancias\n");
    for(i=0;i<nEstrelas;i++){
        printf("%d\t",distancia[i]);
    }
    */
    
    return 0;
}

