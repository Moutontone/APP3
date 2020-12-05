#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"

void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac)
{
  *nb_esp = 0;
  *nb_carac = 0;
  analyse_arbre_rec(racine, nb_esp, nb_carac);

   //printf ("À faire: fonction analyse_arbre fichier " __FILE__ "\n");
}

void analyse_arbre_rec (arbre racine, int* nb_esp, int* nb_carac) {
  if (racine != NULL) {
    if (est_une_feuille(racine)) {
      *nb_esp += 1;
    } else {
      *nb_carac += 1;
      analyse_arbre_rec(racine->droit, nb_esp, nb_carac);
      analyse_arbre_rec(racine->gauche, nb_esp, nb_carac);
    }
  }
}




/* ACTE II */
/* Recherche l'espece dans l'arbre. Modifie la liste passée en paramètre pour y mettre les
 * caractéristiques. Retourne 0 si l'espèce a été retrouvée, 1 sinon.
 */

 int rechercher_espece (arbre racine, char *espece, liste_t* seq) {
   // printf("Liste avant {\n");
   // afficher_liste(seq);
   // printf("}\n");
    int ret;
    ret = rechercher_espece_rec (racine, espece, seq);
    if (ret == 0) {
      afficher_liste(seq);
    } else {
      printf("Espece '%s' non présente dans l'abre.\n",espece);
    }
    // printf("Liste apres {\n");
    // afficher_liste(seq);
    // printf("}\n");
    printf("ret : %d",ret);
    return ret;
}



int rechercher_espece_rec (arbre racine, char *espece, liste_t* seq)
{
    if (racine == NULL) return 1;
    if (est_une_feuille(racine)) {
       if (strcmp(racine->valeur,espece) == 0) {
         return 0;
       } else {
         return 1;
       }
     }
     int isInGauche, isInDroite;
     isInGauche = rechercher_espece_rec(racine->gauche, espece, seq);
     if (isInGauche == 0) {
       return 0;
     } else {
       isInDroite = rechercher_espece_rec(racine->droit, espece, seq);
       if (isInDroite == 0) ajouter_tete(seq, racine->valeur);
       return isInDroite;
     }
}


int retirer_in_liste (char* str, cellule_t* seq) {
  if (seq == NULL) return 0;
  cellule_t *cell, *prec;
  prec = seq;
  cell = prec->suivant;
  if (strcmp(str,prec->val)==0) {
    free(prec);
    seq = cell;
    return 1;
  }
  while (cell != NULL) {
    if (strcmp(str,cell->val)==0) {
      prec->suivant = cell->suivant;
      free(cell);
      return 1;
    }
  prec = cell;
  cell = cell->suivant;
  }


  return 0;
}
/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {
  arbre N = *a;
  printf("\nEtape suivante :\n Liste :\n");
  liste_t l;
  l.tete = seq;
  afficher_liste(&l);

  if (est_une_feuille(N) == 0) {
    //si N est un Noeud 2 cas :
    printf("Noeud : %s. ",N->valeur);
    if (retirer_in_liste(N->valeur, seq)) {
      printf("présent\n");
      return ajouter_espece(&N->droit, espece, seq);
    } else {
      printf("absent\n");
      return ajouter_espece(&N->gauche, espece, seq);
    }
  } else {

  //si N est une feuille ou Nil 4 cas :
    if (N == NULL && seq == NULL) {
      printf("emlacement trouvé !\n");
      printf("pour l'espece '%s'\n",espece);
      arbre newFeuille = nouveau_noeud();
      newFeuille->valeur = espece;
      N = newFeuille;
      return 0;

    }
    if (N == NULL && seq != NULL) {
      printf("nouvelles caractéristiques '%s'\n",seq->val);
      arbre newNoeud = nouveau_noeud();
      newNoeud->valeur = seq->val;
      N = newNoeud;
      printf("Feuille '%s'\n",N->valeur);
      return ajouter_espece(&N->droit, espece, seq->suivant);
    }
    if (N != NULL && seq != NULL) {
      printf("Feuille '%s'\n",N->valeur);
      printf("nouvelles caractéristiques '%s' + feuille deja la\n",seq->val);
      arbre newFeuille = nouveau_noeud();
      newFeuille->valeur = N->valeur;
      N->valeur = seq->val;
      N->gauche = newFeuille;
      printf("Feuille '%s'\n",N->valeur);
      printf("Feuille '%s'\n",N->gauche->valeur);
      return ajouter_espece(&N->droit, espece, seq->suivant);
    }
    if (N != NULL && seq == NULL) {
      printf("Feuille '%s'\n",N->valeur);
      printf("'%s' ne peut pas etre ajouté. l'espece '%s' partage les meme caractéristiques",espece,N->valeur);
      return 1;
    }

  }
  return -1;
}
