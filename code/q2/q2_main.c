#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

void main()
{
    // the char array for input
    char inputString[200];
    char buff[30];

    // the file discripter
    int fd, fd1, fd2;

    printf("\n Enter the string : ");
    
    // taking input
    scanf("%[^\n]%*c", inputString);

    // make the pipe with permissions as given
    fd = mkfifo("capitalPipe", 0777);
    fd1 = mkfifo("reversePipe", 0777);
    fd2 = mkfifo("vowelPipe", 0777);

    if (fd < 0 || fd1 < 0 || fd2 < 0)
    {
        printf("\n\t ::::: Error in Pipe Created :::::\n\n");
    }
    else
    {
        // opening  the pipe for writing only
        // writing on each pipes
        fd = open("capitalPipe", O_WRONLY);
        write(fd, inputString, sizeof(inputString)); // writing string to the pipe
        close(fd);                                   // closing the pipe

        fd = open("reversePipe", O_WRONLY);
        write(fd, inputString, sizeof(inputString)); // writing string to the pipe
        close(fd);                                   // closing the pipe

        fd = open("vowelPipe", O_WRONLY);
        write(fd, inputString, sizeof(inputString)); // writing string to the pipe
        close(fd);                                   // closing the pipe
    }
}