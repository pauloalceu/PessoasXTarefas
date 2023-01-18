#include <stdio.h>
#include <stdlib.h>
#include "ListaPessoas.h"
#include "ListaTarefas.h"

DPessoas* inicializaPessoas(){
  DPessoas *desc = (DPessoas*) malloc(sizeof(DPessoas));
  desc->primeiro = NULL;
  desc->tamanho = 0;
  desc->ultimo = NULL;
  return desc;
}

int comparaIDs(char id1[5], char id2[5]){
  int i = 0;
  int result = 0;
  for(i=0;i<5;i++){
    if(id1[i] != id2[i]){
      result++;
    }
  }
  return result;
}

LPessoas* buscaPessoa(DPessoas *pessoas, char id[5]){
  LPessoas *p = NULL;
  if (pessoas->primeiro)
    p = pessoas->primeiro;
  while( p && comparaIDs(p->id, id) != 0){
    if (p->proximo){
      p = p->proximo;
    }else{
      p = NULL;
    }
  }
  return p;
}

DPessoas* incluirPessoa(DPessoas *pessoas, char id[5], char nome[150]){

  LPessoas *p = (LPessoas*) malloc(sizeof(LPessoas));
  p->anterior = NULL;
  strncpy(p->id, id, sizeof(p->id));
  strncpy(p->nome, nome, 150);
  p->proximo = NULL;
  p->tarefas = inicializaTarefas();

  if (pessoas->primeiro != NULL){
    pessoas->primeiro->anterior = p;
    p->proximo = pessoas->primeiro;
  };

  if (pessoas->ultimo == NULL){
    pessoas->ultimo = p;
  }

  pessoas->primeiro = p;
  pessoas->tamanho++;

  return pessoas;
}


DPessoas* removerPessoa(DPessoas *pessoas, char id[5]){
  LPessoas *p = NULL;
  if (pessoas->primeiro) {
    p = pessoas->primeiro;
  };

  while(p && (comparaIDs(p->id, id) != 0) ){
    if(p->proximo){
      p = p->proximo;
    }else{
      p = NULL;
    }
  }

  if (p != NULL && p->tarefas->tamanho == 0){
    if (p->anterior != NULL)
      p->anterior->proximo = p->proximo;
    if (p->proximo != NULL)
      p->proximo->anterior = p->anterior;
    if (pessoas->primeiro == p)
      pessoas->primeiro = p->proximo;
    if (pessoas-> ultimo == p)
      pessoas->ultimo = p->anterior;
      pessoas->tamanho--; //paulo

    free(p);
    printf("Pessoa excluida com sucesso.");
  }else{
    printf(" Não foi possivel excluir a pessoa de id = %.5s. \n Pessoa nao existe ou possui tarefas pendentes.", id);
  };

  return pessoas;
}

LPessoas* bPessoaPorTarefas(DPessoas *pessoas){
  LPessoas *p = NULL;
  int nTarefas = 0;
  char id[5] = "";
  if (pessoas->primeiro){
    p = pessoas->primeiro;
    nTarefas = p->tarefas->tamanho;
    strncpy(id, p->id, sizeof(id));
  }

  while(p){
    if (nTarefas > p->tarefas->tamanho){
      nTarefas = p->tarefas->tamanho;
      strncpy(id, p->id, sizeof(id));
    }
    if (p->proximo){
      p = p->proximo;
    }else{
      p = NULL;
    };
  }
  return buscaPessoa(pessoas, id);
}

DPessoas* bIncluirTarefa(DPessoas *pessoas, char d[300], int *cTarefas){
//  LPessoas *p = bPessoaPorTarefas(pessoas);
//  p->tarefas = incluirTarefa(p->tarefas, d, cTarefas);
//  return pessoas;
}

void imprimirPessoas(DPessoas *pessoas){
  LPessoas *p = pessoas->primeiro;
  cabecalho();
  printf("               Relatorio de Pessoas cadastradas \n\n\n");
  while((p != NULL)){
    printf(" ID = %.5s        ", &p->id);

    printf(" NOME = %s \n", &p->nome );
    printf("-----\n");
    p = p->proximo;
  }
  printf(" -> Existem %d Pessoa(s) incluida(s) no sistema atualmente.\n", pessoas->tamanho);
  getch();
}

void imprimirNumPessoas(DPessoas *pessoas){
  cabecalho();
  printf("               Relatorio de Pessoas  \n\n\n");
  printf(" -> Existem %d Pessoa(s) incluida(s) no sistema atualmente.\n", pessoas->tamanho);
  getch();
}

