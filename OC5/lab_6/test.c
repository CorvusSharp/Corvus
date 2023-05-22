#include <stdio.h>

int main(){
    FILE* f = fopen("test.txt","w");
    if (!f) {
        printf("Son: cant open file %s\n","test.txt");
        exit(1);
    }
    for (int i=0; i < 10000; i++){
        fprintf(f, "%d\n", i); // пишем их в пайп
    }
    close(f);
    return 0;
}
