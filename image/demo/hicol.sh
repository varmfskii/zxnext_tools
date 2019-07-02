#!/bin/sh
z80asm -b --cpu=z80-zxn -r0xc000 circle.asm
for infile in "$@"
do
    ppmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.ppm/'`
    hcfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.shc/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hc.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hc.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hc.ppm/'`
    echo $infile $ppmfile $hcfile
    convert -resize 256x192 -remap ula_palette.ppm $infile $ppmfile
    ppmtoshc -v $ppmfile $hcfile
    shctoppm -v $hcfile $outfile
    cat >$txtfile <<EOF
circle.bin,0,0
!BANK0
!PCSP\$c000,\$f000
!SHC${hcfile}
EOF
    nexcreator $txtfile $nexfile
done