void imprimirNumTarefasPessoa(DPessoas *pessoas, char id[5]){
  cabecalho();
  int seq = 0;
  LPessoas *p = NULL;
  DTarefas *dt = NULL;
  LTarefas *t = NULL;
  printf("               Relatorio de Tarefas por pessoa  \n\n\n");
  p = buscaPessoa(pessoas, id);
  if(p){
    printf("- Pessoa Selecionada -\n");
    printf(" ID = %.5s        ", &p->id);
    printf(" NOME = %s \n\n", &p->nome );
    printf("- Tarefas -\n");
    dt = p->tarefas;
    if(dt->tamanho >0){
      t = dt->ultimo;
      while(t){
        printf("Ordem %d -> ID = %d     Descricao = %s\n", ++seq, t->id, t->descricao);
        if(t->anterior){
          t = t->anterior;
        }else{
          t = NULL;
        }
      }
      printf("---\n -> Total de tarefas : %d", dt->tamanho);
    }else{
      printf("Nao existem Tarefas cadastradas para esta pessoa.");
    }
  }else{
    printf("Pessoa nao encontrada!");
  }
  getch();
}

void imprimirTudo(DPessoas *pessoas){
  cabecalho();
  printf("               Relatorio de Geral do sistema \n\n\n");
  int seq = 0;
  LPessoas *p = NULL;
  LTarefas *t = NULL;
  if(pessoas->tamanho > 0){
    p = pessoas->primeiro;
  }
  if(p){
    while(p){

      printf("- Pessoa Selecionada -\n");
      printf(" ID = %.5s        ", &p->id);
      printf(" NOME = %s \n\n", &p->nome );
      printf("- Tarefas -\n");
      if(p->tarefas->tamanho > 0){
        t = p->tarefas->ultimo;
        while(t){
          printf("Ordem %d -> ID = %d     Descricao = %s\n", ++seq, t->id, t->descricao);
          if(t->anterior){
            t = t->anterior;
          }else{
            t = NULL;
          }
        }
      };
      printf("---\n -> Total de tarefas : %d\n \n", p->tarefas->tamanho);

     if(p->proximo){
       p = p->proximo;
       seq = 0;
       getch();
       cabecalho();
       printf("               Relatorio de Geral do sistema \n\n\n");
     }else{
       p = NULL;
     }
    }
    printf(" -> Existem %d Pessoa(s) incluida(s) no sistema atualmente.\n", pessoas->tamanho);
  }else{
    printf("Nao existem pessoas cadastradas no sistema.");
  }

  getch();
}

void imprimirPessoasMenosTarefas(DPessoas *pessoas){
  int minTarefas = 0;
  LPessoas *p = NULL;
  cabecalho();
  printf("               Relatorio de pessoas menos atarefadas \n\n\n");
  if (pessoas->primeiro){
    p = pessoas->primeiro;
    minTarefas = p->tarefas->tamanho;

    while(p){
      if(p->tarefas->tamanho < minTarefas){
        minTarefas = p->tarefas->tamanho;
      }
      if(p->proximo){
        p = p->proximo;
      }else{
        p = NULL;
      }
    }

    p = pessoas->primeiro;
    while(p){
      if(p->tarefas->tamanho == minTarefas){
        printf(" ID = %.5s        ", &p->id);
        printf(" NOME = %s \n\n", &p->nome );
      }
      if(p->proximo){
        p = p->proximo;
      }else{
        p = NULL;
      }
    }
    printf("\n ->Numero de Tarefas = %d", minTarefas);
  }else{
    printf("Nao existem pessoas cadastradas no sistema.");
  }
  getch();
}

void imprimirPessoasMaisTarefas(DPessoas *pessoas){
int maxTarefas = 0;
  LPessoas *p = NULL;
  cabecalho();
  printf("               Relatorio de pessoas menos atarefadas \n\n\n");
  if (pessoas->primeiro){
    p = pessoas->primeiro;
    maxTarefas = p->tarefas->tamanho;

    while(p){
      if(p->tarefas->tamanho > maxTarefas){
        maxTarefas = p->tarefas->tamanho;
      }
      if(p->proximo){
        p = p->proximo;
      }else{
        p = NULL;
      }
    }

    p = pessoas->primeiro;
    while(p){
      if(p->tarefas->tamanho == maxTarefas){
        printf(" ID = %.5s        ", &p->id);
        printf(" NOME = %s \n\n", &p->nome );
      }
      if(p->proximo){
        p = p->proximo;
      }else{
        p = NULL;
      }
    }
    printf("\n ->Numero de Tarefas = %d", maxTarefas);
  }else{
    printf("Nao existem pessoas cadastradas no sistema.");
  }
  getch();
}
