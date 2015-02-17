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
#include "main.h"

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



char environment[2][155];       //store the environment variables (PATH AND HOME)
char c = '\0';
char **my_argv;      // this string array  is used to store the arguments of the commend
// when you press the ctrl+c, you will stop it.
char **environ;  //external environement viriables
char cwd[155];
void handle_signal(int signo)
{
    char input=
    printf("\n[Commend terminal, Are you sure?[y/n]] ");
    scanf("%c",&input);
    if(input=='y'|| input=='\n')
    {

        printf("\n[process terminal]\n ");
                exit(0);
    }
    else{
        fflush(stdout);
    }
}
void seperate_argv(char* tmp)
{
    my_argv=(char **)malloc(20*sizeof(char *));

    int first=0;
        strncat(tmp," ", 1);
    char *foo = tmp;
    int index=0;
    char part[100];
    bzero(part, 100);
    while(*foo !='\0')
    {
        if (index== 10)
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
void testAndExecute(){
    char ** inv_path =(char **)malloc(sizeof(char *)*2);
    inv_path[0]=(char *)malloc(strlen(environment[0])*sizeof(char)+1);
    inv_path[1]=(char *)malloc(strlen(environment[1])*sizeof(char)+1);
    strcpy(inv_path[0],environment[0]);
    strncat(inv_path[0], "\0", 1);
    strcpy(inv_path[1],environment[1]);
    strncat(inv_path[1], "\0", 1);
    if(fork() == 0) {
        execve(my_argv[0],&my_argv[0],inv_path);
        printf("%s",inv_path[0]);
        environ=inv_path;
        int i=execvp(my_argv[0], &my_argv[0]);
        if(i<0)
        {
            printf("%s: %s\n", my_argv[0], "command not found");
            exit(1);
        }
         kill(0, SIGKILL);
    }
    else {
        wait(NULL);
    }
}


int preTest(int flag){
    int count=0;
    if (my_argv[1]==NULL || strlen(my_argv[1])==0)
    {
        FILE * pf;
        while(count<strlen(my_argv[0]))
        {
            if(*(my_argv[0])=='$')
            {
                flag =2;
                break;
            }
            
            if(*(my_argv[0]+count++)=='=')
                flag = 1;
        }
        if(flag ==1)
        {
            
            char * dir=malloc(sizeof(char)*100);
            bzero(dir, 100);
            strcpy(dir, cwd);
            strcat(dir,"/variables");
            pf=fopen(dir,"a+");
            fwrite("\n", sizeof(char),1,pf);
            fwrite(my_argv[0], sizeof(char),strlen(my_argv[0]),pf);
            fclose(pf);
            
        }
        if(flag==2)
        {
            char * dir=malloc(sizeof(char)*100);
            int new =0;
            char c;
            bzero(dir, 100);
            strcpy(dir, cwd);
            strcat(dir,"/variables");
             pf=fopen(dir,"r");
            char *val = malloc(sizeof(char)*10);
            bzero(val, 10);
            do{
                c=fgetc(pf);
                while(c!=EOF&& new==0)
                {
                    if(c=='\n')
                    new =1;
                    c=fgetc(pf);
                }
                if(new !=0&& c==*(my_argv[0]+sizeof(char)))
                {
                    while(c!=EOF && c!='\n')
                    {
                    strncat(val,&c,1);
                        c=fgetc(pf);
                    }
                    new=0;
                }
                else
                    new =0;

            }
            while(c!=EOF);
            printf("%s\n\n",val);
        }
        
    }
    return flag;
}



void executeCommend(char* tmp)
{
    int flag =0;
    seperate_argv(tmp);
    if(preTest(flag)==0)
            testAndExecute();
    
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


void readEnv()                          //read the environment vriables from the scripts
{
    int i=0;
    FILE *env;
    if(getcwd(cwd, sizeof(cwd)) == NULL)
        exit(0);
    char * dir=malloc(sizeof(char)*100);
    bzero(dir, 100);
    strcpy(dir, cwd);
    strcat(dir, "/profile");
    env=fopen(dir,"r");
    char line [255];
    if(!env)
    {
        printf("could not find the profile");
        exit(0);
    }
    while(fgets(line ,sizeof line,env)!=NULL)
          {
              strncpy(environment[i++], line, 100);
              bzero(line, 255);
          }
    fclose(env);
}
int main(int argc, const char **argv, char **envp) {
    readEnv();
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
    char *f = "";
    char buf[1024];
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

    printf("%s\n[shell]:",cwd);
    while (c !=EOF) {
        c =getchar();
        if(c!=EOF)
        {
            switch (c) {
                case '\n': /* parse and execute. */
                     //-------------------------------------------start---------------------------------------------
                    while ( !isEmpty(str_stk) ) {
                        char *dest;//store command string
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
                            FILE   *stream;
                            FILE   *wstream;
                            
                            printf("tmp = %s\n",tmp);
                            memset( buf, '\0', sizeof(buf) );//初始化buf,以免后面写如乱码到文件中
                            stream = popen( tmp, "r" ); //将“ls －l”命令的输出 通过管道读取（“r”参数）到FILE* stream
                            //                     wstream = fopen( "test_popen.txt", "w+"); //新建一个可写的文件
                            
                            fread( buf, sizeof(char), sizeof(buf), stream); //将刚刚FILE* stream的数据流读取到buf中
                            //                    fwrite( buf, 1, sizeof(buf), wstream );//将buf中的数据写到FILE    *wstream对应的流中，也是写到文件中
                            //                   *buf = "test_popen.txt";//-------------need to be deleted----------------------------------------------------------------------------------------------
                            pclose( stream );
                            fclose( wstream );
                            
                            //   *f = `cat jlb.sh`;
                            executeCommend(tmp);
                            //   printf("%s",&f);
                            push(tmp_stk, buf);
                            
                            printf("buf = %s\n",buf);
                            
                            bzero(tmp, sizeof(tmp));
                        } else {
                            push(tmp_stk, &dest);
                        }
                        // free(dest);
                    }
                    char *e = (char *)malloc(sizeof(char)*255);
                    bzero(e, 255);
                    while (!isEmpty(tmp_stk)) {
                        top(tmp_stk, &e);
                        strcat(tmp, &e);
                    }
                    
                    //   strncat(tmp, buf, sizeof(buf));
                    
                    printf("last tmp = %s\n",tmp);
                    
                    //--------------------------------------------end--------------------------------------------
                    executeCommend(tmp);
                    printf("executed!!!");
                    bzero(tmp, sizeof(tmp));
                    printf("%s\n[shell]:",cwd);
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
