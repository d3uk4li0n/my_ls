## Task  
A reimplementation of the unix command -- ls and 2 of its flags:  
  -a lists hidden files and directories, that is, files and dirs beginning with a dot (.)      
  -t sort by time modified (most recently modified first) before sorting the operands by lexicographical order  

## Requirements  
Your code must be compiled with -Wall -Wextra -Werror -g3 -fsanitize=address  
You can use:  

malloc(3)  
free(3)  
printf(3)  
write(2)  
stat(2)  
lstat(2)  
opendir(2)  
closedir(2)    
readdir(2)  

You can NOT use:  
Any functions / syscalls which does not appear in the previous list  
Yes, it includes exit  

## Installation  
"make"  
you can clean up after usage with "make fclean"    

## Synopsis  
./my_ls [-at] [dir(s) or file(s) ...]  
examples:  
./my_ls -a .  
./my_ls -t /tmp  
./my_ls -at /tmp /usr  
