#include "ProcessCreator.h"

int main(int argc, char **argv) {
    char *args[] = {"./child.exe", "1", "2", NULL};
    Process_t *proc = CreateNewProcess("./child.exe", args);
    if (!proc) {
        printf("Cannot create child\n");
    }

    int res = EndProcess(proc, 4*1000);
    if (res < 0) {
        printf("ERROR ocurred\n");
    } else if (res == 0) {
        KillProcess(proc);
        printf("Forcefully killed\n");
    } else {
        printf("Child stopped itself\n");
    }

    return 0;
}