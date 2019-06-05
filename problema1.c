#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct Pontoo {
    int x; // coordenada x do ponto
    int y; // coordenada y do ponto
}Ponto;
int nDispositivos;

int intersectGlobal( int (*colidersAtual)[2], int *disp, Ponto *locais, int nColiders, int iterador, int (*ligacoes)[nDispositivos-1], int nDispositivos);
int orientation(Ponto p, Ponto q, Ponto r);
int intersect(Ponto p1, Ponto p2, Ponto t1, Ponto t2);
int onSegment(Ponto p, Ponto q, Ponto r);
int backtracking(Ponto *locais,int (*coliders)[2],int *disp,int nPontos,int nColiders,int nDispositivos,int iterador,int counter, int *visit,  int (*colidersAtual)[2], int (*ligacoes)[nDispositivos-1]);
void preencheLigacoes(int (*ligacoes)[nDispositivos-1],int (*coliders)[2],int nColiders);
int best; // variavel onde se vai guardar o melhor n de colisoes, depois tambem vai ser preciso guardar o inicio e fim de cada collider para validacao
void validar(int nColiders,Ponto (*locais),int (*colidersAtual)[2],int *disp);
int temp;
int acumula;
//provavelmente vou apagar PARTE 2
int ultimoIndice=0;

clock_t start, end;
double cpu_time_used;
double total;


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
    acumula = 0;
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

    int disp[nDispositivos]; //vai guardar os indices dos lugares dos dispositivos
    for(i=0;i<nDispositivos;i++){
        disp[i]=-1;
    }
    best = nColiders*nColiders;
    int visit[nPontos];
    for( i=0;i<nPontos;i++){
        visit[i]=0;
    }

    //Arrays novos
    int colidersAtual[nColiders][2]; //guarda os coliders utilizados no momento

    int ligacoes[nDispositivos][nDispositivos-1]; //guarda as ligacoes de cada um
    int j;
    //<====><====><====><====><====><====><====><====><====><====><====><====><====><====>
    //<====><====><====><====><====><====><====><====><====><====><====><====><====><====>
    //Preencher ligacoes
    for(i=0;i<nDispositivos;i++){
        for(j=0;j<nDispositivos-1;j++){
            ligacoes[i][j]=-1;
        }
    }

    start = clock();
    preencheLigacoes(ligacoes, coliders, nColiders);

    //Preencher colidersAtual
    for(i= 0; i< nColiders; i++) {
        colidersAtual[i][0] = -1;
        colidersAtual[i][1] = -1;
    }

    //<====><====><====><====><====><====><====><====><====><====><====><====><====><====>
    //<====><====><====><====><====><====><====><====><====><====><====><====><====><====>

    temp = 0;
//    temp[0] = 0;
//    temp[1] = 0;
//    temp[2] = 0;
//    for(i=0;i<nDispositivos;i++){
//        for(j=0;j<nDispositivos-1;j++){
//            printf("%d\t",ligacoes[i][j]);
//        }
//        printf("\n");
//    }


    //Chamada da funcao recursiva
//
//    Ponto x1;
//    x1.x = 0;
//    x1.y = 0;
//    Ponto x2;
//    x2.x = 2;
//    x2.y = 0;
//    Ponto x3;
//    x3.x = 3;
//    x3.y = 0;
//    Ponto x4;
//    x4.x = 5;
//    x4.y = 0;
//
//    printf("da isto: %d\n", intersect(x1, x3, x2, x4));
    if(nDispositivos <= 3){
        printf("0\n");
        return 0;
    }
    backtracking(locais, coliders, disp, nPontos, nColiders,  nDispositivos,  0,  0, visit, colidersAtual, ligacoes);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    total+=cpu_time_used;

    printf("%d\n",best);
    //printf("acumulou: %d\n", acumula);
    //printf("Tempo gasto: %f\n",total);
    return 0;
}

void preencheLigacoes(int (*ligacoes)[nDispositivos-1],int (*coliders)[2],int nColiders){
    int i,j,deviceI,deviceF,flag1,flag2;
    for(i=0;i<nColiders;i++){
        flag2=0;
        flag1=0;
        deviceI=coliders[i][0]-1;//0
        deviceF=coliders[i][1]-1;//1
        for(j=0;j<nDispositivos-1;j++){
            if(ligacoes[deviceI][j]==-1&&flag1==0){
                ligacoes[deviceI][j]=deviceF+1;
                flag1=1;
            }
            if(ligacoes[deviceF][j]==-1&&flag2==0){
                ligacoes[deviceF][j]=deviceI+1;
                flag2=1;
            }
        }
    }
}

