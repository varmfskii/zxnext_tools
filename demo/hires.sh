#!/bin/sh
for infile in "$@"
do
    pbmfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.pbm/'`
    hrfile=`echo $infile|sed -e 's/\([^.]*\).*/\1.hr/'`
    txtfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hr.txt/'`
    nexfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hr.nex/'`
    outfile=`echo $infile|sed -e 's/\([^.]*\).*/\1_hr.pbm/'`
    echo $infile $pbmfile $hrfile
    convert -resize 512x384 $infile $pbmfile
    pbmtohires -v2 $pbmfile $hrfile
    hirestopbm -v2 $hrfile $outfile
    echo "!SHR${hrfile}" >$txtfile
    nexcreator $txtfile $nexfile
done
