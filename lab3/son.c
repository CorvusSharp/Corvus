#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
    printf("Вы находитесь в процессе-потомке\n");
	sleep(5);
    return 0;
}

