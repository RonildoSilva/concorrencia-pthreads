#include <stdio.h>
#include <stdlib.h>
#include "lista.h"


struct elemento{
    Processo processo;
    struct elemento *proximo;
} typedef Elemento;

Lista* criar_lista(){
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    if(lista != NULL){
        *lista = NULL;
    }
    return lista;
}

void destruir_lista(Lista* lista){
    if(lista != NULL){
        Elemento* no;
        while((*lista) != NULL){
            no = *lista;
            *lista = (*lista)->proximo;
            free(no);
        }
        free(lista);
    }
}

Processo obter_processo(Lista* lista, int pos){
    Elemento *no = *lista;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->proximo;
        i++;
    }
    return no->processo;
}

int insere_fim(Lista* lista, Processo p){
    if(lista == NULL)
        return 0;
    Elemento *no;
    no = (Elemento*) malloc(sizeof(Elemento));
    
    if(no == NULL){
        return 0;
    }

    no->processo = p;
    no->proximo = NULL;
    if((*lista) == NULL){
        *lista = no;
    }
    else{
        Elemento *aux;
        aux = *lista;
        while(aux->proximo != NULL){
            aux = aux->proximo;
        }
        aux->proximo = no;
    }
    
    return 1;
}

int remove_inicio(Lista* lista){
    if(lista == NULL){
        return 0;
    }
    if((*lista) == NULL){
        return 0;
    }

    Elemento *no = *lista;
    *lista = no->proximo;
    free(no);
    return 1;
}

int tamanho_lista(Lista* lista){
    if(lista == NULL){
        return 0;
    }
    int cont = 0;
    Elemento* no = *lista;
    while(no != NULL){
        cont++;
        no = no->proximo;
    }
    return cont;
}
