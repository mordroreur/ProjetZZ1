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
  maillon *fin;
  int taille;
}liste;


liste *LL_create();
void LL_add_first(liste *l, int val);
void LL_free(liste * l);

#endif /*__GUARDIAN_LISTE_HEADER__*/
