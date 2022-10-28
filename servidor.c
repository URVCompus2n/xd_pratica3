/* Codi solucio de la practica: SERVIDOR */ 

 

/* Inclusio de fitxers .h habituals */ 

#include <stdio.h> 

#include <stdlib.h> 

#include <string.h> 

 

/* Inclusio de fitxers .h per als sockets */ 

#include <sys/socket.h> 

#include <sys/types.h> 

#include <netinet/in.h> 

#include <arpa/inet.h> 

#include <unistd.h> 

 

#define MIDA_BUFFER 1024 

 

int main( ){ 

 

  int s;  /* Per treballar amb el socket */ 

  struct sockaddr_in serv_adr, client_adr; 

  char buffer[MIDA_BUFFER]; 

  char buffer2[MIDA_BUFFER]; 

  socklen_t mida; 

  int n, i; 

 

  /* Volem socket d'internet i no orientat a la connexio */ 

  s = socket(AF_INET, SOCK_DGRAM, 0); 

 

  /* Posem les dades del socket */ 

  serv_adr.sin_family = AF_INET; 

  serv_adr.sin_addr.s_addr =INADDR_ANY; 

  serv_adr.sin_port = htons(44444); 

 printf("%d",INADDR_ANY);

  /* Enllacem el socket */ 

  n = bind(s, (struct sockaddr*)&serv_adr, sizeof(serv_adr)); 

 

  if (n < 0) 

  { 

    printf("No s'ha pogut enllacar el socket\n"); 

  } 

  else 

  { 

 

    /* Servidor operatiu! */ 

    while(1){ 

        //fem un bucle infinit 

      printf("Servidor esperant dades!\n"); 

 

 

      recvfrom(s, buffer, MIDA_BUFFER, 0, (struct sockaddr*)&client_adr, &mida); 

      printf("Paquet rebut!\n"); 

 

      int prim = (int) buffer[0]-'0'; //el primer número 

      int segon = (int) buffer[2]-'0'; //deixem un espai i el següent número 

      int resposta = -1; //resultat a retornar 

      if(prim>=0&&prim<=99&&segon>=0&&segon<=99){ 

        resposta = prim*segon; //fem el producte dels nombres si estan al rang indicat 

      } 

      sprintf(buffer2,"%d",resposta); // convertim el nostre valor enter a una taula de caràcters 

      printf("Valor retornat: %d\n",resposta); 

 

      printf("Buffer enviat: %s\n",buffer2); 

      sendto(s, buffer2, strlen(buffer2), 0, (struct sockaddr*)&client_adr, sizeof(client_adr)); 

 

      printf("Paquet enviat!\n"); 

    } 

  } 

 

  /* Tanquem el socket */ 

  close(s); 

  return 0; 

} 