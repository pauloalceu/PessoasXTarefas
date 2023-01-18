#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ListaPessoas.h"
#include "ListaTarefas.h"

DPessoas *lp = NULL;
int cTarefas = 0;

int main(){
  lp = inicializaPessoas();
  menu();
  return 0;
}

void cabecalho(){
  system("cls");
  printf("======================================================================\n");
  printf("             Trabalho e algoritmos e estruturas de dados\n");
  printf("  Alunos:\n");
  printf("     Paulo Alceu d Almeida Rezende  \n");
  printf("======================================================================\n");
}

void menuIncluirPessoa(){
  char id[5] =""; char nome[150]="";
  cabecalho();
  while(strlen(id) != 5){
    printf("Insira o Identificador:");
    scanf(" %[^\n]", &id);

    if (strlen(id) != 5){
      printf("O formato da identificacao esta incorreto, o id deve ter 5 digitos. \n");
      getch();
      cabecalho();
    }
  }

  printf("Insira o Nome:");
  scanf(" %[^\n]", nome);

  incluirPessoa(lp, id, nome);
  printf("\n Pessoa incluida com sucesso!");
  getch();
}

void menuRemoverPessoa(){
  char id[5] ="";
  cabecalho();
  while(strlen(id) != 5){
    printf("Insira o Identificador:");
    fflush(stdin);
    scanf(" %[^\n]", &id);

    if (strlen(id) != 5){
      printf("O formato da identificacao esta incorreto, o id deve ter 5 digitos. \n");
      getch();
      cabecalho();
    }
  }
    removerPessoa(lp, id);
    getch();
}

void menuIncluirTarefa(){
  DTarefas *dt = NULL;
  LPessoas *p = NULL;
  char d[300] = "";
  cabecalho();
  printf("Insira a descricao da tarefa:\n");
  fflush(stdin);
  //scanf("%[^n]", &d);
  gets(d);

  p = bPessoaPorTarefas(lp);
  if(p){
    incluirTarefa(p->tarefas, d, &cTarefas);
    printf("Tarefa cadastrada com sucesso para a pessoa ID = %.5s.\n", p->id, p->tarefas->tamanho);
    getch();
  }else{
    printf("Nao existem pessoas cadastradas.\n");
    getch();
  }
}

void menuRemoverTarefa(){
  char id[5]= "";
  LPessoas *p = NULL;
  cabecalho();
  while(strlen(id) != 5){
    printf("Insira o Identificador:");
    fflush(stdin);
    scanf(" %s", &id);

    if (strlen(id) != 5){
      printf("O formato da identificacao esta incorreto, o id deve ter 5 digitos. \n");
      getch();
      cabecalho();
    }
  }

  p = buscaPessoa(lp, id);
  if (p){
    removerTarefa(p->tarefas);
  }else{
    printf("Pessoa nao encontrada!");
    getch();
  }
}

void menuImprimirTarefasPessoas(){
   char id[5];
   cabecalho();
   while(strlen(id) != 5){
    printf("Insira o identificador da pessoa: ");
    fflush(stdin);
    scanf(" %s", &id);

    if (strlen(id) != 5){
      printf("O formato da identificacao esta incorreto, o id deve ter 5 digitos. \n");
      getch();
      cabecalho();
    }
  }
  imprimirNumTarefasPessoa(lp, id);
}

void menu (void){
  int opc1=9, opc2=9;

  while (opc1!=0){
    opc2=0;
    cabecalho();
    printf(" [1] Pessoas \n");
    printf(" [2] Tarefas \n");
    printf(" [3] Relatorios \n");
    printf(" [0] Sair \n");
    printf(" Digite sua Opcao: ");
    fflush(stdin);
    scanf (" %d", &opc1);

    switch (opc1){
      case 1:
        opc2 = 9;
        while (opc2!=0){
          cabecalho();
          printf(" [1] Inclusao de pessoas\n");
          printf(" [2] Exclusao de pessoas\n");
          printf(" [0] Voltar para Menu \n");
          printf(" Digite sua opcao:");
          fflush(stdin);
          scanf (" %d", &opc2);

          switch(opc2){
            case 1: menuIncluirPessoa();break;
            case 2: menuRemoverPessoa();break;
          }
        }
        break;

      case 2:
        opc2 = 9;
        while (opc2!=0){
          cabecalho();
          printf(" [1] Inclusao de Tarefas\n");
          printf(" [2] Exclusao de Tarefas\n");
          printf(" [0] Voltar para Menu \n");
          printf(" Digite sua opcao:");
          fflush(stdin);
          scanf (" %d", &opc2);

          switch(opc2){
            case 1: menuIncluirTarefa();break;
            case 2: menuRemoverTarefa();break;
          }
        }
        break;

        case 3:
          opc2 = 9;
          while (opc2!=0){
            cabecalho();
            printf(" [1] Todas as pessoas cadastradas \n");
            printf(" [2] Numero de pessoas cadastradas \n");
            printf(" [3] Tarefas pendentes para uma pessoa selecionada. \n");
            printf(" [4] Pessoas x Tarefas \n");
            printf(" [5] Pessoas com menor numero de tarefas \n");
            printf(" [6] Pessoas com maior numero de tarefas \n");
            printf(" [0] Voltar para Menu \n");
            printf(" Digite sua opcao:");
            fflush(stdin);
            scanf (" %d", &opc2);

            switch(opc2){
              case 1: imprimirPessoas(lp);break;
              case 2: imprimirNumPessoas(lp);break;
              case 3: menuImprimirTarefasPessoas();break;
              case 4: imprimirTudo(lp);break;
              case 5: imprimirPessoasMenosTarefas(lp);break;
              case 6: imprimirPessoasMaisTarefas(lp);break;
            }
        }
        break;
    }
  }
}
