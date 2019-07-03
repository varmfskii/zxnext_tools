#!/bin/bash

out=$1
shift
echo > $out

for file in $@
do
    gcc -MM $file >> $out
done
