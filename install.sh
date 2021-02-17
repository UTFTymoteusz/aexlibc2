#!/bin/sh

GCCPATH=$(which x86_64-aex2-elf-gcc)

if [ -z "$GCCPATH" ] 
then
    echo "failed to install the libc"
    exit 0
fi

VERSION=$(x86_64-aex2-elf-gcc --version | grep -o '[0-9]\+\.[0-9]\+\.[0-9]')
DIR=${GCCPATH%/*}
DST=$DIR/../lib/gcc/x86_64-aex2-elf/$VERSION/

cp /tmp/aex2/libc/obj/crti.o /tmp/aex2/libc/obj/crt0.o /tmp/aex2/libc/obj/crtn.o /tmp/aex2/libc/obj/libc.a $DST
cp -r include/ $DST