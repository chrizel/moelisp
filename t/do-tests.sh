#!/bin/sh

for t in ./t/????-*.lisp; do
    echo `basename $t | cut -d'.' -f1` "\c"
    ./moe ./t/testlib.lisp $t
    echo
done
