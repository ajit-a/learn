#include <stdio.h>

int pid;

int main() {
        __asm__(
                "movl $20, %eax    \n"
                "call *%gs:0x10    \n"
                "movl %eax, pid    \n"
        );
        printf("pid is %d\n", pid);
        return 0;
}
