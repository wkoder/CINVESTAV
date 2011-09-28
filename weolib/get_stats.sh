#! /bin/bash

name=real-
cmd=$name$2
input=$name$2.in
dir=$name$2-stats
outputdir=$dir/output
inputdir=$dir/input
mkdir $dir
mkdir $outputdir
mkdir $inputdir
timez=$1
echo "Running $cmd $timez times..."
for i in `seq 1 $timez`;
do
	echo "    Running #$i"
	cat <(cat $input) <(echo "$RANDOM/32768.0" | bc -l) > "$inputdir/$cmd-$i.in"
	./$cmd < "$inputdir/$cmd-$i.in" > "$outputdir/$cmd-$i.out"
done

