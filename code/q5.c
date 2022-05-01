#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdbool.h>

char message[200] = " ";
bool quit = false;
bool makeChild = true;

bool clockwise = true; // yes initallay will be true

int main()
{

    pid_t child1, child2, child3, child4, child5;

    // the main chid process
    // all 6true pipes wilm be created here and closed accordingly
    // making file descrypter holders
    int fd[6][2];

    // makig the pipes
    for (int i = 0; i < 6; i++)
    {
        pipe(fd[i]); // making pipes
    }

    // making 6 more pipes for two communication
    // all 6 pipes wilm be created here and closed accordingly
    // making file descrypter holders
    int fdBack[6][2];

    // makig the pipes
    for (int i = 0; i < 6; i++)
    {
        pipe(fdBack[i]); // making pipes
    }

again:
    printf("\n ::::::::::::::::::::::::::::::::::::::::::::: \n");

    // taking input
    printf("\nEnter The message : ");
    scanf("%[^\n]%*c", message);

    // looking if quit entered
    quit = !strcmp(message, "Quit");

    printf("\n ::::::::::::::::::::::::::::::::::::::::::::: \n");

    // making childs accordingly
    if (makeChild)
        child1 = fork();

    if (child1 == 0)
    {

        // making other childs
        // making childs accordingly
        if (makeChild)
            child2 = fork();

        if (child2 == 0)
        {
            // making other childs
            // making childs accordingly
            if (makeChild)
                child3 = fork();

            if (child3 == 0)
            {
                // making other childs
                // making childs accordingly
                if (makeChild)
                    child4 = fork();

                if (child4 == 0)
                {
                    // making other childs
                    // making childs accordingly
                    if (makeChild)
                        child5 = fork();

                    if (child5 == 0)
                    {
                        // making other childs
                        // ------------------------------------------------------------------
                        // -------------------- Child 5 Process --------------------------------
                        // ------------------------------------------------------------------

                        while (!quit)
                        {

                            // closing pipes accordingly
                            // will use pipe 4 and pipe 5
                            close(fd[4][1]); // write block
                            close(fd[5][0]); // read block

                            // the back anticloackwise
                            close(fdBack[4][0]); // read block
                            close(fdBack[5][1]); // write block

                            int defaultRead = dup(0);
                            int defaultWrite = dup(1);

                            // creating copies of standard output and input
                            if (clockwise)
                            {
                                // duplicating
                                dup2(fd[4][0], 0); // reading
                                dup2(fd[5][1], 1); // writing
                            }
                            else
                            {
                                // the reverse
                                // duplicating
                                dup2(fdBack[4][1], 1); // writing
                                dup2(fdBack[5][0], 0); // reading
                            }

                            char buff[200] = " ";
                            // reading the before in pipe
                            scanf("%[^\n]%*c", buff);

                            // writing into the pipe
                            printf("%s : %d\n", buff, getpid());

                            // restoring defaults
                            dup2(defaultRead, 0);
                            dup2(defaultWrite, 1);

                            // printing on screen
                            printf("%s : %d\n", buff, getpid());
                        }
                    }
                    else
                    {
                        // ------------------------------------------------------------------
                        // -------------------- Child 4 Process --------------------------------
                        // ------------------------------------------------------------------
                        while (!quit)
                        {

                            // closing pipes accordingly
                            // will use pipe 3 and pipe 4
                            close(fd[3][1]); // write block
                            close(fd[4][0]); // read block

                            close(fdBack[3][0]); // read block
                            close(fdBack[4][1]); // write block

                            // creating copies of standard output and input
                            int defaultRead = dup(0);
                            int defaultWrite = dup(1);

                            if (clockwise)
                            {
                                // duplicating
                                dup2(fd[3][0], 0); // reading
                                dup2(fd[4][1], 1); // writing
                            }
                            else
                            {
                                dup2(fdBack[3][1], 1); // writing
                                dup2(fdBack[4][0], 0); // reading
                            }

                            char buff[200] = " ";
                            // reading the before in pipe
                            scanf("%[^\n]%*c", buff);

                            // writing into the pipe
                            printf("%s : %d\n", buff, getpid());

                            // restoring defaults
                            dup2(defaultRead, 0);
                            dup2(defaultWrite, 1);

                            // printing on screen
                            printf("%s : %d\n", buff, getpid());
                        }
                    }
                }
                else
                {
                    // ------------------------------------------------------------------
                    // -------------------- Child 3 Process --------------------------------
                    // ------------------------------------------------------------------

                    while (!quit)
                    {

                        // closing pipes accordingly
                        // will use pipe 2 and pipe 3
                        close(fd[2][1]); // write block
                        close(fd[3][0]); // read block

                        close(fdBack[2][0]); // read block
                        close(fdBack[3][1]); // raed block

                        // creating copies of standard output and input
                        int defaultRead = dup(0);
                        int defaultWrite = dup(1);

                        if (clockwise)
                        {
                            // duplicating
                            dup2(fd[2][0], 0); // reading
                            dup2(fd[3][1], 1); // writing
                        }
                        else
                        {                          // duplicating
                            dup2(fdBack[2][1], 1); // writing
                            dup2(fdBack[3][0], 0); // reading
                        }

                        char buff[200] = " ";
                        // reading the before in pipe
                        scanf("%[^\n]%*c", buff);

                        // writing into the pipe
                        printf("%s : %d\n", buff, getpid());

                        // restoring defaults
                        dup2(defaultRead, 0);
                        dup2(defaultWrite, 1);

                        // printing on screen
                        printf("%s : %d\n", buff, getpid());
                    }
                }
            }
            else
            {
                // ------------------------------------------------------------------
                // -------------------- Child 2 Process --------------------------------
                // ------------------------------------------------------------------

                while (!quit)
                {

                    // closing pipes accordingly
                    // will use pipe 1 and pipe 2
                    close(fd[1][1]); // write block
                    close(fd[2][0]); // read block

                    close(fdBack[1][0]); // read block
                    close(fdBack[2][1]); // wrute bloc

                    int defaultRead = dup(0);
                    int defaultWrite = dup(1);

                    // creating copies of standard output and input
                    if (clockwise)
                    {
                        // duplicating
                        dup2(fd[1][0], 0); // reading
                        dup2(fd[2][1], 1); // writing
                    }
                    else
                    {
                        // duplicating
                        dup2(fdBack[1][1], 1); // writing
                        dup2(fdBack[2][0], 0); // reading
                    }

                    char buff[200] = " ";
                    // reading the before in pipe
                    scanf("%[^\n]%*c", buff);

                    // writing into the pipe
                    printf("%s : %d\n", buff, getpid());

                    // restoring defaults
                    dup2(defaultRead, 0);
                    dup2(defaultWrite, 1);

                    // printing on screen
                    printf("%s : %d\n", buff, getpid());
                }
            }
        }
        else
        {
            // ------------------------------------------------------------------
            // -------------------- Child 1 Process --------------------------------
            // ------------------------------------------------------------------

            while (!quit)
            {

                // closing pipes accordingly
                // will use pipe 0 and pipe 1
                close(fd[0][1]); // write block
                close(fd[1][0]); // read block

                close(fdBack[0][0]); // read block
                close(fdBack[1][1]); // write block

                // creating copies of standard output and input
                int defaultRead = dup(0);
                int defaultWrite = dup(1);

                if (clockwise)
                {
                    // duplicating
                    dup2(fd[0][0], 0); // reading
                    dup2(fd[1][1], 1); // writing
                }
                else
                {
                    // duplicating
                    dup2(fdBack[0][1], 1); // reading
                    dup2(fdBack[1][0], 0); // writing
                }
                char buff[200] = " ";
                // reading the before in pipe
                scanf("%[^\n]%*c", buff);

                // writing into the pipe
                printf("%s : %d\n", buff, getpid());

                // restoring defaults
                dup2(defaultRead, 0);
                dup2(defaultWrite, 1);

                // printing on screen
                printf("%s : %d\n", buff, getpid());
            }
        }
    }
    else
    {

        // ------------------------------------------------------------------
        // -------------------- Main Process --------------------------------
        // ------------------------------------------------------------------

        while (!quit)
        {

            // closing the pipes 0 and 5 the 0 will be used by the c1 and 5 by c5
            // pipe 0 write access in parent
            // pipe 5 read  access in parent
            close(fd[0][0]); // read  closed of pipe 0
            close(fd[5][1]); // write closed of pipe 5

            close(fdBack[0][1]); // write block
            close(fdBack[5][0]); // read block

            // looking if quit entered
            quit = !strcmp(message, "Quit");

            // // if quit is entered
            // if (quit)
            // {
            //     return 0;
            // }

            printf("\n%s : %d\n", message, getpid());

            // creating copies of standard output and input
            int defaultRead = dup(0);
            int defaultWrite = dup(1);

            if (clockwise)
            {
                // duplicatin
                dup2(fd[0][1], 1); // standard writing
                dup2(fd[5][0], 0); // standard reading
            }
            else
            {                          // duplicatin
                dup2(fdBack[0][0], 0); // standard reading
                dup2(fdBack[5][1], 1); // standard writing
            }

            // writing into the pipe
            printf("%s : %d\n", message, getpid());

            // a kind of blocking state
            // reading from last child
            if (clockwise)
            {
                char buff[200] = " ";
                // reading the before in pipe
                scanf("%[^\n]%*c", buff);
            }

            // restoring defaults
            dup2(defaultRead, 0);
            dup2(defaultWrite, 1);
            // one loop completed
            makeChild = false;

            // after loop alter
            clockwise = !clockwise;

            goto again;
        }
    }

    return 0;
}