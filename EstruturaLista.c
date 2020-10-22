#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "EstruturaLista.h"

/*
::::PENDÊNCIAS ENTREGA 2 (19/10):::::
-AJUSTAR AS FUNÇÕES DE INSERÇÃO ORDENADA   [X]
-TRATAR DUPLICIDADES NA INSERÇÃO           [ ]
-DEFINIR UMA PARA INSERIR ORDENADO         [X] 
  = inserirPorNome()
-REMOVER O MERGE E AS ORDENAÇÕES DO CODIGO [X]

PENDÊCNIAS ENTREGA 3 (26/10):
-DEFINIR ESTRUTURA AS REGIÕES               [ ]
-VERIFICAR NO TEAMS A QTD DE CIDADES/REGIÃO [X]
  DIVISOR/QTDCIDADES DO GerarMassaDeDados.c
-IMPLEMENTAR MODULO DE INSERÇÃO NA REGIÃO   [ ]
-IMPLEMENTAR MODULO DE REMOÇÃO NA REGIÃO    [ ]
-IMPLEMENTAR MODULO DE CALCULAR MEDIA DE PESO DA REGIAO [ ]
-IMPLEMENTAR MODULO DE CALCULAR MEDIA DE GC [ ]
*/

int ligado = SHOW_LOG;
void show_log(char *str){
    if (ligado)
        printf("##%s##\n", str);
}

//insere um novo registro no inicio da lista
int inserirNoInicio (Celula *inicio,  Celula *no){
  show_log("inserirNoInicio()");
  int retorno=FALHA_INSERIR;
	//testar se a lista estah vazia
	if (inicio->prox==NULL){
		//inserir no inicio
		inicio->prox=no;
		no->prox=NULL;
		
		retorno=SUCESSO;
	}else{
    //inserir no inicio
    no->prox=inicio;
    inicio=no;
    retorno=SUCESSO;
  }
  return retorno;
}

int inserirNoFim (Celula *inicio, Celula *no){
  show_log("inserirNoFim()");
	int retorno=FALHA_INSERIR;
	//testar se a lista estah vazia
	if (inicio->prox==NULL){
		inserirNoInicio(inicio,no);
		retorno=SUCESSO;
	}else{
		Celula* busca=inicio->prox;
		//buscar o fim da lista
		while(busca->prox!=NULL){
			busca=busca->prox;
		}
		//inserir
		busca->prox=no;
		no->prox=NULL;
		
		retorno=SUCESSO;
	}
	return retorno;
}

//insere ordenado por nome, caso nao exista no igual
int inserirPorNome (Celula *inicio,  Celula *no){
  show_log("inserirPorNome()");
	//insere ordenado por nome
  int retorno=FALHA_INSERIR;
	//testar se a lista esta vazia
	if (inicio->prox==NULL){
    show_log("LISTA_VAZIA");
		inserirNoInicio(inicio,no);		
		retorno=SUCESSO;
	}else{//não esta vazia
    int comp=1;
    Celula* busca=inicio->prox;
    Celula* anterior=NULL;

    //busca ate o fim ou ate achar um nome igual ou menor
    while((busca!=NULL)&&(comp=1)){
      comp=strcmp(no->nome,busca->nome);
      anterior=busca;
      busca=busca->prox;
    }
    //verificar se ja existe no igual na lista
    retorno=existeNoIgual(busca,no);
    if(retorno==SUCESSO){//ja existe o no na lista
      retorno=INSERCAO_DUPLICADA;
    }else{//não existe no igual, insere
      anterior->prox=no;
      no->prox=busca;
      retorno=SUCESSO;
      show_log("Inserido com sucesso!");
    }
  }
  return retorno;
}

int inserirPorTamanho (Celula *inicio,  Celula *no){
  show_log("inserirPorTamanho()");
	//insere ordenado por tamanho
  int retorno=FALHA_INSERIR;
	//testar se a lista estah vazia
	if (inicio->prox==NULL){
		inserirNoInicio(inicio,no);		
		retorno=SUCESSO;
	}else{
    Celula* busca=inicio->prox;
    Celula* anterior=inicio;
    while((busca!=NULL)&&(no->tamanho>busca->tamanho)){
      anterior=busca;
      busca=busca->prox;
    }
    anterior->prox=no;
    no->prox=busca;
    retorno=SUCESSO;
  }
  return retorno;
}

int inserirPorPeso (Celula *inicio,  Celula *no){
	show_log("inserirPorPeso()");
   int retorno=FALHA_INSERIR;
	//testar se a lista estah vazia
	if (inicio->prox==NULL){
		inserirNoInicio(inicio,no);		
		retorno=SUCESSO;
	}else{
    Celula* busca=inicio->prox;
    Celula* anterior=inicio;
    while((busca!=NULL)&&(no->peso>busca->peso)){
      anterior=busca;
      busca=busca->prox;
    }
    anterior->prox=no;
    no->prox=busca;
    retorno=SUCESSO;
  }
  return retorno;
}

