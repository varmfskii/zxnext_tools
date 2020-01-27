#!/bin/bash
tmp=$(mktemp -p .)
echo $#
if [ $# -eq 2 ]
then
    infile=$1
    outfile=$2
else
    echo "usage: $0 <infile> <outfile>"
    exit 1
fi
if [ ! -f $infile ]
then
    echo "$infile does not exist"
    exit 1
fi
256x192.sh ${infile} ${tmp}.ppm
convert -remap palettes/ula.ppm ${tmp}.ppm ${tmp}_dither.ppm
ppmtoshc ${tmp}_dither.ppm ${outfile}
rm -f ${tmp}*
