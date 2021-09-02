#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include<string.h>

typedef struct {
  char CPF[15];
  char nome[15];
  /* outros componentes */
} TUsuario;

typedef struct celula {
  TUsuario item;
  struct celula* prox;
} TCelula;

typedef struct {
  TCelula *fundo;
  TCelula *topo;
  int tamanho;
} TPilha;

void FPVazia(TPilha *Pilha){
  Pilha->topo = (TCelula*) malloc(sizeof(TCelula));
  Pilha->fundo = Pilha->topo;
  Pilha->topo->prox = NULL;
  Pilha->tamanho = 0;
} //ok

int Vazia(TPilha Pilha){
 return (Pilha.topo == Pilha.fundo);
} //ok

void Empilha(TUsuario x, TPilha *Pilha){
  TCelula* Aux;
  Aux = (TCelula*) malloc(sizeof(TCelula));
  Pilha->topo->item = x;
  Aux->prox = Pilha->topo;
  Pilha->topo = Aux;
  Pilha->tamanho++;
}

void Desempilha(TPilha *Pilha, TUsuario *Item){
  TCelula* q;
  if (Vazia(*Pilha)) {
      printf("Erro: lista vazia\n");
      return;
  }
  q = Pilha->topo;
  Pilha->topo = q->prox;
  *Item = q->prox->item;
  free(q);
  Pilha->tamanho--;
}//ok

int Tamanho(TPilha Pilha){
 return (Pilha.tamanho);
}
void ImprimirUsuario(TUsuario user)
{
    printf("\nNOME: %s",user.nome);
   // printf("\nSOBRE-NOME: %s",user.sobrenome);
    printf("\nCPF: %s",user.CPF);
}
void LerUsuario(TUsuario *user)
{
    printf("\n NOME");
    fflush(stdin);
    fgets(user->nome,15,stdin);
/*
    printf("\n SOBRENOME");
    fflush(stdin);
    fgets(user->sobrenome,15,stdin);
*/
    printf("\n CPF");
    fflush(stdin);
    fgets(user->CPF,15,stdin);
}
void Imprimir(TPilha pilha)
{
    TUsuario item;
    TPilha paux;
    FPVazia(&paux);
    int tam = pilha.tamanho;
    for(int i=0;i<tam;i++)
    {
        Desempilha(&pilha,&item);
        Empilha(item,&paux);
    }
    for(int i=0;i<tam;i++)
    {
        Desempilha(&paux,&item);
        ImprimirUsuario(item);
    }
    free(paux.topo);
}
int Pesquisar(TPilha pilha,TUsuario user)
{
    TUsuario item;
    while(Vazia(pilha)!=1)
    {
        Desempilha(&pilha,&item);
        if(strcmp(user.CPF,item.CPF)==0)
        {
            return 1;
        }
    }
    return 0;
}
// FILAAAAAAAAAAAA
typedef struct Fila
{
    TCelula *frente;
    TCelula *tras;
    int tamanho;
} TFila;

void IniciarFila(TFila *fila)
{
    fila->frente=(TCelula*)malloc(sizeof(TCelula));
    fila->tras=fila->frente;
    fila->frente->prox=NULL;
    fila->tamanho=0;
}
int FV(TFila fila)
{
    return (fila.frente==fila.tras);
}
void Enfileirar(TFila *fila,TUsuario user)
{
    fila->tras->prox=(TCelula*)malloc(sizeof(TCelula));
    fila->tras=fila->tras->prox;
    fila->tras->item = user;
    fila->tamanho++;
}
void Desenfileirar(TFila *fila,TUsuario *item)
{
   TCelula *aux = fila->frente->prox;
   if (FV(*fila)==0){
   *item = fila->frente->prox->item;
    fila->frente->prox = aux->prox;
    free(aux);
    if(fila->frente->prox==NULL)
    {
        fila->tras=fila->frente;
    }
    fila->tamanho--;
   }
}
void InvertePilha_com_fila(TPilha *pilha)
{
    TFila fila;
    TUsuario item;
    IniciarFila(&fila);
    while(Vazia(*pilha)!=1)
    {
        Desempilha(pilha,&item);
        Enfileirar(&fila,item);
    }
    while(fila.tamanho!=0)
    {
        Desenfileirar(&fila,&item);
        Empilha(item,pilha);
    }
}
