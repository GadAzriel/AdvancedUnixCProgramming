#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>

#define MAX_SIZE 128
#define SIZE 256


void Error(char* msg) { fprintf(stderr, "Error: %s\n", msg); exit(1);} //error function

int search(char* path) {
    int fd;
    if ((fd = open(path, O_RDONLY)) == -1) // try to open <ID>.text in diRequest
        return 0;
    else {
fprintf(stdout,"Sorry! you have a request\n");
close(fd);
        return 1; // Added a return statement to indicate a request exists.
    }
}

int openIdDFile(char* path, char* id,char* sum, char* payments) {
    int fd;
    char strTmp[SIZE], strTmp2[SIZE],strTmp4[SIZE] ,name[MAX_SIZE], surName[MAX_SIZE], age[MAX_SIZE];
    srand(time(NULL)); // Seed the random number generator only once.
    int randomNum = (rand() % 10) + 1; // Generate a random number between 1 and 10
    if ((fd = open(path, O_WRONLY | O_CREAT, 0664)) == -1) {
        perror("open new ID file");
        return (-1);
    }
    fprintf(stdout, "Insert Details:\n");
    fprintf(stdout, "Name: ");
    fscanf(stdin, "%s", name);
    fprintf(stdout, "SurName: ");
    fscanf(stdin, "%s", surName);
    fprintf(stdout, "Age: ");
    fscanf(stdin, "%s", age);
fprintf(stdout,"Request Saved!\n");
    sprintf(strTmp, "Name: %s\n", name);
    if ((write(fd, strTmp, strlen(strTmp))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
    sprintf(strTmp, "SurName: %s\n", surName);
    if ((write(fd, strTmp, strlen(strTmp))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
    sprintf(strTmp, "Age: %s\n", age);
    if ((write(fd, strTmp, strlen(strTmp))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
sprintf(strTmp4, "Sum: %s\n", sum);
    if ((write(fd, strTmp4, strlen(strTmp4))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
    sprintf(strTmp, "Payments: %s\n", payments);
    if ((write(fd, strTmp, strlen(strTmp))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
    sprintf(strTmp2, "Rating: %d/10\n", randomNum);
    if ((write(fd, strTmp2, strlen(strTmp2))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
    char strTmp3[] = "Status: Waiting!\n";
    if ((write(fd, strTmp3, strlen(strTmp3))) == -1) {
        Error("String write to <ID>.txt failed.\n");
    }
    close(fd); // Close the file descriptor after writing.
    return 0;
}

int WriteToUser(char* path, char* id) {
    int fd;
    char strTmp[SIZE], uPassword[MAX_SIZE];
    fprintf(stdout, "User: %s\n", id);
    fprintf(stdout, "Password: ");
    fscanf(stdin, "%s", uPassword);
    if ((fd = open(path, O_WRONLY | O_APPEND)) == -1){
        perror("open User.txt");
        return (-1);
    }
    sprintf(strTmp, "%s \t\t %s\n", id, uPassword);
    if ((write(fd, strTmp, strlen(strTmp))) == -1) {
        Error("String write to User.txt failed.\n");
    }
fprintf(stdout,"User Created\n");
    close(fd); // Close the file descriptor after writing.
    return 0;
}

int main(int argc, char* argv[]) {
    if (argc != 4) {
        Error("Bad number of parameters.\n");
    }
char userPath[] = "Loan/User.txt"; // Auxiliary variable to open the User.txt file
    char requestPath[MAX_SIZE] = "Loan/Request/";
char temp []= ".txt";
strcat(requestPath, argv[1]);
    strcat(requestPath, temp);
    if(search(requestPath) == 0){ // The parameter to the function is the user's ID number.
int write = WriteToUser(userPath, argv[1]);

int newF = openIdDFile(requestPath, argv[1],argv[2], argv[3]);
}
    return 0;
}

