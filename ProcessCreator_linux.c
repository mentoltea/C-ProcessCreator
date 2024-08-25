// #include "ProcessCreator.h"

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    pid_t pid;
} Process_t;

Process_t *CreateNewProcess(const char* filepath, char *argv[]) {
    pid_t pid = fork();
    if (pid < 0) {
        fprintf(stderr, "Cannot fork children\n");
        return NULL;
    } else if (pid == 0) {
        execv(filepath, argv);
        // If here, something gone wrong
        fprintf(stderr, "ERROR: %s", filepath);
        char *it = argv[0];
        int n = 0;
        while (it!=NULL) {
            n += 1;
            fprintf(stderr, " %s", it);
            it = argv[n];
        }
        printf("\n");
        exit(1); 
    }

    Process_t *process = malloc(sizeof(Process_t));
    process->pid = pid;
    return process;
}



int EndProcess(Process_t *process, int durationMs) {
    int duration = durationMs/1000;
    int res;
    if (duration<0) res = waitpid(process->pid, NULL, 0);
    else {
        do {
            res = waitpid(process->pid, NULL, WNOHANG);
            if (res != 0) break;
            sleep(1); duration--;
        } while(duration > 0);
    }
    return res;
}

int KillProcess(Process_t *process) {
    return kill(process->pid, SIGABRT);
}