// backtracking, pseudocodigo
int backtracking(Ponto *locais,int (*coliders)[2], int *disp,int nPontos,int nColiders,int nDispositivos,int iterador,int counter, int *visit, int (*colidersAtual)[2], int (*ligacoes)[nDispositivos-1]){

    if (counter >= best){ // caso de rejeicao, se o n de intercecoes ultrapassar o best
        return best;
    }


    if (iterador == nDispositivos) { //chego ao fim do ramo e tenho o melhor caso ou igual
//        printf("\nIntersecoes: %d\n", counter+temp);
//        printf("\n");
        best = counter;
        //validar(nColiders,locais,colidersAtual,disp);

//        printf("Conteudo (FIM DO RAMO): \n");
//            for(int i=0;i<nColiders;i++){
//                printf("%d -> %d\n",colidersAtual[i][0], colidersAtual[i][1]);
//            }
        //printf("<======================>\nbest: %d\n<======================>\n", best);
        return best;
    }
    int i;
    int k;
    for(i = 0; i<nPontos; i++) {
        if(visit[i] == 0) { //caso nao tenha sido visitado
            visit[i] = 1;
            disp[iterador] = i; //colocar o local no dispositivo (ATENCAO QUE 0=1)

//            printf("Conteudo: \n");
//            for(int i=0;i<nColiders;i++){
//                printf("%d -> %d\n",colidersAtual[i][0], colidersAtual[i][1]);
//            }
//            printf("\n");
//            printf("Visit: ");
//            for(int i=0;i<nPontos;i++){
//                printf("%d ",visit[i]);
//            }


            temp = intersectGlobal(colidersAtual, disp, locais, nColiders, iterador, ligacoes, nDispositivos);
            backtracking(locais, coliders, disp, nPontos, nColiders, nDispositivos, iterador+1, counter + temp, visit, colidersAtual, ligacoes);

            if(best == 0) {
                return best;
            }

            //ja foi utilizado:

            for(k=nColiders-1; k>=0; k--){ //se nao adicionar nada
                if(colidersAtual[k][0] == iterador+1 || colidersAtual[k][1] == iterador+1) {
                    colidersAtual[k][0] = -1;
                    colidersAtual[k][1] = -1;
                    //printf("\na removereeeee\n");
                }
            }

            visit[i] = 0;
            disp[iterador] = -1;
        }
    }
    return counter;
}

int intersectGlobal(int (*colidersAtual)[2], int *disp, Ponto *locais, int nColiders, int iterador, int (*ligacoes)[nDispositivos-1], int nDispositivos) {
//    start = clock();
    int i, j;
    int acum = 0;
    int ultimoIndice = 0;

    //printf("device: %d\n", iterador+1);
    for(i=0; i<nDispositivos-1; i++) { //percorremos as ligacoes a procura de dispositivos que estejam ja presentes
        if(ligacoes[iterador][i] != -1) {
            //printf("%d\t", ligacoes[iterador][i]);
            if(disp[ligacoes[iterador][i]-1] != -1) { //quer dizer que existe um colider: iterador+1 -----> ligacoes[iterador][i]
                for(j=0; j<nColiders; j++) { //percorremos o colidersAtual para podermos intersetar
                    //printf("como assim nao entra?\t%d\n", colidersAtual[j][0]);
                    if(colidersAtual[j][0] == -1) { //caso cheguemos ao fim dos coliders presentes
                        //inserir o colider no array a ser usado
                        //printf("bem...%d\n", acum);
                        ultimoIndice = j;
                        break;
                    } else {
//                        aux++;
//                        printf("passei aqui: %d\n", aux);
                        if((disp[iterador] != disp[colidersAtual[j][0]-1]) && (disp[iterador] != disp[colidersAtual[j][1]-1]) && (disp[ligacoes[iterador][i]-1] != disp[colidersAtual[j][0]-1]) && (disp[ligacoes[iterador][i]-1] != disp[colidersAtual[j][1]-1])) {
                            acum += intersect(locais[disp[iterador]], locais[disp[ligacoes[iterador][i]-1]], locais[disp[colidersAtual[j][0]-1]], locais[disp[colidersAtual[j][1]-1]]);
                        }
                    }
                }
                colidersAtual[ultimoIndice][0] = iterador+1;
                colidersAtual[ultimoIndice][1] = ligacoes[iterador][i];
                //quantos++;
            }
        }
    }
//    end = clock();
//    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
//    total+=cpu_time_used;
//    printf("%d\n\n", acum);
//    temp[0] = acum;
//    temp[1] = ultimoIndice;
//    temp[2] = quantos;
//    printf("quantos: %d\tacum: %d\n", quantos, acum);

    return acum;
}

void validar(int nColiders,Ponto (*locais),int (*colidersAtual)[2],int *disp){
    int i;
    FILE *f = fopen("data.out", "w");
    if (f == NULL)
    {
        printf("Erro ao abrir ficheiro!\n");
    }
    for (i=0;i<nColiders;i++){
        fprintf(f, "inicio: [%d %d] \t fim: [%d %d] \n", locais[disp[(colidersAtual[i][0]-1)]].x, locais[disp[(colidersAtual[i][0]-1)]].y, locais[disp[(colidersAtual[i][1]-1)]].x, locais[disp[(colidersAtual[i][1]-1)]].y);
    }


    fclose(f);
}

// Funcao que devolve 1 se os dois colliders se interceptarem
// Caso contrario devolve 0
int intersect(Ponto p1, Ponto t1, Ponto p2, Ponto t2) {  //recebe 4 pontos (duas linhas) e verifica intersecao

//    if((t1.x == t2.x && t1.y == t2.y) || (p1.x == p2.x && p1.y == p2.y)){
//        //printf("tamu juntos\n");
//        return 0;
//    }

    //orientacao entre os nos de forma a descobrir se esta a cada ponto a esquerda/direita da linha
    int o1 = orientation(p1, t1, p2);
    int o2 = orientation(p1, t1, t2);
    int o3 = orientation(p2, t2, p1);
    int o4 = orientation(p2, t2, t1);

    //caso um dos pontos fique num lado e o outro no lado oposto
    if (o1 != o2 && o3 != o4) {
//        if(o1 == 0 || o2 == 0 || o3 == 0 || o4 == 0) {
//            return 0;
//        }
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
