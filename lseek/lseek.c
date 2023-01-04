#include<fcntl.h>
#include<stdlib.h>

#define FILE_MODE O_RDWR

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(){
    int fd;
    if((fd = creat("file.hole", FILE_MODE))<0)
        perror("create_error");
    if(write(fd, buf1, 10)!= 10)
        perror("buf1 write error");
    if(lseek(fd, 16384, SEEK_SET) == -1)
        perror("lseek error");
    if(write(fd,buf2,10)!=10)
        perror("buf2 write error");

    exit(0);
}