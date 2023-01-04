# FileSharing
## Steps
1. Compile the .c code to binary
```command
$ make
```

2. Using generate.py to generate FileSharing.txt file
```command
$ python3 generate.py
```

3. You can run the program with
```command
$ ./FileSharing_dup
$ ./FileSharing_P1 & ./FileSharing_P2
$ ./FileSHaring_open
$ ./FileSharing_fopen
```

4. If there are something you want to modify, please modify the lseek.c and use
```command
$ make clean
$ make
```