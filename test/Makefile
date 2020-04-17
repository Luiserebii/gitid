INCLUDE_FLAGS=-I../lib/C-STL/include
CFLAGS=-g3 -Wall -Wextra

.PHONY: test
test:
	$(CC) $(CFLAGS) $(INCLUDE_FLAGS) ./src/* ../src/git.c ../src/gitid.c ../src/git-user.c ../src/vector-gitid-id.c ../src/git-clone-opts.c ../src/gitid-id.c ../src/util.c ./lib/*.c ../lib/C-STL/src/*.c

.PHONY: out
out: 
	tail -n +1 tmp/*
