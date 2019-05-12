#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

/*
5
6
1 2 2
1 3 3
2 3 15
2 4 2
3 5 13
4 5 9
3
2 5
1 4
3 4
*/
void floydWarshall(int** matriz, int compNumb, int transNumber);
void imprimeGrafos(int **grafo,int n);
void imprimeResultado(int **matriz, int compNumb);

int main()
{
    /*FLOYD WARSHALL*/

    int compNumb; /*numero de compounds*/
    scanf("%d", &compNumb);

    int transNumber; /*numero de transformacoes diretas (ligacoes)*/
    scanf("%d", &transNumber);

    /*matriz que guarda as distancias menores entre pares de pontos*/
    int **matriz;
    matriz = (int**)malloc(sizeof(int*)*compNumb);
    int i, j;
    for(i = 0; i<compNumb; i++) {
        matriz[i] = (int*)malloc(sizeof(int)*compNumb);
        /*incializamos a 0*/
        for(j=0; j<compNumb; j++) {
            if(j==i){
                matriz[i][j] = 0;
            } else {
                matriz[i][j] = 99999; /*nao existe ligacao possivel*/
            }

        }
    }

    floydWarshall(matriz, compNumb, transNumber);
    imprimeResultado(matriz, compNumb);
    return 0;
}

void floydWarshall(int** matriz, int compNumb, int transNumber) {
    /*atualiza com as distancias diretas*/
    int i, aux1, aux2, aux3;
    for(i=0; i<transNumber; i++) {
        scanf("%d %d %d", &aux1, &aux2, &aux3);
        matriz[aux1-1][aux2-1] = aux3;
    }

    int k, j;
    for(k=0; k<compNumb; k++) {
        for(i=0; i<compNumb; i++) {
            for(j=0; j<compNumb; j++) {
                if(matriz[i][j] > matriz[i][k] + matriz[k][j]) {
                    matriz[i][j] = matriz[i][k] + matriz[k][j];
                }
            }
        }
    }
}

void imprimeResultado(int **matriz, int compNumb) {
    int i, aux1, aux2, aux3;
    scanf("%d", &aux3);
    int results[aux3];
    for(i=0; i<aux3; i++) {
        scanf("%d %d", &aux1, &aux2);
        results[i] = matriz[aux1-1][aux2-1];
    }
    for(i=0; i<aux3; i++) {
        if(results[i]!=99999) {
            printf("%d\n", results[i]);
        } else {
            printf("Impossible!\n");
        }
    }
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
