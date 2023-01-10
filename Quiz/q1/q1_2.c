#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main(){
    int fd1,fd2;
    char buf[3];
    fd1 = open("input.txt", O_RDONLY);
    read(fd1, buf, sizeof(buf));
    write(1, buf, sizeof(buf));

    fd2 = dup(fd1);
    read(fd2, buf, sizeof(buf));
    write(1, buf, sizeof(buf));
}