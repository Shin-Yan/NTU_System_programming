# lseek & creating hole
## Steps
1. Compile the .c code to binary
```command
$ make
```

2. Use lseek to generate hole or fill with " " 
```command
$ ./lseek_hole
$ ./lseek_fill
```

3. check the file.hole and file.fill
```command
$ vi file.hole  # You will see a lot of NULL bytes within vi tool
:%! xxd         # You will see hex byte by :%! xxd
:q!             # leave the vi
$ vi file.fill  # You will see a lot of NULL bytes within vi tool
:%! xxd         # You will see hex byte by :%! xxd
:q!             # leave the vi
```

4. If there are something you want to modify, please modify the source files and use
```command
$ make clean
$ make
```