#include<fcntl.h>
#include"apue.h"

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";
char buf3[] = " ";
int main(){
    int fd,i;
    if((fd = creat("file.fill", FILE_MODE))<0)
        err_sys("create_error");
    if(write(fd, buf1, 10)!= 10)
        err_sys("buf1 write error");
    for(i = 0 ; i < 16374 ; i++){
        if(write(fd, buf3, 1)!=1) 
            err_sys("buf3 write error");
    }
    if(write(fd,buf2,10)!=10)
        err_sys("buf2 write error");

    exit(0);
}