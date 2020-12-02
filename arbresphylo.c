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



/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {
  arbre N = *a;
  if (est_une_feuille(N) == 0) {
    //si N est un Noeud 2 cas :
    if (seq == NULL || !strcmp(N->valeur,seq->val)) {
      ajouter_espece(&N->gauche, espece, seq);
    } else {
      ajouter_espece(&N->droit, espece, seq->suivant);
    }
  } else {
  //si N est une feuille ou Nil 4 cas :
    if (N == NULL && seq == NULL) {
      arbre newFeuille = nouveau_noeud();
      newFeuille->valeur = espece;
      N = newFeuille;
      return 0;
    }
    if (N == NULL && seq != NULL) {
      arbre newNoeud = nouveau_noeud();
      newNoeud->valeur = seq->val;
      N = newNoeud;
      ajouter_espece(&N->droit, espece, seq->suivant);
    }
    if (N != NULL && seq == NULL) {
      arbre newFeuille = nouveau_noeud();
      newFeuille->valeur = N->valeur;
      N->valeur = seq->val;
      N->gauche = newFeuille;
      ajouter_espece(&N->droit, espece, seq->suivant);
    }
    if (N != NULL && seq != NULL) {
      printf("'%s' ne peut pas etre ajouté. l'espece '%s' partage les meme caractéristiques",espece,N->valeur);
      return 1;
    }

  }
    return -1;
}
