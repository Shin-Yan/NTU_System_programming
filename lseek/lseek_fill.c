#include<fcntl.h>
#include<stdlib.h>

#define FILE_MODE O_RDWR

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
char buf3[] = " ";
int main(){
    int fd;
    if((fd = creat("file.fill", FILE_MODE))<0)
        perror("create_error");
    if(write(fd, buf1, 10)!= 10){
        perror("buf1 write error");
        return 0;
    }
    for(int i = 0 ; i < 16374 ; i++)
        if(write(fd, buf3, 1)!=1) perror("buf3 write error");
    if(write(fd,buf2,10)!=10)
        perror("buf2 write error");

    exit(0);
}