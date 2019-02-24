
/*so as funcoes de leitura*/


#include <stdio.h>
#include <stdlib.h>

typedef struct Pontoo {
    int x; // coordenada x do ponto
    int y; // coordenada y do ponto
}Ponto;


// Cada Node vai ter 
typedef struct Nodee {
    Ponto p; // Coordenadas do place
    int place; // indice do lugar nos arrays, pode não ser preciso
    int device; // nº(indice) do device presente no node(place)
}Node;

int main()
{

    // Guardar numero de locais e coordenadas x,y
    int nPontos;
    scanf("%d", &nPontos);
    Ponto locais[nPontos];
    for(int i=0; i<nPontos; i++) {
        scanf("%d %d", &(locais[i].x), &(locais[i].y));
    }
    // Ciclo para imprimir as coordenadas dos lugares
    for(int i=0; i<nPontos; i++) {
        printf("Coordenadas dos pontos: %d %d\n", locais[i].x, locais[i].y);
    }

    // guardar nDispositivos e coliders
    int nDispositivos, nColiders;
    scanf("%d %d", &nDispositivos, &nColiders);
    int coliders[nColiders][2]; //coliders
    for(int i=0; i<nColiders; i++) {
        scanf("%d %d", &(coliders[i][0]), &(coliders[i][1]));
    }
    // Ciclo para imprimir as coordenadas dos colliders
    for(int i=0; i<nColiders; i++) {
        printf("Coordenadas dos colliders (inicio e fim): %d %d\n", coliders[i][0], coliders[i][1]);
    }


    return 0;
}

