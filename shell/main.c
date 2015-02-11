//
//  main.c
//  shell
//
//  Created by xieyangyang on 2/10/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
char c = '\0';
char **my_argv;      // this string array  is used to store the arguments of the commend
// when you press the ctrl+c, you will stop it.
void handle_signal(int signo)
{
    printf("\n[ESC] ");
    fflush(stdout);
}
void seperate_argv(char* tmp)
{
    my_argv=(char **)malloc(8*sizeof(char *));

    int first=0;
        strncat(tmp," ", 1);
    char *foo = tmp;
    int index=0;
    char part[100];
    bzero(part, 100);
    while(*foo !='\0')
    {
        if (index== 9)
            break;
        if(*foo == ' ')
        {
            if(my_argv[index]==NULL)
                my_argv[index] = (char *)malloc(strlen(part)* sizeof(char)+1);
            else
                bzero(my_argv[index], strlen(my_argv[index]));
            strncpy(my_argv[index], part, strlen(part));
            strncat(my_argv[index], "\0", 1);
            bzero(part, 100);
            index++;
            
            
        }
        else
            strncat(part,foo,1);
        foo++;
    }
    
}
void testAvailable(){
    char *dir="/bin/";
    char *path=malloc(strlen(dir)+strlen(my_argv[0])-1);
    strcpy(path,dir);
    strcat(path,my_argv[0]);
    strncat(path, "\0", 1);
   // printf("%s",path);
    if(fork() == 0) {
       // printf("\n%s\n","child");
            execve(path,my_argv,NULL);
    }
    else {
        wait(NULL);//printf("%s\n","parent");
    }
}
void executeCommend(char* tmp)
{
    seperate_argv(tmp);
    int i=0;
   // while(my_argv[i]!=NULL)
   //     printf("%s  ",my_argv[i++]);
    testAvailable();
    
}

int main(int argc, const char **argv, char **envp) {
   	signal(SIGINT, SIG_IGN);
    signal(SIGINT, handle_signal);

    char tmp[100];               // a string to store the whole commend.
    bzero(tmp, 100);

    printf("\n[JERRY_SHELL]:");
    while (c !=EOF) {
        c =getchar();
        if(c!=EOF)
        {
            switch (c) {
                case '\n': /* parse and execute. */
                    executeCommend(tmp);
                    bzero(tmp, sizeof(tmp));
                    printf("\n[JERRY_SHELL]:");
                    break;
                default: strncat(tmp, &c, 1);
                    break;
        }
        }
    }
        printf("%s",tmp);

    printf("\n");
    return 0;

}
