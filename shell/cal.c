//
//  main.c
//  calculator
//
//  Created by xieyangyang on 2/16/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>
#include <string.h>
char cwd[155];
int main(int argc, const char * argv[]) {
    FILE * pf;
    char * dir=malloc(sizeof(char)*200);
    bzero(dir,200);
    if(getcwd(cwd, sizeof(cwd)) == NULL)
    { printf("COULD NOT");
        exit(0);
    }
    int new =0;
    char input = '\0';
    char c;
    bzero(dir, 100);
    strcpy(dir, cwd);
    //--------------------------------------start
    int index = 0;
    char *my_argv;
    my_argv=(char *)malloc(40*sizeof(char));
    //---------------------------------------end
    strcat(dir,"/variables");
    printf("%s",dir);
    pf=fopen(dir,"r");
    
    char *val1 = malloc(sizeof(char)*10);
    char *val2 = malloc(sizeof(char)*10);
    bzero(val1, 10);
    while (input!='\n') {
        input =getchar();
       my_argv[index++]=input;
    }
    c=fgetc(pf);
    do{
        new=0;
        if(c==(my_argv[0]))
        {
            bzero(val1, sizeof(val1));
            while(c!=EOF && c!='\n')
            {
                strncat(val1,&c,1);
                c=fgetc(pf);
            }
        }
        else if(c==(my_argv[2]))
        {
            bzero(val2, sizeof(val2));
            while(c!=EOF && c!='\n')
            {
                strncat(val2,&c,1);
                c=fgetc(pf);
            }
        }
        else{
            while(c!=EOF&& new==0)
            {
                if(c=='\n')
                    new =1;
                c=fgetc(pf);
            }
        }
        
    }
    while(c!=EOF);
    printf("%s,%s",val1,val2);
    if(*val1=='\0'&& *val2=='\0')
        printf("not found variable");
    else
    {
        int a;
        int b;
        val1=val1+2;
        val2=val2+2;
        printf("%s",val1);
        a=atoi(val1);
        b=atoi(val2);
        switch (my_argv[1]) {
            case '+':
                printf("\n%d",a+b);
                break;
            case '-':
                printf("\n%d",a-b);
                break;
            case '*':
                printf("\n%d",a*b);
                break;
            case '/':
                printf("\n%d",a/b);
                break;
                
            default:
                break;
        }
    }
    return 0;
}
