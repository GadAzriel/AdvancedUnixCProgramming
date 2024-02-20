//This code is part of homework number - 1
//This code does not accept parameters. It returns the amount of submitted requests.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIZE 128

// Function to handle errors and exit the program
void Error(char* msg) { fprintf(stderr, "Error: %s\n", msg); exit(1); }

// Function to count the number of lines in a file
// Every line (except for the first row) is a user detail that requests a loan.
int amountOfReq(char* path){
    int fd, rbytes, amount = 0;
    char buff[MAX_SIZE];

    if ((fd = open(path, O_RDONLY)) == -1) {
        perror("open User.txt");
        return -1;
    }

    while ((rbytes = read(fd, buff, MAX_SIZE)) > 0) {
        for (int i = 0; i < rbytes; i++) {
            if (buff[i] == '\n') {
                amount++; // Increment the line count for each newline character
            }
        }
    }

    if (rbytes == -1) {
        perror("read");
        close(fd);
        return -1;
    }
    close(fd); // Close the file
    return amount-1; // -1 Because the first line dosen't count.
}

int main(int argc, char* argv[]) {
    if(argc != 1) Error("Bad number of parameters");
    char path[]="Loan/User.txt"; //Path declaration --> In User.txt find all the applications submitted
    int amount = amountOfReq(path);
    if (amount != -1) {
        fprintf(stdout, "%d\n", amount); // Print the line count to stdout
    }
    return 0;
}
