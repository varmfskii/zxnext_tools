#!/bin/sh
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    hcfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.hc/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hc.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hc.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hc.ppm/'`
    echo $infile $ppmfile $hcfile
    convert -resize 256x192 -remap ula_palette.ppm $infile $ppmfile
    ppmtohicol -v $ppmfile $hcfile
    hicoltoppm -v $hcfile $outfile
    echo "!SHC${hcfile}" >$txtfile
    nexcreator $txtfile $nexfile
done
