#include <stdio.h>
#include <string.h>
void process(char*str) {
    char buffer[256];
    strcpy(buffer, str);
    printf("Длина строки = %d\n",(int)strlen(buffer));
    return;
}
void main(int argc, char*argv[]) {
    if (argc == 2)
        process(argv[1]);
    else
        printf("Usage: %s some_ string\n", argv[0]);
}
