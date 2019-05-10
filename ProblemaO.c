/*
 
1
3 3
0 1 1000
1 2 15
2 1 -42
 
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void analisa(void);
void imprimeGrafos(int **grafo,int n);
int main(int argc, const char * argv[]) {
    int nCasos,i;
    scanf("%d",&nCasos);
    for(i=0;i<nCasos;i++){
        analisa();
    }
    return 0;
}

void analisa(){
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
    imprimeGrafos(grafo1,nEstrelas);
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
