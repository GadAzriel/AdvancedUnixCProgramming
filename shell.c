//This code is part of homework number - 1
//This code does not accept parameters. It's open all the dir&file that the program need.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include<time.h>
#include <sys/stat.h> // Include for mkdir
#include <sys/types.h> // Might be necessary for some systems

#define MAX_SIZE 256
#define MAX2_SIZE 1000

void Error(char* msg) { fprintf(stderr, "Error: %s\n", msg); exit(1);} //error function

int main(int argc,char* argv[]){
if(argc != 1) Error("Bad number of parameters.\n");
char strTmp[MAX_SIZE] = ""; //helping string.
char strTmp2[MAX2_SIZE] = ""; //helping string.
char manAcount1[MAX2_SIZE] = "";
char manAcount2[MAX2_SIZE] = "";
char manAcount3[MAX2_SIZE] = "";
if (mkdir("Loan", 0777) == -1) perror("mkdir Loan error");
char strTmpNum[3] = ""; //


char pathUserFile []= "Loan/User.txt";
int fd,fd2,fd3;
    srand(time(NULL)); // Seed the random number generator only once.
    int randomNumber = (rand() % 6) + 5; // Generate a random number between 5 and 10
    if ((fd = open(pathUserFile, O_WRONLY | O_CREAT, 0664)) == -1) {
        perror("open User.txt file");
        return (-1);
    }

sprintf(strTmp, "Acount \t\t\t Pass\n");
if ((write(fd, strTmp, strlen(strTmp))) == -1) {
        Error("Write to User.txt failed.\n");
    }
    if ((fd3 = open("Manager_pass.txt", O_WRONLY | O_CREAT, 0664)) == -1) {
        perror("open Manager_pass.txt file");
        return (-1);
    }
    sprintf(strTmp2,"%-15s %-15s %-15s %-15s\n", "Account", "Pass", "ID", "Name");
    if ((write(fd3, strTmp2, strlen(strTmp2))) == -1) {
        Error("Write to Manager_pass.txt failed.\n");
    }
    sprintf(manAcount1,"%-15s %-15s %-15s %-15s\n","ChenK","Aa123456","123226789","Chen");
    if ((write(fd3, manAcount1, strlen(manAcount1))) == -1) {
        Error("Write to Manager_pass.txt failed.\n");
    }
    sprintf(manAcount2, "%-15s %-15s %-15s %-15s\n","ShellCol","6655433","554432211","Shelli");
    if ((write(fd3, manAcount2, strlen(manAcount2))) == -1) {
        Error("Write to Manager_pass.txt failed.\n");
    }
    sprintf(manAcount3,"%-15s %-15s %-15s %-15s\n","Ran1900 ","55555","554000221","Ran");
    if ((write(fd3, manAcount3, strlen(manAcount3))) == -1) {
        Error("Write to Manager_pass.txt failed.\n");
    }

close(fd); // Close the file descriptor after writing.
close(fd3);
if (mkdir("Loan/Request", 0777) == -1) perror("mkdir Loan/Request error");  //Open Request dir
if (mkdir("Loan/Result", 0777) == -1) perror("mkdir Loan/Result error"); //Open Result dir
if (mkdir("Loan/Result/Approved", 0777) == -1) perror("mkdir Loan/Result/Approved error"); //Open Approved dir
if (mkdir("Loan/Result/Unapproved", 0777) == -1) perror("mkdir Loan/Result/Unapproved error"); //Open Unapproved dir
if ((fd2 = open("Loan/Criteria.txt", O_WRONLY | O_CREAT, 0664)) == -1) {
        Error("open Criteria.txt file");
        return (-1);
    }
sprintf(strTmpNum,"%d",randomNumber);
if ((write(fd2, strTmpNum, strlen(strTmpNum))) == -1) {
        Error("open Criteria.txt file");

    }
close(fd2); // Close the file descriptor after writing.
return 0;
}

