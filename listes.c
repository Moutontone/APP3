#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "listes.h"

/* fichier à compléter au besoin */
void init_liste_vide(liste_t* L) {
    L = (liste_t*)malloc(sizeof(liste_t));
    L->tete = NULL;
}


int ajouter_tete(liste_t* L, string c) { /* retourne 0 si OK, 1 sinon  */
    /* a completer */
        return 1;
}

void ajouter_queue(liste_t *l, string str) {
  cellule_t *lastCell, *newCell;
  //création de la cellule
  newCell = (cellule_t*)malloc(sizeof(cellule_t));
  newCell->val = str;
  newCell->suivant = NULL;
  //ajout à la liste
  lastCell = l->tete;
  if (lastCell == NULL) {
    l->tete = newCell;
  } else {
    while (lastCell->suivant != NULL) {
      lastCell = lastCell->suivant;
    }
    lastCell->suivant = newCell;
  }
}

void afficher_liste (liste_t* l)
{
    cellule_t *cel;
    if (l->tete==NULL) {
        printf("\n");
    }
    else {
        cel = l->tete;
        while (cel!=NULL) {
        if(cel->val !=NULL){
                printf(" %s",cel->val);
        }
           cel = cel->suivant;
        }
        printf("\n");
    }
}
