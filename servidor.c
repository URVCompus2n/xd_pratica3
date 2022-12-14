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

#include <math.h>

#define MIDA_BUFFER 1024 

 void neteja_taula(char array[]){
  int i=0;
  for(i=0;i<MIDA_BUFFER;i++)
  {
      array[i] = 0;
  }
}

int main( ){ 

 

  int s;  /* Per treballar amb el socket */ 

  struct sockaddr_in serv_adr, client_adr; 

  char buffer[MIDA_BUFFER]; 


  socklen_t mida; 

  int n, i; 

 

  /* Volem socket d'internet i no orientat a la connexio */ 

  s = socket(AF_INET, SOCK_DGRAM, 0); 

 

  /* Posem les dades del socket */ 

  serv_adr.sin_family = AF_INET; 

  serv_adr.sin_addr.s_addr =INADDR_ANY; 

  serv_adr.sin_port = htons(44444); 

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

      printf("Paquet rebut %s!\n",buffer); 
    int i = 0;
    int prim = 0;
    int segon = 0;
    sscanf(buffer,"%d %d",&prim,&segon);
     neteja_taula(buffer);
      int resposta = -1; //resultat a retornar 
      if(prim>=0&&prim<=99&&segon>=0&&segon<=99){ 

        resposta = prim*segon; //fem el producte dels nombres si estan al rang indicat 

      } 

      sprintf(buffer,"%d",resposta); // convertim el nostre valor enter a una taula de caràcters 

      

 

      printf("Buffer enviat: %s\n",buffer); 

      sendto(s, buffer, strlen(buffer), 0, (struct sockaddr*)&client_adr, sizeof(client_adr)); 

 

    
     
      neteja_taula(buffer);
    } 

  } 

 

  /* Tanquem el socket */ 

  close(s); 

  return 0; 

} 