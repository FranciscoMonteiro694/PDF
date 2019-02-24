#include <stdio.h>
#include <stdlib.h>

typedef struct Pontoo {
    int x;
    int y;
}Ponto;

int main()
{

    //Guardar numero de locais e coordenadas x,y
    int nPontos;
    scanf("%d", &nPontos);
    Ponto locais[nPontos];
    for(int i=0; i<nPontos; i++) {
        scanf("%d %d", &(locais[i].x), &(locais[i].y));
        //printf("%d %d\n", locais[i].x, locais[i].y);
    }

    //guardar nDispositivos e coliders
    int nDispositivos, nColiders;
    scanf("%d %d", &nDispositivos, &nColiders);
    int coliders[nColiders][2]; //coliders
    for(int i=0; i<nColiders; i++) {
        scanf("%d %d", &(coliders[i][0]), &(coliders[i][1]));
        //printf("%d %d\n", coliders[i][0], coliders[i][1]);
    }


    return 0;
}


