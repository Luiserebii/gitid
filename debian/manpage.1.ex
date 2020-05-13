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
For a complete description, see the Info files.
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
.PP
Additional flags:
.SS "-c, --current, --s, --shift:"
.TP
\fB\-\-global\fR
refer to global git config
.TP
\fB\-\-local\fR
refer to local git config (repository\-level)
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
.SH SEE ALSO
.BR bar (1),
.BR baz (1).
.br
The programs are documented fully by
.IR "The Rise and Fall of a Fooish Bar" ,
available via the Info system.
