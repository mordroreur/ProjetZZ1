#include "liste.h"


liste * LL_create()
{
  liste * l = (liste *)malloc(sizeof(liste));
  l->taille = 0;
  l->deb = NULL;
  l->fin = NULL;
  return l;
}


void LL_add_first(liste * l, int val)
{
  maillon *m = (maillon *)malloc(sizeof(maillon));
  m->value = 0;
  m->suivant = l->deb;
  l->deb = m->suivant;
  if(l->taille == 0){
    l->fin = m->suivant;
  }
  l->taille++;
}


void LL_free(liste * l)
{
  maillon *m1 = l->deb;
  maillon *m2;
  
  while(m1 != NULL){
    m2 = m1;
    m1 = m1->suivant;
    free(m2);
  }
  free(l);
}

/*
int contains(liste * l, int n)
{
  maillon *m = l->deb;
  while(m != NULL && m->value != n)
    {
      m = m->suivant;
    }
  if(m !=NULL && m->value == n){
    return 1;
  }
  return 0;
}

int size(liste * l)
{
    int n = 0;
    while(l != NULL)
    {
        l = l->suivant;
        n++;
    }
    return n;
}

void afficheListe(liste * l)
{
    printf("--- Liste ---\n");
    while(l != NULL)
    {
        printf("->%d ", l->value);
        l = l->suivant;
    }
    printf("\n");
}

int get(liste * l, int n)
{
    int i = 0;
    while(i < n)
    {
        l = l->suivant;
        i++;
    }
    return l->value;
}
*/
