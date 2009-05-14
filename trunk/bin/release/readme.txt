mptoolkit 0.1
-----------

mptoolkit is a multi processing toolkit for windows batch files.

The toolkit consists of 3 executables that you should either,
have next to your batch file, or in your system path somewhere.

The executables use files with .pid extensions to track how many
processes are running and will do so directly next to the executable.

mpstart
-------
Checks to see how many instances of mprun are running by looking
for .pid files in the same directory as the executable. If it
is greater than or equal to number of cores * 2, then it will
wait until one of the instances of mprun finishes, effectively
pausing the execution flow of your batch file. It calls mprun
as a detached processto actually perform your command when it 
detects that it has space in the "thread pool".

mprun
-----
Runs your command. mprun writes out it's own process ID, then 
runs the command you tell it by using cmd.exe /C %*. The reason 
mpstart and mprun are separated is because to allow execution
flow to continue in the batch file, mpstart needs to exit.

mpwait
------
mpwait will pause execution of your batch files until all pid's
are deleted from the directory. You can use this for synchronization
purposes.


Example :

FOR /L %%G IN (1,1,20) DO mpstart ping localhost -n %%G -w 1000
mpwait

This example will start pings of increasing wait times of up to
number of cores * 2 and wait until all are completed before exiting
the batch file.

On a dual core processor, your task manager should look something
like what is shown in mptools.png.

5 cmd.exe's running - 1 for the batch process, 4 for execution

4 mprun's - actually performing the work

1 mpstart - currently in waiting for one of the previous mprun's
            to finish working.



 
