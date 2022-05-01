#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

// will find the vowel
int findVowels(char[]);

void main()
{
    int vowels = 0;

    // the char array reading
    char readMe[200];
  

    // the file discripter
    int fd;

    // opening the pipe
    fd = open("vowelPipe", O_RDONLY);
    read(fd, readMe, sizeof(readMe)); // writing string to the pipe
    close(fd);                        // closing the pipe



    // finfding vowels in string and printing
    printf("\n\t Entered string is : \f %s \n ", readMe);
    vowels = findVowels(readMe);
    printf("\n\t\t ::: Vowels are : %d ::: \n\n", vowels);
}

// will find and return the vowel
int findVowels(char string[])
{
    int i = 0;     // for the loop
    int vowel = 0; // will count the vowels

    // traverse the whole string
    for (i = 0; i < strlen(string); i++)
    {
        if (string[i] == 'a' || string[i] == 'A' || string[i] == 'e' || string[i] == 'E' || string[i] == 'i' || string[i] == 'I' || string[i] == 'o' || string[i] == 'O' || string[i] == 'u' || string[i] == 'U')
        {
            vowel++; // this is a vowel count it
        }
    }

    return vowel; // returning the vowel
}