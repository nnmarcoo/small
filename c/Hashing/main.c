#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

unsigned int padlength(unsigned int length) { return (((length*8 + 8 + 64 + 512 - 1) / 512) * 512) / 8; }
unsigned int md5(unsigned char* str);
void print(unsigned char* str, unsigned int len);

int main(void) {
    md5("helloworld"); 
    return 0;
}

unsigned int md5(unsigned char* str) {
    unsigned int a = 0x67452301;
    unsigned int b = 0xefcdab89;
    unsigned int c = 0x98badcfe;
    unsigned int d = 0x10325476; 
    
    unsigned int strlength = strlen(str);
    unsigned int blocklength = padlength(strlength);
    unsigned char* paddedstr = (unsigned char*)malloc(blocklength);
    strcpy(paddedstr, str);
    paddedstr[strlength] = 128;
    memset(paddedstr + strlength+1, 0, blocklength - strlength-1);

    
    print(paddedstr, blocklength);

    free(paddedstr);
    return 0;
}

void print(unsigned char *str, unsigned int len) {
    for (unsigned int i = 0; i < len; i++) {
        if (str[i] == 128)
            printf("1");
        else if (str[i] == 0)
            printf("0");
        else
            printf("%c", str[i]);
    }
    printf("\n");
}
