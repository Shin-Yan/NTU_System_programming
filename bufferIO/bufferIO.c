#include<stdio.h>
#include<stdlib.h>
void write_file(FILE *fp,int size){
    int i;
    char buffer[] = {'@'};
    char iobuf[256];
    setvbuf(fp, iobuf, _IOFBF, 256);

    for(int i = 0 ; i < size ; i++) fwrite(buffer,1,1,fp);
}

int main(int argc, char** argv){
    FILE* fp = fopen("./write.txt","w+");
    if(argc != 2){
        printf("./usage: ./bufferIO <write file size>\n");
        exit(-1);
    }
    int count = atoi(argv[1]);
    write_file(fp,count);
    fclose(fp);
    return 0;
}