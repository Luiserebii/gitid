# gitid
![gitid-logo](https://serebii.io/projects/img/gitid-black-padded-rounded.png)

![GitHub](https://img.shields.io/github/license/Luiserebii/gitid?color=222222)
[![CircleCI](https://circleci.com/gh/Luiserebii/gitid.svg?style=svg)](https://circleci.com/gh/Luiserebii/gitid)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/cdba0bbafbf2465eac0e3f1e8302342a)](https://www.codacy.com/manual/Luiserebii/gitid?utm_source=github.com&amp;utm_medium=referral&amp;utm_content=Luiserebii/gitid&amp;utm_campaign=Badge_Grade)

gitid is a simple, minimal command line tool allowing for easy management of git identities (username, email, and signing key (e.g GPG)). It aims to make working with different git configurations easy and shifting between identities painless. Above all, the tool aims to reduce any possibility of user error.

A short, readable guide on this tool may be found at: [https://luiserebii.io/2020/05/introduction-to-gitid/](https://luiserebii.io/2020/05/introduction-to-gitid/)

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
  --global                  refer to global git config
  --local                   refer to local git config (repository-level)

-n, --new, -u, --update:
  --user=<username>         specify username
  --email=<email>           specify email
  --sigkey=<sigkey>         specify signing key (key-id format: LONG)
```

## Building

### Make

Building with make is very simple, simply run `make`, and it'll produce an executable `gitid`. 

### Autotools

Alternatively, one can build with Autotools:
```
make autogen
mkdir build && cd build
../configure
make
```

The commands above are also avaliable as `make autobuild` for convenience. Similarly, `make distcheck` will test the build for distribution.

## Installation

### Unix-like OS (e.g. Linux, BSD, Mac OS)
To install, simply build with Autotools and install with the following commands:
```
make autogen
mkdir build && cd build
../configure
make
make install
```

Note that `make install` may need to be executed with higher permissions.

The tool should now be installed under the name `gitid`.

## Testing

Run `make && ./a.out` in the [test/](./test) directory to run all tests. For simplicity, some tests are not automated, and ask for runner confirmation to ensure that the output is valid (e.g. `gitid_id_min_write`).

To easily confirm this output, an additional script has been added to the test makefile. Simply run `make out` to execute.

## License
This code has been licensed under the GNU General Public License v3.0.
