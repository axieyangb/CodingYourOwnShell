//
//  shellerror.c
//  shell
//
//  Created by xieyangyang on 2/25/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//

#include "shellerror.h"

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *SH_message;

/* print a message to standard out describing the error */
void
printError (int error)
{
    if (SH_message != NULL)
        printf("EC (%i), \"%s\"\n", error, SH_message);
    else
        printf("EC (%i)\n", error);
}

char *
errorMessage (int error)
{
    char *message;
    
    if (SH_message != NULL)
    {
        message = (char *) malloc(strlen(SH_message) + 30);
        sprintf(message, "EC (%i), \"%s\"\n", error, SH_message);
    }
    else
    {
        message = (char *) malloc(30);
        sprintf(message, "EC (%i)\n", error);
    }
    
    return message;
}