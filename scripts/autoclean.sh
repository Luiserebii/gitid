#!/bin/bash

# Simple script to clean up all autotools generated/required files

rm -f autoscan.log configure.scan aclocal.m4 compile config.h.in configure COPYING depcomp INSTALL install-sh Makefile.in missing AUTHORS NEWS README ChangeLog
rm -rf autom4te.cache
rm -rf build
