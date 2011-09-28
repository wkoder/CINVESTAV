#! /bin/bash

name=$1
timez=$2

cmd=$name
input=config.in
outputdir=$name-output
inputdir=$name-input
mkdir $outputdir
mkdir $inputdir

for N in `seq 10 20 30`;
do
	for F in `seq 1 20`;
	do
		echo "Running '$cmd $F $N' $timez times..."
		for i in `seq 1 $timez`;
		do
			in=$inputdir/$F-$N-$i.in
			out=$outputdir/$F-$N-$i.out
			echo "    Running #$i..."
			cat <(echo "$N*2" | bc -l) <(echo "$N*5000" | bc -l) <(cat $input) <(echo "$RANDOM/32768.0" | bc -l) > "$in"
			./"$cmd" $F $N --silent < "$in" > "$out"
		done
	done
done

