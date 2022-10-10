#include <tsh.h>
#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <sys/wait.h>

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
    // TODO: tokenize the command string into arguments
    /*
    int token_index = 0;
    char* acc_token;
    char* cur_token_index = *cmdTokens;
    cout << *cmd << endl;
    cmd++;
    if (*cmd == '\n') {
        cout << "here";
    }
    cout << int(*cmd) << endl;
    */

   
    char* acc_token;
    string acc_string;
    int cmd_count = 0;
    while (*cmd != NULL) {
        if (*cmd == ' ' || *cmd == '\n') {
            acc_token = (char*) malloc((acc_string.length() + 1) * sizeof(char));
            //calling c_str to make sure the null termination is good
            strcpy(acc_token, acc_string.c_str());
            acc_string = "";
            *cmdTokens = acc_token;
            cmdTokens++;
            if (*cmd == '\n') {
                cmdTokens[cmd_count] = (char*) NULL;
                return;
            }
            cmd_count++;
            cmd++;
        }
        else {
            acc_string += *cmd;
            cmd++;
        }
    }
}

void simple_shell::exec_command(char** argv) {
    // TODO: fork a child process to execute the command.
    // parent process should wait for the child process to complete and reap it
    int pid = fork();
    if (pid < 0) {
        cout << "error in fork in exec_command";
    }
    //in child
    if (pid == 0) {
        execvp(*argv, argv);
    }
    //parent
    else {
        wait(NULL);
        return;
    }
}

bool simple_shell::isQuit(char* cmd) {
    // TODO: check for the command "quit" that terminates the shell
    return (strcmp(cmd, "quit") == 0);
}
