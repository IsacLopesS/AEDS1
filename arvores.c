# include <stdio.h>
# include <stdlib.h>

typedef struct item{
    int chave;
} TItem;

typedef struct celula{
    TItem item;
    struct celula *pai;
    struct celula *esq;
    struct celula *dir;
} TCelula;

typedef struct arvore{
    TCelula *raiz;
}TArvore;

void Iniciar(TCelula **no){
    *no = NULL;
}

TCelula *criaNo(TItem Item){
    TCelula *no = (TCelula*) malloc(sizeof(TCelula));
    no->pai = NULL;
    no->esq = NULL;
    no->dir = NULL;
    no->item = Item;
    return no;
}

void Inserir(TCelula **x, TCelula *pai, TItem Item){
    if((*x) == NULL){
        (*x) = criaNo(Item);
        if(pai != NULL)
            (*x)->pai = pai;
        return;
    }
    if((*x)->item.chave > Item.chave){
        Inserir(&(*x)->esq, (*x), Item);
        return;
    }
    if ((*x)->item.chave < Item.chave)
        Inserir(&(*x)->dir, (*x), Item);
    else
        printf("\n>>>>> AVISO: ELEMENTO %d JA EXISTE! <<<<<\n",Item.chave);
}
void Insere(TCelula **x,TCelula *pai, TItem item)
{

}

TCelula* Pesquisar(TCelula *x, TItem Item){
    if((x == NULL)||(x->item.chave == Item.chave))
        return x;
    if(Item.chave < x->item.chave)
        return Pesquisar(x->esq,Item);
    else if(Item.chave > x->item.chave)
        return Pesquisar(x->dir, Item);
}

void Central(TCelula *x){
    if (x != NULL){
     Central(x->esq);
     printf("%d ",x->item.chave);
     Central(x->dir);
    }
}

TCelula* Minimo(TCelula *x){
    if (x == NULL)
        return NULL;
    while(x->esq != NULL){
        x = x->esq;
    }
    return x;
}

TCelula* Maximo(TCelula *x){
    if (x == NULL)
        return NULL;
    while(x->dir != NULL){
        x = x->dir;
    }
    return x;
}

TCelula* Sucessor(TCelula *x){
    if(x == NULL)
        return NULL;
    if(x->dir != NULL)
        return Minimo(x->dir);
    TCelula *y = x->pai;
    while(y != NULL && x == y->dir){
        x = y;
        y = y->pai;
    }
    return y;
}

TCelula* Predecessor(TCelula *x){
    if(x == NULL)
        return x;
    if(x->esq != NULL)
        return Maximo(x->esq);
    TCelula* y = x->pai;
    while(y != NULL && x == y->esq){
        x = y;
        y = y->pai;
    }
    return y;
}

// Substitui subárvore enraizada no nó 'u' pela subárvore enraizada no nó 'v'.
void Transplante(TArvore *Arvore, TCelula **u, TCelula **v){
    if ((*u)->pai == NULL)
        Arvore->raiz = (*v);
    else if((*u) == (*u)->pai->esq)
        (*u)->pai->esq = (*v);
    else
        (*u)->pai->dir = (*v);
    if(*v != NULL)
        (*v)->pai = (*u)->pai;
}

// Retira um nó 'z' na árvore 'Arvore'.
void Retirar(TArvore *Arvore, TCelula **z){
    if (*z == NULL){
        printf("\n>>>>> AVISO: NO' \"z\" E' NULO! <<<<<\n");
        return;
    }
    if((*z)->esq == NULL)
        Transplante(Arvore, z, &(*z)->dir);
    else if((*z)->dir == NULL)
        Transplante(Arvore, z, &(*z)->esq);
    else{
        TCelula *y = Minimo((*z)->dir);
        if(y->pai != (*z)){
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
void MSG_MENUU()
{
    printf("\n--------------------------MENU---------------------------");
        printf("\n\t1. INSERIR");
        printf("\n\t2. PESQUISAR");
        printf("\n\t3. CENTRAL");
        printf("\n\t4. MINIMO");
        printf("\n\t5. MAXIMO");
        printf("\n\t6. SUCESSOR");
        printf("\n\t6. PREDECESSOR");
        printf("\n\t6. RETIRAR");

}
int main()
{
    TArvore tree;
    Iniciar(&tree.raiz);
int opcao;
TItem item;
TCelula aux;
    do
        {
            printf("\n\tEscolha uma Opcao:");
            fflush(stdin);
            scanf("%d",&opcao);
            switch (opcao)
            {
            case 1:
                printf("insira o item que deseja inserir: ");
                scanf("%d",&item);
                Inserir(&tree.raiz,tree.raiz->pai,item);
                printf("item inserido com sucesso!");
               break;
            case 2:
               printf("insira o item que deseja pesquisar: ");
                scanf("%d",&item);
                printf("item: %d",Pesquisar(&tree.raiz,item));
                break;
            case 3:
                Central(&tree.raiz);
                break;
            case 4:

                Minimo(&tree.raiz);
                break;
            case 5:
               Maximo(&tree.raiz);
                break;
            case 6:

               Sucessor(&aux);
                break;
            case 7:

               Predecessor(&aux);
                break;
            case 8:

              Retirar(&tree,tree.raiz);
                break;
            case 9:
                printf("\n>>>>>>>>>>>>SAINDO<<<<<<<<<<<<<<<<,");
                break;
            default:
                printf("Digite uma opcao valida!!");
                system("PAUSE"); //BURRO! KKKKKK
            }
        }
        while(opcao!=9);
    }


