encrypt.o: encrypt.c
	gcc -c -L../shared_libraries/ encrypt.c -o encrypt.o
checksum.o: checksum.c
	gcc -c -L../shared_libraries/ checksum.c -o checksum.o
libhfsecurity.a: ../shared_libraries/encrypt.o ../shared_libraries/checksum.o
	ar -rcs ../shared_libraries/libhfsecurity.a ../shared_libraries/encrypt.o ../shared_libraries/checksum.o
bank_vault: bank_vault.c libhfsecurity.a
	gcc bank_vault.c -I../shared_libraries/ -L../shared_libraries/ -L. -lhfsecurity -o bank_vault