.\"                                      Hey, EMACS: -*- nroff -*-
.\" (C) Copyright 2020 Luiserebii <luis@serebii.io>,
.\"
.\" First parameter, NAME, should be all caps
.\" Second parameter, SECTION, should be 1-8, maybe w/ subsection
.\" other parameters are allowed: see man(7), man(1)
.TH GITID 1 "May 12 2020" "gitid 0.3.1" "User Commands"
.\" Please adjust this date whenever revising the manpage.
.\"
.\" Some roff macros, for reference:
.\" .nh        disable hyphenation
.\" .hy        enable hyphenation
.\" .ad l      left justify
.\" .ad b      justify to both left and right margins
.\" .nf        disable filling
.\" .fi        enable filling
.\" .br        insert line break
.\" .sp <n>    insert n+1 empty lines
.\" for manpage-specific macros, see man(7)
.SH NAME
gitid \- A simple, minimal git identity management tool
.SH SYNOPSIS
.B gitid
[\fI\,-valch\/\fR] [\fI\,-s <id-name>\/\fR] [\fI\,-n <id-name>\/\fR] [\fI\,-u <id-name>\/\fR] [\fI\,-d <id-name>\/\fR] [\fI\,--global\/\fR] [\fI\,--local\/\fR] [\fI\,--user=<username>\/\fR] [\fI\,--email=<email>\/\fR] [\fI\,--sigkey=<sigkey>\/\fR]
.SH DESCRIPTION
.PP
\fBgitid\fP is a command line tool allowing for easy shifting between git identities
(username, email, and signing key (e.g GPG)). It aims to make working with
different git configurations easy and shifting between identities painless.
Above all, the tool aims to reduce any possibility for user error.
.PP
It is intended for people who need to manage multiple username/email/signing
key configurations, and want to minimize the difficulties and risk of managing
multiple repositories with multiple configurations.
.SH OPTIONS
These programs follow the usual GNU command line syntax, with long
options starting with two dashes (`-').
A summary of options is included below.
.TP
\fB\-v\fR, \fB\-\-version\fR
output the version number
.TP
\fB\-a\fR, \fB\-\-about\fR
about this tool
.TP
\fB\-l\fR, \fB\-\-list\fR
list all registered identities
.TP
\fB\-c\fR, \fB\-\-current\fR
current global git identity
.TP
\fB\-s\fR, \fB\-\-shift=\fR<id\-name>
shift git identity to registered identity (global by default)
.TP
\fB\-n\fR, \fB\-\-new=\fR<id\-name>
add new identity
.TP
\fB\-u\fR, \fB\-\-update=\fR<id\-name>
update registered identity
.TP
\fB\-d\fR, \fB\-\-delete=\fR<id\-name>
delete registered identity
.TP
\fB\-h\fR, \fB\-\-help\fR
display this help and exit
.SS Additional flags:
.BR
.SS "-c, --current, --s, --shift:"
.TP
\fB\-\-global\fR
refers to global git config
.TP
\fB\-\-local\fR
refers to local git config (repository\-level)
.SS "-n, --new, -u, --update:"
.TP
\fB\-\-user=\fR<username>
specify username
.TP
\fB\-\-email=\fR<email>
specify email
.TP
\fB\-\-sigkey=\fR<sigkey>
specify signing key (key\-id format: LONG)
.TP
.B \-h, \-\-help
Show summary of options.
.TP
.B \-v, \-\-version
Show version of program.
.SH GITID-CLONE
.BR
.SS SYNOPSIS
.B gitid clone
\/\fR[\fI\,-vqnlh\/\fR] <repo> \/\fR[\fI\,-s <id-name>\/\fR] [\fI\,--progress\/\fR] [\fI\,--bare\/\fR] [\fI\,--mirror\/\fR] [\fI\,--no-hardlinks\/\fR] [\fI\,--shared\/\fR] [\fI\,--recursive\/\fR] [\fI\,--recurse-submodules\/\fR] [\fI\,--template=<template-directory>\/\fR] [\fI\,--reference=<repo>\/\fR] [\fI\,--dissociate\/\fR] [\fI\,-o <name>\/\fR] [\fI\,-b <branch>\/\fR] [\fI\,-u <path>\/\fR] [\fI\,--depth=<depth>\/\fR] [\fI\,--single-branch\/\fR] [\fI\,--seperate-git-dir=<gitdir>\/\fR] [\fI\,-c <key=value>\/\fR]
.SS OPTIONS
.TP
\fB\-s\fR, \fB\-\-shift=\fR<id\-name>
set git identity of repo to registered identity post\-clone
.TP
\fB\-v\fR, \fB\-\-verbose\fR
be more verbose
.TP
\fB\-q\fR, \fB\-\-quiet\fR
be more quiet
.TP
\fB\-\-progress\fR
force progress reporting
.TP
\fB\-n\fR, \fB\-\-no\-checkout\fR
don't create a checkout
.TP
\fB\-\-bare\fR
create a bare repository
.TP
\fB\-\-mirror\fR
create a mirror repository (implies bare)
.TP
\fB\-l\fR, \fB\-\-local\fR
to clone from a local repository
.TP
\fB\-\-no\-hardlinks\fR
don't use local hardlinks, always copy
.TP
\fB\-\-shared\fR
setup as shared repository
.TP
\fB\-\-recursive\fR
initialize submodules in the clone
.TP
\fB\-\-recurse\-submodules\fR
initialize submodules in the clone
.TP
\fB\-\-template=\fR<template\-directory>
directory from which templates will be used
.TP
\fB\-\-reference=\fR<repo>
reference repository
.TP
\fB\-\-dissociate\fR
use \fB\-\-reference\fR only while cloning
.TP
\fB\-o\fR, \fB\-\-origin=\fR<name>
use <name> instead of 'origin' to track upstream
.TP
\fB\-b\fR, \fB\-\-branch=\fR<branch>
checkout <branch> instead of the remote's HEAD
.TP
\fB\-u\fR, \fB\-\-upload\-pack=\fR<path>
path to git\-upload\-pack on the remote
.TP
\fB\-\-depth=\fR<depth>
create a shallow clone of that depth
.TP
\fB\-\-single\-branch\fR
clone only one branch, HEAD or \fB\-\-branch\fR
.TP
\fB\-\-seperate\-git\-dir=\fR<gitdir>
separate git dir from working tree
.TP
\fB\-c\fR, \fB\-\-config=\fR<key=value>
set config inside the new repository
.TP
\fB\-h\fR, \fB\-\-help\fR
display this help and exit
.SH EXAMPLES
.TP
\fBAdding a new git identity:\fR
gitid -n strawberry \-\-user Strawberry \-\-email strawberry@fruit.io \-\-sigkey 5B3A4739
.TP
\fBListing all registered identities:\fR
gitid -l
.TP
\fBSetting a new git identity globally:\fR
gitid -s strawberry
.TP
\fBDisplaying the current global git identity:\fR
gitid -c
\fBSetting a new git identity locally:\fR
gitid -s strawberry \-\-local
.TP
\fBDisplaying the current local git identity:\fR
gitid -c \-\-local
.TP
\fBCloning a repository and setting the local identity within:\fR
gitid clone -s strawberry https://github.com/Luiserebii/gitid
.SH AUTHOR
Written by Luiserebii.
.SH COPYRIGHT
Copyright (C) 2020 Luiserebii
.PP
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
.PP
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
.SH NOTES
1. GitHub repository:
.br
   https://github.com/Luiserebii/gitid
