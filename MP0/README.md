# Example usages
## Read from a file
Suppose a file input.txt with the following content. ‘\n’ indicates the line break character.
```
Ada\n
Grace Hopper\n
Margaret Hamilton\n
```
We count the occurences in any of “abc”.
```command
./char_count abc input.txt
```
Your program should produces the following output.
```
1\n
2\n
3\n
```
Once the INPUT_FILE does not exist or is a directory, our program prints “error\n” to standard error.
```command
./char_count abc a_nonexisting_file.txt
```
the standard error:
```
error\n
```
## Read from *standard input*
You can test this feature by redirection techniques. Note that input.txt is no longer an command argument. It’s comsumed by < redirection symbol.
```command
./char_count abc < input.txt
```
or you can type the input from terminal directly, and end the input by sending ^D (*Ctrl*+D).
```command
./char_count abc
Ada\n
Grace Hopper\n
Margaret Hamilton\n
^D
```
Another scenario making standard input useful is that your program is pipelined. This technique makes it possible that your program consumes from other program’s output. TAs use similar tricks to judge large input case.
```
./TAs_large_text_generator | ./char_count abc
```
## Specify an empty string as CHARSET
You can use single or double quotes to specify an empty argument. Be aware that single quotes and double quotes won’t be parsed in the same way. However, in this case the effect is the same.
```command
# use double quotes
./char_count "" input.txt

# or single quotes
./char_count '' input.txt

# this one is wrong since input.txt is treated as this first argument
# ./char_count input.txt
```