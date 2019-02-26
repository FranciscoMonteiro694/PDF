
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

int best; // variável onde se vai guardar o melhor nº de colisões, depois também vai ser preciso guardar o inicio e fim de cada collider para validação

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

// backtrackin dos slides, pseudocódigo
int backtracking(s){
    if reject(s) = true then // caso de rejeição, se o nº de interceções ultrapassar o best
        return false
    if accept(s) = true then // caso base, se todos os devices já foram colocados; ou se tivermos menos de 4 devices retornamos 0 aqui (?)
        output(s)
        return true
    while condition(s) = true do // dois ciclos for?
        s′ = update(s)  // novo candidato
        if BT(s′) = true then // passo recursivo
        return true 
    return false
}

// Função que devolve 1 se os dois colliders se interceptarem
// Caso contrário devolve 0
int intercept(int x1, int y1, int x2, int y2){

}
