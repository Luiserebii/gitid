all:
	cc -g3 -Wall ./src/*.c ./lib/argtable3/*.c -lm -o gitid
