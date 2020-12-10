#ifndef _FILE_H
#define _FILE_H
#include "arbres.h"

typedef struct file file;

typedef struct cellulef cellulef;
/*
 * Déclaration de cellul et sequence
 */
struct cellulef {
    arbre tree;
    cellulef *suivant;
};

struct file {
    cellulef *tete;
    cellulef *queue;
};

file *nouvelleFile();

cellulef *newCel ();

int file_vide(file l);

void enfiler(file *l, arbre n);

arbre defiler(file *l);


#endif /* _FILE_H */
