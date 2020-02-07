CFLAGS = -g3 -Wall -Wextra -Wstrict-prototypes

all:
	$(CC) $(CFLAGS) ./src/*.c ./lib/argtable3/*.c -lm -o gitid
