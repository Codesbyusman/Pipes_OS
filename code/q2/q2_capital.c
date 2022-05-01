#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

// will convert to capital
void capitalizeMe(char[]);

void main()
{

    // the char array reading
    char readMe[200];

    // the file discripter
    int fd;

    // opening the pipe
    fd = open("capitalPipe", O_RDONLY);
    read(fd, readMe, sizeof(readMe)); // writing string to the pipe
    close(fd);                        // closing the pipe

    // finfding vowels in string and printing
    printf("\n\t Entered string is : \f %s \n ", readMe);
    capitalizeMe(readMe);
    printf("\n\t Capitalized string is : \f %s \n ", readMe);
}

// will reverse the string
void capitalizeMe(char string[])
{
    int totalCap = 0; // for counting capital letters

    // traversing inthe string
    for (int i = 0; i < strlen(string); i++)
    {
    	
    	 // count capitals
        if (string[i] >= 'A' && string[i] <= 'Z')
        {
            totalCap++;
        }
        
        //    if small then mapping to capital ascii
        if (string[i] >= 'a' && string[i] <= 'z')
        {
            string[i] -= 32; // going back to the capital letter ascii
        }

        
    }

    printf("\n\t Total Capital Letters are : %d \n", totalCap);
}
