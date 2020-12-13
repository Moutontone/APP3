#ifndef ACTE5_H
#define ACTE5_H

#include "arbres.h"
#include "arbresphylo.h"
#include "common_tests.h"


typedef struct ligne ligne_t;

struct ligne {
  char * nom;
  int tab[MAX];
}

int arbre_vide(arbre *a);
int ajouterEspece(File *f, );



#endif