int inserirPorGC (Celula *inicio,  Celula *no){
	show_log("inserirPorGC()");
   int retorno=FALHA_INSERIR;
	//testar se a lista estah vazia
	if (inicio->prox==NULL){
		inserirNoInicio(inicio,no);		
		retorno=SUCESSO;
	}else{
    Celula* busca=inicio->prox;
    Celula* anterior=inicio;
    while((busca!=NULL)&&(no->gc>busca->gc)){
      anterior=busca;
      busca=busca->prox;
    }
    anterior->prox=no;
    no->prox=busca;
    retorno=SUCESSO;
  }
  return retorno;
}

int gerarSubstring(char str[], char linha[], int posicao){
	show_log("gerarSubstring()");
  int i;

	for(i = 0; linha[posicao] != ';' && linha[posicao] != '\n'; i++, posicao++) { 
		str[i] = linha[posicao];
	}

	if(posicao == 0) {
		return LISTA_VAZIA;
	}

	str[i++] = '\0';
	posicao++;

	return posicao;
}

int converteLinha(Celula *no, char linha[]){
	show_log("converteLinha()");
  int i;
	int j = 0;

	char nome[TAM];
	char tamanho[TAM];
	char peso[TAM];
	char gc[TAM];

	// Encontra nome do LP
	j = gerarSubstring(nome, linha, j);
	
	if(j == LISTA_VAZIA)
		return LISTA_VAZIA;

	// Encontra o tamanho
	j = gerarSubstring(tamanho, linha, j);
	
	// // Encontra o Peso
	j = gerarSubstring(peso, linha, j);
	
	// // Encontra o GC
	j = gerarSubstring(gc, linha, j);
	
	// Armazena a string na struct
	strcpy(no->nome, nome);
	// Converte para Float
	no->tamanho = atof(tamanho);
	// Converte para Int
	no->peso = atoi(peso);
	no->gc = atoi(gc);
  no->prox=NULL;

	// Impressoes
	// printf("nome: %s \n", inicio->nome);
	// printf("Tamanho: %f \n", inicio->tamanho);
	// printf("Peso: %d \n", inicio->peso);
	// printf("GC: %d \n", inicio->gc);

	return SUCESSO;
}

int extrairLinha(char* linha, FILE* arquivo){
  show_log("extrairLinha()");
  int retorno=SUCESSO;

  //testa se arquivo é nulo
      if(arquivo==NULL){
      show_log("ERRO_FALHA_ABRIR_ARQUIVO");
        retorno=FALHA_ABRIR_ARQUIVO;
      //testa se o arquivo esta vazio
      }else if (feof(arquivo)){
          show_log("ERRO_FIM_DO_ARQUIVO");
          retorno=FIM_DO_ARQUIVO;
      }else{
      //sucesso
      fgets(linha,TAM,arquivo);
    }
      return retorno;
}

//verifica se ja existe um no igual na lista
int existeNoIgual(Celula* inicio, Celula* no){
  show_log("existeNoIgual()");
  int retorno=NAO_ENCONTRADO;
  Celula* busca=inicio;
  int comp=-1;
  //busca enquanto não acabou ou enquanto o nome for menor
  while((busca!=NULL)&&(comp<0)){
    comp=strcmp(busca->nome,no->nome);
    //testa se a busca ja achou um no igual ou se ja passou daquele nome
    if(comp==1||retorno==SUCESSO){
      break;
    //testa se achou nome igual
    }else if (comp==0){//achou nome igual! 
      //busca até acabar ou enquanto o nome for igual
      while(busca!=NULL && comp==0){
        comp=strcmp(busca->nome,no->nome);
        //testa se a busca atual é igual ao no
        if((comp==0)&&(no->tamanho==busca->tamanho)&&(no->peso==busca->peso)&&(no->gc==busca->gc)){
          //encontrei no igual!
          retorno=SUCESSO;
          break;
        }
        busca=busca->prox;
      }
    }
    busca=busca->prox;
  }
  return retorno;
}

int buscarPorNome(Celula* inicio, char* nome, Celula* resultado){
	show_log("buscarPorNome()");
  int retorno=SUCESSO;
	Celula* busca=inicio->prox;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
    resultado=NULL;
  }else{
    //busca enquanto lista não acaba ou acha o 1º nome correspondente
    while((busca!=NULL)&&(strcmp(nome,busca->nome)!=0)){
      busca=busca->prox;
    }
    resultado=busca;
    //verifica se a busca reotrnou nulo
    if (resultado==NULL){
      retorno = NAO_ENCONTRADO;
    }
  }
	return retorno;
}

