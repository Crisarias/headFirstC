To create libraries from several .o files use the ar command:

ar -rcs lib<name>.a <file1>.o <file2>.o

-rcs, r mean the a file will be updated if exists, c no feedback, create an index at the start of the a file.