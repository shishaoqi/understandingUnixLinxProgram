/* prompting shell verson 1
 * Prompts for the command and its arguments.
 * Builds the argument vector for the call to execvp.
 * Uses execvp(), and never returns.
 */

#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>

#define MAXARGS 20    /* cmdline args */
#define ARGLEN 100    /* token length */

int main()
{
    char *arglist[MAXARGS + 1];     /* an array of ptrs */
    int numargs;                    /* index into array */
    char argbuf[ARGLEN];            /* read stuff here  */
    char *makestring();             /* malloc etc */
    numargs = 0;
    while (numargs < MAXARGS )
    {
        printf("Arg[%d]?", numargs);
        if (fgets(argbuf, ARGLEN, stdin) && *argbuf != '\n')
            arglist[numargs++] = makestring(argbuf);
        else
        {
            if (numargs > 0) {  /* any args? */
                arglist[numargs] = NULL; /* close list */
                execute(arglist);       /* do it */
                numargs = 0;            /* and reset */
            }
        }
    }
    return 0;
}

/*
 * use execvp to do it
 */
int execute(char *arglist[])
{
    execvp(arglist[0], arglist);     /* do it */
    perror("execvp failed");
    exit(1);
}

/*
 * trim off newline and create storage for the string
 */
char *makestring(char *buf)
{
    char *cp;

    buf[strlen(buf) - 1] = '\0';  /* trim newline */
    cp = malloc(strlen(buf) + 1); /* get memory */
    if ( cp == NULL) {
        fprintf(stderr, "no memory\n");
        exit(1);
    }
    strcpy(cp, buf);    /* copy char */
    return cp;          /* return ptr */
}

