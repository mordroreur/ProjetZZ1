#include "listeFloat.h"


listef LLf_create()
{
  listef l;
  l.taille = 0;
  l.deb = NULL;
  return l;
}


void LLf_add_first(listef * l, float val)
{
  maillonf *m = (maillonf *)malloc(sizeof(maillonf));
  m->value = val;
  
  m->suivant = l->deb;
  l->deb = m;
  l->taille++;
}


void LLf_free(listef * l)
{
  maillonf *m1 = l->deb;
  maillonf *m2;
  
  while(m1 != NULL){
    m2 = m1;
    m1 = m1->suivant;
    free(m2);
  }
}


int LLf_contains(listef * l, float n)
{
  maillonf *m = l->deb;
  while(m != NULL && m->value != n)
    {
      m = m->suivant;
    }
  if(m !=NULL && m->value == n){
    return 1;
  }
  return 0;
}


int LLf_size(listef * l)
{
  return l->taille;
}

void LLf_afficheListef(listef * l)
{
  maillonf *m = l->deb;
  printf("--- Listef ---\n");
  while(m != NULL)
    {
      if(m != l->deb){
	printf("%lf ", m->value);
      }else{
	printf("->%lf ", m->value);
      }
      m = m->suivant;
    }
    printf("\n");
}

void LLf_add_last(listef *l, float val){
  if(l->deb != NULL){
    maillonf *nouv = (maillonf*)malloc(sizeof(maillonf));
    nouv->value = val;
    nouv->suivant = NULL;
    maillonf **m = &(l->deb);
    while((*m)->suivant != NULL){
      m = &((*m)->suivant);
    }
    (*m)->suivant = nouv;
    l->taille++;
  }else{
    LLf_add_first(l, val);
  }
}

float LLf_get_n(listef *l, int index){
  int i = 0;
  maillonf *m = l->deb;

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


void LLf_remove_n(listef *l, int index){
  if(index == 0){
    LLf_remove_head(l);
  }else{
    int i = 0;
    maillonf *m = l->deb;
    while(m->suivant != NULL && i != index-1){
      m = m->suivant;
      i++;
    }
    if(m->suivant != NULL){
      maillonf *m1 = m->suivant;
      m->suivant = m1->suivant;
      free(m1);
      l->taille--;
    }    
  }
}

void LLf_remove_head(listef *l){
  maillonf *m = l->deb;
  if(m != NULL){
    l->deb = m->suivant;
    free(m);
    l->taille--;
  }
}

void LLf_remove_tail(listef *l){
  LLf_remove_n(l, l->taille-1);
}
