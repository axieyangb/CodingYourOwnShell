# CodingYourOwnShell
this project is using the system call to customize the shell.


The requirements

The shell shall be invoked from the Ash shell provided with Minix.

The shell shall first execute a PROFILE file which defines the PATH variable that will allow you to access programs provided in /bin and /usr/bin. Once the PROFILE file is executed, you will be in a HOME directory specified by you in the PROFILE file.The PATH and HOME variables do not replace those of the Ash shell from which your shell is instantiated.

The prompt shall display the current directory name. 

In a command line of the shell it will be able to exercise any executable programs including the utilities provided in /bin and /usr/bin.  

The shell shall support the execution of a list of commands in the following format: curdir ( command1, command2, (command3))  The precedence of the commands are from left to right but parenthesized commands supersedes that order. In the example, command3 has highest precedence, followed by command1 then  command2. The output of the higher precedence command becomes the input to the command next in precedence.
