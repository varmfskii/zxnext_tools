#!/bin/sh
z80asm -b --cpu=z80-zxn -r0xc000 circle.asm
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    crfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.scr/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_cr.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_cr.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_cr.ppm/'`
    echo $infile $ppmfile $crfile
    convert -resize 256x192 -remap ula_palette.ppm $infile $ppmfile
    ppmtoscr -v $ppmfile $crfile
    scrtoppm -v $crfile $outfile
    cat >$txtfile <<EOF
circle.bin,0,0
!BANK0
!PCSP\$c000,\$f000
!SCR${crfile}
EOF
    nexcreator $txtfile $nexfile
done
