//
//  main.h
//  shell
//
//  Created by xieyangyang on 2/16/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//

#ifndef shell_main_h
#define shell_main_h
void handle_signal(int signo);
void seperate_argv(char* tmp);
void testAndExecute();
int preTest(int flag);
void executeCommend();
void readEnv();
char environment[2][155];       //store the environment variables (PATH AND HOME)
char * stackStorage(Stack str_stk);

#endif
