# gitid
![GitHub](https://img.shields.io/github/license/Luiserebii/gitid?color=222222)
[![Codacy Badge](https://api.codacy.com/project/badge/Grade/6da3671805334d0dbe46732f18bef7d3)](https://app.codacy.com/manual/Luiserebii/gitid?utm_source=github.com&utm_medium=referral&utm_content=Luiserebii/gitid&utm_campaign=Badge_Grade_Dashboard)
[![CircleCI](https://circleci.com/gh/Luiserebii/gitid.svg?style=svg)](https://circleci.com/gh/Luiserebii/gitid)

A command line tool allowing for easy shifting between git identities (username, email, and GPG). A lighter, more portable rewrite of [git-identity](https://github.com/Luiserebii/git-identity) in C.

Still in development!

## Testing

Run `make && ./a.out` in the [test/](./test) directory to run all tests. For simplicity, some tests are not automated, and ask for runner confirmation to ensure that the output is valid (e.g. gitid_id_min_write).

To easily confirm this output, an additional script has been added to the test makefile. Simply run `make out` to execute.

## License
This code has been licensed under the GNU General Public License v3.0.
