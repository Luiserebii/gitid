INCLUDE_FLAGS=-I../lib/C-STL/include
CFLAGS=-g3 -Wall -Wextra -Wvla
MACROS=-DCSTL_CUSTOM_MEMORY

.PHONY: test
test:
	$(CC) $(CFLAGS) $(MACROS) $(INCLUDE_FLAGS) ./src/* ../src/git.c ../src/gitid.c ../src/git-user.c ../src/vector-gitid-id.c ../src/git-clone-opts.c ../src/gitid-id.c ../src/util.c ../src/memory.c ./lib/*.c ../lib/C-STL/src/*.c
	mkdir -p tmp

.PHONY: out
out: 
	tail -n +1 tmp/*
