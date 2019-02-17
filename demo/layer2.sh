#!/bin/sh
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    l2file=`echo $infile|sed -e 's/\([^.]*\).*/\1.l2/'`
    palfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pal/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.ppm/'`
    echo $infile $ppmfile $l2file
    convert -resize 256x192 -remap zxnext_palette.ppm $infile $ppmfile
    getpalette -v $ppmfile $palfile
    ppmtolayer2 -v -p$palfile $ppmfile $l2file
    layer2toppm -v $l2file $outfile
    echo "!SL2${l2file}" >$txtfile
    nexcreator $txtfile $nexfile
done
