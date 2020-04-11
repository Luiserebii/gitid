bin_PROGRAMS=gitid

gitid_src=./src/cli.c ./src/git.c ./src/git-clone-opts.c ./src/gitid.c ./src/gitid-id.c ./src/git-user.c ./src/util.c ./src/vector-gitid-id.c
argtable3_src=./lib/argtable3/arg_cmd.c ./lib/argtable3/arg_dstr.c ./lib/argtable3/arg_hashtable.c ./lib/argtable3/arg_rem.c ./lib/argtable3/argtable3.c ./lib/argtable3/arg_date.c ./lib/argtable3/arg_end.c ./lib/argtable3/arg_int.c ./lib/argtable3/arg_rex.c ./lib/argtable3/arg_utils.c ./lib/argtable3/arg_dbl.c ./lib/argtable3/arg_file.c ./lib/argtable3/arg_lit.c ./lib/argtable3/arg_str.c ./lib/argtable3/getopt_long.c

gitid_SOURCES=$(gitid_src) $(argtable3_src)
gitid_CFLAGS=-Wall -Wextra -Wstrict-prototypes

gitid_inc=./include/cli.h ./include/git-clone-opts.h ./include/git.h ./include/gitid.h ./include/gitid-id.h ./include/git-user.h ./include/limits.h ./include/struct.h ./include/util.h ./include/vector-gitid-id.h
argtable3_inc=./lib/argtable3/argtable3.h ./lib/argtable3/argtable3_private.h ./lib/argtable3/getopt.h
cstl_inc=./lib/c-stl/include/algorithm.h ./lib/c-stl/include/vector.h

pkginclude_HEADERS=$(gitid_inc) $(argtable3_inc) $(cstl_inc)
