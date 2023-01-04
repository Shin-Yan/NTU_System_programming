#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>

int main(){

    int fd,fd2;
    int intfromfile, sum = 0 , max = 0, i = 0;
    char readfromfile[10];

    if((fd = open("FileSharing.txt", O_RDONLY))<0) return -1;

    fd2 = dup(fd);
    srand(time(NULL));
    max = 10;
    for(i = 0 ; i < max ; i++){
        if(i%2 == 0){
            if(read(fd,readfromfile,10)<10)
                return -1;
            else
                intfromfile = atoi(readfromfile);
            sum+= intfromfile;
            printf("From fd: sum is %d after reading %d\n", sum, intfromfile);
        }
        else{
            if(read(fd2, readfromfile, 10) <10)
                return -1;
            else
                intfromfile = atoi(readfromfile);
            sum+=intfromfile;
            printf("From fd2:\t\t\t sum is %d after reading %d\n", sum, intfromfile);
        }
    }
    close(fd);
    return 0;
}