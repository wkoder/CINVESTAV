use strict;

my $MAX = 500;
for (my $a = 0; $a <= $MAX; $a++) {
	for (my $b = $a; $b <= $MAX; $b++) {
		my $c = int(sqrt($a*$a + $b*$b) + 0.5);
		if ($c*$c == $a*$a + $b*$b) {
			print "$a $b $c\n";
		}
	}
}
