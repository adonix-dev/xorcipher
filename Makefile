SRC=./src
CC=gcc
CFLAGS=-Wall -Wextra -g -Ofast
OBJ=$(SRC)/main.o $(SRC)/xor_function.o $(SRC)/xorProcess.o $(SRC)/xorProcess_lib.o $(SRC)/xorCheck.o

util:	$(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(SRC)/xorcipher

$(SRC)/main.o: $(SRC)/main.c
$(SRC)/xor_function.o: $(SRC)/xor_function.c
$(SRC)/xorProcess.o: $(SRC)/xorProcess.c
$(SRC)/xorProcess_lib.o: $(SRC)/xorProcess_lib.c
$(SRC)/xorCheck.o: $(SRC)/xorCheck.c

clean:
	rm -rf *.o

maxclean: clean
	  rm -rf $(EXEC)