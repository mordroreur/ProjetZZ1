#ifndef __GUARDIAN_LISTEFLOAT_HEADER__
#define __GUARDIAN_LISTEFLOAT_HEADER__

#include <stdio.h>
#include <stdlib.h>

typedef struct maillonFloat
{
    float value;
    struct maillonFloat * suivant;

} maillonf;

typedef struct listeFloat{
  maillonf *deb;
  int taille;
}listef;


listef LLf_create();
void LLf_add_first(listef *l, float val);
void LLf_free(listef *l);
int LLf_contains(listef *l, float n);
int LLf_size(listef *l);
void LLf_afficheListef(listef * l);
void LLf_add_last(listef *l, float val);
float LLf_get_n(listef *l, int index);
void LLf_remove_n(listef *l, int index);
void LLf_remove_head(listef *l);
void LLf_remove_tail(listef *l);

#endif /*__GUARDIAN_LISTEFLOAT_HEADER__*/
