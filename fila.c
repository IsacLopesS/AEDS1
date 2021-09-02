#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>

typedef struct Usuario
{
    char nome[20];
    char sobrenome[20];
    char CPF[15];
} TUsuario;

typedef struct Celula
{
    TUsuario item;
    struct Celula *prox;
} TCelula;

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

TUsuario Pesquisar(TFila *fila,TUsuario user)
{
   int tam = fila->tamanho;
   TUsuario aux;
   TUsuario retorno;
   for(int i=0;i<tam;i++)
   {
       Desenfileirar(fila,&aux);
       if(strcmp(aux.CPF,user.CPF)==0)
       {
           retorno = aux;
       }
       Enfileirar(fila,aux);
   }
   return retorno;

}
void ImprimirUsuario(TUsuario user)
{
    printf("\nNOME: %s",user.nome);
    printf("\nSOBRE-NOME: %s",user.sobrenome);
    printf("\nCPF: %s",user.CPF);
}
void Imprimir(TFila *fila)
{
    TUsuario aux;
    int tam = fila->tamanho;
    for(int i=0;i<tam;i++)
   {
       Desenfileirar(fila,&aux);
       ImprimirUsuario(aux);
       Enfileirar(fila,aux);
   }

}
int Pesquisar2(TFila *fila,TUsuario user)
{
   int tam = fila->tamanho;
   TUsuario aux;
   int retorno=0;
   for(int i=0;i<tam;i++)
   {
       Desenfileirar(fila,&aux);
       if(strcmp(aux.CPF,user.CPF)==0)
       {
           retorno = 1;
       }
       Enfileirar(fila,aux);
   }
   return retorno;

}
void LerUsuario(TUsuario *user)
{
    printf("\n NOME");
    fflush(stdin);
    fgets(user->nome,15,stdin);

    printf("\n SOBRENOME");
    fflush(stdin);
    fgets(user->sobrenome,15,stdin);

    printf("\n CPF");
    fflush(stdin);
    fgets(user->CPF,15,stdin);
}

int FilasIguais(TFila *fila1,TFila *fila2)
{
    if(fila1->tamanho!=fila2->tamanho)
    {
        return 0;
    }
    TUsuario item1,item2;
    int tam = fila1->tamanho;
    int resultado=1;
    for(int i=0;i<tam;i++)
    {
       Desenfileirar(fila1,&item1);
       Desenfileirar(fila2,&item2);
       if(strcmp(item1.CPF,item2.CPF)!=0)
       {
         resultado=0;
       }
        Enfileirar(fila1,item1);
        Enfileirar(fila2,item2);
    }
    return resultado;
}
void Intercalacao(TFila *fila1,TFila *fila2)
{
    TFila fila3;
    TUsuario item1,item2;
    IniciarFila(&fila3);
    int i=0;
    while(i<fila1->tamanho || i<fila2->tamanho)
    {
        if(i<fila1->tamanho)
        {
          Desenfileirar(fila1,&item1);
          Enfileirar(&fila3,item1);
          Enfileirar(fila1,item1);
        }
        if(i<fila2->tamanho)
        {
            Desenfileirar(fila2,&item1);
            Enfileirar(&fila3,item1);
            Enfileirar(fila2,item1);
        }
        i++;
    }
    Imprimir(&fila3);

}
void InverteFila(TFila *fila)
{
    TUsuario item;
    TFila faux;
    IniciarFila(&faux);
    int j=0,tam=fila->tamanho;
    while(j<tam)
    {


  for(int i=0;i<fila->tamanho-1;i++)
  {
      Desenfileirar(fila,&item);
      Enfileirar(fila,item);
  }
  Desenfileirar(fila,&item);
  Enfileirar(&faux,item);
  j++;
    }
    Imprimir(&faux);
    system("pause");
    for(int h=0;h<tam;h++)
    {
        Desenfileirar(&faux,&item);
        Enfileirar(fila,item);
    }
 free(faux.frente);
}
int main()

{
    TFila fila,fila2;
    TUsuario item;
    IniciarFila(&fila);
    IniciarFila(&fila2);

    for(int i=0;i<3;i++)
    {
        //printf("\n%d",FV(fila));
       LerUsuario(&item);
       Enfileirar(&fila,item);


    }
printf("\nvamo ver\n\n");
    InverteFila(&fila);
    printf("\nFILA INVERTIDA: \n\n");
    Imprimir(&fila);




return 0;
}
