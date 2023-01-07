#include<iostream>
#include<string>
#include<vector>
using namespace std;
int main(int argc, char** argv){
    string charset = argv[1];
    /*Init CHARSET lookup table*/
    vector<bool> isIn(128,false);
    for(int i = 0 ; i < (int)charset.size() ; i++)
        isIn[charset[i]]=true;
    
    FILE* fileIn = stdin;
    if(argc == 3)
        fileIn = fopen(argv[2],"r");
    if(fileIn == NULL){
        fprintf(stderr,"error\n");
        return 0;
    }
    char c;
    int counter = 0;
    while((c = fgetc(fileIn)) && !feof(fileIn)){
        if(c == '\n'){
            fprintf(stdout,"%d\n",counter);
            counter = 0;
        }
        else if(isIn[c])
            counter++;
    }
    return 0;
}