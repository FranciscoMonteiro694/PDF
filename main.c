#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pontoo {
    int x; // coordenada x do ponto
    int y; // coordenada y do ponto
}Ponto;
int intersectGlobal( int (*coliders)[2], int *disp, Ponto *locais,int nColiders, int iterador);
int orientation(Ponto p, Ponto q, Ponto r);
int intersect(Ponto p1, Ponto p2, Ponto t1, Ponto t2);
int onSegment(Ponto p, Ponto q, Ponto r);
int backtracking(Ponto *locais,int (*coliders)[2],
                 int *disp,int nPontos,int nColiders,int nDispositivos,int iterador,int counter, int *visit);
int best; // variavel onde se vai guardar o melhor n de colisoes, depois tambem vai ser preciso guardar o inicio e fim de cada collider para validacao

int temp;

//clock_t start, end;
//double cpu_time_used;
//double total;


int max2(int a, int b) {
    if ((a) > (b)) {
        return a;
    } else
        return b;
}

int min2(int a, int b) {
    if ((a) < (b)) {
        return a;
    } else
        return b;
}

int main()
{
    //total=0;
    // Guardar numero de locais e coordenadas x,y
    int nPontos;
    int i;
    scanf("%d", &nPontos);
    Ponto locais[nPontos];
    for(i=0; i<nPontos; i++) {
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
    for(i=0; i<nColiders; i++) {
        scanf("%d %d", &(coliders[i][0]), &(coliders[i][1]));
    }
    // Ciclo para imprimir as coordenadas dos colliders
    //    for(int i=0; i<nColiders; i++) {
    //        printf("Coordenadas dos colliders (inicio e fim): %d %d\n", coliders[i][0], coliders[i][1]);
    //    }
    //
    int disp[nDispositivos]; //vai guardar os indices dos lugares dos dispositivos
    for(i=0;i<nDispositivos;i++){
        disp[i]=-1;
    }
    best = nColiders*nColiders;
    int visit[nPontos];
    for( i=0;i<nPontos;i++){
        visit[i]=0;
    }
    backtracking(locais, coliders, disp, nPontos, nColiders,  nDispositivos,  0,  0, visit);

    printf("%d",best);
//    printf("Tempo gasto: %f\n",total);
    return 0;
}

// backtracking, pseudocodigo
int backtracking(Ponto *locais,int (*coliders)[2],
                 int *disp,int nPontos,int nColiders,int nDispositivos,int iterador,int counter, int *visit){

    if (counter > best){ // caso de rejeicao, se o n de intercecoes ultrapassar o best
        return best;
    }

    if (iterador == nDispositivos) { //chego ao fim do ramo e tenho o melhor caso ou igual
//        printf("\nIntersecoes: %d\n", counter+temp);
//        printf("\n");
        best = counter;
        return best;
    }

    int i;
    for(i = 0; i<nPontos; i++) {
        if(visit[i] == 0) { //caso nao tenha sido visitado
            visit[i] = 1;
            disp[iterador] = i; //colocar o local no dispositivo (ATENCAO QUE 0=1)
//            if(disp[3]!=-1) {
//                temp = intersectGlobal(coliders, disp, locais, nColiders, iterador);
//            } else {
//                counter = 0;
//                temp = 0;
//            }
            //counter += temp;
//            printf("Conteudo: ");
//            for(int i=0;i<nDispositivos;i++){
//                printf("%d ",disp[i]);
//            }
//            printf("\n");
//            printf("Visit: ");
//            for(int i=0;i<nPontos;i++){
//                printf("%d ",visit[i]);
//            }
//
//printf("\nIntersecoes: %d\n", counter+temp);
//printf("\n");
            temp = intersectGlobal(coliders, disp, locais, nColiders, iterador);
            backtracking(locais, coliders, disp, nPontos, nColiders, nDispositivos, iterador+1, counter + temp, visit);
            visit[i] = 0;
            disp[iterador] = -1;
        }
    }
    return counter;
}

int intersectGlobal(int (*coliders)[2], int *disp, Ponto *locais, int nColiders, int iterador) {
//    start = clock();
    int i, j;
    int acum = 0;
    for(i=0; i<nColiders; i++) {
        if(coliders[i][0] == iterador +1 || coliders[i][1] == iterador +1){
            if(disp[coliders[i][0]-1] != (-1) && disp[coliders[i][1]-1] != (-1)) {
               //printf("primeiro cralhes\n");
                for(j=0; j<nColiders; j++) {
                    if(i!=j){
                        //printf("segundo cralhes\n");
                        if(disp[coliders[j][0]-1] != (-1) && disp[coliders[j][1]-1] != (-1)) {
                            //printf("terceiro cralhes\n");
                            acum += intersect(locais[disp[coliders[i][0]-1]], locais[disp[coliders[i][1]-1]], locais[disp[coliders[j][0]-1]], locais[disp[coliders[j][1]-1]]);
                        }
                    }
                }
            }
        }
    }
//    end = clock();
//    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//    total+=cpu_time_used;
    return acum;
}

// Funcao que devolve 1 se os dois colliders se interceptarem
// Caso contrario devolve 0
int intersect(Ponto p1, Ponto t1, Ponto p2, Ponto t2) {  //recebe 4 pontos (duas linhas) e verifica intersecao

    //orientacao entre os nos de forma a descobrir se esta a cada ponto a esquerda/direita da linha
    int o1 = orientation(p1, t1, p2);
    int o2 = orientation(p1, t1, t2);
    int o3 = orientation(p2, t2, p1);
    int o4 = orientation(p2, t2, t1);

    //caso um dos pontos fique num lado e o outro no lado oposto
    if (o1 != o2 && o3 != o4) {
        if(o1 == 0 || o2 == 0 || o3 == 0 || o4 == 0) {
            return 0;
        }
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
    if (q.x <= max2(p.x, r.x) && q.x >= min2(p.x, r.x) && q.y <= max2(p.y, r.y) && q.y >= min2(p.y, r.y)) {
        return 1;
    }

    return 0;
}
