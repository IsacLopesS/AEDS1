# include <stdio.h>
# include <stdlib.h>

typedef struct item
{
    int chave;
} TItem;

typedef struct celula
{
    TItem item;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
} TCelula;

typedef struct arvore
{
    TCelula *raiz;
} TArvore;

void Iniciar(TCelula **no)
{
    *no = NULL;
}

TCelula *criaNo(TItem Item)
{
    TCelula *no = (TCelula*) malloc(sizeof(TCelula));
    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;
    no->item = Item;
    return no;
}

void Inserir(TCelula **x, TCelula *pai, TItem Item)
{
    if((*x) == NULL)
    {
        (*x) = criaNo(Item);
        if(pai != NULL)
            (*x)->pai = pai;
        return;
    }
    if((*x)->item.chave > Item.chave)
    {
        Inserir(&(*x)->esq, (*x), Item);
        return;
    }
    if ((*x)->item.chave < Item.chave)
        Inserir(&(*x)->dir, (*x), Item);
    else
        printf("\n>>>>> AVISO: ELEMENTO %d JA EXISTE! <<<<<\n",Item.chave);
}
//questao 6
void InsereIterativo(TCelula **x, TCelula *pai, TItem Item)
{
   while((*x)->item.chave>Item.chave || (*x)->item.chave<Item.chave )
   {
       if((*x)->item.chave>Item.chave)
       {
         pai=*x;
         (*x)=(*x)->esq;
       }
       if((*x)->item.chave<Item.chave)
       {
           pai=*x;
           (*x)=(*x)->dir;
       }

   }
   if((*x) == NULL){
        (*x) = criaNo(Item);
        if(pai != NULL)
            (*x)->pai = pai;
        return;
    }

}


TCelula* Pesquisar(TCelula *x, TItem Item)
{
    if((x == NULL)||(x->item.chave == Item.chave))
        return x;
    if(Item.chave < x->item.chave)
        return Pesquisar(x->esq,Item);
    else if(Item.chave > x->item.chave)
        return Pesquisar(x->dir, Item);
}

void Central(TCelula *x)
{
    if (x != NULL)
    {
        Central(x->esq);
        printf("%d ",x->item.chave);
        Central(x->dir);
    }
}

TCelula* Minimo(TCelula *x)
{
    if (x == NULL)
        return NULL;
    while(x->esq != NULL)
    {
        x = x->esq;
    }
    return x;
}

TCelula* Maximo(TCelula *x)
{
    if (x == NULL)
        return NULL;
    while(x->dir != NULL)
    {
        x = x->dir;
    }
    return x;
}

TCelula* Sucessor(TCelula *x)
{
    if(x == NULL)
        return NULL;
    if(x->dir != NULL)
        return Minimo(x->dir);
    TCelula *y = x->pai;
    while(y != NULL && x == y->dir)
    {
        x = y;
        y = y->pai;
    }
    return y;
}
//exe 7
void PercorreImprime(TCelula **raiz)
{
   TCelula *aux = Minimo(*raiz);
   int i=1;
   while(aux!=NULL)
   {
       printf("item %d: [%d]",i,aux->item.chave);
       i++;
       aux=Sucessor(aux);
   }

}
//questao 8
void LiberaGeral(TCelula **raiz,TCelula *pai)
{
    TCelula *aux;
    if(((*raiz)->esq==NULL)&&((*raiz)->dir==NULL))
    {
        aux=*raiz;
        *raiz=pai;
        free(aux);
    }
    if((*raiz)->esq!=NULL)
    {
        LiberaGeral((*raiz)->esq,(*raiz)->pai);
    }
     if((*raiz)->dir!=NULL)
    {
        LiberaGeral((*raiz)->dir,(*raiz)->pai);
    }

}


TCelula* Predecessor(TCelula *x)
{
    if(x == NULL)
        return x;
    if(x->esq != NULL)
        return Maximo(x->esq);
    TCelula* y = x->pai;
    while(y != NULL && x == y->esq)
    {
        x = y;
        y = y->pai;
    }
    return y;
}

// Substitui sub??rvore enraizada no n?? 'u' pela sub??rvore enraizada no n?? 'v'.
void Transplante(TArvore *Arvore, TCelula **u, TCelula **v)
{
    if ((*u)->pai == NULL)
        Arvore->raiz = (*v);
    else if((*u) == (*u)->pai->esq)
        (*u)->pai->esq = (*v);
    else
        (*u)->pai->dir = (*v);
    if(*v != NULL)
        (*v)->pai = (*u)->pai;
}

// Retira um n?? 'z' na ??rvore 'Arvore'.
void Retirar(TArvore *Arvore, TCelula **z)
{
    if (*z == NULL)
    {
        printf("\n>>>>> AVISO: NO' \"z\" E' NULO! <<<<<\n");
        return;
    }
    if((*z)->esq == NULL)
        Transplante(Arvore, z, &(*z)->dir);
    else if((*z)->dir == NULL)
        Transplante(Arvore, z, &(*z)->esq);
    else
    {
        TCelula *y = Minimo((*z)->dir);
        if(y->pai != (*z))
        {
            Transplante(Arvore, &y, &y->dir);
            y->dir = (*z)->dir;
            y->dir->pai = y;
        }
        Transplante(Arvore, z, &y);
        y->esq = (*z)->esq;
        y->esq->pai = y;
    }
    free(*z);
    *z = NULL;
}
