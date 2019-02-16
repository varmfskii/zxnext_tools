#!/bin/sh
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    l2file=`echo $infile|sed -e 's/\([^.]*\).*/\1.l2/'`
    palfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pal/'`
    l2file=`echo $infile|sed -e 's/\([^.]*\).*/\1.l2/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.ppm/'`
    echo $infile $ppmfile $l2file
    convert -resize 256x192 -remap zxnext_palette.ppm $infile $ppmfile
    getpalette $ppmfile $palfile
    ppmtolayer2 -p$palfile -i$ppmfile -o$l2file
    layer2toppm $l2file $outfile
done
