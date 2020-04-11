CFLAGS = -g3 -Wall -Wextra -Wstrict-prototypes

gitid:
	$(CC) $(CFLAGS) ./src/*.c ./lib/argtable3/*.c -lm -o gitid

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
