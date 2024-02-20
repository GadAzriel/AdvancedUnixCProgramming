//This code is part of homework number - 1
//This code does not accept parameters. This program is a new shell that called Manager_shell.c
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include<time.h>
#include <sys/wait.h>

#define ReqNum "ShowReqNum"
#define AReqNum "ShowAReqNum"
#define UnAReqNum "ShowUnAReqNum"
#define CheckReq "CheckRequestList"
#define ShowCReq "ShowReqDetails"
#define ShowCriteria "Show"
#define UpdateCri "UpdateCriteria"
#define Approve "ApproveReqLoan"
#define UnApprove "UnApproveReqLoan"

void Error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1); // Exit the program with an error status
}

int main(int argc, char* argv[]) {
	if(argc != 1) Error("Bad number of parameters.\n"); //checks the amount of parameters.
	char prog[30];
	char *param[2];
	int status; //varible to store the exit status of the child process
	fprintf(stdout,"ManagerShell> ");
	while(1) //run until got 'LogOut'.
    {
		fgets(prog,29,stdin); //get program from the user.
		prog[strlen(prog)-1]='\0';
    	param[0] = strtok(prog," ");
    	param[1] = strtok(NULL," ");
		if(strcmp(param[0], "LogOut") == 0)
			break;
		if(fork()==0) //new procces for exec prog.
		{
			if(strcmp(param[0],ReqNum) == 0)
				execlp("./ShowReqNum", "ShowReqNum", NULL);
			if(strcmp(param[0],AReqNum) == 0)
				execlp("./ShowAReqNum", "ShowAReqNum", NULL);
			if(strcmp(param[0],UnAReqNum) == 0)
				execlp("./ShowUnAReqNum", "ShowUnAReqNum", NULL);
			if(strcmp(param[0],CheckReq) == 0)
				execlp("./CheckRequestList", "CheckRequestList", NULL);
			if(strcmp(param[0],ShowCReq) == 0)
				execlp("./ShowReqDetails", "ShowReqDetails",param[1], NULL);
			if(strcmp(param[0],ShowCriteria) == 0 && strcmp(param[1],"Criteria")==0)
				execlp("./ShowCriteria", "ShowCriteria", NULL);
			if(strcmp(param[0],UpdateCri) == 0)
				execlp("./UpdateCriteria", "UpdateCriteria", param[1], NULL);
			if(strcmp(param[0],Approve) == 0)
				execlp("./ApproveReqLoan", "ApproveReqLoan", param[1], NULL);
			if(strcmp(param[0],UnApprove) == 0)
				execlp("./UnApproveReqLoan", "UnApproveReqLoan", param[1], NULL);
			fprintf(stdout,"Not Supported\n");
			exit(0);
        }
		wait(&status);
		fprintf(stdout,"ManagerShell> ");	
	}
    if(fork()==0) {//new procces for exit prog.
        execlp("./LogOut" ,"./LogOut",NULL);
        Error("error in LogOut from the shell");
    }
    wait(&status);
    return 0;
}

