#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include <stdio.h>
const char wrong[]="wrong, please try again \n";
const char good[]="good we can start \n";
int main(int argc, char *argv[]){
	if(argc<3){
		 write(STDOUT_FILENO,wrong,sizeof(wrong));
	}
	else{
		write(STDOUT_FILENO,good,sizeof(good));
	}
	    write(STDOUT_FILENO,argv,sizeof(wrong));//ligne pour compiler et ne pas mettre en erreur (inutile)
	
}
