#!/bin/sh
z80asm -b --cpu=z80-zxn -r0xc000 circle.asm
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    l2file=`echo $infile|sed -e 's/\([^.]*\).*/\1.sl2/'`
    palfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pal/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_l2.ppm/'`
    echo $infile $ppmfile $l2file
    convert -resize 256x192 -remap zxnext_palette.ppm $infile $ppmfile
    getpalette -v $ppmfile $palfile
    ppmtosl2 -v -p$palfile $ppmfile $l2file
    sl2toppm -v $l2file $outfile
    cat >$txtfile <<EOF
circle.bin,0,0
!BANK0
!PCSP\$c000,\$f000
!XSL2${l2file},0,1,0,1,1
EOF
    nexcreator $txtfile $nexfile
done
