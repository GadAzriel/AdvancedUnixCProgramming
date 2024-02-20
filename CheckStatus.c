#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>

#define MAX_SIZE 128

#define W "Status: Waiting!"
#define A "Status: Approve"
#define U "Status: UnApprove"
#define AS "Status: Awaiting signature"

void Error(char* msg) { fprintf(stderr, "Error: %s\n", msg); exit(1);} //error function

int checkPassword(char* path,char* user){

int flag =0;
int fd = open(path, O_RDWR);
char buff[MAX_SIZE + 1]; // Buffer for reading file content, +1 for null terminator
    char *line;
    if (fd != -1) {  // if the file it exists in the Request directory
        while (read(fd, buff, MAX_SIZE) > 0) {
            buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
            line = strtok(buff, "\n"); // Tokenize the buffer to get lines
            while (line != NULL) {
                if ((strcmp(line, user)) == 0){
			flag =1;
			break; // No need to continue searching
		}
            	line = strtok(NULL, "\n"); // Get the next line
            }
	if (flag == 1) break;
	}
}
if (fd == -1)
        Error("open");
close(fd);
return flag;
}

int checkStatus(char* id){
//file paths
    char temp[] = ".txt";
    char path1[MAX_SIZE] = "Loan/Request/";
    strcat(path1, id); strcat(path1, temp);
    char path2[MAX_SIZE] = "Loan/Result/Approved/";
    strcat(path2, id); strcat(path2, temp);
    char path3[MAX_SIZE] = "Loan/Result/Unapproved/";
    strcat(path3, id); strcat(path3, temp);
    // open files
    int fd1 = open(path1, O_RDONLY);
    int fd2 = open(path2, O_RDONLY);
    int fd3 = open(path3, O_RDONLY);

char buff[MAX_SIZE + 1]; // Buffer for reading file content, +1 for null terminator
    char *line;
    if (fd1 != -1) {  // if the file it exists in the Request directory
fprintf(stdout,"Status: Waiting!\n");
close(fd1); // Close
}
if (fd2 != -1) { // if the file it exists in the Approved directory
while (read(fd2, buff, MAX_SIZE) > 0) {
            buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
            line = strtok(buff, "\n"); // Tokenize the buffer to get lines
            while (line != NULL) {
		if(strcmp(A,line) == 0) {fprintf(stdout,"Approve\n"); break;}
		if(strcmp(AS,line) == 0) {fprintf(stdout,"Awaiting signature\n"); break;}

            line = strtok(NULL, "\n"); // Get the next line
            }
}
close(fd2); // Close
}
if (fd3 != -1) { // if the file it exists in the Unapproved directory
fprintf(stdout,"Sorry! UnApprove\n");
close(fd3); // Close
}
if (fd1 == -1 && fd2 == -1 && fd3 == -1)
        Error("File not found in any directory.");
    return 0;
}

int main(int argc, char* argv[]){
if(argc != 3) Error("Bad number of parameters.\n");
char userPath[] = "Loan/User.txt"; // Auxiliary variable to open the User.txt file
char strTmp[MAX_SIZE] = "";
char requestPath[MAX_SIZE] = "Loan/Request/";
char temp []= ".txt";
strcat(requestPath, argv[1]);
    strcat(requestPath, temp);
sprintf(strTmp, "%s \t\t %s", argv[1], argv[2]);

if(checkPassword(userPath,strTmp) == 1)
checkStatus(argv[1]);
else
fprintf(stdout,"Wrong Pass!!!\n");
return 0;
}


