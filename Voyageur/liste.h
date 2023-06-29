#ifndef __GUARDIAN_LISTE_HEADER__
#define __GUARDIAN_LISTE_HEADER__

#include <stdio.h>
#include <stdlib.h>

typedef struct maillon
{
    int value;
    struct maillon * suivant;

} maillon;

typedef struct liste{
  maillon *deb;
  int taille;
}liste;


liste* LL_create();
void LL_add_first(liste *l, int val);
void LL_add_n(liste *l, int val, int index);
void LL_free(liste *l);
int LL_contains(liste *l, int n);
int LL_size(liste *l);
void LL_afficheListe(liste * l);
void LL_add_last(liste *l, int val);
int LL_get_n(liste *l, int index);
void LL_remove_n(liste *l, int index);
void LL_remove_head(liste *l);
void LL_remove_tail(liste *l);

#endif /*__GUARDIAN_LISTE_HEADER__*/
