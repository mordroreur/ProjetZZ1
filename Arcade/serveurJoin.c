#include "serveurJoin.h"

#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/socket.h>
#include <string.h>
#include <unistd.h>






void *ConnectServeur(void *param){
  ecran *screen = (ecran *)param;


  char buffer[200],texte[200];
  int sock,i,c;
  struct sockaddr_in addr;
  struct hostent *entree;
  addr.sin_port=htons(42420);
  addr.sin_family=AF_INET;
  entree=(struct hostent *)gethostbyname("localhost");
  bcopy((char *)entree->h_addr,(char *)&addr.sin_addr,entree->h_length);
  sock= socket(AF_INET,SOCK_STREAM,0);

  if (connect(sock, (struct sockaddr *)&addr,sizeof(struct sockaddr_in)) < 0) {
    printf("probleme connexion\n");
    screen->etapeDuJeu = 2;
  }else{
    printf("connexion passe\n");

    bzero(texte,sizeof(texte));
    bzero(buffer,sizeof(buffer));
    strcpy(texte, "NOM");
    send(sock,texte,strlen(texte)+1,0);

    recv(sock,buffer,sizeof(buffer),0);
    
    /*
    while (screen->etapeDuJeu) {
   
      bzero(texte,sizeof(texte));
      bzero(buffer,sizeof(buffer));
      i = 0;
      printf("Entrez une ligne de texte : \n");
      while((c=getchar()) != '\n')
	texte[i++]=c;
      send(sock,texte,strlen(texte)+1,0);
      recv(sock,buffer,sizeof(buffer),0);
      printf("recu %s\n",buffer);
      if (strcmp("FIN",texte) == 0) break;
      }*/
    
    close(sock);
  }
  return NULL;
}
