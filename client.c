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
#define NUM_TESTS 6
typedef struct{
  int num1;
  int num2;
  int resposta;
}test_t;

int main(int argc, char **argv){ 

 

  if (argc != 2) { 

    //Fem un sistema de control d'errors que atura l'execució si no s'ha indicat cap IP de destí 

    printf("Error, escriu: %s IP\n", argv[0]);  

    exit(0); 

  } 

  /*Inicialitzem testos*/
  test_t test[]={{10,10,100},{-1,90,-1},{90,-1,-1},{500,500,-1},{4,5,20},{255,-255,-1}};
 /*Fi testos*/

  int s;  /* Per treballar amb el socket */ 

  struct sockaddr_in adr; 

  char buffer[MIDA_BUFFER]; 

  char buffer2[MIDA_BUFFER]; 

  socklen_t mida; 

  int i, num1,num2, resposta; 
  int ok=0;
  int ko=0;
 

  /* Volem socket d'internet i no orientat a la connexio */ 

  s = socket(AF_INET, SOCK_DGRAM, 0); 

 

  adr.sin_family = AF_INET; 

  adr.sin_port = htons(44444); //posem el port 44444 

 

  /* L'adreca de comunicacio sera la IP del servidor, es a dir el parametre */ 

  adr.sin_addr.s_addr = inet_addr(argv[1]); 

  printf("Inici del joc de proves de la part 3 de la pràctica de xarxes\n");
  for(int i = 0; i < NUM_TESTS; i++){
    num1 = test[i].num1; //el primer numero
    num2 = test[i].num2; //el segon numero 
    char aux[5];
    sprintf(aux,"%d",num1); // convertim el nostre valor enter a una taula de caràcters ; //codifiquem el primer número 
    sprintf(buffer,"%s %d",aux,num2); // Afegim un espai i el segon numero

    //Enviem el paquet 

    sendto(s, buffer, strlen(buffer), 0, (struct sockaddr*)&adr, sizeof(adr)); 
    //Esperem la resporta del servidor 

    recvfrom(s, buffer2, MIDA_BUFFER, 0,(struct sockaddr*)&adr, &mida); 

     sscanf(buffer2,"%d",&resposta);
    if(resposta==test[i].resposta){
      ok++;
    }else{
      ko++;
    }
    memset(buffer,'\0',strlen(buffer));
  }

  
  printf("Resultat del joc de proves\n\tOK = %d\n\tKO = %d\n\tTests %d\n",ok,ko,NUM_TESTS);
  

  /* Tanquem el socket */ 

  close(s); 

  return 0; 

} 