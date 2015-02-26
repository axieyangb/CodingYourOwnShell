//
//
//  calculator
//
//  Created by Yuzhang Hu, Yangyang Xie, Qinyao Xu on 2/10/15.
//
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include<signal.h>
#include <string.h>
char cwd[155];
int main(int argc, const char * argv[]) {
    do{
        FILE * pf;
        char * dir=malloc(sizeof(char)*100);
        if(getcwd(cwd, sizeof(cwd)) == NULL)    //get the current directory
            exit(0);
        int new =0;
        char input = '\0';
        char c;
        bzero(dir, 100);    //empty the directory
        strcpy(dir, cwd);
        int index = 0;
        char *my_argv;
        my_argv=(char *)malloc(40*sizeof(char));
        strcat(dir,"/variables");   //add the file name to the directory
        pf=fopen(dir,"r");
        char *val1 = malloc(sizeof(char)*10);
        char *val2 = malloc(sizeof(char)*10);
        bzero(val1, 10);
        bzero(val2, 10);
        index = 0;
        input = '\0';
        printf("Please input formula in format \"x+y\" (input q to exit):\n");
        while (input!='\n') {   //condition to end input
            input =getchar();
            if (input == 'q') {     //input q to exit
                exit(0);
            }
            my_argv[index++]=input;
        }
        c=fgetc(pf);
        do{
            new=0;
            if(c==(my_argv[0]))     //check if the input character matches the records
            {
                bzero(val1, 10);
                while(c!=EOF && c!='\n')
                {
                    strncat(val1,&c,1);
                    c=fgetc(pf);
                }
            }
            else if(c==(my_argv[2]))
            {
                bzero(val2, 10);
                while(c!=EOF && c!='\n')
                {
                    strncat(val2,&c,1);
                    c=fgetc(pf);
                }
            }
            else{
                while(c!=EOF&& new==0)      //current line no match result, goto next line
                {
                    if(c=='\n')
                        new =1;
                    c=fgetc(pf);
                }
            }
            
        }while(c!=EOF);
        if (strchr("+-*/", my_argv[1])==NULL) { //consider different conditions
            printf("Incorrect format.\n");
        }
        else if (*val1=='\0'&& *val2!='\0') {
            printf("Variable \"%c\" not found.\n",my_argv[0]);
        }
        else if (*val1!='\0'&& *val2=='\0') {
            printf("Variable \"%c\" not found.\n",my_argv[2]);
        }
        else if(*val1=='\0'&& *val2=='\0')
            printf("Variables \"%c\" and \"%c\" not found.\n",my_argv[0],my_argv[2]);
        else
        {
            printf("%s,%s",val1,val2);  //display varialbes and their values
            float a;
            float b;
            val1=val1+2;    //move 2 bits towards right
            val2=val2+2;
            a=atof(val1);   //convert string to float
            b=atof(val2);
            switch (my_argv[1]) {
                case '+':
                    printf("\n%c+%c=%.2f\n",my_argv[0],my_argv[2],a+b); //output the calculation result
                    break;
                case '-':
                    printf("\n%c-%c=%.2f\n",my_argv[0],my_argv[2],a-b);
                    break;
                case '*':
                    printf("\n%c*%c=%.2f\n",my_argv[0],my_argv[2],a*b);
                    break;
                case '/':
                    printf("\n%c/%c=%.2f\n",my_argv[0],my_argv[2],a/b);
                    break;
                    
                default:
                    break;
            }
            bzero(my_argv, sizeof(my_argv));
        }
        fclose(pf);     //close file
    }while (1);
    return 0;
}
