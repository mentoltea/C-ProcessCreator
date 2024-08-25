#ifndef S7k_PROCESS_CREATOR
#define S7k_PROCESS_CREATOR

#include <stdlib.h>
#include <stdio.h>

typedef void Process_t;

Process_t *CreateNewProcess(const char* filepath, char *argv[]);

// @param duration
// duration to wait in milliseconds. if -1, infinite waiting;
//
// @return
// -1 if error;
// 0 if duration passed, but process did not finish;
// >0 if process finished;
int EndProcess(Process_t *process, int durationMs);

// @return
// 0 on success;
// -1 on error
int KillProcess(Process_t *process);

#endif