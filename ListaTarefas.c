#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaPessoas.h"
#include "ListaTarefas.h"

DTarefas* inicializaTarefas()
{
  DTarefas *desc = (DTarefas*) malloc(sizeof(DTarefas));
  desc->primeiro = NULL;
  desc->tamanho = 0;
  desc->ultimo = NULL;
  return desc;
}

DTarefas* incluirTarefa(DTarefas *tarefas, char d[300], int *ct){
  LTarefas *t = (LTarefas*) malloc(sizeof(LTarefas));

  t->anterior = NULL;
  t->id = ++*ct;
  strncpy(t->descricao, d, sizeof(t->descricao));

  if (tarefas->primeiro != NULL){
    tarefas->primeiro->anterior = t;
    t->proximo = tarefas->primeiro;
  }

  if (tarefas->ultimo == NULL)
    tarefas->ultimo = t;

  tarefas->primeiro = t;
  tarefas->tamanho++;

  return tarefas;

}

DTarefas* removerTarefa(DTarefas *tarefas){
  LTarefas *t = NULL;

  if (tarefas->ultimo){
    t = tarefas->ultimo;
    tarefas->ultimo = t->anterior;
    if (t->anterior){
      t->anterior->proximo = NULL;
    }
    tarefas->tamanho--;
    free(t);
  }else{
    printf("Essa pessoa nao possui tarefas em sua fila.\n");
    getch();
  }

  return tarefas;
}
