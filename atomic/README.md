# Atomic operation: lseek and write
## Steps
1. Compile the .c code to binary
```command
$ make
```

2. You can run the program with
```command
$ ./atomic_append f3 1000000 & ./atomic_append f3 1000000
$ ./atomic_append f4 1000000 x & ./atomic_append f4 1000000 x
```

3. Observe the file size with command
```command
$ ls -ls f*
```

4. If there are something you want to modify, please modify the atomic_append.c and use
```command
$ make clean
$ make
```