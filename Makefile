INCLUDE_FLAGS=-I./lib/C-STL/include
CFLAGS = -g3 -Wall -Wextra -Wstrict-prototypes $(INCLUDE_FLAGS)

.PHONY: gitid
gitid:
	$(CC) $(CFLAGS) ./src/*.c ./lib/argtable3/*.c ./lib/C-STL/src/*.c -lm -o gitid

#### Development-related scripts:

.PHONY: lint
lint:
	./scripts/lint.sh

.PHONY: test
test:
	cd test && make && ./a.out

#### Autotools scripts:

.PHONY: autogen
autogen:
	./scripts/autogen.sh

.PHONY: autobuild
autobuild:
	./scripts/autogen.sh
	mkdir -p build && cd build && \
	../configure && \
	make

.PHONY: autodistcheck
autodistcheck:
	./scripts/autogen.sh
	mkdir -p build && cd build && \
	../configure && \
	make && \
	make distcheck

.PHONY: autoclean
autoclean:
	./scripts/autoclean.sh
