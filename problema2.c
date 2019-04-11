//
//  main.c
//  Problema2
//
//  Created by Francisco Monteiro on 02/04/2019.
//  Copyright © 2019 Francisco Monteiro. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>

typedef struct Eventoo {
    int deadline;
    int duracao;
    int lucro;
}Evento;

// Headers
int profit(int nEventos,int maxDeadline,int **tabela,Evento * eventos);
void imprimir(int nEventos, int maxDeadline,int **tabela);
int max(int v1, int v2);
void swap(Evento *x,Evento *y);
void quicksort(Evento *eventos,int m,int nEventos);
int choose_pivot(int i,int j);
void verificaSol(int **tabela,int nEventos, int maxDeadline,Evento *eventos);
int checklinha(int valor,int **tabela,int maxDeadline,int nEventos);
void imprimeSol(Evento *eventos,int indice,int time,int flag);
/*
6
9 1 4
7 3 2
7 4 5
4 1 3
4 1 1
4 3 4
*/

int main(int argc, const char * argv[]) {
    // Guardar numero de eventos
    int nEventos;
    int i,max;
    max=0;
    scanf("%d", &nEventos);
    Evento *eventos;
    eventos=(Evento*)malloc(sizeof(Evento)*nEventos);
    for(i=0; i<nEventos; i++) {
        scanf("%d %d %d", &(eventos[i].deadline), &(eventos[i].duracao), &(eventos[i].lucro));
    }
    quicksort(eventos,0, nEventos-1);
    printf("Conteudo ordenado dos eventos\n");
    for(i=0; i<nEventos; i++) {
        printf("%d %d %d\n", eventos[i].deadline,eventos[i].duracao,eventos[i].lucro);
    }
    max=eventos[nEventos-1].deadline;
    int **tabela;
    tabela= (int**)malloc(sizeof(int*)*(nEventos+1));
    for (i=0;i<nEventos+1;i++){
        tabela[i]=(int*)malloc(sizeof(int)*(max+1));
    }
    // Ordenar por deadline
    
    printf("%d\n",profit(nEventos,max,tabela,eventos));
    
    verificaSol(tabela,nEventos,max,eventos);
    // Para ver a Tabela
    imprimir(nEventos,max,tabela);
    free(eventos);
    for (i=0;i<nEventos+1;i++){
        free(tabela[i]);
    }
    free(tabela);
    return 0;
}
// Função para debug
void imprimir(int nEventos, int maxDeadline,int **tabela){
    printf("Conteúdo da tabela\n");
    int i,j;
    for(i=0;i<nEventos+1;i++){
        for(j=0;j<maxDeadline+1;j++){
            printf("%d    ",tabela[i][j]);
        }
        printf("\n");
    }
    printf("------############------\n");
}
int profit(int nEventos, int maxDeadline,int **tabela,Evento *eventos){
    int iE,iD;
    // Inicializar a primeira coluna a 0
    for(iE=0;iE<nEventos+1;iE++){
        tabela[iE][0]=0;
    }
    // Inicializar a primeira linha a 0
    for(iD=0;iD<maxDeadline+1;iD++){
        tabela[0][iD]=0;
    }
    
    for(iE=1;iE<nEventos+1;iE++){
        for(iD=1;iD<maxDeadline+1;iD++){
            if(eventos[iE-1].deadline < iD) {
                tabela[iE][iD]=tabela[iE][iD-1];
            }
            else if(eventos[iE-1].duracao>iD ){
                tabela[iE][iD]=tabela[iE-1][iD];
            }
            else{
                tabela[iE][iD]=max(tabela[iE-1][iD],tabela[iE-1][iD-eventos[iE-1].duracao]+eventos[iE-1].lucro);
            }
                
        }
    }
    // Vai devolver o último elemento que vai conter o resultado certo
    return tabela[nEventos][maxDeadline];
}
void verificaSol(int **tabela,int nEventos, int maxDeadline,Evento *eventos){
    int iE;
    int aux;
    int colAux,colAux2=0;
    int flag=0;
    // Último valor da tabela
    aux = tabela[nEventos][maxDeadline];
    // Linhas
    for(iE=nEventos;iE>=0;iE--){
        // Colunas
            colAux=checklinha(aux, tabela,maxDeadline,iE);
            if(colAux==-1){ // Se não encontrou o valor na linha, imprime
                imprimeSol(eventos, iE+1, colAux2,flag);
                flag=1;
                aux=aux-eventos[iE].lucro;//aqui
            }
            else{ // Se encontrou
                colAux2=colAux;
            
            }
        
        
    }
}

int checklinha(int valor,int **tabela,int maxDeadline,int nEventos){
    int col;
    for(col=0;col<maxDeadline;col++){
        if(valor==tabela[nEventos][col])
            return col;
    }
    return -1;
}

void imprimeSol(Evento *eventos,int indice,int time,int flag){
    // Tenho de substituir depois para imprimir tudo na mesma linha
    // Verificar indices!
    if (flag==0){ // Veio start time
        printf("Indice do evento: %d\n",indice);
        printf("Starting time: %d\n",time);
        printf("Ending time: %d\n",time+eventos[indice-1].duracao);
        printf("Deadline: %d\n",eventos[indice-1].deadline);
        printf("Profit: %d\n",eventos[indice-1].lucro);
    }
    else{
        printf("Indice do evento: %d\n",indice);
        printf("Starting time: %d\n",time-eventos[indice-1].duracao);
        printf("Ending time: %d\n",time);
        printf("Deadline: %d\n",eventos[indice-1].deadline);
        printf("Profit: %d\n",eventos[indice-1].lucro);
    }
}

/*
 Créditos quicksort
 
 http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
 */
void quicksort(Evento *eventos,int m,int nEventos)
{
    int key,i,j,k;
    if( m < nEventos)
    {
        k = choose_pivot(m,nEventos);
        swap(&eventos[m],&eventos[k]);
        key = eventos[m].deadline;
        i = m+1;
        j = nEventos;
        while(i <= j)
        {
            while((i <= nEventos) && (eventos[i].deadline <= key))
                i++;
            while((j >= m) && (eventos[j].deadline > key))
                j--;
            if( i < j)
                swap(&eventos[i],&eventos[j]);
        }
        /* swap two elements */
        swap(&eventos[m],&eventos[j]);
        
        /* recursively sort the lesser list */
        quicksort(eventos,m,j-1);
        quicksort(eventos,j+1,nEventos);
    }
}

void swap(Evento *x,Evento *y)
{
    Evento temp;
    temp = *x;
    *x = *y;
    *y = temp;
}

int choose_pivot(int i,int j )
{
    return((i+j) /2);
}

int max(int v1, int v2){
    if(v1>v2)
        return v1;
    else
        return v2;
}
