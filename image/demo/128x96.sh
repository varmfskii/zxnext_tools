#!/bin/bash
IN=$1
OUT=$2
GEO=`identify -verbose $IN|grep Geometry|sed -e's/.*: \([0-9]*x[0-9]*\)+.*/\1/'`
X=`echo $GEO|sed -e 's/x.*//'`
Y=`echo $GEO|sed -e 's/.*x//'`
let X2=$Y*4/3
let Y2=$X*3/4
if [ $X2 -gt $X ]
then
    let LT=($X2-$X)/2
    let RT=$X2-$X-$LT
    S1="-gravity east -splice ${LT}x0"
    S2="-gravity west -splice ${RT}x0"
else
    echo "$IN($X*$Y)->$OUT($X*$Y2)"
    let TP=($Y2-$Y)/2
    let BT=$Y2-$Y-$TP
    S1="-gravity north -splice 0x${BT}"
    S2="-gravity south -splice 0x${TP}"
fi
convert $IN $S1 $S2 -resize 128x96! $OUT

