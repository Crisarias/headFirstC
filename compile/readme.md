# Compile

* In order to compile with share libraries the share library need the header file and its c implementation.

Then just do:

gcc message_hider.c encrypt.c -o message_hider

* In order to do not compile all the files every time create object code files for each files and recompile them as needed.

To create object code files for all the c files in the folder do:

gcc -c *.c

This will compile the code but no link it. To linked do:

gcc *.o -o message_hider

# Automate the process make file

