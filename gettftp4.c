 #include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define ipserveursize 25
#define CMDSIZE 100
#define buffersize 1500
const char wrong[]="wrong, please try again \n";
const char good[]="good we can start \n";
const char*port="69";//numero du port addr info
char ipserveur[ipserveursize];
ssize_t nread;
//struct sockaddr_storage peer_addr; utiliser pour lire le fichier reçu mais n'as pas fonctionné
//socklen_t peer_addr_len;
int s;

       int main(int argc, char *argv[]){
	   struct addrinfo hints;
       struct addrinfo *result,*tmp;
       char cmd[CMDSIZE]; 
       char buffer[buffersize];
       
       //socklen_t addrlen=sizeof(src_addr);utiliser pour lire le fichier reçu mais n'as pas fonctionné
    
    int defRRQ(char* filename,char* mode, char* cmd){//cette fonction permet de dénifinir la requete en lecture
					int cmdlen=(2+strlen(filename)+1+strlen(mode)+1);//prend en parametre le nombre d'octet a reserve
					//le 2 est en octet
					//le 1 correspont au caractère 0
					cmd[0]=0;
					cmd[1]=1;
					strcpy(&cmd[2],filename);
					strcpy(&cmd[3+strlen(filename)],mode);
					write(STDOUT_FILENO,cmd,sizeof(cmd));
					return cmdlen;
				} 
		//on vérifie si on a bien écrit le bon nombre d'arguments		
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
                   
                   int socketserv=socket(result->ai_family,result->ai_socktype,result->ai_protocol); //réservation d'un socket de connection vers le serveur 
                   if(socketserv < 0){
					   write(STDOUT_FILENO,wrong,sizeof(wrong));
				   }  
				   
				int cmdsize=defRRQ(argv[2],"octet",cmd);
				sendto(socketserv,cmd,cmdsize,0,result->ai_addr,result->ai_addrlen);//transmission du socket
					//code pour afficher le fichier reçu mais il ne fonctionne pas encore
					//int recept=recvfrom(socketserv,buffer,buffersize,0,&src_addr,&addrlen);
				//if (recp>1){
					//fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(s));
					 //exit(EXIT_FAILURE);}
					puts(buffer);

        exit(EXIT_FAILURE);
            }         
}

