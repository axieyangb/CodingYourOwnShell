Our MINIX os version is MINIX 3.3.0.

We use Mac OS X system and run MINIX by VMware Fusion.

The executable of our MINIX is located in "Minix.vmwarevm" folder. 
To boot up our MINIX, you can open VMware player and choose "Open a Virtual Machine". Then you can direct to "Minix.vmwarevm" folder and open the VM file named "Minix" to run.
 firstly, locate in your current directory 
  you need to compile the main file using the gcc 
  using the commend 
  "gcc main.c myStack.c -o main "
  then your will enter our shell.
  you can use all the commends 
  like "ls -a"
      "pwd"
     also you can execute the documents in your current directory
      using the "/.123"
      and the barkets are also available
      for example, you could use the commends combination
      like 
      "wc -l, (ls)"
  you could use the variables like "x=2"
  to set the global variables.
  these variables are stored in the extern file.
  you could use the $x to get the value.
  so even when you exit the shell, you still can acess the varables
  we have some necessary test cases , some of them have been pass successfully, some are not considering some static global variables.
 In order to realize the priority of commends, 
 we spend a lot of time together to discuss the structure of the data storage.
 Finally,we make a decision to use the stack, and establish our own stack in c.
  If you have any question, please feel free to contact us.
