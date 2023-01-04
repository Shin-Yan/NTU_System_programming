#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<time.h>

int main(){

    pid_t pid;
    FILE* fileobj;
    int intfromfile, sum = 0 , max = 0, i = 0;

    if((fileobj = fopen("FileSharing.txt", "r")) == NULL) return -1;
    setvbuf(fileobj, (char*)NULL, _IONBF, 0);
    
    pid = fork();
    if(pid == -1)   printf("Fail to fork processes.\n");
    srand(time(NULL));
    
    if(pid == 0) { /*child*/
        max = (rand()%10)+1;
        for(i = 0 ; i < max ; i++){
            if(fscanf(fileobj, "%d\n", &intfromfile)==0){
                printf("fscanf error.\n");
                break;
            }
            sum+= intfromfile;
            printf("Child process : sum is %d after reading %d\n", sum, intfromfile);
            usleep(10);
        }
        printf("child: last number read is %d after reading %d lines, and the sum is %d(%d)\n",intfromfile, max, sum, (1+intfromfile)*max/2);
        fclose(fileobj);
    }
    else { /*parent*/
        max = (rand()%30)+1;
        for(i = 0 ; i < max ; i++){
            if(fscanf(fileobj, "%d\n", &intfromfile)==0){
                printf("fscanf error.\n");
                break;
            }
            sum+= intfromfile;
            printf("Parent process :\t\t\t sum is %d after reading %d\n", sum, intfromfile);
            usleep(10);
        }
        printf("parent: last number read is %d after reading %d lines, and the sum is %d(%d)\n",intfromfile, max, sum, (1+intfromfile)*max/2);
        fclose(fileobj);
    }
    return 0;
}