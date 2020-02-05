CFLAGS = -g3 -Wall -Wextra

all:
	$(CC) $(CFLAGS) ./src/*.c ./lib/argtable3/*.c -lm -o gitid
