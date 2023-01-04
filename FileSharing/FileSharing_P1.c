#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>

int main(){

    int fd;
    int intfromfile, sum = 0 , max = 0, i = 0;
    char readfromfile[10];

    if((fd = open("FileSharing.txt", O_RDONLY))<0) return -1;

    srand(time(NULL));
    max = (rand()%10)+1;
    for(i = 0 ; i < max ; i++){
        if(read(fd,readfromfile,10)<10)
            return -1;
        else
            intfromfile = atoi(readfromfile);
        sum+= intfromfile;
        printf("P1 process : sum is %d after reading %d\n", sum, intfromfile);
        sleep(1);
    }
    printf("P1 process:last number read is %d after reading %d lines, and the sum is %d(%d)\n",intfromfile, max, sum, (1+intfromfile)*max/2);
    close(fd);
    return 0;
}