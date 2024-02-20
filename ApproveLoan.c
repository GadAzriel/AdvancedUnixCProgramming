#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/stat.h>

#define MAX_SIZE 128

#define Status "Status: Awaiting signature"
#define NEW_STATUS "Status: Approve"


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

int checkStatus(char* path,char* Userpath,char* username){
int fd,rbytes,flag=0;
char strTmp[MAX_SIZE*2], approve[MAX_SIZE],password[MAX_SIZE];
char *line;
int count =0;
    int original_length = strlen(Status); // Length of original status string
char buff[MAX_SIZE], temp[]="Status: Approve!";
if( ( fd = open( path, O_RDWR ) ) == -1 ) //open the given file
{ perror("No approve reqest!"); return( - 1 ); }
while (read(fd, buff, MAX_SIZE) > 0) {
        buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
line = strtok(buff, "\n"); // Tokenize the buffer to get lines
        while (line != NULL) {
            if (strcmp(line,Status) == 0) {
count += strlen(Status) + 1;
                fprintf(stdout,"Plz type Approve: ");
                fscanf(stdin,"%s",approve);
while (1) { //Check the password
fprintf(stdout,"Password: ");
fscanf(stdin,"%s",password);
sprintf(strTmp, "%s \t\t %s", username, password);
if (checkPassword(Userpath, strTmp) == 1)
break; // Exit loop if password matches
else
fprintf(stdout, "Wrong Password!!!\n");
}
                if(lseek(fd, -count, SEEK_CUR) ==  -1)
Error("seeking file position");
                // Pad the replacement string with spaces if needed
int spaces_to_add = original_length - strlen(NEW_STATUS);
                char padded_new_status[MAX_SIZE];
                sprintf(padded_new_status, "%s%*s", NEW_STATUS, spaces_to_add, "");
                if (write(fd, padded_new_status, strlen(Status)) == -1)
Error("writing to file");
                flag = 1;
                break;
            }
            else
                fprintf(stdout,"%s\n",line);
            line = strtok(NULL,"\n");
        }
        if(flag == 1) break;
    }
    if(fd == -1){
fprintf(stdout,"No approved request!\n");
return flag;
}
chmod(path, 0444); //Changes file permmision to read only
fprintf(stdout,"Good Luck!!\n");
close(fd);
return flag;
}



int main(int argc, char* argv[]){
if(argc != 3) Error("Bad number of parameters.\n"); //checks the amount of parameters.
char userPath[] = "Loan/User.txt"; // Auxiliary variable to open the User.txt file
char strTmp[MAX_SIZE] = "";
char requestPath[MAX_SIZE] = "Loan/Result/Approved/";
char temp []= ".txt";
strcat(requestPath, argv[1]);
    strcat(requestPath, temp);
sprintf(strTmp, "%s \t\t %s", argv[1], argv[2]);
if(checkPassword(userPath,strTmp) == 1)
checkStatus(requestPath,userPath,argv[1]);
else
fprintf(stdout,"Wrong Pass!!!\n");
return 0;
}
