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
char * cwd;
int main(int argc, const char * argv[]) {
    FILE * pf;
    char * dir=malloc(sizeof(char)*100);
    cwd =(char *)malloc(sizeof(char)*100);
    bzero(cwd, 100);
    if(getcwd(cwd, sizeof(cwd)) == NULL)
        exit(0);
    int new =0;
    char c;
    bzero(dir, 100);
    strcpy(dir, cwd);
    strcat(dir,"/variables");
    pf=fopen(dir,"r");
    char *val1 = malloc(sizeof(char)*10);
    char *val2 = malloc(sizeof(char)*10);
    bzero(val1, 10);
    do{
        c=fgetc(pf);
        while(c!=EOF&& new==0)
        {
            if(c=='\n')
                new =1;
            c=fgetc(pf);
        }
        if(new !=0&& c==*(argv[0]))
        {
            while(c!=EOF && c!='\n')
            {
                strncat(val1,&c,1);
                c=fgetc(pf);
            }
            new=0;
        }
        else if(new !=0&& c==*(argv[2]))
        {
            while(c!=EOF && c!='\n')
            {
                strncat(val2,&c,1);
                c=fgetc(pf);
            }
            new=0;
        }
        else
            new =0;
        
    }
    while(c!=EOF);
    if(*val1=='\0'&& *val2=='\0')
        printf("not found variable");
    else
    {
        int a;
        int b;
        a=val1[3]-'0';
        b=val2[3]-'0';
        switch (argv[1][0]) {
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
