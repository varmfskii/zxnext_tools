#!/bin/sh
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    lrfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.lr/'`
    palfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pal/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lr.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lr.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lr.ppm/'`
    echo $infile $ppmfile $lrfile
    convert -resize 128x96 -remap zxnext_palette.ppm $infile $ppmfile
    getpalette -v $ppmfile $palfile
    ppmtolores -v -p$palfile $ppmfile $lrfile
    lorestoppm -v $lrfile $outfile
    echo "!SLR${lrfile}" >$txtfile
    nexcreator $txtfile $nexfile
done
