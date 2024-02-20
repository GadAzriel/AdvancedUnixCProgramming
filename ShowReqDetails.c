#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define MAX_SIZE 128
#define S "Status:"

// Function to display an error message and exit the program
void Error(char* msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(1);
}

int showReqDetails(char* id) {
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
        while (read(fd1, buff, MAX_SIZE) > 0) {
            buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
            line = strtok(buff, "\n"); // Tokenize the buffer to get lines
            while (line != NULL) {
                if (strstr(line, S) == NULL) {
                    printf("%s\n", line); // Print the line if it not contains "Status:"
                }
                line = strtok(NULL, "\n"); // Get the next line
            }
        }
        close(fd1); // Close the file descriptor
    }

    if (fd2 != -1) { // if the file it exists in the Approved directory
        while (read(fd2, buff, MAX_SIZE) > 0) {
            buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
            line = strtok(buff, "\n"); // Tokenize the buffer to get lines
            while (line != NULL) {
                if (strstr(line, S) == NULL) {
                    printf("%s\n", line); // Print the line if it not contains "Status:"
                }
                line = strtok(NULL, "\n"); // Get the next line
            }
        }
        close(fd2); // Close the file descriptor
    }

    if (fd3 != -1) { // if the file it exists in the Approved directory
        while (read(fd3, buff, MAX_SIZE) > 0) {
            buff[MAX_SIZE] = '\0'; // Ensure the buffer is null-terminated
            line = strtok(buff, "\n"); // Tokenize the buffer to get lines
            while (line != NULL) {
                if (strstr(line, S) == NULL) {
                    printf("%s\n", line); // Print the line if it not contains "Status:"
                }
                line = strtok(NULL, "\n"); // Get the next line
            }
        }
        close(fd3); // Close the file descriptor
    }

    // If none of the files were opened successfully, show an error
    if (fd1 == -1 && fd2 == -1 && fd3 == -1) {
        Error("File not found in any directory.");
    }

    return 0; 
}

int main(int argc, char* argv[]) {
    if (argc != 2) Error("Incorrect number of parameters. Usage: program <ID>");
    // Call the function to show request details for the provided ID
    showReqDetails(argv[1]);
    return 0; 
}
