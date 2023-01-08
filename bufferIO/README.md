# bufferIO
## Steps
1. Compile the .c code to binary
```command
$ make
```

2. Use fully buffered IO to write the character in a new file "write.txt", You need to try to modify source code such that when you type this command, and check the write.txt, you will find all file with "@": 
```command
$ ./bufferIO 50
$ cat write.txt
@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ #This situation is correct but you need to type > 256 bytes and get this result.
```

3. If there are something you want to modify, please modify the source files and use
```command
$ make clean
$ make
```