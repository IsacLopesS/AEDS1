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

typedef struct Lista
{
    TCelula *primeiro;
    TCelula *ultimo;
    int tamanho;
} TLista;

void LV(TLista *lista)
{
    lista->primeiro=(TCelula*)malloc(sizeof(TCelula));
    lista->ultimo = lista->primeiro;
    lista->ultimo->prox=NULL;
    lista->tamanho = 0;
}
void Inserir(TLista *lista,TUsuario item)
{
    lista->ultimo->prox=(TCelula*)malloc(sizeof(TCelula));
    lista->ultimo=lista->ultimo->prox;
    lista->ultimo->item=item;
    lista->ultimo->prox = NULL;
    lista->tamanho++;
}
int Vazia(TLista lista)
{
    return (lista.primeiro==lista.ultimo);
}

TCelula* Pesquisar(TLista lista,TUsuario user)
{
    TCelula *aux=lista.primeiro;
    while(aux->prox!=NULL)
    {
        if(strcmp(aux->prox->item.CPF,user.CPF)==0)
        {
            return aux;
        }
        aux=aux->prox;
    }
    return NULL;
}

void Excluir(TLista *lista, TUsuario item)
{
    TCelula *p,*aux;
    p = Pesquisar(*lista,item);
    aux->prox = p->prox;
    aux = lista->primeiro;
    for(int i=0; i<lista->tamanho; i++)
    {
        if (aux->prox==p)
        {
            aux->prox=aux->prox;
            i=lista->tamanho;
        }
    }
    free(p);

}

int VerificarListasIguais(TLista l1,TLista l2)
{
    if(l1.tamanho!=l2.tamanho)
    {
        return 0;
    }
    TCelula *aux1,*aux2;
    aux1=l1.primeiro;
    aux2=l2.primeiro;
    while(aux1->prox!=NULL)
    {
        if(strcmp(aux1->item.CPF,aux2->item.CPF)==0)
        {
            aux1=aux1->prox;
            aux2=aux2->prox;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}
void Concatenacao(TLista l1,TLista l2)
{
    TCelula *aux1;
    aux1=l2.primeiro;
    while(l2.primeiro->prox!=NULL)
    {
        Inserir(&l1,l2.primeiro->prox->item);
    }
}

TLista Intercalacao(TLista l1,TLista l2)
{
    TLista lista3;
    LV(&lista3);
    TCelula *aux1,*aux2;
    aux1 = l1.primeiro;
    aux2 = l2.primeiro;
    while(aux1->prox!=NULL || aux2->prox!=NULL)
    {
        if(aux1->prox!=NULL)
        {
            Inserir(&lista3,aux1->prox->item);
        }
        if(aux2->prox!=NULL)
        {
            Inserir(&lista3,aux2->prox->item);
        }

    }

}
void LerUsuario(TUsuario *user)
{
    printf("\n NOME");
    fflush(stdin);
    fgets(user->nome,20,stdin);
    printf("\n CPF");
    fflush(stdin);
    fgets(user->CPF,15,stdin);
}
void ImprimirUsuario(TUsuario user)
{
    printf("\nNOME: %s",user.nome);
    printf("\nCPF: %s",user.CPF);
}
void ImprimirLista(TLista lista)
{
    while(lista.primeiro->prox!=NULL)
    {
        ImprimirUsuario(lista.primeiro->prox->item);
        printf("\n");
        lista.primeiro=lista.primeiro->prox;
    }
}

int main()
{
    TLista lista1,lista2;
    TUsuario item;
    LV(&lista1);
    LV(&lista2);
    for(int i=0;i<3;i++)
    {
        LerUsuario(&item);
        Inserir(&lista1,item);
        Inserir(&lista2,item);
    }
   printf("\nlista igual: %d\n",VerificarListasIguais(lista1,lista2)) ;
   return 0;

}
