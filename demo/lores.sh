#!/bin/sh
z80asm -b --cpu=z80-zxn -r0xc000 circle.asm
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    lrfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.slr/'`
    palfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pal/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lr.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lr.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_lr.ppm/'`
    echo $infile $ppmfile $lrfile
    convert -resize 128x96 -remap zxnext_palette.ppm $infile $ppmfile
    getpalette -v $ppmfile $palfile
    ppmtoslr -v -p$palfile $ppmfile $lrfile
    slrtoppm -v $lrfile $outfile
    cat >$txtfile <<EOF
circle.bin,0,0
!BANK0
!PCSP\$c000,\$f000
!XSLR${lrfile}
EOF
    nexcreator $txtfile $nexfile
done
