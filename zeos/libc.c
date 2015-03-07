/*
 * libc.c 
 */

#include <libc.h>

#include <types.h>

int errno;

void itoa(int a, char *b) {
    int i, i1;
    char c;

    if (a==0) { 
        b[0]='0'; b[1]=0; return ;
    }

    i=0;
    while (a>0) {
        b[i]=(a%10)+'0';
        a=a/10;
        i++;
    }

    for (i1=0; i1<i/2; i1++) {
        c=b[i1];
        b[i1]=b[i-i1-1];
        b[i-i1-1]=c;
    }
    b[i]=0;
}

int strlen(char *a) {
    int i;
    
    i=0;
    
    while (a[i]!=0) i++;
    
    return i;
}

/** write syscall wrapper
* int fd : file descriptor
* char * buffer : pointer to the char array    
* int size : # bytes
*
* result : #bytes written if OK, negative otherwise
*/
int write (int fd, char * buffer, int size) {
    
    int result;

    __asm__ __volatile__(
        "int $0x80"
        :"=a" (result)
        :"a"(4),"b"(fd),"c"(buffer),"d"(size)
    );

    if (result < 0) {
        errno = -result;
        result = -1;
    }

    return result;
}

