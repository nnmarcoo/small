#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int md5(const char* str);
inline unsigned int padlength(const char* str) { return ((strlen(str) * 8 + 8 + 511) / 512) * 512; } // This is wrong

int main(void) {
    
    printf("%d\n", md5("helloworld"));
    
    return 0;
}

unsigned int md5(const char* str) {
    unsigned int length = padlength(str);
    return length;
}

