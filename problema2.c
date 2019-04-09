//
//  main.c
//  Problema2
//
//  Created by Francisco Monteiro on 02/04/2019.
//  Copyright © 2019 Francisco Monteiro. All rights reserved.
//
#include <stdio.h>

typedef struct Eventoo {
    int deadline;
    int duracao;
    int lucro;
}Evento;

// Headers
int profit(int nEventos,int maxDeadline,int tabela[nEventos+1][maxDeadline+1],Evento eventos[nEventos]);
void imprimir(int nEventos, int maxDeadline,int tabela[nEventos+1][maxDeadline+1]);
int max(int v1, int v2);
void swap(Evento *x,Evento *y);
void quicksort(Evento eventos[],int m,int nEventos);
int choose_pivot(int i,int j);


int main(int argc, const char * argv[]) {
    // Guardar numero de eventos
    int nEventos;
    int i,max;
    max=0;
    scanf("%d", &nEventos);
    Evento eventos[nEventos];
    for(i=0; i<nEventos; i++) {
        scanf("%d %d %d", &(eventos[i].deadline), &(eventos[i].duracao), &(eventos[i].lucro));
        if(eventos[i].deadline>max)
            max=eventos[i].deadline;
    }
    // Criar tabela para guardar os valores
    int tabela[nEventos+1][max+1];
    // Ordenar por deadline
    quicksort(eventos,0, nEventos);
    printf("%d\n",profit(nEventos,max,tabela,eventos));
    
    // Para ver se a Tabela
    //imprimir(nEventos,max,tabela);
    return 0;
}
// Função para teste
void imprimir(int nEventos, int maxDeadline,int tabela[nEventos+1][maxDeadline+1]){
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
int profit(int nEventos, int maxDeadline,int tabela[nEventos+1][maxDeadline+1],Evento eventos[nEventos]){
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

/*
 Créditos quicksort
 
 http://www.zentut.com/c-tutorial/c-quicksort-algorithm/
 */
void quicksort(Evento eventos[],int m,int nEventos)
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
