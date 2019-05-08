#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define ALFA 26


/*
1
 
7
Z G
D Z
A C
C Y
D G
G A
D Y
6
Z G
G A
Z A
C Y
A C
D Z
 
2 casos de teste
 
2
 
7
Z G
D Z
A C
C Y
D G
G A
D Y
6
Z G
G A
Z A
C Y
A C
D Z
 
7
Z G
D Z
A C
C Y
D G
G A
D Y
6
Z G
G A
Z A
C Y
A C
D Z
 
 
 
 
 
 */
void analisa(int *array,int nCasosTeste,int iterador);
char alfabeto[26] = { 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I','J','K','L','M','N','O','P','Q'
    ,'R','S','T','U','V','W','X','Y','Z'};
int indiceAlfa(char letra);
void imprimeGrafos(int **grafo);
int compara(int **grafo1,int **grafo2);
void floyd(int **grafo);
int main(int argc, const char * argv[]) {
    int nCasosTeste,i;
    int *array;
    scanf("%d",&nCasosTeste);
    /* Cria e inicializa array a 0 */
    array=(int*)malloc(sizeof(int)*nCasosTeste);
    memset (array, 0, sizeof (int) * nCasosTeste);
    for(i=0;i<nCasosTeste;i++){
        analisa(array,nCasosTeste,i);
    }
    
    for(i=0;i<nCasosTeste;i++){
        if(array[i]==0)
            printf("NO\n");
        else
            printf("YES\n");
        
        if(i!=nCasosTeste-1)
            printf("\n");
    }

    return 0;
}
/* Vai receber uma letra e devolver o seu indice */
int indiceAlfa(char letra){
    int i;
    for(i=0;i<26;i++){
        if(letra==alfabeto[i])
            return i;
    }
    return 0;
}
/* Debug */
void imprimeGrafos(int **grafo){
    printf("Conteudo do grafo\n");
    int i,j;
    printf("  ");
    for(j=0;j<ALFA;j++){
        printf("%c ",alfabeto[j]);
    }
    printf("\n");
    for (i=0;i<ALFA;i++){
        printf("%c ",alfabeto[i]);
        for(j=0;j<ALFA;j++){
            printf("%d ",grafo[i][j]);
        }
        printf("\n");
    }
}
void analisa(int *array,int nCasosTeste,int iterador){
    int nLigacoes1,nLigacoes2;
    int i;
    int **grafo1,**grafo2;
    char aux1,aux2;
    /* Gondola1 */
    scanf("\n%d",&nLigacoes1);
    /* Inicializar grafo 1 26x26 */
    grafo1=(int**)malloc(sizeof(int*)*ALFA);
    for (i=0;i<ALFA;i++){
        grafo1[i]=(int*)malloc(sizeof(int)*ALFA);
    }
    // Para inicializar a matriz a 0
    for (i=0;i<ALFA;i++){
        memset (grafo1[i], 0, sizeof (int) * ALFA);
    }
    for(i=0;i<nLigacoes1;i++){
        scanf(" %c %c",&aux1,&aux2);
        grafo1[indiceAlfa(aux1)][indiceAlfa(aux2)]=1;
    }
    /* Gondola2 */
    scanf("%d",&nLigacoes2);
    /* Inicializar grafo 2 26x26*/
    grafo2=(int**)malloc(sizeof(int*)*ALFA);
    for (i=0;i<ALFA;i++){
        grafo2[i]=(int*)malloc(sizeof(int)*ALFA);
    }
    // Para inicializar a matriz a 0
    for (i=0;i<ALFA;i++){
        memset (grafo2[i], 0, sizeof (int) * ALFA);
    }
    for(i=0;i<nLigacoes2;i++){
        scanf(" %c %c",&aux1,&aux2);
        grafo2[indiceAlfa(aux1)][indiceAlfa(aux2)]=1;
    }
    // Chamar a funcao floyd para os dois grafos
    floyd(grafo1);
    floyd(grafo2);
    array[iterador]=compara(grafo1,grafo2);
    

}

void floyd(int **grafo){
    int k,i,j;
    for (k=0;k<ALFA;k++){
        for(i=0;i<ALFA;i++){
            for(j=0;j<ALFA;j++){
                if((grafo[i][k] == 1) && (grafo[k][j]==1))
                    grafo[i][j]=1;
            }
        }
    }
}

int compara(int **grafo1,int **grafo2){
    int i,j;
    for(i=0;i<ALFA;i++){
        for(j=0;j<ALFA;j++){
            // Vai falhar, imprimir NO
            if(grafo1[i][j]!=grafo2[i][j])
                return 0;
        }
    }
    return 1;
}
