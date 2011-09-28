#! /bin/bash

timez=$1
name=$2
input=parsimony.in
if [ $# -eq 2 ]
then
	instancedir=instances/*.txt
else
	instancedir=$3
fi

cmd=parsimony
dir=$name
outputdir=$dir/output
inputdir=$dir/input
mkdir $dir
mkdir $outputdir
mkdir $inputdir

for file in $instancedir
do
	extpos=`expr index "$file" \.`
	dirpos=`expr index "$file" /`
	inst=${file:dirpos:extpos-dirpos-1}

	echo "Running '$cmd $name $inst' $timez times..."
	for i in `seq 1 $timez`;
	do
		in=$inputdir/$cmd-$inst-$i.in
		out=$outputdir/$cmd-$inst-$i.out
		echo "    Running #$i..."
		cat <(cat $input) <(echo "$RANDOM/32768.0" | bc -l) > "$in"
		./"$cmd" $name $inst $i < "$in" > "$out"
	done
done

