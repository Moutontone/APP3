#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "arbres.h"
#include "arbresphylo.h"
#include "listes.h"
#include "file.h"

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
  printf("\nEtape suivante :\n");
  liste_t l;
  l.tete = seq;
  printf("Liste : \n");
  afficher_liste(&l);

  if (est_une_feuille(*a) == 0) {
    //si N est un Noeud 2 cas :
    printf("Noeud : %s. ",(*a)->valeur);
    // if (retirer_in_liste((*a)->valeur, seq)) {
    if (seq != NULL && strcmp((*a)->valeur,seq->val)==0) {
      printf("présent\n");
      return ajouter_espece(&(*a)->droit, espece, seq->suivant);
    } else {
      printf("absent\n");
      return ajouter_espece(&(*a)->gauche, espece, seq);
    }
  }


  //si N est une feuille ou Nil 4 cas :
  if (*a == NULL && seq == NULL) {
    printf("emlacement trouvé !\n");
    printf("pour l'espece '%s'\n",espece);
    arbre newFeuille = nouveau_noeud();
    newFeuille->valeur = espece;
    *a = newFeuille;
    return 0;

  }
  if (*a == NULL && seq != NULL) {
    printf("nouvelles caractéristiques '%s'\n",seq->val);
    arbre newNoeud = nouveau_noeud();
    newNoeud->valeur = seq->val;
    *a = newNoeud;
    printf("Feuille '%s'\n",(*a)->valeur);
    return ajouter_espece(&(*a)->droit, espece, seq->suivant);
  }
  if (*a != NULL && seq != NULL) {
    printf("Feuille '%s'\n",(*a)->valeur);
    printf("nouvelles caractéristiques '%s' + feuille deja la\n",seq->val);
    arbre newFeuille = nouveau_noeud();
    newFeuille->valeur = (*a)->valeur;
    (*a)->valeur = seq->val;
    (*a)->gauche = newFeuille;
    printf("Feuille '%s'\n",(*a)->valeur);
    printf("Feuille '%s'\n",(*a)->gauche->valeur);
    return ajouter_espece(&(*a)->droit, espece, seq->suivant);
  }
  if (*a != NULL && seq == NULL) {
    printf("Feuille '%s'\n",(*a)->valeur);
    printf("'%s' ne peut pas etre ajouté. l'espece '%s' partage les meme caractéristiques",espece,(*a)->valeur);
    return 1;
  }
  return -1;
}

/* Doit afficher la liste des caractéristiques niveau par niveau, de gauche
 * à droite, dans le fichier fout.
 * Appeler la fonction avec fout=stdin pour afficher sur la sortie standard.
 */
void afficher_par_niveau (arbre racine, FILE* fout) {
  file *F1 = nouvelleFile();
  file *F2 = nouvelleFile();
  enfiler(F1, racine);

  afficher_par_niveau_rec(*F1, *F2, fout);
}

void afficher_par_niveau_rec(file F1, file F2, FILE* fout) {

  arbre tree;
  char texte[100000];
  texte[0] = '\0';
  while (file_vide(F1) == 0) {
    tree = defiler(&F1);
    // printf("noeud de valeur : ");
    // printf("'%s'\n",tree->valeur );
    if (tree != NULL && est_une_feuille(tree) == 0) {
      // printf("feuille\n");
      strcat(texte,tree->valeur);
      strcat(texte, " ");
      enfiler(&F2,tree->gauche);
      enfiler(&F2, tree->droit);
    }
  }
  // printf("%s",texte);
  fprintf(fout,"%s\n",texte);
  if (file_vide(F2) == 0) {
    afficher_par_niveau_rec(F2,F1,fout);
  }
}

// Acte 4

int in_liste (char* str, cellule_t* seq) {
  if (seq == NULL) return 0;
  cellule_t *cell, *prec;
  prec = seq;
  cell = prec->suivant;
  if (strcmp(str,prec->val)==0) {
    return 1;
  }
  while (cell != NULL) {
    if (strcmp(str,cell->val)==0) {
      return 1;
    }
  prec = cell;
  cell = cell->suivant;
  }
  return 0;
}

arbre *clade(arbre *a, cellule_t* seq, int *cladeComplet){
  //CladeComplet vaut 0 au premier appel
  //*a est un Noeud :
  if (est_une_feuille(*a)==0) {
    arbre *g, *d;
    g = clade(&(*a)->gauche,seq,cladeComplet);
    d = clade(&(*a)->droit, seq, cladeComplet);
    if ((*a)->gauche == NULL) {
      if (*cladeComplet==0) return (d==NULL)? d: a;
      return d;
    }
    if ((*a)->droit == NULL) {
      if (*cladeComplet==0) return (g==NULL)? g: a;
      return g ;
    }
    if (g!=NULL && d!=NULL && *cladeComplet==0) return a;
    if (g!=NULL && d!=NULL && *cladeComplet==1) return NULL;
    if (g==NULL && d==NULL) return NULL;
    if (g==NULL||d==NULL) {
      *cladeComplet = 1;
      printf("%s\n",(*a)->valeur);
      printf("bool : %d\n",d==NULL);
    }
    return (g==NULL)? d : g ;
  }
  if (*a == NULL) return a;
  printf("feuille ; '%s' =>  %s\n",(*a)->valeur,(in_liste((*a)->valeur, seq))? "dans la liste ": "absent"  );
  return (in_liste((*a)->valeur, seq))? a : NULL ;
}


int ajouter_carac(arbre* a, char* carac, cellule_t* seq) {
   arbre *emplacement;
   int cladeComplet = 0;
   if (*a == NULL) return 0;
   emplacement = clade(a, seq, &cladeComplet);
   if (emplacement != NULL) {
     arbre new = nouveau_noeud();
     new->valeur = carac;
     new->droit = (*emplacement);
     *emplacement = new;
     return 1;
   }
   return 0;
}
