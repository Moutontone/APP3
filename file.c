#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include "file.h"

/**
* Ceci-dessous sont les fonctions pour pile
*/
file* nouvelleFile(){
    file* l;
    l = (file*) malloc(sizeof(file));
    l->tete = NULL;
    l->queue = NULL;
    return l;
}

cellulef* newCel ()
{
    cellulef *cel;
    cel = (cellulef *) malloc(sizeof(cellulef));
    cel->tree = NULL;
    cel->suivant = NULL;
    return cel;
}

void enfiler(file *l, arbre n){
    cellulef* cel = newCel();
    cel->tree = n;
    cel->suivant = NULL;
    if (file_vide(*l)) {
      l->tete = cel;
    } else {
      l->queue->suivant = cel;
    }
    l->queue = cel;
}

arbre defiler(file *l){
    if(l->tete != NULL){
        cellulef *cel = l->tete;
        l->tete = l->tete->suivant;
        if (l->tete == NULL) l->queue = NULL;
        return cel->tree;
    }
    return NULL;
}

int file_vide(file f){
    int valeur =0;
    if(f.tete == NULL){
        valeur= 1;
    }
    else {
        valeur =0;
    }
    return valeur;
}
