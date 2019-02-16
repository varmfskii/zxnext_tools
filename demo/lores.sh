#!/bin/sh
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    lofile=`echo $infile|sed -e 's/\([^.]*\).*/\1.lo/'`
    palfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pal/'`
    l2file=`echo $infile|sed -e 's/\([^.]*\).*/\1.lo/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lo.ppm/'`
    echo $infile $ppmfile $lofile
    convert -resize 128x96 -remap zxnext_palette.ppm $infile $ppmfile
    getpalette -v $ppmfile $palfile
    ppmtolores -v -p$palfile $ppmfile $lofile
    lorestoppm -v $l2file $outfile
done
