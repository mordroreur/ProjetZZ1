#include "serveurHost.h"

#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <pthread.h>
#include "serveurJoin.h"


typedef struct client_ecran{
  ecran *screen;
  int scom;
  struct sockaddr_storage *recep;
  int lg_app;
  int s_ecoute;
}client_ecran;





//pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;




char client_message[2000];


void *communicationAvecClient(void* param){
  char buf[1500];
  int newSocket = *((int *)param);


  bzero(buf,sizeof(buf));
  
  recv(newSocket , buf , sizeof(buf), 0);

  printf("Le client %s vient de se connecter\n", buf);
  
  /*client_ecran *tmp = param;
  ecran *screen = tmp->screen;
  struct sockaddr_storage *recep = tmp->recep;
  int lg_app = tmp->lg_app;
  int scom = tmp->scom;
  int s_ecoute = tmp->s_ecoute;
  free(tmp);

  int i;
  int j;
  char buf[1500], renvoi[1500];
  char host[1024],service[20];

  printf("nouveau scom = %d\n", scom);*/
  /*
  scom=accept(s_ecoute,(struct sockaddr *)recep, (unsigned int *)&lg_app);
	  getnameinfo((struct sockaddr *)recep,sizeof (*recep), host, sizeof(host),service, sizeof(service),0); //optionnelle pour info
	  printf("recu de %s venant du port %s\n",host, service); //optionnnelle
  */
  //bzero(buf,sizeof(buf));

  
  /*
  while(1){
    recv(scom,buf,sizeof(buf),0);

    printf("Le client %s vient de se connecter\n", buf);
    }*/
  /*
  while(screen->etapeDuJeu){

    send(scom,renvoi,strlen(renvoi),0);

    
    recv(scom,buf,sizeof(buf),0);

    //printf("buf recu %s\n",buf);

    bzero(renvoi,sizeof(renvoi));

    //for(i=strlen(buf)-1,j=0;i>=0;i--,j++) renvoi[j]=buf[i];

    //renvoi[j+1]='\0';

    send(scom,renvoi,strlen(renvoi),0);

    if (strcmp(buf,"FIN") == 0){screen->etapeDuJeu = 0;}

    bzero(buf,sizeof(buf));

    }*/
  
  
 

  return NULL;
}








void *launchServeur(void* param){
  ecran *screen = (ecran *)param;
  int s_ecoute,scom, lg_app,i,j;
  struct sockaddr_in adr;
  struct sockaddr_storage recep;

  char buf[1500], renvoi[1500];
  
  char host[1024],service[20];
  s_ecoute=socket(AF_INET,SOCK_STREAM,0);
  
  printf("creation socket\n");
  adr.sin_family=AF_INET;
  adr.sin_port=htons(42420);
  adr.sin_addr.s_addr=INADDR_ANY;
  if (bind(s_ecoute,(struct sockaddr *)&adr,sizeof(struct sockaddr_in)) !=0) {
    printf("probleme de bind sur v4\n");
    screen->etapeDuJeu = 69;
  }else{

    pthread_t threadclient;
    int RetourDuThreadDuClient = pthread_create(&threadclient, NULL, ConnectServeur,  screen);
    if(RetourDuThreadDuClient){
      screen->etapeDuJeu = 69;
    }else{
      if (listen(s_ecoute,5) != 0) {
	printf("pb ecoute\n");
	screen->etapeDuJeu = 69;
      }else{
	printf("en attente de connexion\n");
	int trouve = 0;
	int i = 0;
	pthread_t tid[60];
	while (!trouve) {
	  
	  scom=accept(s_ecoute,(struct sockaddr *)&recep, (unsigned int *)&lg_app);

	  
	  if(pthread_create(&tid[i], NULL, communicationAvecClient,  &scom)){
	    screen->etapeDuJeu = 69;
	    printf("PB ICI\n");
	    break;
	  }
	  
	  //pthread_join(tid[i], NULL);
	  i++;
	  
	  //close(scom);
	}
      }
    }
    close(s_ecoute);
  }
  return NULL;
}
