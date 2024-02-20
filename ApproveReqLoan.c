//This code is part of homework number - 1
//This code accept 1 parameter. It approve a  submitted requests.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define Status "Status: Waiting!"
#define NEW_STATUS "Status: Awaiting signature"
#define MAX_SIZE 128

void Error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1); // Exit the program with an error status
}

int approveReqLoan(char* id){
char temp[] = ".txt";
    char path1[MAX_SIZE] = "Loan/Request/";
    strcat(path1, id); strcat(path1, temp);
    char path2[MAX_SIZE] = "Loan/Result/Approved/";
	int count = 0,flag =0,status;
	int fd = open(path1, O_RDWR);
	char buff[MAX_SIZE + 1]; // Buffer for reading file content, +1 for null terminator
    char *line;
    if (fd != -1) {  // if the file it exists in the Request directory
        while (read(fd, buff, MAX_SIZE) > 0) {
            buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
            line = strtok(buff, "\n"); // Tokenize the buffer to get lines
            while (line != NULL) {
                if (strcmp(line, Status) == 0){
					count += strlen(Status)+1;
				
					if (lseek(fd, -count, SEEK_CUR) == -1) 
						Error("Error seeking file position");
					// Write the new status "Status: Awaiting signature"
					if (write(fd, NEW_STATUS, strlen(NEW_STATUS)) == -1) 
                    	Error("Error writing to file");
					flag =1;
					break; // No need to continue searching
                    //write "Status: Awaiting signature" instead of Status: Waiting!
					
				}
                line = strtok(NULL, "\n"); // Get the next line
            }
			if (flag == 1) break;
        }
	}
	if (fd == -1){
        fprintf(stdout,"Request Not Found!\n");
		return flag;
	}
	close(fd); // Close
	if(fork()==0){//new procces for exec prog.
		execlp("mv", "mv", path1, path2, NULL);
		Error("execlp");
	}
	return flag;
}

int main(int argc, char* argv[]) {
	if (argc != 2) Error("bad number of parameters");
	if((approveReqLoan(argv[1])) == 1)
		fprintf(stdout,"Request Approved.\n");
	return 0;
}

