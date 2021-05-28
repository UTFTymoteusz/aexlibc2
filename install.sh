#!/bin/sh

GCCPATH=$(which x86_64-pc-aex2-gcc)

if [ -z "$GCCPATH" ] 
then
    echo "failed to install the libc"
    exit 0
fi

VERSION=$(x86_64-pc-aex2-gcc --version | grep -o '[0-9]\+\.[0-9]\+\.[0-9]')
DIR=${GCCPATH%/*}
DST=$DIR/../lib/gcc/x86_64-pc-aex2/$VERSION/

cp -u /tmp/aex2/libc/obj/crti.o /tmp/aex2/libc/obj/crt0.o /tmp/aex2/libc/obj/crtn.o /tmp/aex2/libc/obj/libc.a $DST
cp -ur include/ $DST