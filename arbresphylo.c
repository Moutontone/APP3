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
    int ret;
    ret = rechercher_espece_rec (racine, espece, seq);
    if (ret == 0) {
      afficher_liste(seq);
    } else {
      printf("Espece '%s' non présente dans l'abre.\n",espece);
    }
    return ret;
}



int rechercher_espece_rec (arbre racine, char *espece, liste_t* seq)
{
    if (racine == NULL) return 1;
    if (est_une_feuille(racine)) {
       if (racine->valeur == espece) {
         printf("feuille %s <> %s\n",racine->valeur,espece);
         printf("trouve !\n");
         return 0;
       } else {
         return 1;
       }
     }
     int isIsGauche;
     isIsGauche = rechercher_espece_rec(racine->gauche, espece, seq);
     if (isIsGauche == 0) {
       return 0;
     } else {
       ajouter_queue(seq, racine->valeur);
       return rechercher_espece_rec(racine->droit, espece, seq);
     }
}



/* Doit renvoyer 0 si l'espece a bien ete ajoutee, 1 sinon, et ecrire un
 * message d'erreur.
 */
int ajouter_espece (arbre* a, char *espece, cellule_t* seq) {

    return 1;
}
