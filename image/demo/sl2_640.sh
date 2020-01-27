#!/bin/bash
tmp=$(mktemp -p .)
echo $#
if [ $# -eq 2 ]
then
    mode=next
    infile=$1
    outfile=$2
elif [ $# -eq 3 ]
then
     mode=$1
     infile=$2
     outfile=$3
else
    echo "usage: $0 [<mode>] <infile> <outfile>"
    exit 1
fi
if [ ! -f $infile ]
then
    echo "$infile does not exist"
    exit 1
fi
case $mode in
    gray)
	dither=palettes/gray3.ppm
	pal=palettes/gray3_4.pal
    ;;

    grayc1)
	dither=palettes/gray4.ppm
	pal=palettes/gray4c1_4.pal
    ;;

    grayc2)
	dither=palettes/gray4.ppm
	pal=palettes/gray4c2_4.pal
    ;;

    image)
	convert -resize 640x256! $infile ${tmp}.ppm
	getpalette -b 4 ${tmp}.ppm ${tmp}.pal
	paltoppm -b 4 ${tmp}.pal ${tmp}_pal.ppm
	dither=${tmp}_pal.ppm
	pal=${tmp}.pal
    ;;

    next)
	dither=palettes/next.ppm
	pal=palettes/next_4.pal
    ;;
    
    *)
	dither=$mode
	pal=$mode
    ;;
esac
if [ ! -f $dither ]
then
   echo "$dither does not exist"
   exit 1
fi
if [ ! -f $pal ]
then
   echo "$pal does not exist"
   exit 1
fi
./640x256.sh $infile ${tmp}.ppm
case $mode in
    gray*)
	convert ${tmp}.ppm -remap ${dither} ${tmp}_dither.pgm
	ppmtosl2 -6 -p ${pal} ${tmp}_dither.pgm $outfile
	;;

    *)
	convert ${tmp}.ppm -remap ${dither} ${tmp}_dither.ppm
	ppmtosl2 -6 -p ${pal} ${tmp}_dither.ppm $outfile
	;;
esac
rm -f ${tmp}*
