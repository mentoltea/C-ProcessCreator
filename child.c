#include <stdio.h>
#include <unistd.h>

void foo(const char* args, ...) {
    printf(args);
}


int main(int argc, char** argv) {
    printf("Hello from child!\n");
    int n=0;
    while (n<7) {
        printf("%d\n", n);
        n++;
        sleep(1);
    }
    
    return 0;
}