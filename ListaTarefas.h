#ifndef LISTATAREFAS_H_INCLUDED
#define LISTATAREFAS_H_INCLUDED

struct listaTarefas{
  struct listaTarefas *anterior;
  int id;
  char descricao[300];
  struct listaTarefas *proximo;
};

struct descrTarefas{
  struct listaTarefas *primeiro;
  struct listaTarefas *ultimo;
  int tamanho;
};

typedef struct listaTarefas LTarefas;
typedef struct descrTarefas DTarefas;

DTarefas* inicializaTarefas();
DTarefas* incluirTarefa(DTarefas *tarefas, char descricao[300], int *ct);
DTarefas* removerTarefa(DTarefas *tarefas);

#endif // LISTATAREFAS_H_INCLUDED
