#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>

void Error(char* msg) { fprintf(stderr, "Error: %s\n", msg); exit(1);} //error function

int main(int argc,char* argv[]) {
if(argc != 1) Error("Bad number of parameters.\n"); //checks the amount of parameters.
    exit(0);
}
