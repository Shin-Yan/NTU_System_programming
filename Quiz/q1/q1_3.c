#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include <sys/wait.h>
int main(){
    int fd;
    pid_t pid;
    char buf[3];
    pid = fork();
    fd = open("input.txt", O_RDONLY);
    if(pid == 0){
        read(fd, buf, sizeof(buf));
        write(1, buf, sizeof(buf));
    }
    else{
        int status;
        wait(&status);
        read(fd, buf, sizeof(buf));
        write(1, buf, sizeof(buf));
    }
}