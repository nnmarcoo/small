#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int md5(const char* str);
inline unsigned int padlength(unsigned int length) { return (((length*8 + 8 + 64 + 511) / 512) * 512) / 8; }

int main(void) {
    
    md5("helloworld"); 
    return 0;
}

unsigned int md5(const char* str) {
    unsigned int strlength = strlen(str);
    unsigned int blocklength = padlength(strlength);
    char* paddedstr = (char*)malloc(blocklength + 1);

    strcpy(paddedstr, str);
    paddedstr[strlength] = '1';
    memset(paddedstr + strlength+1, '0', blocklength - strlength-1); 
    paddedstr[blocklength] = '\0';  // Is this necessary?

    printf("%s\n", paddedstr);
    free(paddedstr);
    return 0;
}

