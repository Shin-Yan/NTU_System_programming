# File descriptor and read/write
## Steps
1. First, compile the .c code to binary
```command
$ make
```

2. Second, change the parameter for testing  
```command
-i: input file name
-o: output file name
-m: {r|b|w}: mode (r: read only for input file, w: write only for output file, b: both r/w)
-b: block size for each round
-n: number of rounds to write

ex: ./file_FD -i aaa.txt -o tmp.txt -m b -b 4 -n 10000
```

3. Third, if there are something you want to modify, please modify the syncio.c and use
```command
$ make clean
$ make
```