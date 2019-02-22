#!/bin/sh
z80asm +zx --cpu=z80-zxn -r0xc000 circle.asm
for infile in "$@"
do
    pbmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pbm/'`
    hrfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.shr/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hr.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hr.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hr.pbm/'`
    echo $infile $pbmfile $hrfile
    convert -resize 512x192\! $infile $pbmfile
    pbmtoshr -v $pbmfile $hrfile
    shrtopbm -v2 $hrfile $outfile
    cat >$txtfile <<EOF
circle.bin,0,0
!BANK0
!PCSP\$c000,\$f000
!SHR${hrfile}
EOF
    nexcreator $txtfile $nexfile
done
