/** Codi solucio de la practica: CLIENT **/ 

 

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

 

int main(int argc, char **argv){ 

 

  if (argc != 2) { 

    //Fem un sistema de control d'errors que atura l'execució si no s'ha indicat cap IP de destí 

    printf("Error, escriu: %s IP\n", argv[0]);  

    exit(0); 

  } 

 

  int s;  /* Per treballar amb el socket */ 

  struct sockaddr_in adr; 

  char buffer[MIDA_BUFFER]; 

  char buffer2[MIDA_BUFFER]; 

  socklen_t mida; 

  int i, num1,num2; 

 

  /* Volem socket d'internet i no orientat a la connexio */ 

  s = socket(AF_INET, SOCK_DGRAM, 0); 

 

  adr.sin_family = AF_INET; 

  adr.sin_port = htons(44444); //posem el port 44444 

 

  /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */ 

  adr.sin_addr.s_addr = inet_addr(argv[1]); 

 

  printf("escriu un numero: \n"); //demanem un número a l'usuari 

  scanf("%d", &num1); 

 

  printf("escriu el segon numero: \n"); //demanem un segon número a l'usuari 

  scanf("%d", &num2); 

 

 char aux[5];

  sprintf(aux,"%d",num1); // convertim el nostre valor enter a una taula de caràcters ; //codifiquem el primer número 

 sprintf(buffer2,"%s %d\0",aux,num2); // Afegim un espai i el segon numero

  //Enviem el paquet 

  sendto(s, buffer, strlen(buffer), 0, (struct sockaddr*)&adr, sizeof(adr)); 

 

  printf("Paquet enviat!\n"); 

  //Esperem la resporta del servidor 

  recvfrom(s, buffer2, MIDA_BUFFER, 0,(struct sockaddr*)&adr, &mida); 

  printf("Resposta: %s", buffer2); //printejem la resposta 

 

  /* Tanquem el socket */ 

  close(s); 

  return 0; 

} 