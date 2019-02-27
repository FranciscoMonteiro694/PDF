
/*so as funcoes de leitura*/

/*
7
5 9
7 8
7 5
6 2
3 3
2 5
3 8
5 4
1 2
1 3
3 5
2 4
*/

#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )

#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )

#include <stdio.h>
#include <stdlib.h>

typedef struct Pontoo {
    int x; // coordenada x do ponto
    int y; // coordenada y do ponto
}Ponto;
int intersectGlobal( int (*coliders)[2], int *disp, Ponto *locais,int nColiders);
int orientation(Ponto p, Ponto q, Ponto r);
int intersect(Ponto p1, Ponto p2, Ponto t1, Ponto t2);
int onSegment(Ponto p, Ponto q, Ponto r);
int backtracking(Ponto *locais,int (*coliders)[2],
                 int *disp,int nPontos,int nColiders,int nDispositivos,int iterador,int counter, int *visit);
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
//    for(int i=0; i<nPontos; i++) {
//        printf("Coordenadas dos pontos: %d %d\n", locais[i].x, locais[i].y);
//    }
    
    // guardar nDispositivos e coliders
    int nDispositivos;
    int nColiders;
    scanf("%d %d", &nDispositivos, &nColiders);
    int coliders[nColiders][2]; //coliders
    for(int i=0; i<nColiders; i++) {
        scanf("%d %d", &(coliders[i][0]), &(coliders[i][1]));
    }
    // Ciclo para imprimir as coordenadas dos colliders
//    for(int i=0; i<nColiders; i++) {
//        printf("Coordenadas dos colliders (inicio e fim): %d %d\n", coliders[i][0], coliders[i][1]);
//    }
//
    int disp[nDispositivos]; //vai guardar os indices dos lugares dos dispositivos
    for(int i=0;i<nDispositivos;i++){
        disp[i]=-1;
    }
    best = nColiders*nColiders;
    int visit[nDispositivos];
    
    backtracking(locais, coliders, disp, nPontos, nColiders,  nDispositivos,  0,  0, visit);
    
    printf("Best: %d",best);
    return 0;
}

// backtracking, pseudocódigo
int backtracking(Ponto *locais,int (*coliders)[2],
                 int *disp,int nPontos,int nColiders,int nDispositivos,int iterador,int counter, int *visit){
    
    printf("Conteudo: ");
    for(int i=0;i<nDispositivos;i++){
        printf("%d ",disp[i]);
    }
    printf("\n");
    if (counter > best){ // caso de rejeição, se o nº de interceções ultrapassar o best
        printf("Best: %d",best);
        return best;
    }
    
    if (iterador == nDispositivos) { //chego ao fim do ramo e tenho o melhor caso ou igual
        best=counter;
        printf("Entrei no final do ramo: %d",best);
        return best;
    }
    
    int i;
    for(i = 0; i<nPontos; i++) {
        //if(visit[i] == 0) { //caso nao tenha sido visitado
            visit[i] = 1;
            disp[iterador] = i; //colocar o local no dispositivo (ATENCAO QUE 0=1)
            //calcula intersecoes, tirem se quiserem FDS
            counter = intersectGlobal(coliders, disp,locais,nColiders);
            backtracking(locais, coliders, disp, nPontos, nColiders, nDispositivos, iterador+1, counter, visit);
            visit[i] = 0;
        //}
    }
    
    return counter;
    
}

int intersectGlobal(int (*coliders)[2], int *disp, Ponto *locais,int nColiders) {
    int i, j;
    int acum = 0;
    for(i=0; i<nColiders-1; i++) {
        if(disp[coliders[i][0]-1] != (-1) && disp[coliders[i][1]-1] != (-1)) {
            for(j=i+1; j<nColiders; j++) {
                if(disp[coliders[j][0]-1] != (-1) && disp[coliders[j][1]-1] != (-1)) {
                    acum += intersect(locais[disp[coliders[i][0]-1]], locais[disp[coliders[i][1]-1]], locais[disp[coliders[j][0]-1]], locais[disp[coliders[j][1]-1]]);
                }
            }
        }
    }
    return acum;
    
}

// Função que devolve 1 se os dois colliders se interceptarem
// Caso contrário devolve 0
int intersect(Ponto p1, Ponto p2, Ponto t1, Ponto t2) {  //recebe 4 pontos (duas linhas) e verifica interseçao
    
    //orientacao entre os nos de forma a descobrir se esta a cada ponto a esquerda/direita da linha
    int o1 = orientation(p1, t1, p2);
    int o2 = orientation(p1, t1, t2);
    int o3 = orientation(p2, t2, p1);
    int o4 = orientation(p2, t2, t1);
    
    //caso um dos pontos fique num lado e o outro no lado oposto
    if (o1 != o2 && o3 != o4) {
        return 1;
    }
    
    // p1, q1 and p2 are colinear and p2 lies on segment p1q1
    if (o1 == 0 && onSegment(p1, p2, t1) == 1) {
        return 1;
    }
    // p1, q1 and q2 are colinear and q2 lies on segment p1q1
    if (o2 == 0 && onSegment(p1, t2, t1) == 1) {
        return 1;
    }
    
    // p2, q2 and p1 are colinear and p1 lies on segment p2q2
    if (o3 == 0 && onSegment(p2, p1, t2) == 1) {
        return 1;
    }
    
    // p2, q2 and q1 are colinear and q1 lies on segment p2q2
    if (o4 == 0 && onSegment(p2, t1, t2) == 1) {
        return 1;
    }
    
    return 0;
}



int orientation(Ponto p, Ponto q, Ponto r) {
    
    int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (val == 0) return 0; // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
    
}

int onSegment(Ponto p, Ponto q, Ponto r)
{
    if (q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) && q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y)) {
        return 1;
    }
    
    return 0;
}
