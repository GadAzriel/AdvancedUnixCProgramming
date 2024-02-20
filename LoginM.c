//the three standart includes
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <unistd.h> //for functions such as execv and close.
#include <errno.h> //for perror function
#include <sys/types.h> //open and read
#include <stdbool.h>//using boolean
#include <fcntl.h> //O_RDONLY
#define MAX_LINE_LENGTH 256
#define FILE_PATH "Manager_pass.txt"

int main(int argc, char *argv[]) 
{
    // Check if the correct number of arguments is provided.
    if (argc < 3)
    {
        perror("Bad number of parameters\n");
        return EXIT_FAILURE;
    }

    // Directory path for 'Manager_shell' program
    char line[MAX_LINE_LENGTH]; //for a line
    char *username = argv[1]; char *password = argv[2];
    char *token, *account, *pass, *id, *name;
    int file, res, bytesRead = 0; //res-result of read operation
    // Open the 'Manager_pass.txt' file for read.
    file = open(FILE_PATH, O_RDONLY);
    if (file == -1) {
        perror("Manager_pass open error.");
        return EXIT_FAILURE;
    }

    // Read the file line by line.
    while ((res = read(file, &line[bytesRead], 1)) != 0) {
        if (res < 0) {
            perror("Error reading file");
            return EXIT_FAILURE;
        } else {
            bytesRead += res;

            // Check if the line is complete.
            if (line[bytesRead - 1] == '\n') {
                line[bytesRead] = '\0';

                // Tokenize the line using strtok to extract values.
                token = strtok(line, " \t");
                if (token != NULL) 
                    account = token;
                token = strtok(NULL, " \t");
                if (token != NULL) 
                    pass = token;
                token = strtok(NULL, " \t");
                if (token != NULL) 
                    id = token;
                token = strtok(NULL, " \t\n");
                if (token != NULL) 
                    name = token;
                //check if username is exist
                if (strcmp(account, username) == 0) {
                    //check if password is exist for this username.
                    if (strcmp(pass, password) == 0) {
                        // if its true we need to trasfer the user to the 'Manager_shell' program.
                        close(file);
						execlp("./Manager_shell","Manager_shell",NULL);
             
                    } 
                    else 
                    {
                        printf("Incorrect password!\n");
                        close(file);
                        exit(EXIT_SUCCESS);
                    }
                }
                // Reset the line variable for the next iteration.
                strcpy(line, "");
                bytesRead = 0;
            }
        }
    }
    //if the manager username isn't found
    printf("Manager Not Found!\n");
    close(file);
    exit(EXIT_SUCCESS);
 }
