#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EstruturaLista.h"

/*
PROJETO FINAL (MASSA DE DADOS) - INF006: ESTRUTURA DE DADOS E ALGORITMOS P
ALUNOS: ISAAC CONCEICAÇÃO (2019116053); JULIANA RIBEIRO (); LUIZ (); REINAN (); 
*/


int extrairDados(FILE* arquivo, Celula* inicio, int* tamanhoArquivo);

void menu(){
  //imprime menu
}


int main(void) {
  Celula* inicio=NULL;
  FILE* arquivo;
  int tamanhoArquivo=-1;
  int tamanhoLista=0;
  int retorno;
  //aloca inicio da lista
  inicio=(Celula*)malloc(sizeof(Celula));

  if(inicio==NULL){
    show_log("FALHA_ALOCAÇÃO");
    return FALHA_ALOCACAO;
  }
  inicio->prox=NULL;
  //acessa o arquivo
  arquivo=fopen("maDados.txt", "r");
  
  if(arquivo==NULL){
    return FALHA_ABRIR_ARQUIVO;
  }

  retorno=extrairDados(arquivo,inicio,&tamanhoArquivo);
  printf("O arquivo tem tamanho=%d linhas\n",tamanhoArquivo);
  fclose(arquivo);
  //retorno=extrairDados(&inicio, &tamanhoArquivo);
  //printf("Tamanho do arquivo = %d linhas\n",tamanhoArquivo);
  imprimeLista(inicio);
  destruirLista(inicio);
  free(inicio);
  return retorno;
}

//extrai os dados da maDados.txt, converte eles e gera uma lista encadeada simples
int extrairDados(FILE* arquivo, Celula* inicio, int* tamanhoArquivo){
  Celula *no;
  char linha[TAM];
  int retorno=SUCESSO;
  //percorre o arquivo 
  while((!feof(arquivo))&&(arquivo!=NULL)){
    //lê uma linha do arquivo
    retorno=extrairLinha(linha, arquivo);
    //verifica se leu com sucesso
    if(retorno==SUCESSO){
      //conta o tamanho do arquivo em linhas
      *tamanhoArquivo+=1;
      //aloca um no
      no=(Celula*)malloc(sizeof(Celula));
      //checa se alocou
      if (no!=NULL){
          //converte a linha lida no formato struct e atribui ao no alocado
          retorno=converteLinha(no,linha);
          if(retorno==SUCESSO){
            //insere o no na lista
            retorno=inserirPorNome(inicio, no);
      }else{
          retorno=FALHA_ALOCACAO;
        }
      }
    }
  }
  return 0;
}