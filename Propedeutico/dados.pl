use strict;

sub roll() {
	return 1 + int(rand(6));
}

my $times = <>;

my @hist;
for (my $sum = 2; $sum <= 12; $sum++) {
	$hist[$sum] = 0;
}

for (my $i = 0; $i < $times; $i++) {
	$hist[roll() + roll()]++;
}

for (my $sum = 2; $sum <= 12; $sum++) {
	my $expected = (6 - abs(7 - $sum)) / 36;
	my $res = $hist[$sum] / $times;
	print "$sum $expected $res\n";
}
