/*
  ||  file_FD: program to test and demonstrate READ/WRITE flags
  ||
  ||  file_FD: [-i infile] [-m {b|s|d}] [-b bsize] [-n recs]
  ||
  ||  -i infile     input file pathname, default file_input.in
  ||
  ||  -o outfile    output file pahtname, default $TEMPDIR/file_output.out
  ||  
  ||  -m {r|w|b}    file mode: read only for infile, read and write for infile and outfile, and write only for outfile
  ||  Note that if you don't choose any mode, the writing task will fail.
  ||
  ||  -n recs       file write recs           
  ||
  ||  Example:
  ||  ./file_FD -i aaa.txt -o tmp.txt -m b -b 4 -n 10000
  ||
*/

#include<errno.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>

int main(int argc, char** argv){
    char*   tmpdir;
    char*   ofile = NULL;
    char*   ifile = NULL;
    int     oflag = 0;
    int     iflag = 0;
    size_t  bsize = 512;
    void*   buffer;
    int     ifd;
    int     ofd;
    int     info = 0;
    int     c;
    char    inpath[128];
    char    outpath[128];
    int     nwrites = 100;

    oflag = 0;
    while( -1 != (c = getopt(argc,argv,"i:o:s:k:b:n:m")) ){
        switch(c){
            case 'i':{
                ifile = optarg;
                break;
            }
            case 'o':{
                ofile = optarg;
                break;
            }
            case 's':{
                oflag |= O_SYNC;
                break;
            }
            case 'k':{
                oflag |= O_NONBLOCK;
                iflag |= O_NONBLOCK;
                break;
            }
            case 'b':{
                bsize = strtol(optarg, NULL , 0);
                break;
            }
            case 'n':{
                nwrites = strtol(optarg, NULL , 0);
                break;
            }
            case 'm':{
                switch (*optarg){
                    case 'r':
                        iflag |= O_RDONLY;
                        break;
                    case 'w':
                        oflag |= O_WRONLY;
                        break;
                    case 'b': /* -m b read/write for input and output*/
                        iflag |= O_RDWR;
                        oflag |= O_RDWR;
                        break;
                    default:
                        fprintf(stderr,"? -m %c\n", *optarg);
                        return -1;
                }
                break;
            }
            default:
                return -1;
        }   /* end switch */
    }       /* end while */
    if(ifile)
        strcpy(inpath,ifile);
    else{
        char msg[256];
        sprintf(msg,"input file is missing");
        perror(msg);
        return -1;
    }
    if(ofile)
        strcpy(outpath, ofile);
    else{
        tmpdir = getenv("TMPDIR");
        if(!tmpdir)
            tmpdir = "/var/tmp";
        strcpy(outpath,tmpdir);
        strcat(outpath,"/file_output.out");
    }
    /* Open the file for output, truncating or creating it*/
    iflag |= O_EXCL;
    oflag |= O_CREAT | O_TRUNC;
    ofd = open(outpath, oflag, 0644);
    if(-1 == ofd){
        char msg[256];
        sprintf(msg, "open(%s,0x%x,0644)", outpath, oflag);
        perror(msg);
        return -1;
    }

    ifd = open(inpath,iflag);
    if(-1 == ifd){
        char msg[256];
        sprintf(msg, "open(%s,0x%x,0644)", inpath, iflag);
        perror(msg);
        return -1;
    }
    
    printf("File Descriptor for input file %s is %d.\n",inpath, ifd);
    printf("File Descriptor for output file %s is %d.\n",outpath, ofd);

    buffer = malloc(bsize);
    memset(buffer,0,bsize);
    
    read(ifd, buffer, bsize);
    printf("%s, %d times\n",(char*)buffer, nwrites);
    for(int i = 0 ; i < nwrites ;i ++)
        write(ofd,(char*)buffer, bsize);
    close(ifd);
    close(ofd);
    return 0;
}
