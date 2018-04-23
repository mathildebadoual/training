#include <stdio.h>

int main(){
    unsigned int x = 0x1234;
    char *c = (char*)&x;
    printf("*c is: 0x%x\n", *c);
    if(*c == 0x34){
        printf("Little endian.");
    }
    else{
        printf("Big endian.");
    }
}
