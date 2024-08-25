#include <sys/types.h>
#include <unistd.h>

#include <windows.h>

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    HANDLE hProcess;
} Process_t;

Process_t *CreateNewProcess(const char* filepath, char *argv[]) {
    char buffer[1024];
    char *it = argv[0];
    int n = 0;
    while (it!=NULL) {
        n += 1;
        snprintf(buffer, 1024, "%s ", it);
        it = argv[n];
    }
    STARTUPINFO siStartInfo;
    ZeroMemory(&siStartInfo, sizeof(siStartInfo));
    siStartInfo.cb = sizeof(STARTUPINFO);
    siStartInfo.hStdError = GetStdHandle(STD_ERROR_HANDLE);
    siStartInfo.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    siStartInfo.hStdInput = GetStdHandle(STD_INPUT_HANDLE);
    siStartInfo.dwFlags |= STARTF_USESTDHANDLES;

    PROCESS_INFORMATION piProcInfo;
    ZeroMemory(&piProcInfo, sizeof(PROCESS_INFORMATION));
    
    CreateProcessA(filepath, buffer, NULL, NULL, TRUE, 0, NULL, NULL, &siStartInfo, &piProcInfo);

    Process_t *process = malloc(sizeof(Process_t));
    process->hProcess = piProcInfo.hProcess;
    return process;
}

int EndProcess(Process_t *process, int durationMs) {
    int res;
    if (durationMs==-1) res = WaitForSingleObject(process->hProcess, INFINITE);
    else res = WaitForSingleObject(process->hProcess, durationMs);

    switch (res) {
    case WAIT_OBJECT_0:
        return 1;
    case WAIT_TIMEOUT:
        return 0;
    case WAIT_ABANDONED:
    case WAIT_FAILED:
    default:
        return -1;
    }
}


int KillProcess(Process_t *process) {
    if (TerminateProcess(process->hProcess, 1) == 0) return -1;
    return 0;
}