# gitid
![GitHub](https://img.shields.io/github/license/Luiserebii/gitid?color=222222)
[![CircleCI](https://circleci.com/gh/Luiserebii/gitid.svg?style=svg)](https://circleci.com/gh/Luiserebii/gitid)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/cdba0bbafbf2465eac0e3f1e8302342a)](https://www.codacy.com/manual/Luiserebii/gitid?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Luiserebii/gitid&amp;utm_campaign=Badge_Grade)

A command line tool allowing for easy shifting between git identities (username, email, and signing key (e.g GPG)). A lighter, more portable rewrite of [git-identity](https://github.com/Luiserebii/git-identity) in C.

## Usage
```
Usage: gitid [-valch] [-s <id-name>] [-n <id-name>] [-u <id-name>] [-d <id-name>] [--global] [--local] [--user=<username>] [--email=<email>] [--sigkey=<sigkey>]
A command line tool allowing for easy shifting between git identities (username, email, and signing key).

  -v, --version             output the version number
  -a, --about               about this tool
  -l, --list                list all registered identities
  -c, --current             current global git identity
  -s, --shift=<id-name>     shift git identity to registered identity (global by default)
  -n, --new=<id-name>       add new identity
  -u, --update=<id-name>    update registered identity
  -d, --delete=<id-name>    delete registered identity
  -h, --help                display this help and exit

Additional flags:

-c, --current, --s, --shift:
  --global                  global (option for -s and -c)
  --local                   local (option for -s and -c)

-n, --new, -u, --update:
  --user=<username>         specify username
  --email=<email>           specify email
  --sigkey=<sigket>         specify signing key (key-id format: LONG)
```

## Building

Building is very simple, simply run `make`, and it'll produce an executable `gitid`.

## Testing

Run `make && ./a.out` in the [test/](./test) directory to run all tests. For simplicity, some tests are not automated, and ask for runner confirmation to ensure that the output is valid (e.g. `gitid_id_min_write`).

To easily confirm this output, an additional script has been added to the test makefile. Simply run `make out` to execute.

## License
This code has been licensed under the GNU General Public License v3.0.
