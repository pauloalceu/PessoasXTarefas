#ifndef LISTAPESSOAS_H_INCLUDED
#define LISTAPESSOAS_H_INCLUDED

struct listaPessoas{
    struct listaPessoas *anterior;
    char id[5];
    char nome[150];
    struct listaPessoas *proximo;
    struct descrTarefas *tarefas;
};

struct descrPessoas{
  struct listaPessoas *primeiro;
  int tamanho;
  struct listaPessoas *ultimo;
};

typedef struct descrPessoas DPessoas;
typedef struct listaPessoas LPessoas;

/* */
DPessoas* inicializaPessoas();

int comparaIDs(char id1[5], char id2[5]);
/* */
LPessoas* buscaPessoa(DPessoas *pessoas, char id[5]);
/* */
DPessoas* incluirPessoa(DPessoas *pessoas, char id[5], char nome[150]);
/* */
DPessoas* removerPessoa(DPessoas *pessoas, char id[5]);
/* */
LPessoas* bPessoaPorTarefas(DPessoas *pessoas);
/* */
DPessoas* bIncluirTarefa(DPessoas *pessoas, char d[300], int *cTarefas);

void imprimirPessoas(DPessoas *pessoas);

void imprimirNumPessoas(DPessoas *pessoas);

#endif // LISTAPESSOAS_H_INCLUDED
