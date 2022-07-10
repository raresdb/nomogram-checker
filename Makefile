#Butilca Rares

# compiler
CC=gcc

# define target
TARGET=nomogram

build: $(TARGET)

nomogram: nomogram.c
	$(CC) nomogram.c -o nomogram

clean:
	rm -f $(TARGET)
