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
percorres a matriz até encontrar um + não visitado anteriormente.
Quando encontrares, aumentas o contador de stains e chamas um BFS ou DFS a começar nesse pixel,
que vai procurar todos os vizinhos com + e assim sucessivamente, metendo esses pixeis como visitados.
Quando retornar do BFS, continuas a percorrer a matriz e fazes o mesmo sempre que encontras um + não visitado
 */
int numeroNodoas;
void imprimeGrafos(int **grafo,int n,int k);
void dfsAlgorithm(int**grafo, int**visited,int nLinhas,int nColunas, int indexI, int indexJ);
int main(int argc, const char * argv[]) {
    numeroNodoas=0;
    int nLinhas,nColunas,i,j;
    char c;
    int **grafo;
    int **visited;
    scanf("%d %d",&nLinhas,&nColunas);
    /* Alocar grafo  */
    grafo=(int**)malloc(sizeof(int*)*nLinhas);
    visited=(int**)malloc(sizeof(int*)*nLinhas);
    for(i=0;i<nLinhas;i++){
        grafo[i]=(int*)malloc(sizeof(int)*nColunas);
        visited[i]=(int*)malloc(sizeof(int)*nColunas);
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
            visited[i][j]=-1;
        }
    }

    printf("%d\n",calculaNodoas(grafo,visited,nLinhas,nColunas));
    return 0;
}
/* Devolve o número de nódoas */
int calculaNodoas(int **grafo, int **visited, int nLinhas, int nColunas){
    /*Percorrer o array até encontrar o primeiro + */
    int i,j;
    for(i=0;i<nLinhas;i++){
        for(j=0;j<nColunas;j++){

            /* Se for um + */
            if(grafo[i][j]==1 && visited[i][j]==-1){
                visited[i][j]=1;
                /* Aumentamos o nº de nodoas */
                numeroNodoas++;
                /* Chamamos o DFS */
                dfsAlgorithm(grafo,visited,nLinhas,nColunas,i,j);
            }

        }
    }
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

void dfsAlgorithm(int**grafo, int**visited,int nLinhas,int nColunas, int indexI, int indexJ){
    int i,j;
    visited[indexI][indexJ] = 1;

    for(i=0; i<nLinhas; i++){
        for(j=0; j<nColunas;j++){
            /* Se for um + e ainda não tiver sido visitado */
            if(visited[i][j]==-1 && grafo[i][j] == 1) {
                dfsAlgorithm(grafo, visited, nLinhas,nColunas, indexI,indexJ);
            }
        }
    }
}
