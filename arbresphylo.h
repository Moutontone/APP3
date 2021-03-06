#ifndef ARBRESPHYLO_H
#define ARBRESPHYLO_H

#include "listes.h"
#include "file.h"

/* Analyse un arbre: doit mettre à jour le nombre d'espèces et de
 * caractéristiques.
 */
void analyse_arbre (arbre racine, int* nb_esp, int* nb_carac);

void analyse_arbre_rec (arbre racine, int* nb_esp, int* nb_carac);

/* Recherche une espèce dans l'arbre et remplit seq avec la séquence de ses
 * caractéristiques.
 *
 * Doit retourner 0 si l'espèce a été retrouvée, 1 sinon.
 */
int rechercher_espece (arbre racine, char *espece, liste_t* seq);

int rechercher_espece_rec (arbre racine, char *espece, liste_t* seq);

int ajouter_espece (arbre* racine, char *espece, cellule_t* seq);

int ajouter_espece (arbre* a, char *espece, cellule_t* seq);

void afficher_par_niveau (arbre racine, FILE* fout) ;

int ajouter_carac(arbre* a, char* carac, cellule_t* seq);

void afficher_par_niveau_rec(file F1, file F2, FILE* fout);

#endif
