#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
const char wrong[]="wrong, please try again \n";
const char good[]="good we can start \n";
const char*port="69";//numero du port addr info
char ipserveur[256];
  int s;
int main(int argc, char *argv[]){
	struct addrinfo hints;
    struct addrinfo *result,*tmp;
	   if(argc<3){
		 write(STDOUT_FILENO,wrong,sizeof(wrong));
	      }
	   else{
		write(STDOUT_FILENO,good,sizeof(good));
    
    memset(&hints, 0, sizeof(struct addrinfo));
    hints.ai_family = AF_INET;    //Allow IPv4
    hints.ai_socktype = SOCK_DGRAM;
    hints.ai_flags = 0;
    hints.ai_protocol = IPPROTO_UDP;//protocol IPv4

    s = getaddrinfo(argv[1], port, &hints, &result);
    
          if(s !=0){
			  fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
			  exit(EXIT_FAILURE);
			  }
			  for (tmp = result; tmp != NULL; tmp = tmp->ai_next) {//on choisis la bonne adresse ip sur toute la liste 
				  getnameinfo(tmp->ai_addr, tmp->ai_addrlen, ipserveur, sizeof(ipserveur), NULL, 0, NI_NUMERICHOST);//mise au format ip
				  write(STDOUT_FILENO,ipserveur,strlen(ipserveur));//on affiche l'adresse ip du serveur 
                   }
              
               
        exit(EXIT_FAILURE);
            }

}
