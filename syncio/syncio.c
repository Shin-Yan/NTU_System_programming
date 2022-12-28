/*
  ||  syncio: program to test and demonstrate synchronous I/O.
  ||  
  ||  syncio  [-o outfile] [-m {b|s|d} ] [-b bsize] [-n recs] [-i]
  ||    
  ||  -o outfile    output file pathname, default $TEMPDIR/dirio.out
  ||    
  ||  -m {b|s|d}    file mode: buffered (default), synchronous, or force data synchronization
  ||    
  ||  -b bsize      block size for each write, default 512
  ||    
  ||  -n recs       how many writes to do, default 1000
  ||    
  ||  -i            display info from fcntl(F_DIOINFO)
  ||    
  ||  Example:
  ||  time syncio -o /var/tmp/dout -m -s -b 4096 -n 10000  
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
    char*   tmpdir;         /* -> name string of temp dir */
    char*   ofile = NULL;   /* argument name of file path */
    int     oflag = 0;      /* -m b/s/d result */
    size_t  bsize = 512;    /* blocksize */
    void*   buffer;         /* aligned buffer */
    int     nwrites = 1000; /* number of writes */
    int     ofd;            /* file descriptor from open() */
    int     info = 0;       /* -i option default 0 */
    int     c;              /* scratch var for getopt */
    char    outpath[128];   /* build area for output pathname*/

    oflag = 0;
    while( -1 != (c = getopt(argc,argv,"o:m:b:n:i:k")) ){
        switch(c){
            case 'o':{
                ofile = optarg;
                break;
            }
            case 'k':{
                oflag |= O_NONBLOCK;
                break;
            }
            case 'b':{
                bsize = strtol(optarg, NULL , 0);
                break;
            }
            case 'n':{
                nwrites = strtol(optarg, NULL, 0);
                break;
            }
            case 'i':{
                info = 1;
                break;
            }
            case 'm':{
                switch (*optarg){
                    case 'b':
                        oflag |= O_ASYNC;
                        break;
                    case 's':
                        oflag |= O_SYNC;
                        break;
                    case 'd':
                        oflag |= O_DSYNC;
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

    if(ofile)
        strcpy(outpath, ofile);
    else{
        tmpdir = getenv("TMPDIR");
        if(!tmpdir)
            tmpdir = "/var/tmp";
        strcpy(outpath,tmpdir);
        strcat(outpath,"/dirio.out");
    }
    /* Open the file for output, truncating or creating it*/
    oflag |= O_WRONLY | O_CREAT | O_TRUNC;
    ofd = open(outpath, oflag, 0644);
    if(-1 == ofd){
        char msg[256];
        sprintf(msg, "open(%s,0x%x,0644)", outpath, oflag);
        perror(msg);
        return -1;
    }
    /* Get a buffer aligned the way we need it*/
    buffer = malloc(bsize);
    if(!buffer){
        fprintf(stderr, "could not allocate buffer\n");
        return -5;
    }
    memset(buffer, 0, bsize);
    /* Write the number of records requested as fast as we can. */
    for(c = 0 ; c < nwrites ; ++c){
        memset(buffer, 65 + c%26, bsize);
        if( bsize != (write(ofd, buffer, bsize)) ){
            char msg[80];
            sprintf(msg, "%d th write(%d,buffer,%d)", c+1, ofd, (int) bsize);
            perror(msg);
            break;
        }
    }
    /*To level the playing field, sync the file if not sync'd alreafy. */
    if(0 == (oflag & (O_SYNC|O_DSYNC)))
        fdatasync(ofd);

            free(buffer);
    close(ofd);
    return 0;
}