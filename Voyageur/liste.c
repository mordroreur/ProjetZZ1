#include "liste.h"
#include <stdlib.h>


liste* LL_create()
{
  liste* l = (liste *)malloc(sizeof(liste));
  l->taille = 0;
  l->deb = NULL;
  return l;
}


void LL_add_first(liste * l, int val)
{
  maillon *m = (maillon *)malloc(sizeof(maillon));
  m->value = val;
  
  m->suivant = l->deb;
  l->deb = m;
  l->taille++;
}

void LL_add_n(liste *l, int val, int index){
  maillon *nouv = (maillon*)malloc(sizeof(maillon));
  nouv->value = val;
  nouv->suivant = NULL;
  maillon **m = &(l->deb);
  int i = 0;
  while((*m)->suivant != NULL && i != index){
    m = &((*m)->suivant);
    i++;
  }
  (*m)->suivant = nouv;
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


int LL_contains(liste * l, int n)
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


int LL_size(liste * l)
{
  return l->taille;
}

void LL_afficheListe(liste * l)
{
  maillon *m = l->deb;
  printf("--- Liste ---\n");
  while(m != NULL)
    {
      if(m != l->deb){
	printf("%d ", m->value);
      }else{
	printf("->%d ", m->value);
      }
      m = m->suivant;
    }
    printf("\n");
}

void LL_add_last(liste *l, int val){
  if(l->deb == NULL){
    LL_add_first(l, val);
  }else{
    maillon *nouv = (maillon*)malloc(sizeof(maillon));
    nouv->value = val;
    nouv->suivant = NULL;
    maillon **m = &(l->deb);
    while((*m)->suivant != NULL){
      m = &((*m)->suivant);
    }
    (*m)->suivant = nouv;
    l->taille++;
  }
}

int LL_get_n(liste *l, int index){
  int i = 0;
  maillon *m = l->deb;

  while (m != NULL && i != index) {
    m = m->suivant;
    i++;
  }
  if(i == index && m != NULL){
    return m->value;
  }else{
    return -1;
  }
}


void LL_remove_n(liste *l, int index){
  if(index == 0){
    LL_remove_head(l);
  }else{
    int i = 0;
    maillon *m = l->deb;
    while(m->suivant != NULL && i != index-1){
      m = m->suivant;
      i++;
    }
    if(m->suivant != NULL){
      maillon *m1 = m->suivant;
      m->suivant = m1->suivant;
      free(m1);
      l->taille--;
    }    
  }
}

void LL_remove_head(liste *l){
  maillon *m = l->deb;
  if(m != NULL){
    l->deb = m->suivant;
    free(m);
    l->taille--;
  }
}

void LL_remove_tail(liste *l){
  LL_remove_n(l, l->taille-1);
}
