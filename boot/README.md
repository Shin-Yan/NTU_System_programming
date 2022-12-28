# Simple bootable program: HelloWorld
## Steps
1. First, compile the assembly code to the img file
```command
$ make
```

2. Second, Using your VM to startup this image file with 
```
type: Other
version: DOS
HDD file type: VDI
Dynamically
```
3. Third, if there are something you want to modify, please modify the HelloWorld2017.asm and use
```command
$ make clean
$ make
```