int buscarPorTamanho(Celula* inicio, float tamanho, Celula* resultado){
	show_log("buscarPorTamanho()");
  int retorno=SUCESSO;
	Celula* busca=inicio->prox;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
    resultado=NULL;
  }else{
    //busca enquanto lista não acaba ou acha o 1º tamanho correspondente
    while((busca!=NULL)&&(busca->tamanho!=tamanho)){
      busca=busca->prox;
    }
    resultado=busca;
    //verifica se a busca reotrnou nulo
    if (busca==NULL){
      retorno = NAO_ENCONTRADO;
    }
  }
	return retorno;
}

int buscarPorPeso(Celula* inicio, int peso, Celula* resultado){
	show_log("buscarPorPeso()");
  int retorno=SUCESSO;
	Celula* busca=inicio->prox;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
    resultado=NULL;
  }else{
    //busca enquanto lista não acaba ou acha o 1º peso correspondente
    while((busca!=NULL)&&(busca->peso!=peso)){
      busca=busca->prox;
    }
    resultado=busca;
    //verifica se a busca reotrnou nulo
    if (busca==NULL){
      retorno = NAO_ENCONTRADO;
    }
  }
	return retorno;
}

int buscarPorGC(Celula* inicio, int gc, Celula* resultado){
	show_log(" buscarPorGC()");
  int retorno=SUCESSO;
	Celula* busca=inicio->prox;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
    resultado=NULL;
  }else{
    //busca enquanto lista não acaba ou acha o 1º GC correspondente
    while((busca!=NULL)&&(busca->gc!=gc)){
      busca=busca->prox;
    }
    resultado=busca;
    //verifica se a busca reotrnou nulo
    if (busca==NULL){
      retorno = NAO_ENCONTRADO;
    }
  }
	return retorno;
}

int ExcluirPorTamanho(Celula* inicio, float tamanho){
  show_log("ExcluirPorTamanho()");
  int retorno=SUCESSO;
  Celula* busca=inicio->prox;
  Celula* anterior = busca;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
  }else{
    //busca enquanto lista não acaba ou acha o 1º tamanho correspondente
    while((busca!=NULL)&&(busca->tamanho!=tamanho)){
      anterior = busca;
      busca=busca->prox;
    }

    //verifica se a busca reotrnou nulo
    if(busca != NULL) {
      anterior->prox = busca->prox;
      free(busca);
    } else {
      retorno = NAO_ENCONTRADO;
    }
  }
  return retorno;
}

int ExcluirPorPeso(Celula* inicio, int peso){
  show_log("ExcluirPorPeso()");
  int retorno=SUCESSO;
  Celula* busca=inicio->prox;
  Celula* anterior = busca;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
  }else{
    //busca enquanto lista não acaba ou acha o 1º peso correspondente
    while((busca!=NULL)&&(busca->peso!=peso)){
      anterior = busca;
      busca=busca->prox;
    }
    //verifica se a busca reotrnou nulo
    if(busca != NULL) {
      anterior->prox = busca->prox;
      free(busca);
    } else {
      retorno = NAO_ENCONTRADO;
    }
  }
  return retorno;
}

int ExcluirPorGC(Celula* inicio, int gc){
  show_log("ExcluirPorGC()");
  int retorno=SUCESSO;
  Celula* busca=inicio->prox;
  Celula* anterior = busca;
  
  //verifica se a lista está vazia
  if(inicio->prox==NULL){
    retorno = LISTA_VAZIA;
  }else{
    //busca enquanto lista não acaba ou acha o 1º gc correspondente
    while((busca!=NULL)&&(busca->gc!=gc)){
      anterior = busca;
      busca=busca->prox;
    }

    //verifica se a busca reotrnou nulo
    if(busca != NULL) {
      anterior->prox = busca->prox;
      free(busca);
    } else {
      retorno = NAO_ENCONTRADO;
    }
  }
  return retorno;
}

void imprimeLista(Celula* inicio){
  show_log("imprimeLista()");
  //testa se a lista esta vazia
  if(inicio->prox==NULL)
    show_log("ERRO_LISTA_VAZIA");
  else{
    Celula* busca=inicio->prox;
    while(busca!=NULL){
      printf("%s;%.2f;%d;%d\n",busca->nome,busca->tamanho,busca->peso,busca->gc);
      busca=busca->prox;
    }
  }
}

void destruirLista(Celula* inicio){
  show_log("destruirLista()");
  Celula* anterior;
  //checar se a lista exite
  if(inicio->prox==NULL){
    show_log("ERRO_LISTA_VAZIA");
  }else{
    while(inicio!=NULL){
      anterior=inicio;
      inicio=inicio->prox;
      free(anterior);
    }
  }
}