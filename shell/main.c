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
#include "myStack.h"


//----------------------------------test stack-----------------------------------------------------------------------

//int
//main(int argc, char **argv)
//{
//    Stack int_stk, str_stk;
//    int i;
//    char *names[] = {
//        "C", "C++", "Jave", "C#", "Python",
//        "PHP", "Basic", "Objective C", "Matlab", "Golang"
//    };
//    
//    /* test integer stack */
//    printf("Test integer stack\n");
//    int_stk = stack_create(sizeof(int), NULL);
//    for ( i = 0; i < 10; ++i ) {
//        stack_push(int_stk, &i);
//    }
//    
//    while ( !stack_is_empty(int_stk) ) {
//        int val;
//        stack_top_and_pop(int_stk, &val);
//        printf("%d\n", val);
//    }
//    
//    stack_dispose(int_stk);
//    
//    /* test string stack */
//    printf("Test string stack\n");
//    str_stk = stack_create(sizeof(char *), strfreefn);
//    for ( i = 0; i < 10; ++i ) {
//        char *copy = strdup(names[i]);
//        char *dest;
//        push(str_stk, &copy);
//    }
//    
//    while ( !stack_is_empty(str_stk) ) {
//        char *dest;
//        stack_top_and_pop(str_stk, &dest);
//        printf("%s\n", dest);
//        free(dest);
//    }
//    stack_dispose(str_stk);
//    
//    return 0;
//}


//--------------------------------test stack end here---------------------------------------------------------------




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
//-------------------------------------------start----------------------------------------------------
char *revstr(char *str, size_t len)
{
    
    char    *start = str;
    char    *end = str + len - 1;
    char    ch;
    
    if (str != NULL)
    {
        while (start < end)
        {
            ch = *start;
            *start++ = *end;
            *end-- = ch;
        }
    }
    return str;
}
//-------------------------------------------end-------------------------------------------------

int main(int argc, const char **argv, char **envp) {
   	signal(SIGINT, SIG_IGN);
    signal(SIGINT, handle_signal);

    char tmp[100];               // a string to store the whole commend.
    bzero(tmp, 100);
    
    //-------------------------------------start-----------------------------------------------

//    result = system("pwd");
//    FILE * fp;
//    char buffer[80];
//    fp=popen("pwd","r");
//    fgets(buffer,sizeof(buffer),fp);
//    pclose(fp);
    
    Stack str_stk,tmp_stk;
//    char *names[] = {
//        "C", "C++", "Jave", "C#", "Python",
//        "PHP", "Basic", "Objective C", "Matlab", "Golang"
//    };
    str_stk = initial(sizeof(char *), freeStr);
    tmp_stk = initial(sizeof(char *), freeStr);
//    for ( i = 0; i < 10; ++i ) {
//        char *copy = strdup(names[i]);
//        char *dest;
//        push(str_stk, &copy);
//    }

    //--------------------------------------end----------------------------------------------

    printf("\n[shell]:");
    while (c !=EOF) {
        c =getchar();
        if(c!=EOF)
        {
            switch (c) {
                case '\n': /* parse and execute. */
                     //-------------------------------------------start---------------------------------------------
                    while ( !isEmpty(str_stk) ) {
                        char *dest;
                        char *d = "";
                        char *p1 = "(";
                        char *p2 = ")";
                        top(str_stk, &dest);
                        if (strcmp(&dest, p1)==0) {
                            top(tmp_stk, &d);
                            while ((!isEmpty(tmp_stk)) && strcmp(&d, p2)!=0) {
                                strncat(tmp, &d, 1);
                                top(tmp_stk, &d);
                            }
                            executeCommend(tmp);
                            bzero(tmp, sizeof(tmp));
                        } else {
                            push(tmp_stk, &dest);
                        }
                       // free(dest);
                    }
                     //--------------------------------------------end--------------------------------------------
                    
//                    executeCommend(tmp);
//                    bzero(tmp, sizeof(tmp));
                    printf("\n[shell]:");
                    break;
                default: {
                    //strncat(tmp, &c, 1);
                    push(str_stk, &c);
                }
                    break;
            }
        }
    }
        printf("%s",tmp);

    printf("\n");
    return 0;

}
