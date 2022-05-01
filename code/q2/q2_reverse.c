#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

// will find the vowel
void reverseMe(char[]);

void main()
{

    // the char array reading
    char readMe[200];
   

    // the file discripter
    int fd;

    // opening the pipe
    fd = open("reversePipe", O_RDONLY);
    read(fd, readMe, sizeof(readMe)); // writing string to the pipe
    close(fd);                        // closing the pipe


    // finfding vowels in string and printing
    printf("\n\t Entered string is : \f %s \n ", readMe);
    reverseMe(readMe);
    printf("\n\t Reversed string is : \f %s \n ", readMe);
    
}

// will reverse the string
void reverseMe(char string[])
{
    // for swapping
    char swap = ' ';

    int end = strlen(string) -1; //the ending
    int start = 0; //the starting
    
    while(start<= end)
    {
        // swapping the start and last element
        swap = string[start];
        string[start] = string[end];
        string[end] = swap;
        start++; //going forward
        end--; //coming back
    }
  
}