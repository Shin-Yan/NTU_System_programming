# fileflags
## Steps
1. Compile the .c code to binary
```command
$ make
```

2. Use fileflags to observe the flags of correspond file descriptor file, for example: 
```command
$ ./fileflags 0 < /dev/tty
read only
$ ./fileflags > temp.foo
$ cat temp.foo
write only
$ ./fileflags 2 2>>temp.foo
write only, append
$ ./fileflags 5 5<>temp.foo
read write
```

3. If there are something you want to modify, please modify the source files and use
```command
$ make clean
$ make
```