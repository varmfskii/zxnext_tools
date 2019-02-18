#!/bin/sh
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    crfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.cr/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_cr.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_cr.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_cr.ppm/'`
    echo $infile $ppmfile $crfile
    convert -resize 256x192 -remap ula_palette.ppm $infile $ppmfile
    ppmtoula -v $ppmfile $crfile
    ulatoppm -v $crfile $outfile
    echo "!SCR${crfile}" >$txtfile
    nexcreator $txtfile $nexfile
done
