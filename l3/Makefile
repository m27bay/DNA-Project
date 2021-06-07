DEBUG=yes
# DEBUG=no
CC=gcc
EXEC=dna

#################################
###### SETUP COMPILE FLAGS ######
#################################

ifeq ($(DEBUG), yes)
	CFLAGS = -Wall -Wextra -g3 -O3
else
	CFLAGS = -O3
endif

#################################
###### COMPILATION PROJECT ######
#################################

all: build $(EXEC)
	./bin/dna

build:
	./build.sh

$(EXEC): main.o struct.o lire.o manipulation.o
	$(CC) $(CFLAGS) target/*.o -o bin/$@

#################################
########## COMPILE FILE #########
#################################

main.o: main.c
	$(CC) -c $(CFLAGS) $< -o target/$@

struct.o: src/include/struct.c src/include/struct.h
	$(CC) -c $(CFLAGS) $< -o target/$@

lire.o: src/lib/lire.c src/lib/lire.h
	$(CC) -c $(CFLAGS) $< -o target/$@

manipulation.o: src/lib/manipulation.c src/lib/manipulation.h
	$(CC) -c $(CFLAGS) $< -o target/$@

#################################
######## VALGRIND AND DGB #######
#################################

vg:
	valgrind ./bin/$(EXEC)

vg2:
	valgrind --leak-check=full --show-leak-kinds=all ./bin/$(EXEC) $(FILE)

vg3:
	valgrind -v ./bin/$(EXEC)

gdb:
	gdb ./bin/$(EXEC)

#################################
############  CLEAN  ############
#################################

clean:
	rm target/*.o
	rmdir target/

mrproper: clean
	rm bin/$(EXEC)
	rmdir bin/