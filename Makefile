CFLAGS = -g3 -Wall -Wextra -Wstrict-prototypes

gitid:
	$(CC) $(CFLAGS) ./src/*.c ./lib/argtable3/*.c -lm -o gitid

#### Development-related scripts:

.PHONY: lint
lint:
	./scripts/lint.sh

#### Autotools scripts:

.PHONY: autogen
autogen:
	./scripts/autogen.sh

.PHONY: autoclean
autoclean:
	./scripts/autoclean.sh
