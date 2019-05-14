#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

5
5 1 2 3 4
0
6
2 1 3
5 4 6 2
0
0
*/
void analisa(int nPlaces);
void imprimeGrafos(int **grafo,int n);
int main(int argc, const char * argv[]) {
    int nPlaces;
    while(1){/* Usar breaks aqui à campeão */
        scanf("%d\n",&nPlaces);
        if(nPlaces==0)
            break;
        analisa(nPlaces);
    }

    return 0;
}
/* Se estrabuchar a imprimir, tentar por esta funcao a retornar int */
void analisa(int nPlaces){
    int **grafo;
    int i;
    char *buffer;
    char *token;
    grafo=(int**)malloc(sizeof(int*)*nPlaces);
    buffer=(char*)malloc(sizeof(char)*50);
    for (i=0;i<nPlaces;i++){
        grafo[i]=(int*)malloc(sizeof(int)*nPlaces);
        memset (grafo[i], 0, sizeof (int) * nPlaces);
    }
    while(fgets(buffer, sizeof(buffer), stdin)){
//        if (strcmp(buffer,"0")==0)
//            printf("Fodasse");
        printf("valor do buffer %s",buffer);
        token=strtok(buffer," ");
        while(token != NULL){
            //printf("Valor do token %s",token);
            token = strtok(NULL," ");
        }
    }
}

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
