bin_PROGRAMS=gitid

gitid_src=./src/cli.c ./src/git.c ./src/git-clone-opts.c ./src/gitid.c ./src/gitid-id.c ./src/git-user.c ./src/util.c ./src/vector-gitid-id.c
argtable3_src=./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_utils.c 

gitid_SOURCES=$(gitid_src) $(argtable3_src)
gitid_CFLAGS=-Wall -Wextra -Wstrict-prototypes

gitid_inc=./include/cli.h ./include/git-clone-opts.h ./include/git.h ./include/gitid.h ./include/gitid-id.h ./include/git-user.h ./include/limits.h ./include/struct.h ./include/util.h ./include/vector-gitid-id.h
argtable3_inc=./lib/argtable3/argtable3.h
cstl_inc=./lib/c-stl/include/algorithm.h ./lib/c-stl/include/vector.h

pkginclude_HEADERS=$(gitid_inc) $(argtable3_inc) $(cstl_inc)
