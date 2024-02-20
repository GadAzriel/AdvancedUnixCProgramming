//This code is part of homework number - 1
//This code get 1 parameters - num. This program updates the criteria for receiving a loan.
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include<time.h>
#include <string.h>

void Error(char* msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1); // Exit the program with an error status
}

int main(int argc, char* argv[]) {
    if(argc != 2) Error("Wrong Parmters!");
srand(time(NULL)); // Seed the random number generator only once.
int getNum = atoi(argv[1]);
int temp = 10 - getNum;
    int randomNumber = (rand() % getNum) + temp; // Generate a random number between getNum and 10
char command[256];
    sprintf(command, "echo %d > Loan/Criteria.txt", randomNumber); //Make the command string
    execlp("/bin/sh", "sh", "-c", command, NULL);
Error("execlp failed");
return 0;
}

