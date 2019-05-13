#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*


5 5
----+
-++-+
-+--+
+++-+
++--+
 
 */
void imprimeGrafos(int **grafo,int n,int k);
int main(int argc, const char * argv[]) {
    int nLinhas,nColunas,i,j;
    char c;
    int **grafo;
    scanf("%d %d",&nLinhas,&nColunas);
    /* Alocar grafo  */
    grafo=(int**)malloc(sizeof(int*)*nLinhas);
    for(i=0;i<nLinhas;i++){
        grafo[i]=(int*)malloc(sizeof(int)*nColunas);
    }
    /* Ler matriz do teclado */
    for(i=0;i<nLinhas;i++){
        for(j=0;j<nColunas;j++){
            scanf(" %c",&c);
            if(c=='-'){
                grafo[i][j]=-1;
            }
            if(c=='+'){
                grafo[i][j]=1;
            }
        }
    }
    return 0;
}

void imprimeGrafos(int **grafo,int n,int k){
    printf("Conteudo do grafo\n");
    int i,j;
    for (i=0;i<n;i++){
        for(j=0;j<k;j++){
            printf("%d\t",grafo[i][j]);
        }
        printf("\n");
    }
}
