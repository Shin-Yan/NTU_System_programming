# lseek & creating hole
## Steps
1. Compile the .c code to binary
```command
$ make
```

2. Use lseek to generate hole 
```command
$ ./lseek
```

3. check the file.hole
```command
$ vi file.hole  # You will see a lot of NULL bytes within vi tool
:%! xxd         # You will see hex byte by :%! xxd
:q!             # leave the vi
```

4. If there are something you want to modify, please modify the lseek.c and use
```command
$ make clean
$ make
```