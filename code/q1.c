#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdlib.h>

int main()
{
    // for making the unnamed pipes
    //  the three pipes
    int fd[2];  // ls
    int fd1[2]; // grep
    int fd2[2]; // sort

    // making the pipe -- will be inherited to child
    pipe(fd);
    pipe(fd1);
    pipe(fd2);

    // making childs
    pid_t pid = fork();

    if (pid == 0)
    {
        // child
        // the ls command
        // closing the read of fd
        close(fd[0]);

        // duplicating the standard writing to directly write on pipe
        dup2(fd[1], 1);

        // the exec command
        execlp("ls", "ls", "-l", "/", NULL);
    }
    else
    {
        // parent
        // wait till child has done
        wait(NULL);

        // child
        // closing the writing of fd in main the ls
        close(fd[1]);

        // duplicating the reading for direct input
        dup2(fd[0], 0);

        // making another child
        pid_t child2 = fork();

        if (child2 == 0)
        {

            // and the fd1 pipe writing will be enabled to write the command in the pipe
            close(fd1[0]); // read close
            dup2(fd1[1], 1);

            execlp("grep", "grep", "a", NULL);
        }

        // parent waiting
        wait(NULL);

        // making another child
        // child
        // closing the writing of fd in main the ls
        close(fd1[1]);

        // duplicating the reading for direct input
        dup2(fd1[0], 0);

         // making another child
        pid_t child3 = fork();

        if (child3 == 0)
        {

            // and the fd1 pipe writing will be enabled to write the command in the pipe
            close(fd2[0]); // read close
            dup2(fd2[1], 1);

            execlp("sort", "sort", "-r", NULL);
        }

        // parent waiting
        wait(NULL);

        // child
        // closing the writing of fd in main the ls
        close(fd2[1]);

        // duplicating the reading for direct input
        dup2(fd2[0], 0);

        pid_t child4 = fork();

        if(child4 == 0)
        {
             // and the fd1 pipe writing will be enabled to write the command in the pipe
            // creating file and will re direct the output to file
            creat("count.txt" , 0666);

            int fdF = open("count.txt" , O_WRONLY);
            // duplicating to this fdF
            dup2(fdF, 1);

            execlp("wc", "wc",  NULL);

        }


    }

    return 0;
}