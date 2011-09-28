#! /bin/bash

timez=$1
name=$2
input=motif.in
instancedir=instances/*.fasta

cmd=$name
outputdir=$name-output
inputdir=$name-input
mkdir $outputdir
mkdir $inputdir

for file in $instancedir
do
	extpos=`expr index "$file" \.`
	dirpos=`expr index "$file" /`
	inst=${file:dirpos:extpos-dirpos-1}
	from=8
	to=12
	if [ $inst -eq 3 ]
	then
		from=6
		to=10
	fi
	for L in `seq $from $to`;
	do
		echo "Running '$cmd $file $L' $timez times..."
		for i in `seq 1 $timez`;
		do
			in=$inputdir/$inst-$L-$i.in
			out=$outputdir/$inst-$L-$i.out
			out2=$outputdir/$inst-$L-$i.time
			echo "    Running #$i..."
			cat <(cat $input) <(echo "$RANDOM/32768.0" | bc -l) > "$in"
			(time ./"$cmd" $file $L --silent) < "$in" 1> "$out" 2>"$out2"
		done
	done
done

