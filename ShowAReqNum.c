//This code is part of homework number - 1
//This code does not accept parameters. It returns the amount of submitted requests that approved.
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

void Error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1); // Exit the program with an error status
}

int main(int argc, char* argv[]) {
    if (argc != 1) Error("Bad number of parameters");
execlp("/bin/sh","sh","-c","ls -1 Loan/Result/Approved | wc -l",NULL);
//first arg: shell interpreter, second arg: name of the program, third arg: tell to read commands from the command srtring.
//Fourth arg:This is the command string to be executed by the shell, Last arg: Marks the end of the arguments list.
Error("execlp");
return 0;
}
