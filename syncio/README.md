# Sync mode vs Buffer mode
## Steps
1. First, compile the .c code to binary
```command
$ make
```

2. Second, change the parameter for testing  
```command
-o: output file name
-m: {b|s|d}: mode (b means buffer mode, s means synchronous mode, d means data type synchronous)
-b: block size for each round
-n: number of rounds to write
-i: display info from fcntl(F_DIOINFO)

using time command to see the detail execution time
ex: time syncio -o foo.out -b 4096 -n 10000 -m b
```
3. Third, if there are something you want to modify, please modify the syncio.c and use
```command
$ make clean
$ make
```