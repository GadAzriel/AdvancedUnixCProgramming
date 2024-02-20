//This code is part of homework number - 1
//This code does not accept parameters. This program is a new shell that called Main_shell.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
#include <sys/wait.h>

#define GetLoan "GetLoan"
#define CheckStatus "CheckStatus"
#define ApproveLoan "ApproveLoan"
#define LoginM "LoginM"


void Error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1); // Exit the program with an error status
}

int main(int argc, char* argv[]) {
if(argc != 1) Error("Bad number of parameters.\n"); //checks the amount of parameters.
char prog[30];
char *param[4];
int status; //varible to store the exit status of the child process
fprintf(stdout,"MainShell> ");
while(1) //run until got 'LogOut'.
    {
fgets(prog,29,stdin); //get program from the user.  
prog[strlen(prog)-1]='\0';  
param[0] = strtok(prog," ");
param[1] = strtok(NULL," ");
param[2] = strtok(NULL," ");
param[3] = strtok(NULL," ");
if(strcmp(param[0], "exit") == 0)
break;
if(fork()==0) //new procces for exec prog.
{
if(strcmp(param[0],GetLoan) == 0)
execlp("./GetLoan", "GetLoan", param[1], param[2],param[3], NULL);
if(strcmp(param[0],CheckStatus) == 0)
execlp("./CheckStatus", "CheckStatus",param[1], param[2], NULL);
if(strcmp(param[0],ApproveLoan) == 0)
execlp("./ApproveLoan", "ApproveLoan",param[1], param[2], NULL);
if(strcmp(param[0],LoginM) == 0)
execlp("./LoginM", "LoginM", param[1], param[2], NULL);
fprintf(stdout,"Not Supported\n");
exit(0); // Exit the child process with a successful status
}
wait(&status);
fprintf(stdout,"MainShell> ");
}
    if(fork()==0) {//new procces for exit prog.
    	fprintf(stdout,"GoodBye...\n");
        execlp("./exit" ,"./exit",NULL);
        Error("error in exit from the shell");
    }
    wait(&status);
    return 0;
}
