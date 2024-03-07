#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int md5(const char* str);
inline unsigned int padlength(const char* str) { return ((strlen(str)*8 + 512 - 1) / 512) * 512; }

int main(void) {
    
    printf("%d\n", md5("abvdwadwad"));
    
    return 0;
}

unsigned int md5(const char* str) {
    unsigned int length = padlength(str);
    return length;
}

