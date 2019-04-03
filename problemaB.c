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
int profit(int nEventos,int maxDeadline,int tabela[nEventos+1][maxDeadline+1]);

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
    int tabela[nEventos+1][max+1]; // O +1 é por causa das linhas só com 0's
    profit(nEventos,max,tabela);
    return 0;
}

int profit(int nEventos, int maxDeadline,int tabela[nEventos+1][maxDeadline+1]){
    int iteradorEvento,iteradorDeadline;
    // Inicializar a primeira coluna a 0
    for(iteradorEvento=0;iteradorEvento<nEventos+1;iteradorEvento++){
        tabela[iteradorEvento][0]=0;
    }
    // Inicializar a primeira linha a 0
    for(iteradorDeadline=0;iteradorDeadline<maxDeadline+1;iteradorDeadline++){
        tabela[0][iteradorDeadline]=0;
    }
    for(iteradorEvento=1;iteradorEvento<nEventos+1;iteradorEvento++){
        for(iteradorDeadline=1;iteradorDeadline<maxDeadline+1;iteradorDeadline++){
            //Ifs e elses do mal
                
        }
    }
    // Vai devolver o último elemento que vai conter o resultado certo
    return tabela[nEventos+1][maxDeadline+1];
}
