#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <stdlib.h>


int main()
{
    bool makeChild = true;
    bool askAgain = false;

    // for holding the times
    char timeSlot[10] = " ";

    char checkBy[10] = "ok";

    // making the pipes 10 unmed pipes for the time giving to employees
    int fdTime[10][2];

    // making 10 unmmed pipes
    for (int i = 0; i < 10; i++)
    {
        // making pipes
        pipe(fdTime[i]);
    }

    // making the pipes 10 unmed pipes for the employee response
    int fdResponse[10][2];

    // making 10 more unmmed pipes
    for (int i = 0; i < 10; i++)
    {
        // making pipes
        pipe(fdResponse[i]);
    }

    //------------------------------------
    // making childs 10 of a parent
    pid_t child[10];

doAgain:

    askAgain = false;

    // will use 1 for the writing date and other for taking the response
    // main as the owner and child as employees
    // taking the input from the onwer
    printf("\n ::::::::::::::::::: Owner ::::::::::::::::::: \n");

    // taking input
    printf("\n Enter The meeting time : ");
    scanf("%[^\n]%*c", timeSlot);

    printf("\n\t The Metting Time is : %s \n", timeSlot);
    printf("\n ::::::::::::::::::::::::::::::::::::::::::::: \n");

    printf("\n :::::::::::::::: Employees :::::::::::::::::: \n");
    printf("\n\t The Metting Time is : %s \n", timeSlot);
    printf("\n ::::::::::::::::::::::::::::::::::::::::::::: \n\n");

    // writing in the pipes
    write(fdTime[0][1], timeSlot, sizeof(timeSlot));

    if (makeChild)
        child[0] = fork();

    if (child[0] == 0)
    {
        // the first child
        // closing the reading ends on response pipe and writing on time pipe
        for (int i = 0; i < 10; i++)
        {
            close(fdResponse[i][0]);
            close(fdTime[i][1]);
        }

        // iterate till ok is not send by parent
        while (strcmp(timeSlot, "ok"))
        {

            char timeslot[10] = " ";
            // reading time from the pipe

            read(fdTime[0][0], timeSlot, sizeof(timeSlot));

            // take response if ok was not there
            if (strcmp(timeSlot, "ok"))
            {

                // asking response from the employee and writing on response time
                // the input
                char inputResponse[2];

                // for making pipes
                // child
                do
                {
                    // taking response of the employee
                    printf("\n Employee 1 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                    scanf("%c", inputResponse);

                    // removing the input buffer ... same as cin.ignore
                    while ((getchar()) != '\n')
                        ;

                    // validating and not accepting other characters
                } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                inputResponse[1] = '\0';

                // writing response to pipe
                write(fdResponse[0][1], inputResponse, sizeof(inputResponse));
            }
        }
    }
    else
    {
        char buff[2];
        read(fdResponse[0][0], buff, sizeof(buff));

        if (buff[0] == 'n' || buff[0] == 'N')
        {
            askAgain = true;
        }

        // writing in the pipes
        write(fdTime[1][1], timeSlot, sizeof(timeSlot));

        if (makeChild)
            child[1] = fork();

        if (child[1] == 0)
        {
            // the first child
            // closing the reading ends on response pipe and writing on time pipe
            for (int i = 0; i < 10; i++)
            {
                close(fdResponse[i][0]);
                close(fdTime[i][1]);
            }
            // iterate till ok is not send by parent
            while (strcmp(timeSlot, "ok"))
            {
                char timeslot[10] = " ";
                // reading time from the pipe

                read(fdTime[1][0], timeSlot, sizeof(timeSlot));

                // take response if ok was not there
                if (strcmp(timeSlot, "ok"))
                {
                    // asking response from the employee and writing on response time
                    // the input
                    char inputResponse[2];

                    // for making pipes
                    // child
                    do
                    {
                        // taking response of the employee
                        printf("\n Employee 2 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                        scanf("%c", inputResponse);

                        // removing the input buffer ... same as cin.ignore
                        while ((getchar()) != '\n')
                            ;

                        // validating and not accepting other characters
                    } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                    inputResponse[1] = '\0';

                    // writing response to pipe
                    write(fdResponse[1][1], inputResponse, sizeof(inputResponse));
                }
            }
        }
        else
        {
            char buff[2];
            read(fdResponse[1][0], buff, sizeof(buff));

            if (buff[0] == 'n' || buff[0] == 'N')
            {
                askAgain = true;
            }

            // writing in the pipes
            write(fdTime[2][1], timeSlot, sizeof(timeSlot));

            if (makeChild)
                child[2] = fork();

            if (child[2] == 0)
            {
                // the first child
                // closing the reading ends on response pipe and writing on time pipe
                for (int i = 0; i < 10; i++)
                {
                    close(fdResponse[i][0]);
                    close(fdTime[i][1]);
                }

                // iterate till ok is not send by parent
                while (strcmp(timeSlot, "ok"))
                {
                    char timeslot[10] = " ";
                    // reading time from the pipe

                    read(fdTime[2][0], timeSlot, sizeof(timeSlot));

                    // take response if ok was not there
                    if (strcmp(timeSlot, "ok"))
                    {
                        // asking response from the employee and writing on response time
                        // the input
                        char inputResponse[2];

                        // for making pipes
                        // child
                        do
                        {
                            // taking response of the employee
                            printf("\n Employee 3 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                            scanf("%c", inputResponse);

                            // removing the input buffer ... same as cin.ignore
                            while ((getchar()) != '\n')
                                ;

                            // validating and not accepting other characters
                        } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                        inputResponse[1] = '\0';

                        // writing response to pipe
                        write(fdResponse[2][1], inputResponse, sizeof(inputResponse));
                    }
                }
            }
            else
            {
                char buff[2];
                read(fdResponse[2][0], buff, sizeof(buff));

                if (buff[0] == 'n' || buff[0] == 'N')
                {
                    askAgain = true;
                }

                // writing in the pipes
                write(fdTime[3][1], timeSlot, sizeof(timeSlot));

                if (makeChild)
                    child[3] = fork();

                if (child[3] == 0)
                {
                    // the first child
                    // closing the reading ends on response pipe and writing on time pipe
                    for (int i = 0; i < 10; i++)
                    {
                        close(fdResponse[i][0]);
                        close(fdTime[i][1]);
                    }

                    // iterate till ok is not send by parent
                    while (strcmp(timeSlot, "ok"))
                    {
                        char timeslot[10] = " ";
                        // reading time from the pipe

                        read(fdTime[3][0], timeSlot, sizeof(timeSlot));

                        // take response if ok was not there
                        if (strcmp(timeSlot, "ok"))
                        {
                            // asking response from the employee and writing on response time
                            // the input
                            char inputResponse[2];

                            // for making pipes
                            // child
                            do
                            {
                                // taking response of the employee
                                printf("\n Employee 4 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                scanf("%c", inputResponse);

                                // removing the input buffer ... same as cin.ignore
                                while ((getchar()) != '\n')
                                    ;

                                // validating and not accepting other characters
                            } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                            inputResponse[1] = '\0';

                            // writing response to pipe
                            write(fdResponse[3][1], inputResponse, sizeof(inputResponse));
                        }
                    }
                }
                else
                {

                    char buff[2];
                    read(fdResponse[3][0], buff, sizeof(buff));

                    if (buff[0] == 'n' || buff[0] == 'N')
                    {
                        askAgain = true;
                    }

                    // writing in the pipes
                    write(fdTime[4][1], timeSlot, sizeof(timeSlot));

                    if (makeChild)
                        child[4] = fork();

                    if (child[4] == 0)
                    {
                        // the first child
                        // closing the reading ends on response pipe and writing on time pipe
                        for (int i = 0; i < 10; i++)
                        {
                            close(fdResponse[i][0]);
                            close(fdTime[i][1]);
                        }

                        // iterate till ok is not send by parent
                        while (strcmp(timeSlot, "ok"))
                        {

                            char timeslot[10] = " ";
                            // reading time from the pipe
                            read(fdTime[4][0], timeSlot, sizeof(timeSlot));

                            // take response if ok was not there
                            if (strcmp(timeSlot, "ok"))
                            {

                                // asking response from the employee and writing on response time
                                // the input
                                char inputResponse[2];

                                // for making pipes
                                // child
                                do
                                {
                                    // taking response of the employee
                                    printf("\n Employee 5 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                    scanf("%c", inputResponse);

                                    // removing the input buffer ... same as cin.ignore
                                    while ((getchar()) != '\n')
                                        ;

                                    // validating and not accepting other characters
                                } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                                inputResponse[1] = '\0';

                                // writing response to pipe
                                write(fdResponse[4][1], inputResponse, sizeof(inputResponse));
                            }
                        }
                    }
                    else
                    {
                        char buff[2];
                        read(fdResponse[4][0], buff, sizeof(buff));

                        if (buff[0] == 'n' || buff[0] == 'N')
                        {
                            askAgain = true;
                        }

                        // writing in the pipes
                        write(fdTime[5][1], timeSlot, sizeof(timeSlot));

                        if (makeChild)
                            child[5] = fork();

                        if (child[5] == 0)
                        {
                            // the first child
                            // closing the reading ends on response pipe and writing on time pipe
                            for (int i = 0; i < 10; i++)
                            {
                                close(fdResponse[i][0]);
                                close(fdTime[i][1]);
                            }

                            // iterate till ok is not send by parent
                            while (strcmp(timeSlot, "ok"))
                            {
                                char timeslot[10] = " ";
                                // reading time from the pipe

                                read(fdTime[5][0], timeSlot, sizeof(timeSlot));

                                // take response if ok was not there
                                if (strcmp(timeSlot, "ok"))
                                {
                                    // asking response from the employee and writing on response time
                                    // the input
                                    char inputResponse[2];

                                    // for making pipes
                                    // child
                                    do
                                    {
                                        // taking response of the employee
                                        printf("\n Employee 6 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                        scanf("%c", inputResponse);

                                        // removing the input buffer ... same as cin.ignore
                                        while ((getchar()) != '\n')
                                            ;

                                        // validating and not accepting other characters
                                    } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                                    inputResponse[1] = '\0';

                                    // writing response to pipe
                                    write(fdResponse[5][1], inputResponse, sizeof(inputResponse));
                                }
                            }
                        }
                        else
                        {
                            char buff[2];
                            read(fdResponse[5][0], buff, sizeof(buff));

                            if (buff[0] == 'n' || buff[0] == 'N')
                            {
                                askAgain = true;
                            }

                            // writing in the pipes
                            write(fdTime[6][1], timeSlot, sizeof(timeSlot));

                            if (makeChild)
                                child[6] = fork();

                            if (child[6] == 0)
                            {
                                // the first child
                                // closing the reading ends on response pipe and writing on time pipe
                                for (int i = 0; i < 10; i++)
                                {
                                    close(fdResponse[i][0]);
                                    close(fdTime[i][1]);
                                }

                                // iterate till ok is not send by parent
                                while (strcmp(timeSlot, "ok"))
                                {
                                    char timeslot[10] = " ";
                                    // reading time from the pipe

                                    read(fdTime[6][0], timeSlot, sizeof(timeSlot));

                                    // take response if ok was not there
                                    if (strcmp(timeSlot, "ok"))
                                    {
                                        // asking response from the employee and writing on response time
                                        // the input
                                        char inputResponse[2];

                                        // for making pipes
                                        // child
                                        do
                                        {
                                            // taking response of the employee
                                            printf("\n Employee 7 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                            scanf("%c", inputResponse);

                                            // removing the input buffer ... same as cin.ignore
                                            while ((getchar()) != '\n')
                                                ;

                                            // validating and not accepting other characters
                                        } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                                        inputResponse[1] = '\0';

                                        // writing response to pipe
                                        write(fdResponse[6][1], inputResponse, sizeof(inputResponse));
                                    }
                                }
                            }
                            else
                            {
                                char buff[2];
                                read(fdResponse[6][0], buff, sizeof(buff));

                                if (buff[0] == 'n' || buff[0] == 'N')
                                {
                                    askAgain = true;
                                }

                                // writing in the pipes
                                write(fdTime[7][1], timeSlot, sizeof(timeSlot));

                                if (makeChild)
                                    child[7] = fork();

                                if (child[7] == 0)
                                {
                                    // the first child
                                    // closing the reading ends on response pipe and writing on time pipe
                                    for (int i = 0; i < 10; i++)
                                    {
                                        close(fdResponse[i][0]);
                                        close(fdTime[i][1]);
                                    }

                                    // iterate till ok is not send by parent
                                    while (strcmp(timeSlot, "ok"))
                                    {

                                        char timeslot[10] = " ";
                                        // reading time from the pipe

                                        read(fdTime[7][0], timeSlot, sizeof(timeSlot));

                                        // take response if ok was not there
                                        if (strcmp(timeSlot, "ok"))
                                        {
                                            // asking response from the employee and writing on response time
                                            // the input
                                            char inputResponse[2];

                                            // for making pipes
                                            // child
                                            do
                                            {
                                                // taking response of the employee
                                                printf("\n Employee 8 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                                scanf("%c", inputResponse);

                                                // removing the input buffer ... same as cin.ignore
                                                while ((getchar()) != '\n')
                                                    ;

                                                // validating and not accepting other characters
                                            } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                                            inputResponse[1] = '\0';

                                            // writing response to pipe
                                            write(fdResponse[7][1], inputResponse, sizeof(inputResponse));
                                        }
                                    }
                                }
                                else
                                {
                                    char buff[2];
                                    read(fdResponse[7][0], buff, sizeof(buff));

                                    if (buff[0] == 'n' || buff[0] == 'N')
                                    {
                                        askAgain = true;
                                    }

                                    // writing in the pipes
                                    write(fdTime[8][1], timeSlot, sizeof(timeSlot));

                                    if (makeChild)
                                        child[8] = fork();

                                    if (child[8] == 0)
                                    {
                                        // the first child
                                        // closing the reading ends on response pipe and writing on time pipe
                                        for (int i = 0; i < 10; i++)
                                        {
                                            close(fdResponse[i][0]);
                                            close(fdTime[i][1]);
                                        }

                                        // iterate till ok is not send by parent
                                        while (strcmp(timeSlot, "ok"))
                                        {
                                            char timeslot[10] = " ";
                                            // reading time from the pipe

                                            read(fdTime[8][0], timeSlot, sizeof(timeSlot));

                                            // take response if ok was not there
                                            if (strcmp(timeSlot, "ok"))
                                            {
                                                // asking response from the employee and writing on response time
                                                // the input
                                                char inputResponse[2];

                                                // for making pipes
                                                // child
                                                do
                                                {
                                                    // taking response of the employee
                                                    printf("\n Employee 9 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                                    scanf("%c", inputResponse);

                                                    // removing the input buffer ... same as cin.ignore
                                                    while ((getchar()) != '\n')
                                                        ;

                                                    // validating and not accepting other characters
                                                } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                                                inputResponse[1] = '\0';

                                                // writing response to pipe
                                                write(fdResponse[8][1], inputResponse, sizeof(inputResponse));
                                            }
                                        }
                                    }
                                    else
                                    {
                                        char buff[2];
                                        read(fdResponse[8][0], buff, sizeof(buff));

                                        if (buff[0] == 'n' || buff[0] == 'N')
                                        {
                                            askAgain = true;
                                        }

                                        // writing in the pipes
                                        write(fdTime[9][1], timeSlot, sizeof(timeSlot));

                                        if (makeChild)
                                            child[9] = fork();

                                        if (child[9] == 0)
                                        {
                                            // the first child
                                            // closing the reading ends on response pipe and writing on time pipe
                                            for (int i = 0; i < 10; i++)
                                            {
                                                close(fdResponse[i][0]);
                                                close(fdTime[i][1]);
                                            }

                                            // iterate till ok is not send by parent
                                            while (strcmp(timeSlot, "ok"))
                                            {
                                                char timeslot[10] = " ";
                                                // reading time from the pipe

                                                read(fdTime[9][0], timeSlot, sizeof(timeSlot));

                                                // take response if ok was not there
                                                if (strcmp(timeSlot, "ok"))
                                                {

                                                    // asking response from the employee and writing on response time
                                                    // the input
                                                    char inputResponse[2];

                                                    // for making pipes
                                                    // child
                                                    do
                                                    {
                                                        // taking response of the employee
                                                        printf("\n Employee 10 :- Are you available at the ( %s ) time slot :- (Y/N) : ", timeSlot);
                                                        scanf("%c", inputResponse);

                                                        // removing the input buffer ... same as cin.ignore
                                                        while ((getchar()) != '\n')
                                                            ;

                                                        // validating and not accepting other characters
                                                    } while (!(inputResponse[0] == 'y' || inputResponse[0] == 'Y' || inputResponse[0] == 'n' || inputResponse[0] == 'N'));

                                                    inputResponse[1] = '\0';

                                                    // writing response to pipe
                                                    write(fdResponse[9][1], inputResponse, sizeof(inputResponse));
                                                }
                                            }
                                        }
                                        else
                                        {
                                            char buff[2];
                                            read(fdResponse[9][0], buff, sizeof(buff));

                                            if (buff[0] == 'n' || buff[0] == 'N')
                                            {
                                                askAgain = true;
                                            }

                                            if (askAgain)
                                            {
                                                printf("\n\n\t ::::::::::::: Time not selected :::::::::::::::::::::: \n\n");
                                                sleep(1);
                                                system("clear");

                                                printf("\n\n\t ::::::::::::::::: Again ::::::::::::::::::::: \n\n");

                                                makeChild = false;
                                                goto doAgain;
                                            }
                                            else
                                            {
                                                // for the termination of childs
                                                for (int i = 0; i < 10; i++)
                                                {
                                                    char buff[10] = "ok";
                                                    write(fdTime[i][1], "ok", sizeof(buff));
                                                }

                                                // also displaying the time
                                                printf("\n\n ::::::::::::::::::::::::::::::::::::::::::::: \n");
                                                printf("\n\t The Metting Time is : %s  \n", timeSlot);
                                                printf("\n ::::::::::::::: Confirmed ::::::::::::::::::: ");
                                                printf("\n ::::::::::::: See You There ::::::::::::::::: ");
                                                printf("\n ::::::::::::::::::::::::::::::::::::::::::::: \n");

                                                printf("\n ::::::::::::::::::::::::::::::::::::::::::::: \n\n");
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0;
}