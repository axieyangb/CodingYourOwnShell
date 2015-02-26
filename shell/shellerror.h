//
//  shellerror.h
//  shell
//
//  Created by xieyangyang on 2/25/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//

#ifndef __shell__shellerror__
#define __shell__shellerror__

#include <stdio.h>

#endif /* defined(__shell__shellerror__) */

#define SH_OK 1
#define SH_WRITE_FAILED 2
#define SH_READ_NON_EXISTING_FILE 3
#define SH_READ_FAILED 4

#define THROW(rc,message) \
do {			  \
SH_message=message;	  \
return rc;		  \
} while (0)		  \

// check the return code and exit if it is an error
#define CHECK(code)							\
do {									\
int SH_internal = (code);						\
if (SH_internal != SH_OK)						\
{									\
char *message = errorMessage(SH_internal);			\
printf("[%s-L%i-%s] ERROR: Operation returned error: %s\n",__FILE__, __LINE__, __TIME__, message); \
free(message);							\
exit(1);							\
}									\
} while(0);

