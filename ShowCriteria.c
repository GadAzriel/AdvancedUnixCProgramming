//This code is part of homework number - 1
//This code does not accept parameters. It returns a Presentation of loan approval criteria.
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

void Error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1); // Exit the program with an error status
}

int main(int argc, char* argv[]) {
    if(argc != 1) Error("Bad number of parameters");
int status;
fprintf(stdout,"Min Rating ");
fflush(stdout); //function call that explicitly flushes the output buffer
	if(fork()==0){
		execlp("/bin/sh","sh","-c","cat Loan/Criteria.txt",NULL);
		Error("execlp failed");
	}
	wait(&status);
	fprintf(stdout,"\n");
return 0;
}
