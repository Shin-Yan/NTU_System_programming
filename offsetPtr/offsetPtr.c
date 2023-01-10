#include<stdio.h>

int main(){
    FILE* fp = fopen("./test.txt", "r+");

    char c;
    fread( &c, 1, 1, fp);
    // fseek(fp, 0, SEEK_CUR);
    fwrite( &c, 1, 1, fp);

    fclose(fp);
    return 0;
}