#!/bin/sh

GCCPATH=$(which x86_64-aex2-elf-gcc)
VERSION=$(x86_64-aex2-elf-gcc --version | grep -o '[0-9]\+\.[0-9]\+\.[0-9]')
DIR=${GCCPATH%/*}
DST=$DIR/../lib/gcc/x86_64-aex2-elf/$VERSION/

cp crti.o crt0.o crtn.o libc.a $DST