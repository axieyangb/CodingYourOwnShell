//
//  test_main.c
//  shell
//
//  Created by xieyangyang on 2/16/15.
//  Copyright (c) 2015 xieyangyang. All rights reserved.
//

#include "test_main.h"
#include "main.c"
#include "test_helper.h"
void main(void){
    char * args ="ls -a ";
    test_seperate_argv(args);
    ASSERT_TRUE(my_argv[0],"ls");
}
    test_seperate_argv(args)
{
    void
    testCreateOpenClose(void)
    {
        SM_FileHandle fh;
        
        testName = "test create and seperate the vals";
        
        TEST_CHECK(preTest(TESTPF));
        
        TEST_CHECK(openPageFile (TESTPF, &fh));
        ASSERT_TRUE(strcmp(fh.fileName, TESTPF) == 0, "filename correct");
        ASSERT_TRUE((fh.totalNumPages == 1), "expect 1 page in new file");
        ASSERT_TRUE((fh.curPagePos == 0), "freshly opened file's page position should be 0");
        
        TEST_CHECK(seperate_argv(tmp));
        TEST_CHECK(preTest(flag));
        
        // after destruction trying to open the file should cause an error
        ASSERT_TRUE((handle_signal(int signo)!= 0), "opening non-existing file should return an error.");
        
        TEST_DONE();
    }
}