#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int md5(const char* str);
inline unsigned int padlength(const char* str) { return ((strlen(str)*8 + 8 + 64 + 511) / 512) * 512; }

int main(void) {
    
    md5("helloworld"); 
    return 0;
}

unsigned int md5(const char* str) {
    unsigned int length = padlength(str);
    char* paddedstr = (char*)malloc(length + 1);
    memset(paddedstr, '0', length);
    paddedstr[length] = '\0';        // Is this necessary?
    printf("%s\n", paddedstr);
    free(paddedstr);
    return 0;
}

